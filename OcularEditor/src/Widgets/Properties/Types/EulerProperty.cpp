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
#include "Widgets/Properties/Types/EulerProperty.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"
#include "Math/Euler.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::EulerProperty, OCULAR_TYPE_NAME(Ocular::Math::Euler));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        EulerProperty::EulerProperty(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(Ocular::Math::Euler), parent)
        {
            m_LabelX = new QLabel("X");
            m_LabelY = new QLabel("Y");
            m_LabelZ = new QLabel("Z");
            
            m_EditX = new LineEdit(LineType::Float);
            m_EditY = new LineEdit(LineType::Float);
            m_EditZ = new LineEdit(LineType::Float);
            
            m_LayoutRight->addWidget(m_LabelX);
            m_LayoutRight->addWidget(m_EditX);
            m_LayoutRight->addWidget(m_LabelY);
            m_LayoutRight->addWidget(m_EditY);
            m_LayoutRight->addWidget(m_LabelZ);
            m_LayoutRight->addWidget(m_EditZ);
        }

        EulerProperty::~EulerProperty()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool EulerProperty::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                Math::Euler* euler = void_cast<Math::Euler*>(m_Variable.data);

                if(m_EditX->wasEdited())
                {
                    (*euler).setPitch(m_EditX->asFloat());
                    result = true;
                }
                else if(!m_EditX->hasFocus())
                {
                    m_EditX->setText(OcularString->toString<float>(euler->getPitch()).c_str());
                }

                if(m_EditY->wasEdited())
                {
                    (*euler).setYaw(m_EditY->asFloat());
                    result = true;
                }
                else if(!m_EditY->hasFocus())
                {
                    m_EditY->setText(OcularString->toString<float>(euler->getYaw()).c_str());
                }

                if(m_EditZ->wasEdited())
                {
                    (*euler).setRoll(m_EditZ->asFloat());
                    result = true;
                }
                else if(!m_EditZ->hasFocus())
                {
                    m_EditZ->setText(OcularString->toString<float>(euler->getRoll()).c_str());
                }
            }

            return result;
        }

        void EulerProperty::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(Math::Euler)))
            {
                Math::Euler valueCast = void_cast<Math::Euler>(value);

                if(m_Variable.data)
                {
                    Math::Euler* valuePtr = void_cast<Math::Euler*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_EditX->setText(OcularString->toString<float>(valueCast.getPitch()).c_str());
                m_EditY->setText(OcularString->toString<float>(valueCast.getYaw()).c_str());
                m_EditZ->setText(OcularString->toString<float>(valueCast.getRoll()).c_str());
            }
        }

        std::string EulerProperty::getValue() const
        {
            auto qstr = m_EditX->text() + " " + m_EditY->text() + " " + m_EditZ->text();
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