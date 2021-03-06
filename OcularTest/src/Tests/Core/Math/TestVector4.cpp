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

#include "Math/Vector4.hpp"

#ifdef _DEBUG

#include "gtest/gtest.h"

//------------------------------------------------------------------------------------------

const Ocular::Math::Vector4d vecA(10.0, 10.0, 0.0, 5.0);
const Ocular::Math::Vector4d vecB(33.0, 10.8, 3.0, 8.0);

TEST(Vector4, VectorAddition)
{
    const Ocular::Math::Vector4d expected(43.0, 20.8, 3.0, 13.0);
    const Ocular::Math::Vector4d result = vecA + vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, ScalarAddition)
{
    const Ocular::Math::Vector4d expected(20.0, 20.0, 10.0, 15.0);
    const Ocular::Math::Vector4d result = vecA + 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, VectorSubtraction)
{
    const Ocular::Math::Vector4d expected(-23.0, -0.8, -3.0, -3.0);
    const Ocular::Math::Vector4d result = vecA - vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, ScalarSubtraction)
{
    const Ocular::Math::Vector4d expected(0.0, 0.0, -10.0, -5.0);
    const Ocular::Math::Vector4d result = vecA - 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, VectorMultiplication)
{
    const Ocular::Math::Vector4d expected(330.0, 108.0, 0.0, 40.0);
    const Ocular::Math::Vector4d result = vecA * vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, ScalarMultiplication)
{
    const Ocular::Math::Vector4d expected(100.0, 100.0, 0.0, 50.0);
    const Ocular::Math::Vector4d result = vecA * 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, VectorDivision)
{
    const Ocular::Math::Vector4d expected(0.303030, 0.92592, 0.0, 0.62500);
    const Ocular::Math::Vector4d result = vecA / vecB;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, ScalarDivision)
{
    const Ocular::Math::Vector4d expected(1.0, 1.0, 0.0, 0.5);
    const Ocular::Math::Vector4d result = vecA / 10.0;

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, Magnitude)
{
    const double expected = 15.0;
    const double result = vecA.getMagnitude();

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, Normalize)
{
    const Ocular::Math::Vector4d expected(0.666667, 0.666667, 0.0, 0.333333);
    const Ocular::Math::Vector4d result = vecA.getNormalized();

    EXPECT_TRUE((expected == result));
}

TEST(Vector4, DotProduct)
{
    const double expected = 478.0;
    const double result = vecA.dot(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, AngleBetween)
{
    const double expected = 0.47087;
    const double result = vecA.angleBetween(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

TEST(Vector4, Distance)
{
    const double expected = 23.4017;
    const double result = vecA.distanceTo(vecB);

    EXPECT_NEAR(expected, result, Ocular::Math::EPSILON_DOUBLE);
}

#endif