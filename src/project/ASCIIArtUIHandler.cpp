#include "ASCIIArtUIHandler.h"

#include <memory>
#include <ostream>
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "PieceUIHandlerBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new ASCII art UI handler that outputs to the
/// given output stream. Traps are hidden by default.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
ASCIIArtUIHandler::ASCIIArtUIHandler(std::ostream* outputStream)
    : PieceUIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    this->SetHideTraps(true);
    ensure(this->CheckInvariants());
}

/// \brief Creates a new ASCII art UI handler that outputs to the
/// given output stream. Traps can be hidden or displayed, as
/// per the 'HideTraps' boolean argument.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
ASCIIArtUIHandler::ASCIIArtUIHandler(std::ostream* outputStream, bool HideTraps)
    : PieceUIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    this->SetHideTraps(HideTraps);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given barrel piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayBarrel(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "O";
    ensure(this->CheckInvariants());
}

/// \brief Displays a button piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayButton(std::shared_ptr<Button> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << ".";
    ensure(this->CheckInvariants());
}

/// \brief Displays an unknown piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayDefault(std::shared_ptr<PieceBase> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "?";
    ensure(this->CheckInvariants());
}

/// \brief Displays an empty cell.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayEmpty(Vector2<int> Position)
{
    require(this->CheckInvariants());
    *this->outputStream << " ";
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    if (IsOpened)
        this->DisplayEmpty(Piece->GetPosition());
    else
        *this->outputStream << "=";

    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayGoal(std::shared_ptr<Goal> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "X";
    ensure(this->CheckInvariants());
}

/// \brief Displays the given monster piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayMonster(std::shared_ptr<Monster> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "@";
    ensure(this->CheckInvariants());
}

/// \brief Displays the given player piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayPlayer(std::shared_ptr<Player> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "Y";
    ensure(this->CheckInvariants());
}

/// \brief Displays the end of a row.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayRow()
{
    require(this->CheckInvariants());
    *this->outputStream << "\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays a trap piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayTrap(std::shared_ptr<Trap> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    if (this->GetHideTraps())
        this->DisplayEmpty(Piece->GetPosition());
    else
        *this->outputStream << "^";

    ensure(this->CheckInvariants());
}

/// \brief Displays the given wall piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayWall(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "#";
    ensure(this->CheckInvariants());
}

/// \brief Displays a water piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void ASCIIArtUIHandler::DisplayWater(std::shared_ptr<Water> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "~";
    ensure(this->CheckInvariants());
}

/// \brief Gets a boolean value that indicates whether traps are to be
/// displayed or hidden.
/// \pre require(this->CheckInvariants());
bool ASCIIArtUIHandler::GetHideTraps() const
{
    require(this->CheckInvariants());
    return this->HideTraps_value;
}

/// \brief Sets a boolean value that indicates whether traps are to be
/// displayed or hidden.
void ASCIIArtUIHandler::SetHideTraps(bool value)
{
    this->HideTraps_value = value;
}