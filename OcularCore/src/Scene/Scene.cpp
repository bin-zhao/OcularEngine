/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "OcularEngine.hpp"

#include "Scene/Scene.hpp"
#include "Scene/ISceneTree.hpp"
#include "Scene/SceneObject.hpp"
#include "Scene/ARoutine.hpp"
#include "Scene/ARenderable.hpp"

// SceneTree implementations

#include "Scene/BVHSceneTree.hpp"
#include "Graphics/Shader/Uniform/UniformBuffer.hpp"
#include "Renderer/Renderer.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        Scene::Scene()
            : m_UniformBufferPerFrame(OcularGraphics->createUniformBuffer(Graphics::UniformBufferType::PerFrame)),
            m_RoutinesAreDirty(false),
            m_StaticTreeType(SceneTreeType::BoundingVolumeHierarchyCPU),
            m_DynamicTreeType(SceneTreeType::BoundingVolumeHierarchyCPU),
            m_StaticSceneTree(nullptr),
            m_DynamicSceneTree(nullptr),
            m_Renderer(nullptr)
        {

        }

        Scene::~Scene()
        {
            delete m_Renderer;
            m_Renderer = nullptr;

            //------------------------------------------------------------
            // Tell the routines the scene is ending

            for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
            {
                ARoutine* routine = (*iter);

                if(routine)
                {
                    routine->onSceneEnd();
                }
            }

            m_Routines.clear();

            //------------------------------------------------------------
            // Destroy the SceneTrees

            if(m_StaticSceneTree)
            {
                delete m_StaticSceneTree;
                m_StaticSceneTree = nullptr;
            }

            if(m_DynamicSceneTree)
            {
                delete m_DynamicSceneTree;
                m_DynamicSceneTree = nullptr;
            }

            //------------------------------------------------------------
            // Destroy the Uniform Buffers

            if(m_UniformBufferPerFrame)
            {
                delete m_UniformBufferPerFrame;
                m_UniformBufferPerFrame = nullptr;
            }
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void Scene::initialize()
        {
            switch(m_StaticTreeType)
            {
            case SceneTreeType::BoundingVolumeHierarchyCPU:
                m_StaticSceneTree = new BVHSceneTree();
                m_DynamicSceneTree = new BVHSceneTree();
                break;

            default:
                m_StaticSceneTree = nullptr;
                OcularLogger->error("Unsupported SceneTree Type specified for new Static SceneTree", OCULAR_INTERNAL_LOG("Scene", "Scene"));
                break;
            }

            switch(m_DynamicTreeType)
            {
            case SceneTreeType::BoundingVolumeHierarchyCPU:
                m_DynamicSceneTree = new BVHSceneTree();
                break;

            default:
                m_DynamicSceneTree = nullptr;
                OcularLogger->error("Unsupported SceneTree Type specified for new Dynamic SceneTree", OCULAR_INTERNAL_LOG("Scene", "Scene"));
                break;
            }
        }

        void Scene::addObject(SceneObject* object)
        {
            if(object && verifySceneTrees())
            {
                if(object->isStatic())
                {
                    m_StaticSceneTree->addObject(object);
                }
                else
                {
                    m_DynamicSceneTree->addObject(object);
                }

                auto routines = object->getAllRoutines();

                for(auto routine : routines)
                {
                    routineAdded(routine);
                }
            }
        }

        void Scene::addObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto iter = objects.begin(); iter != objects.end(); ++iter)
            {
                addObject((*iter));
            }
        }

        void Scene::removeObject(SceneObject* object)
        {
            bool result = true;

            if(object)
            {
                SceneObject* parent = object->getParent();

                if(parent)
                {
                    parent->removeChild(object);
                }

                //--------------------------------------------------------
                // Remove the object from the SceneTrees

                if(object->isStatic())
                {
                    result = m_StaticSceneTree->removeObject(object);
                }

                if(!object->isStatic() || !result)
                {
                    // Object is dynamic or was not found in the static tree to remove...
                    m_DynamicSceneTree->removeObject(object);
                }

                //--------------------------------------------------------
                // Remove it's Routines

                auto routines = object->getAllRoutines();

                for(auto routine = routines.begin(); routine != routines.end(); ++routine)
                {
                    routineRemoved((*routine));
                }

                //--------------------------------------------------------
                // Remove it's Renderables


                /// \todo Remove renderables
            }
        }

        void Scene::removeObjects(std::vector<SceneObject*> const& objects)
        {
            for(auto iter = objects.begin(); iter != objects.end(); ++iter)
            {
                removeObject((*iter));
            }
        }

        void Scene::removeAllObjects()
        {
            if(verifySceneTrees())
            {
                m_StaticSceneTree->destroy();
                m_DynamicSceneTree->destroy();
            }

            m_Routines.clear();
        }

        void Scene::update()
        {
            updateTrees();
            updateRoutines();
        }

        void Scene::render()
        {
            //if(m_UniformBufferPerFrame)
            //{
                //m_UniformBufferPerFrame->bind();
            //}

            if(m_Renderer)
            {
                auto cameras = OcularCameras->getCameras();

                if(cameras.size())
                {
                    for(auto camera : cameras)
                    {
                        //------------------------------------------------
                        // Perform simple Frustum Culling on the SceneObjects
                        //------------------------------------------------

                        OcularCameras->setActiveCamera(camera);
                        const Math::Frustum frustum = camera->getFrustum();

                        std::vector<SceneObject*> objects;

                        if(m_StaticSceneTree)
                        {
                            //m_StaticSceneTree->getAllVisibleObjects(frustum, objects);
                        }

                        if(m_DynamicSceneTree)
                        {
                            m_DynamicSceneTree->getAllVisibleObjects(frustum, objects);
                        }

                        //------------------------------------------------
                        // Remove any SceneObjects that can't be rendered
                        //------------------------------------------------

                        for(auto iter = objects.begin(); iter != objects.end(); )
                        {
                            if((*iter)->getRenderable() == nullptr)
                            {
                                iter = objects.erase(iter);
                            }
                            else
                            {
                                ++iter;
                            }
                        }

                        //------------------------------------------------
                        // Render the remaining SceneObjects
                        //------------------------------------------------

                        m_Renderer->render(objects);
                    }
                }
            }
        }

        //----------------------------------------------------------------------------------
        // Getters / Setters
        //----------------------------------------------------------------------------------

        void Scene::getVisibleSceneObjects(std::vector<SceneObject*>& objects, Math::Frustum const& frustum)
        {
            if(m_StaticSceneTree)
            {
                m_StaticSceneTree->getAllVisibleObjects(frustum, objects);
            }

            if(m_DynamicSceneTree)
            {
                m_DynamicSceneTree->getAllVisibleObjects(frustum, objects);
            }
        }

        void Scene::setStaticTreeType(SceneTreeType const type)
        {
            m_StaticTreeType = type;
        }

        SceneTreeType const& Scene::getStaticTreeType() const
        {
            return m_StaticTreeType;
        }

        void Scene::setDynamicTreeType(SceneTreeType const type)
        {
            m_DynamicTreeType = type;
        }

        SceneTreeType const& Scene::getDynamicTreeType() const
        {
            return m_DynamicTreeType;
        }

        void Scene::setRendererType(std::string const& type)
        {
            delete m_Renderer;

            m_RendererType = type;
            m_Renderer = OcularScene->getRendererFactory().createComponent(type);
        }

        std::string const& Scene::getRendererType() const
        {
            return m_RendererType;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void Scene::updateTrees()
        {
            if(verifySceneTrees())
            {
                //m_StaticSceneTree->restructure();
                m_DynamicSceneTree->restructure();
            }
        }

        void Scene::updateRoutines()
        {
            sortRoutines();

            const float delta = OcularEngine.Clock()->getDelta();

            for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
            {
                ARoutine* routine = (*iter);

                if(routine)
                {
                    SceneObject* parent = routine->getParent();

                    if(parent && parent->isActive())
                    {
                        routine->onUpdate(delta);
                    }
                }
            }
        }

        void Scene::sortRoutines()
        {
            if(m_RoutinesAreDirty)
            {
                std::sort(m_Routines.begin(), m_Routines.end(), [](ARoutine const* lhs, ARoutine const* rhs)->bool
                {
                    return (lhs->getPriorityLevel() > rhs->getPriorityLevel());
                });

                m_RoutinesAreDirty = false;
            }
        }

        ISceneTree* Scene::getStaticTree() const
        {
            return m_StaticSceneTree;
        }

        ISceneTree* Scene::getDynamicTree() const
        {
            return m_DynamicSceneTree;
        }

        void Scene::objectTreeChanged(SceneObject* object)
        {
            if(object && verifySceneTrees())
            {
                if(object->isStatic())
                {
                    // Was dynamic, is now static.
                    m_DynamicSceneTree->removeObject(object);
                    m_StaticSceneTree->addObject(object);
                }
                else
                {
                    // Was static, is now dynamic.
                    m_StaticSceneTree->removeObject(object);
                    m_DynamicSceneTree->addObject(object);
                }
            }
        }

        void Scene::objectParentChanged(SceneObject* object, SceneObject* oldParent)
        {
            if(object && verifySceneTrees())
            {
                /**
                 * A change in object parentage can have an effect on the SceneTrees.
                 * 
                 * If the old parent is null, then the object used to be a top-level
                 * object and thus the appropriate SceneTree will need to be updated.
                 * As far as the tree is concerned, the object was removed as they
                 * only deal with top-level parents.
                 *
                 * The the new parent is null, then the appropriate SceneTree will
                 * need to add the object as a new top-level parent.
                 *
                 * If neither the old parent or the new parent are null, then the
                 * SceneTrees do not need to do anything as they do not interact
                 * while child objects.
                 */

                if(oldParent == nullptr)
                {
                    bool removed = false;

                    if(object->isStatic())
                    {
                        removed = m_StaticSceneTree->removeObject(object);
                    }

                    if(!removed)
                    {
                        removed = m_DynamicSceneTree->removeObject(object);\
                    }

                    if(!removed)
                    {
                        // Was not successfully removed from either tree.
                        // Means the object is not part of the proper Scene ecosystem.

                        OcularLogger->warning("Failed to properly handle new parent change. SceneObject is invalid.", OCULAR_INTERNAL_LOG("Scene", "objectParentChanged"));
                    }
                }

                if(object->getParent() == nullptr)
                {
                    if(object->isStatic())
                    {
                        m_StaticSceneTree->addObject(object);
                    }
                    else
                    {
                        m_DynamicSceneTree->addObject(object);
                    }
                }
            }
        }

        void Scene::routineAdded(ARoutine* routine)
        {
            if(routine)
            {
                m_Routines.insert(m_Routines.begin(), routine);
                m_RoutinesAreDirty = true;
            }
        }

        void Scene::routineRemoved(ARoutine* routine)
        {
            if(routine)
            {
                for(auto iter = m_Routines.begin(); iter != m_Routines.end(); ++iter)
                {
                    if((*iter) == routine)
                    {
                        m_Routines.erase(iter);
                        break;
                    }
                }
            }
        }
        
        void Scene::triggerObjectDirty(UUID const& uuid, bool const staticObject)
        {
            if(staticObject)
            {
                if(m_StaticSceneTree)
                {
                    m_StaticSceneTree->setDirty(uuid);
                }
            }
            else
            {
                if(m_DynamicSceneTree)
                {
                    m_DynamicSceneTree->setDirty(uuid);
                }
            }
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

        bool Scene::verifySceneTrees() const
        {
            bool result = true;

            if(m_StaticSceneTree == nullptr)
            {
                result = false;
                OcularLogger->error("Attempting to use static SceneTree that was not properly created", OCULAR_INTERNAL_LOG("Scene", "verifySceneTrees"));
            }

            if(m_DynamicSceneTree == nullptr)
            {
                result = false;
                OcularLogger->error("Attempting to use dynamic SceneTree that was not properly created", OCULAR_INTERNAL_LOG("Scene", "verifySceneTrees"));
            }

            return result;
        }
    }
}