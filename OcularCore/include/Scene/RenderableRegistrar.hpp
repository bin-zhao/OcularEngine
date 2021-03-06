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
#ifndef __H__OCULAR_CORE_SCENE_RENDERABLE_REGISTRAR__H__
#define __H__OCULAR_CORE_SCENE_RENDERABLE_REGISTRAR__H__

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
        /**
         * \class RenderableRegistrar
         */
        template<class T>
        class RenderableRegistrar
        {
        public:

            RenderableRegistrar(std::string const& name)
            {
                if(!OcularScene->getRenderableFactory().registerComponent<T>(name))
                {
                    OcularLogger->error("Failed to register Renderable with name '", name, "' as the name is already in use",
                                         OCULAR_INTERNAL_LOG("RenderableRegistrar", "RenderableRegistrar"));
                }
            }

            ~RenderableRegistrar()
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

#define OCULAR_REGISTER_RENDERABLE(x,y) Ocular::Core::RenderableRegistrar<x> OCULAR_INTERNAL_RenderableRegistrar(y);

//------------------------------------------------------------------------------------------

#endif