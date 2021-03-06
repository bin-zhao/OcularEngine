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
#ifndef __H__OCULAR_EDITOR_GIZMO__H__
#define __H__OCULAR_EDITOR_GIZMO__H__

#include "Scene/SceneObject.hpp"

//------------------------------------------------------------------------------------------

/**
 * \addtogroup Ocular
 * @{
 */
namespace Ocular
{
    /**
     * \addtogroup Editor
     * @{
     */
    namespace Editor
    {
        /**
         * \class Gizmo
         *
         * Base class for an editor gizmo. 
         */
        class Gizmo : public Core::SceneObject
        {
        public:

            Gizmo(std::string const& name, Core::SceneObject* parent, std::string const& type);
            virtual ~Gizmo();

            virtual void setSelected(bool selected);
            virtual bool isSelected() const;

        protected:

            bool m_IsSelected;    ///< Set to TRUE if this Gizmo has been selected. Note that a Gizmo can not be set as _the_ selected object.

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

//------------------------------------------------------------------------------------------

#endif
#pragma once
