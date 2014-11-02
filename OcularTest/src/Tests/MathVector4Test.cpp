/**
* Copyright 2014 Steven T Sell (ssell@ocularinteractive.com)
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

#include "Math/Vector4.hpp"
#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

Ocular::Math::Vector4d vecA(10.0, 10.0, 0.0, 5.0);
Ocular::Math::Vector4d vecB(33.0, 10.8, 3.0, 8.0);

TEST(Vector4, Magnitude)
{
    double expected = 15.0;
    double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, Normalize)
{
    Ocular::Math::Vector4d expected(0.666667, 0.666667, 0.0, 0.333333);
    Ocular::Math::Vector4d result = vecA.getNormalized();

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, DotProduct)
{
    double expected = 478.0;
    double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, AngleBetween)
{
    double expected = 0.47087;
    double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, Distance)
{
    double expected = 23.4017;
    double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}