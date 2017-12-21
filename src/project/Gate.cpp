#include "Gate.h"

#include <memory>
#include <string>
#include "ArraySlice.h"
#include "Board.h"
#include "Button.h"
#include "Collision.h"
#include "Contracts.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new gate piece at the given position and with
/// the given associated buttons.
/// \post ensure(this->CheckInvariants());
Gate::Gate(Vector2<int> Position, std::string Name, stdx::ArraySlice<std::shared_ptr<Button>> AssociatedButtons)
{
    this->SetPosition(Position);
    this->SetName(Name);
    this->SetAssociatedButtons(AssociatedButtons);
    this->SetObstacleType("poort");
    this->SetMovable(false);
    ensure(this->CheckInvariants());
}

/// \brief Figures out if all of this gate's buttons are in the given
/// board.
/// \pre require(this->CheckInvariants());
bool Gate::CheckButtonsInBoard(std::shared_ptr<Board> Scene) const
{
    require(this->CheckInvariants());
    for (auto& item : this->GetAssociatedButtons())
        if (!Scene->HasPiece(item))
            return false;

    return true;
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool Gate::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = !this->OverlapsWithButtons();
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
/// \pre require(this->CheckButtonsInBoard(Event.GetScene()));
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
bool Gate::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    require(this->CheckButtonsInBoard(Event.GetScene()));
    require(this->CheckInvariants());
    bool result = this->IsOpened(Event.GetScene());
    ensure(this->CheckInvariants());
    return result;
}

/// \brief Determines whether the given button is one of this gate's
/// associated buttons.
/// \pre require(this->CheckInvariants());
bool Gate::IsAssociatedButton(const Button* Piece) const
{
    require(this->CheckInvariants());
    for (auto& item : this->GetAssociatedButtons())
        if (item.get() == Piece)
            return true;

    return false;
}

/// \brief Figures out whether the gate is currently in an opened
/// state.
/// \pre require(this->CheckButtonsInBoard(Scene));
/// \pre require(this->CheckInvariants());
bool Gate::IsOpened(std::shared_ptr<Board> Scene) const
{
    require(this->CheckButtonsInBoard(Scene));
    require(this->CheckInvariants());
    for (auto& item : this->GetAssociatedButtons())
        if (!Scene->GetItem(item->GetPosition())->GetIsTerrain())
            return true;

    return false;
}

/// \brief Figures out whether this gate overlaps with its own
/// buttons.
/// \pre require(this->CheckInvariants());
bool Gate::OverlapsWithButtons() const
{
    require(this->CheckInvariants());
    for (auto& item : this->GetAssociatedButtons())
        if (item->GetPosition() == this->GetPosition())
            return true;

    return false;
}

/// \brief Gets this gate's associated buttons.
/// \pre require(this->CheckInvariants());
stdx::ArraySlice<std::shared_ptr<Button>> Gate::GetAssociatedButtons() const
{
    require(this->CheckInvariants());
    return this->AssociatedButtons_value;
}

/// \brief Sets this gate's associated buttons.
void Gate::SetAssociatedButtons(stdx::ArraySlice<std::shared_ptr<Button>> value)
{
    this->AssociatedButtons_value = value;
}

/// \brief Gets a boolean value that indicates whether this piece is a
/// terrain piece, i.e. it can share its position with another
/// piece.
/// \pre require(this->CheckInvariants());
bool Gate::GetIsTerrain() const
{
    require(this->CheckInvariants());
    return true;
}

/// \brief Sets the gate's name.
void Gate::SetName(std::string value)
{
    this->Name_value = value;
}

/// \brief Gets the gate's name.
/// \pre require(this->CheckInvariants());
std::string Gate::GetName() const
{
    require(this->CheckInvariants());
    return this->Name_value;
}