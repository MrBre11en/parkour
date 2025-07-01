#include "windows.h"

namespace random
{
    void RandSeed(int seed)
    {
        srand(seed);
    }

    int GetRandom(int min = 1, int max = 0)
    {
        if (max > min)
        {
            return rand() % (max - min) + min;
        }
        else
        {
            return rand() % min;
        }
    }
}