#include "Actor.h"

#include <string>
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "PieceBase.h"
#include "Player.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new actor instance.
/// \post ensure(this->CheckInvariants());
Actor::Actor(std::string Name)
{
    this->SetName(Name);
    ensure(this->CheckInvariants());
}

/// \brief Attacks this piece. A boolean is returned which indicates
/// whether it has been destroyed or not.
/// \pre require(Event.GetStaticPiece().get() == this);
/// \pre require(this->CheckInvariants());
/// \post ensure(result);
/// \post ensure(this->CheckInvariants());
bool Actor::Attack(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    require(this->CheckInvariants());
    bool result = Event.GetScene()->RemovePiece(Event.GetStaticPiece());
    ensure(result);
    ensure(this->CheckInvariants());
    return result;
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool Actor::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->CheckInvariantsCore();
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case.
/// \remark This method should not be called directly.
/// It should only be called from 'CheckInvariants'.
bool Actor::CheckInvariantsCore() const
{
    return this->GetName() != "";
}

/// \brief Moves the piece to the given target position.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->GetPosition() == Target);
/// \post ensure(this->CheckInvariants());
void Actor::Move(Vector2<int> Target)
{
    require(this->CheckInvariants());
    this->SetPosition(Target);
    ensure(this->GetPosition() == Target);
    ensure(this->CheckInvariants());
}

/// \brief Gets a boolean value that indicates whether this piece is a
/// terrain piece, i.e. it can share its position with another
/// piece.
/// \pre require(this->CheckInvariants());
bool Actor::GetIsTerrain() const
{
    require(this->CheckInvariants());
    return false;
}

/// \brief Finds out if the given piece can be moved or not.
/// \pre require(this->CheckInvariants());
bool Actor::GetMovable() const
{
    require(this->CheckInvariants());
    return false;
}

/// \brief Gets the actor's name.
/// \pre require(this->CheckInvariants());
std::string Actor::GetName() const
{
    require(this->CheckInvariants());
    return this->Name_value;
}

/// \brief Sets the actor's name.
void Actor::SetName(std::string value)
{
    this->Name_value = value;
}