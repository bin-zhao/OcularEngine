/**
* Copyright 2014-2015 Steven T Sell (ssell@vertexfragment.com)
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

#include "Tests/Performance/PriorityContainerTest.hpp"
#include "Utilities/Structures/PriorityList.hpp"
#include "Utilities/Structures/PriorityMultiQueue.hpp"
#include "Math/Random/Random.hpp"
#include "Time/Timer.hpp"
#include <queue>

static const int64_t ACTION_SEED   = 100LL;
static const int64_t PRIORITY_SEED = 55LL;

//------------------------------------------------------------------------------------------

namespace Ocular
{
    namespace Tests
    {
        //----------------------------------------------------------------------------------
        // CONSTRUCTORS
        //----------------------------------------------------------------------------------

        PriorityContainerComparisonTest::PriorityContainerComparisonTest()
            : ATest("PriorityContainerComparisonTest")
        {
        
        }

        PriorityContainerComparisonTest::~PriorityContainerComparisonTest()
        {
        
        }

        //----------------------------------------------------------------------------------
        // PUBLIC METHODS
        //----------------------------------------------------------------------------------

        void PriorityContainerComparisonTest::run()
        {
            OCULAR_RUN_TEST(testSTLPriorityQueue);
            OCULAR_RUN_TEST(testPriorityMultiQueue);
            OCULAR_RUN_TEST(testPriorityList);

            ATest::run();
        }

        //----------------------------------------------------------------------------------
        // PROTECTED METHODS
        //----------------------------------------------------------------------------------

        void PriorityContainerComparisonTest::testSTLPriorityQueue()
        {
            auto prngAction   = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, ACTION_SEED);
            auto prngPriority = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, PRIORITY_SEED);

            //----------------------------------------

            std::priority_queue<unsigned> queue;
            Core::Timer timer;

            OcularEngine.Logger()->info("Testing STL PriorityQueue Performance...");

            for(unsigned iterations = 10; iterations <= 10000000; iterations *= 10)
            {
                timer.reset();
                timer.start();

                for(unsigned i = 0; i < iterations; i++)
                {
                    unsigned action = prngAction->next(0, 5);
                    unsigned priority = prngPriority->next(0, 5);

                    if(action < 3)
                    {
                        queue.push(priority);
                    }
                    else if(action < 4)
                    {
                        if(!queue.empty())
                        {
                            queue.pop();
                        }
                    }
                    else 
                    {
                        while(!queue.empty())
                        {
                            queue.pop();
                        }
                    }
                }

                OcularEngine.Logger()->info("\t- ", iterations, " actions in ", timer.getElapsedMS(), "ms");
            }

            OcularEngine.Logger()->info("");
        }

        void PriorityContainerComparisonTest::testPriorityMultiQueue()
        {
            auto prngAction   = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, ACTION_SEED);
            auto prngPriority = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, PRIORITY_SEED);

            //----------------------------------------

            Utils::PriorityMultiQueue<unsigned, 512> queue;
            Core::Timer timer;

            unsigned retVal = 0;

            OcularEngine.Logger()->info("Testing Ocular PriorityMultiQueue Performance...");

            for(unsigned iterations = 10; iterations <= 10000000; iterations *= 10)
            {
                timer.reset();
                timer.start();

                for(unsigned i = 0; i < iterations; i++)
                {
                    unsigned action = prngAction->next(0, 5);
                    unsigned priority = prngPriority->next(0, 5);

                    if(action < 3)
                    {
                        queue.enqueue(5, (Core::Priority)priority);
                    }
                    else if(action < 4)
                    {
                        queue.dequeue(retVal);
                    }
                    else 
                    {
                        while(!queue.empty())
                        {
                            queue.dequeue(retVal);
                        }
                    }
                }

                OcularEngine.Logger()->info("\t- ", iterations, " actions in ", timer.getElapsedMS(), "ms");
            }

            OcularEngine.Logger()->info("");
        }

        void PriorityContainerComparisonTest::testPriorityList()
        {
            auto prngAction   = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, ACTION_SEED);
            auto prngPriority = Math::Random::CreatePRNG(Math::Random::PRNG::XorShift, PRIORITY_SEED);

            //----------------------------------------

            Utils::PriorityList<unsigned, 512> list;
            Core::Timer timer;

            unsigned retVal = 0;

            OcularEngine.Logger()->info("Testing Ocular PriorityList Performance...");

            for(unsigned iterations = 10; iterations <= 10000000; iterations *= 10)
            {
                timer.reset();
                timer.start();

                for(unsigned i = 0; i < iterations; i++)
                {
                    unsigned action = prngAction->next(0, 5);
                    unsigned priority = prngPriority->next(0, 5);

                    if(action < 3)
                    {
                        list.push(5, (Core::Priority)priority);
                    }
                    else if(action < 4)
                    {
                        list.pop();
                    }
                    else 
                    {
                        while(list.pop());
                    }
                }

                OcularEngine.Logger()->info("\t- ", iterations, " actions in ", timer.getElapsedMS(), "ms");
            }

            OcularEngine.Logger()->info("");
        }

        //----------------------------------------------------------------------------------
        // PRIVATE METHODS
        //----------------------------------------------------------------------------------

    }
}