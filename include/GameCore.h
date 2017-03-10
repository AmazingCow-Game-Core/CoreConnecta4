#pragma once
//std
#include <memory>
//AmazingCow Libs
#include "CoreCoord.h"
#include "CoreGame.h"
#include "CoreRandom.h"
//CoreConnecta4
#include "CoreConnecta4_Utils.h"
#include "CoreConnecta4_Types.h"
#include "AIPlayer.h"
#include "Board.h"


NS_CORECONNECTA4_BEGIN

class GameCore
{
    // Friends //
public:
    friend class AIPlayer;


    // Enums / Constants / Typedefs //
public:
    enum class GameMode { SinglePlayer, Multiplayer };

    // CTOR / DTOR //
public:
    GameCore(
        GameMode gameMode,
        int      starterPlayer,
        int      boardWitdh,
        int      boardHeight,
        int      aiStrength,
        int      seed = CoreRandom::Random::kRandomSeed);


    // Public Methods //
public:
    CoreCoord::Coord makeMove(int column);
    const Board& getBoard() const;

    int getAIMove() const;

    int getTurnsCount() const;

    CoreGame::Status getStatus() const;

    int getCurrentPlayer() const;
    int getNextPlayer() const;
    int getWinner() const;


    // iVars //
private:
    GameMode m_mode;
    Board    m_board;
    int      m_turnsCount;
    int      m_currentPlayer;
    int      m_winnerPlayer;

    std::unique_ptr<AIPlayer> m_pAIPlayer;

    CoreRandom::Random m_random;
};

NS_CORECONNECTA4_END

