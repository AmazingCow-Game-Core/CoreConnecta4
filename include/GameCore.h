
#pragma once
//AmazingCow Libs
#include "CoreCoord.h"
#include "CoreGame.h"
#include "CoreRandom.h"
//CoreConnecta4
#include "CoreConnecta4_Utils.h"
#include "AIPlayer.h"


NS_CORECONNECTA4_BEGIN

class GameCore
{
    // Friends //
public:
    friend class AIPlayer;


    // Enums / Constants / Typedefs //
public:
    enum class GameMode { SinglePlayer, Multiplayer }

    static const int kPlayerInvalid;
    static const int kPlayer1;
    static const int kPlayer2;

    typedef std::vector<std::vector<int>> Board;


    // CTOR / DTOR //
public:
    GameCore(
        GameMode gameMode,
        int      boardWitdh,
        int      boardHeight,
        int      aiStrength,
        int      seed = CoreRandom::Random::kRandomSeed);


    // Public Methods //
public:
    CoreCoord::Coord makeMove(int row);
    const Board& getBoard() const;

    int getAIMove() const;

    int getTurnsCount() const;

    CoreGame::Status getStatus() const;
    int getWinner() const;


    // Private Methods //
private:
    void checkStatus ();
    void revertAIMove();


    // iVars //
private:
    Board            m_board;
    int              m_turnsCount;
    CoreGame::Status m_status;
    int              m_winner;

    std::unique_ptr<AIPlayer> m_pAIPlayer;
};

NS_CORECONNECTA4_END

