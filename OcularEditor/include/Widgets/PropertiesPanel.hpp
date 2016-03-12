/**
 * Copyright 2014-2016 Steven T Sell (ssell@ocularinteractive.com)
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
#ifndef __H__OCULAR_EDITOR_PROPERTIES_PANEL__H__
#define __H__OCULAR_EDITOR_PROPERTIES_PANEL__H__

#include <QtWidgets/qframe.h>
#include "Events/AEventListener.hpp"

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
        class CommonPropertiesDisplay;

        /**
         * \class PropertiesPanel
         */
        class PropertiesPanel : public QFrame, public Ocular::Core::AEventListener
        {
        public:

            PropertiesPanel(QWidget* parent = nullptr);
            ~PropertiesPanel();

            virtual QSize sizeHint() const override;

            //------------------------------------------------------------

            void selectObject(Core::SceneObject* object);

        protected:

            virtual bool onEvent(std::shared_ptr<Core::AEvent> event) override;

            void displayCommon(Core::SceneObject* object);
            void displayCustom(Core::SceneObject* object);
            void displayRenderable(Core::SceneObject* object);
            void displayRoutines(Core::SceneObject* object);

        private:

            QVBoxLayout* m_Layout;
            CommonPropertiesDisplay* m_CommonProperties;
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