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

#include "ObjectIO/BuilderNode.hpp"

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //--------------------------------------------------------------------------------------
        // CONSTRUCTORS
        //--------------------------------------------------------------------------------------

        BuilderNode::BuilderNode(BuilderNode* parent, std::string const& name, std::string const& type, std::string const& value)
            : m_Parent(parent),
            m_Name(name),
            m_Value(value),
            m_Type(type)
        {

        }

        BuilderNode::~BuilderNode()
        {
            for(auto nodePair : m_ChildMap)
            {
                delete nodePair.second;
                nodePair.second = nullptr;
            }
        }

        //--------------------------------------------------------------------------------------
        // PUBLIC METHODS
        //--------------------------------------------------------------------------------------

        std::string const& BuilderNode::getName() const
        {
            return m_Name;
        }

        std::string const& BuilderNode::getValue() const
        {
            return m_Value;
        }

        std::string const& BuilderNode::getType() const
        {
            return m_Type;
        }

        BuilderNode const* BuilderNode::getParent() const
        {
            return m_Parent;
        }

        BuilderNode* BuilderNode::addChild(std::string const& name, std::string const& type, std::string const& value)
        {
            BuilderNode* result = nullptr;
            auto findPair = m_ChildMap.find(name);

            if(findPair != m_ChildMap.end())
            {
                delete findPair->second;
            }

            result = new BuilderNode(this, name, type, value);
            m_ChildMap[name] = result;

            return result;
        }

        BuilderNode const* BuilderNode::getChild(std::string const& name) const
        {
            BuilderNode* result = nullptr;
            auto findPair = m_ChildMap.find(name);

            if(findPair != m_ChildMap.end())
            {
                result = findPair->second;
            }

            return result;
        }
        
        void BuilderNode::findChildrenByName(std::vector<BuilderNode*>& children, std::string const& name) const
        {
            children.reserve(m_ChildMap.size());

            for(auto childPair : m_ChildMap)
            {
                BuilderNode* node = childPair.second;

                if(node)
                {
                    if(node->getName().find(name) != std::string::npos)
                    {
                        children.emplace_back(node);
                    }
                }
            }
        }
        
        void BuilderNode::findChildrenByType(std::vector<BuilderNode*>& children, std::string const& type) const
        {
            children.reserve(m_ChildMap.size());

            for(auto childPair : m_ChildMap)
            {
                BuilderNode* node = childPair.second;

                if(node)
                {
                    if(Utils::String::IsEqual(type, node->getType()))
                    {
                        children.emplace_back(node);
                    }
                }
            }
        }

        void BuilderNode::getAllChildren(std::vector<BuilderNode*>& children) const
        {
            children.reserve(children.size() + m_ChildMap.size());

            for(auto childPair : m_ChildMap)
            {
                children.push_back(childPair.second);
            }
        }

        uint32_t BuilderNode::getNumChildren() const
        {
            return static_cast<uint32_t>(m_ChildMap.size());
        }

        //--------------------------------------------------------------------------------------
        // PROTECTED METHODS
        //--------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------
        // PRIVATE METHODS
        //--------------------------------------------------------------------------------------
    }
}