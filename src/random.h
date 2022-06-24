#pragma once

#include <random>
#include <ctime>

namespace game
{
    namespace random
    {
        void setSeed(unsigned int s);
        void setSeedToTime();

        int range(int min, int max);

    } // namespace random

}