//Header
#include "../include/Board.h"
//std
#include <sstream>
//AmazingCow Libs
#include "CoreGame.h"
//CoreConnecta4
#include "../include/CoreConnecta4_Types.h"

//Usings
USING_NS_CORECONNECTA4;


////////////////////////////////////////////////////////////////////////////////
// Enums / Constants / Typedefs                                               //
////////////////////////////////////////////////////////////////////////////////
const CoreCoord::Coord Board::kInvalidCoord = CoreCoord::Coord(-1, -1);


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR                                                                //
////////////////////////////////////////////////////////////////////////////////
Board::Board(int width, int height) :
    m_winner(kPlayerNone)
{
    //Initialize board.
    m_board.resize(height);
    for(auto &line : m_board)
        line.resize(width);
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
bool Board::putPlayerAt(int column, int player, CoreCoord::Coord *pOutCoord)
{
    COREGAME_ASSERT_ARGS(
        isValidColumn(column),
        "Column(%d) is not in Board range (0,%d]",
        column,
        m_board[0].size()
    );

    *pOutCoord = getFirstAvailableCoord(column);
    if(*pOutCoord == Board::kInvalidCoord)
        return false;

    m_board[pOutCoord->y][pOutCoord->x] = player;
    checkVictory(*pOutCoord);

    return true;
}

int Board::getPlayerAt(const CoreCoord::Coord &coord) const
{
    COREGAME_ASSERT_ARGS(
        isValidCoord(coord),
        "Coord(%d,%d) is not in Board range",
        coord.y,
        coord.x
    );

    return m_board[coord.y][coord.x];
}


int Board::getWidth() const
{
    return m_board[0].size();
}

int Board::getHeight() const
{
    return m_board.size();
}


int Board::getWinner() const
{
    return m_winner;
}


bool Board::isValidColumn(int column) const
{
    return column >= 0 && column < m_board[0].size();
}

bool Board::isValidCoord(const CoreCoord::Coord &coord) const
{
    return coord.y >= 0 && coord.y < m_board.size()
        && coord.x >= 0 && coord.x < m_board[0].size();
}


CoreCoord::Coord Board::getFirstAvailableCoord(int column) const
{
    COREGAME_ASSERT_ARGS(
        isValidColumn(column),
        "Column(%d) is not in Board range (0,%d]",
        column,
        m_board[0].size()
    );

    for(CoreCoord::Coord coord(getHeight()-1, column); coord.y >= 0; --coord.y)
    {
        if(getPlayerAt(coord) == kPlayerNone)
            return coord;
    }

    return Board::kInvalidCoord;
}


std::string Board::ascii() const
{
    std::stringstream ss;
    for(auto &line : m_board)
    {
        for(auto &player : line)
        {
            switch(player)
            {
                case kPlayerNone : ss << ". "; break;
                case kPlayer1    : ss << "X "; break;
                case kPlayer2    : ss << "O "; break;
            }
        }
        ss << std::endl;
    }

    return ss.str();
}


////////////////////////////////////////////////////////////////////////////////
// Private Methods                                                            //
////////////////////////////////////////////////////////////////////////////////
void Board::checkVictory(const CoreCoord::Coord &placedCoord)
{
    //COWTODO: Implement correctly...
    CoreCoord::Coord evalCoords[3] = {
        CoreCoord::Coord(0, 1),
        CoreCoord::Coord(1, 0),
        CoreCoord::Coord(1, 1)
    };

    for(auto &displacement : evalCoords)
    {
        for(int i = 0; i < 4; ++i)
        {
            auto coord1 = placedCoord - (displacement * (3 - i));
            auto coord2 = (displacement * i) + placedCoord;

            /*COREGAME_DLOG(CoreGame::Log::Type::Debug1, "1 %d, %d", coord1.y, coord1.x);
            COREGAME_DLOG(CoreGame::Log::Type::Debug1, "2 %d, %d", coord2.y, coord2.x);
            COREGAME_DLOG(CoreGame::Log::Type::Debug1, "\n",);*/

            if(checkRange(coord1, coord2))
            {
                m_winner = getPlayerAt(placedCoord);
                return;
            }
        }
    }
} 

bool Board::checkRange(const CoreCoord::Coord &c1, const CoreCoord::Coord &c2)
{
    //One (or both) coords are outside of Board's bound.
    if(!isValidCoord(c1) || !isValidCoord(c2))
        return false;

    //Early check.
    auto player = getPlayerAt(c1);
    if(player == kPlayerNone || player != getPlayerAt(c2))
        return false;

    auto displacement = c2 - c1;
    auto curr = c1;
    
    displacement.makeUnit();
    
    while(curr != c2)
    {
        curr += displacement;
        if(player != getPlayerAt(curr))
            return false;
    }

    return true;
}