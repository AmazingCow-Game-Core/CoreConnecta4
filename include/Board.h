
#pragma once
//AmazingCow Libs
#include "CoreCoord.h"
//CoreConnecta4
#include "CoreConnecta4_Utils.h"

NS_CORECONNECTA4_BEGIN

class Board
{
    // Enums / Constants / Typedefs //
    enum class PlayerIndex { None, One, Two };

    // CTOR / DTOR //
public:
    Board(int width, int height);


    // Public Methods //
public:
    CoreCoord::Coord putPlayerAt(int column, PlayerIndex player);
    PlayerIndex      getPlayerAt(const CoreCoord::Coord &coord) const;

    int getWidth () const;
    int getHeight() const;

    PlayerIndex getWinner  () const;
    void        checkWinner();


    // iVars //
public:
    std::vector<std::vector<PlayerIndex>>
}

NS_CORECONNECTA4_END
