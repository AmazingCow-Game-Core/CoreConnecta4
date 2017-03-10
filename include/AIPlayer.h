
#pragma once
//AmazingCow Libs
#include "CoreCoord.h"
#include "CoreGame.h"
#include "CoreRandom.h"
//CoreConnecta4
#include "CoreConnecta4_Utils.h"
#include "Board.h"

NS_CORECONNECTA4_BEGIN

class AIPlayer
{
    // CTOR / DTOR //
public:
    AIPlayer(int strength) {}

    // Public Methods //
public:
    int decideMove(Board board) {
        return 0;
    }
};

NS_CORECONNECTA4_END
