/**
 * Copyright 2014-2017 Steven T Sell (ssell@vertexfragment.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#ifndef __H__OCULAR_CORE_SCENE_OBJECT_REGISTRAR__H__
#define __H__OCULAR_CORE_SCENE_OBJECT_REGISTRAR__H__

#include "OcularEngine.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Core
     * @{
     */
    namespace Core
    {
        template<class T>
        class SceneObjectRegistrar
        {
        public:

            SceneObjectRegistrar(std::string const& name)
            {
                if(!OcularScene->getSceneObjectFactory().registerComponent<T>(name))
                {
                    OcularLogger->error("Failed to register SceneObject with name '", name, "' as the name is already in use", OCULAR_INTERNAL_LOG("RoutineRegistrar", "RoutineRegistrar"));
                }
            }

            ~SceneObjectRegistrar()
            {

            }

        protected:

        private:
        };
    }
    /**
     * @} End of Doxygen Groups
     */
}
/**
 * @} End of Doxygen Groups
 */

#define OCULAR_REGISTER_SCENEOBJECT(x,y) Ocular::Core::SceneObjectRegistrar<x> OCULAR_INTERNAL_SceneObjectRegistrar(y);

//------------------------------------------------------------------------------------------

#endif