//Header
#include "../include/GameCore.h"

//Usings
USING_NS_CORECONNECTA4;


////////////////////////////////////////////////////////////////////////////////
// CTOR / DTOR //
////////////////////////////////////////////////////////////////////////////////
GameCore::GameCore(
    GameMode gameMode,
    int      starterPlayer,
    int      boardWitdh,
    int      boardHeight,
    int      aiStrength,
    int      seed /* = CoreRandom::Random::kRandomSeed */) :
    m_mode         (gameMode),
    m_board        (boardWitdh, boardHeight),
    m_turnsCount   (0),
    m_currentPlayer(starterPlayer),
    m_winnerPlayer (kPlayerNone),
    //m_pAIPlayer - Set in body.
    m_random    (seed)
{
    //AI Setup.
    if(m_mode == GameMode::SinglePlayer)
    {
        aiStrength  = CoreGame::MathUtils::clamp(1, 10, aiStrength);
        m_pAIPlayer = CoreGame::make_unique<AIPlayer>(aiStrength);
    }
    else
    {
        m_pAIPlayer = nullptr;
    }

    //StarterPlayer setup.
    if(starterPlayer != kPlayer1 && starterPlayer != kPlayer2)
    {
        m_currentPlayer = (m_random.nextBool()) ? kPlayer1 : kPlayer2;
    }
}


////////////////////////////////////////////////////////////////////////////////
// Public Methods                                                             //
////////////////////////////////////////////////////////////////////////////////
CoreCoord::Coord GameCore::makeMove(int column)
{
    CoreCoord::Coord coord;
    if(m_board.putPlayerAt(column, m_currentPlayer, &coord))
    {
        m_currentPlayer = getNextPlayer();
        ++m_turnsCount;
    }

    return coord;
}

const Board& GameCore::getBoard() const
{
    return m_board;
}

int GameCore::getAIMove() const
{
    COREGAME_ASSERT(
        (m_mode == GameMode::SinglePlayer),
        "Game isn't in SinglePlayer mode - AI is not initialized."
    );

    return m_pAIPlayer->decideMove(m_board);
}

int GameCore::getTurnsCount() const
{
    return m_turnsCount;
}

CoreGame::Status GameCore::getStatus() const
{
    return (getWinner() == kPlayerNone)
            ? CoreGame::Status::Continue
            : CoreGame::Status::Victory;
}

int GameCore::getCurrentPlayer() const
{
    return m_currentPlayer;
}

int GameCore::getNextPlayer() const
{
    return (m_currentPlayer == kPlayer1) ? kPlayer2 : kPlayer1;
}

int GameCore::getWinner() const
{
    return m_board.getWinner();
}
