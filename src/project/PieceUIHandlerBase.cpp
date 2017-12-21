#include "PieceUIHandlerBase.h"

#include <memory>
#include <ostream>
#include "Actor.h"
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "IsInstance.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new UI handler from the given output stream.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
PieceUIHandlerBase::PieceUIHandlerBase(std::ostream* outputStream)
    : UIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Displays the board.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::Display()
{
    require(this->CheckInvariants());
    this->DisplayHeader();
    for (int y = this->board->GetHeight() - 1; y >= 0; --y)
    {
        for (int x = 0; x < this->board->GetWidth(); ++x)
            this->DisplayPiece(this->board->GetItem(x, y), 
                               Vector2<int>(x, y));
        this->DisplayRow();
    }
    this->DisplayFooter();
    ensure(this->CheckInvariants());
}

/// \brief Displays an actor piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayActor(std::shared_ptr<Actor> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    if (stdx::isinstance<Player>(Piece))
        this->DisplayPlayer(std::dynamic_pointer_cast<Player>(Piece));
    else if (stdx::isinstance<Monster>(Piece))
        this->DisplayMonster(std::dynamic_pointer_cast<Monster>(Piece));
    else
        this->DisplayDefault(Piece);

    ensure(this->CheckInvariants());
}

/// \brief Displays the given barrel piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayBarrel(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a button piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayButton(std::shared_ptr<Button> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays an empty cell.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayEmpty(Vector2<int> Position)
{
    require(this->CheckInvariants());
    ensure(this->CheckInvariants());
}

/// \brief Displays a footer.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayFooter()
{
    require(this->CheckInvariants());
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayGoal(std::shared_ptr<Goal> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a header.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayHeader()
{
    require(this->CheckInvariants());
    ensure(this->CheckInvariants());
}

/// \brief Displays the given monster piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayMonster(std::shared_ptr<Monster> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given obstacle piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayObstacle(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    if (Piece->GetObstacleType() == "ton")
        this->DisplayBarrel(Piece);
    else if (Piece->GetObstacleType() == "muur")
        this->DisplayWall(Piece);
    else
        this->DisplayDefault(Piece);

    ensure(this->CheckInvariants());
}

/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayPiece(std::shared_ptr<PieceBase> Piece, Vector2<int> Position)
{
    require(this->CheckInvariants());
    if (Piece == nullptr)
        this->DisplayEmpty(Position);
    else if (stdx::isinstance<Actor>(Piece))
        this->DisplayActor(std::dynamic_pointer_cast<Actor>(Piece));
    else if (stdx::isinstance<Goal>(Piece))
        this->DisplayGoal(std::dynamic_pointer_cast<Goal>(Piece));
    else if (stdx::isinstance<Gate>(Piece))
    {
        auto item = std::dynamic_pointer_cast<Gate>(Piece);
        this->DisplayGate(item, item->IsOpened(this->board));
    }
    else if (stdx::isinstance<Water>(Piece))
        this->DisplayWater(std::dynamic_pointer_cast<Water>(Piece));
    else if (stdx::isinstance<Button>(Piece))
        this->DisplayButton(std::dynamic_pointer_cast<Button>(Piece));
    else if (stdx::isinstance<Trap>(Piece))
        this->DisplayTrap(std::dynamic_pointer_cast<Trap>(Piece));
    else if (stdx::isinstance<Obstacle>(Piece))
        this->DisplayObstacle(std::dynamic_pointer_cast<Obstacle>(Piece));
    else
        this->DisplayDefault(Piece);

    ensure(this->CheckInvariants());
}

/// \brief Displays the given player piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayPlayer(std::shared_ptr<Player> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the end of a row.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayRow()
{
    require(this->CheckInvariants());
    ensure(this->CheckInvariants());
}

/// \brief Displays a trap piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayTrap(std::shared_ptr<Trap> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given wall piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayWall(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a water piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void PieceUIHandlerBase::DisplayWater(std::shared_ptr<Water> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayDefault(Piece);
    ensure(this->CheckInvariants());
}