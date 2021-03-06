/**
 * Copyright 2014-2032 Steven T Sell (ssell@vertexfragment.com)
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
#include "Widgets/Properties/Types/Arithmetic/Int32Property.hpp"
#include "Widgets/Properties/PropertyWidgetRegistrar.hpp"

OCULAR_REGISTER_PROPERTY_WIDGET(Ocular::Editor::Int32Property, OCULAR_TYPE_NAME(int32_t));

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Editor
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        Int32Property::Int32Property(QWidget* parent)
            : PropertyWidget(OCULAR_TYPE_NAME(int32_t), parent)
        {
            m_EditValue = new LineEdit(LineType::Int32);
            m_LayoutRight->addWidget(m_EditValue);
        }

        Int32Property::~Int32Property()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        bool Int32Property::updateProperties()
        {
            bool result = false;

            if(m_Variable.data)
            {
                int32_t* value = void_cast<int32_t*>(m_Variable.data);

                if(m_EditValue->wasEdited())
                {
                    (*value) = m_EditValue->as<int32_t>();
                    result = true;
                }
                else if(!m_EditValue->hasFocus())
                {
                    m_EditValue->setText(OcularString->toString<int32_t>(*value).c_str());
                }
            }

            return result;
        }

        void Int32Property::setValue(void* value, uint32_t const size)
        {
            if(value && (size == sizeof(int32_t)))
            {
                int32_t valueCast = void_cast<int32_t>(value);

                if(m_Variable.data)
                {
                    int32_t* valuePtr = void_cast<int32_t*>(m_Variable.data);

                    if(valuePtr)
                    {
                        (*valuePtr) = valueCast;
                    }
                }

                m_EditValue->setText(OcularString->toString<int32_t>(valueCast).c_str());
            }
        }

        std::string Int32Property::getValue() const
        {
            return m_EditValue->text().toStdString();
        }

        LineEdit* Int32Property::getLineEdit()
        {
            return m_EditValue;
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}