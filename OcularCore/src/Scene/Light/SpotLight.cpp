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

#include "Scene/Light/SpotLight.hpp"
#include "Scene/SceneObjectRegistrar.hpp"

#include "OcularEngine.hpp"

OCULAR_REGISTER_SCENEOBJECT(Ocular::Core::SpotLight, "Spot Light");

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Core
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------
        
        SpotLight::SpotLight(std::string const& name, SceneObject* parent)
            : LightSource(name, parent, "Spot Light")
        {
            m_LightType = 2.0f;
            exposeProperties();
        }

        SpotLight::SpotLight()
            : LightSource("Spot Light", nullptr, "Spot Light")
        {
            m_LightType = 2.0f;
            exposeProperties();
        }

        SpotLight::~SpotLight()
        {

        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------
        
        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------
        
        void SpotLight::exposeProperties()
        {

        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------
    }
}