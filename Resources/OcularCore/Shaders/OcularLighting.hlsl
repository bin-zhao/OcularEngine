/**
 * Copyright 2014-2016 Steven T Sell (ssell@vertexfragment.com)
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

#include "OcularCommon.hlsl"

 /**
  * Collection of shader lighting methods
  */

float calcLightingIntensitySimpleCos(float4 normal, float4 source)
{
    float4 transformedNormal = mul(_ModelMatrix, normal);
    float angleCos = dot(transformedNormal, source);
    
    return clamp(angleCos, 0.0f, 1.0f);
}