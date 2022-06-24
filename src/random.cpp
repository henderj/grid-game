#include "random.h"

#include <random>
#include <ctime>

namespace game
{
    namespace random
    {

        namespace
        {
            std::minstd_rand engine;
            int _max = engine.max();
        }

        void setSeed(unsigned int s)
        {
            engine.seed(s);
        }

        void setSeedToTime()
        {
            setSeed((unsigned)std::time(0));
        }

        int range(int min, int max)
        {
            int _range = max - min;
            int num = engine() % _range;
            return num - min;
        }

    } // namespace random
}