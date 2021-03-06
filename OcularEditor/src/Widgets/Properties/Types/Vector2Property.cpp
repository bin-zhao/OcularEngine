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

#include "stdafx.h"
#include "Widgets/Properties/Types/Vector2Property.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"
#include "Math/Vector2.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::Vector2Property, OCULAR_TYPE_NAME(Ocular::Math::Vector2f));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        Vector2Property::Vector2Property(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(Ocular::Math::Vector2f), parent)
        {
            m_LabelX = new QLabel("X");
            m_LabelY = new QLabel("Y");
            
            m_EditX = new LineEdit(LineType::Float);
            m_EditY = new LineEdit(LineType::Float);
            
            m_LayoutRight->addWidget(m_LabelX);
            m_LayoutRight->addWidget(m_EditX);
            m_LayoutRight->addWidget(m_LabelY);
            m_LayoutRight->addWidget(m_EditY);
        }

        Vector2Property::~Vector2Property()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool Vector2Property::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                Math::Vector2f* vector = void_cast<Math::Vector2f*>(m_Variable.data);

                if(m_EditX->wasEdited())
                {
                    (*vector).x = m_EditX->asFloat();
                    result = true;
                }
                else if(!m_EditX->hasFocus())
                {
                    m_EditX->setText(OcularString->toString<float>(vector->x).c_str());
                }

                if(m_EditY->wasEdited())
                {
                    (*vector).y = m_EditY->asFloat();
                    result = true;
                }
                else if(!m_EditY->hasFocus())
                {
                    m_EditY->setText(OcularString->toString<float>(vector->y).c_str());
                }
            }

            return result;
        }

        void Vector2Property::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(Math::Vector2f)))
            {
                Math::Vector2f valueCast = void_cast<Math::Vector2f>(value);

                if(m_Variable.data)
                {
                    Math::Vector2f* valuePtr = void_cast<Math::Vector2f*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr).x = valueCast.x;
                        (*valuePtr).y = valueCast.y;
                    }
                }
                
                m_EditX->setText(OcularString->toString<float>(valueCast.x).c_str());
                m_EditY->setText(OcularString->toString<float>(valueCast.y).c_str());
            }
        }

        std::string Vector2Property::getValue() const
        {
            auto qstr = m_EditX->text() + " " + m_EditY->text();
            return qstr.toStdString();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}