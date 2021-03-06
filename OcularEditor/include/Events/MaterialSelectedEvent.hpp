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
#ifndef __H__OCULAR_EDITOR_EVENTS_MATERIAL_SELECTED__H__
#define __H__OCULAR_EDITOR_EVENTS_MATERIAL_SELECTED__H__

#include "Events/AEvent.hpp"

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
         * \class MaterialSelectedEvent
         * 
         * Event generated when a Material has been selected in the MaterialEditor tree widget.
         *
         * String Descriptor: "MaterialSelectedEvent" <br/>
         * Event Priority: Medium 
         */
        class MaterialSelectedEvent : public Core::AEvent
        {
        public:
            
            /**
             * \param[in] object Pointer to object that was selected. Set to NULL to indicate previous object was unselected.
             */
            MaterialSelectedEvent(std::string const& mappingName);
            ~MaterialSelectedEvent();

            std::string mappingName;

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

//------------------------------------------------------------------------------------------

#endif