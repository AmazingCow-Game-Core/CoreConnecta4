#pragma once

//std
#include <string>
//AmazingCow Libs
#include "CoreCoord.h"
//CoreConnecta4
#include "CoreConnecta4_Utils.h"

NS_CORECONNECTA4_BEGIN

class Board
{
    // Enums / Constans / Typedefs //
public:
    const static CoreCoord::Coord kInvalidCoord;


    // CTOR / DTOR //
public:
    Board(int width, int height);


    // Public Methods //
public:
    bool putPlayerAt(int column, int player, CoreCoord::Coord *pOutCoord);
    int getPlayerAt(const CoreCoord::Coord &coord) const;

    int getWidth() const;
    int getHeight() const;

    int getWinner() const;

    bool isValidColumn(int column) const;
    bool isValidCoord(const CoreCoord::Coord &coord) const;

    CoreCoord::Coord getFirstAvailableCoord(int column) const;

    std::string ascii() const;


    // Private Methods //
public:
    void checkVictory(const CoreCoord::Coord &placedCoord);
    bool checkRange(const CoreCoord::Coord &c1, const CoreCoord::Coord &c2);

    // iVars //
public:
    int m_winner;
    std::vector<std::vector<int>> m_board;
};

NS_CORECONNECTA4_END
