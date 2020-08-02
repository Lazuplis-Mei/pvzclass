#include "ZombieState.h"

const char* ZombieState::ToString(ZombieState state)
{
    switch (state) {
    case WALKING:
        return "WALKING";
    case DYING:
        return "DYING";
    case DYING_FROM_INSTANT_KILL:
        return "DYING_INSTANT_KILL";
    case DYING_FROM_LAWNMOWER:
        return "DYING_FROM_LAWNMOWER";
    default:
        return "UNKNOW";
    }
}
