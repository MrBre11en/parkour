#include "windows.h"

namespace random
{
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