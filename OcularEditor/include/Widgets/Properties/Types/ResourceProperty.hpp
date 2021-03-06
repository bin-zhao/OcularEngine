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
#ifndef __H__OCULAR_EDITOR_RESOURCE_PROPERTY__H__
#define __H__OCULAR_EDITOR_RESOURCE_PROPERTY__H__

#include "Widgets/Properties/PropertyWidget.hpp"
#include "Widgets/Standard/LineEdit.hpp"
#include "Widgets/Standard/ButtonResourceBrowse.hpp"

#include <string>

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
         * \class ResourceProperty
         *
         * Pre-built property display for Core::Resource variables.
         */
        class ResourceProperty : public PropertyWidget
        {
        public:

            ResourceProperty(QWidget* parent = nullptr);
            virtual ~ResourceProperty();
            
            /**
             *
             */
            virtual bool updateProperties() override;

            /**
             *
             */
            void setResourceType(Core::ResourceType type);

            /**
             * \param[in] value Resource mapping name expected as a std::string
             * \param[in] size  Unused in this implementation
             */
            virtual void setValue(void* value, uint32_t size = 0) override;
            
            /**
             *
             */
            virtual std::string getValue() const override;

            /**
             * Validates if the resource specified in the line edit exists or not.
             * If the resource exists, returns TRUE. If it does not exists, then
             * returns FALSE and a red border is placed around the line edit.
             *
             * \param[in] isEmptyValid If TRUE, then an empty resource (assumed NULL) is considered valid.
             */
            bool validateResource(bool isEmptyValid = true);

        protected:

        private:

            LineEdit* m_LineValue;
            ButtonResourceBrowse* m_ButtonBrowse;

            Core::ResourceType m_Type;
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