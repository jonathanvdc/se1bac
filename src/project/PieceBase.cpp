#include "PieceBase.h"

#include <memory>
#include "Actor.h"
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "Player.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new piece at the origin.
PieceBase::PieceBase()
{
    this->SetPosition(Vector2<int>(0, 0));
}

/// \brief Creates a new piece at the given position.
PieceBase::PieceBase(Vector2<int> Position)
{
    this->SetPosition(Position);
}

/// \brief Attacks this piece. A boolean is returned which indicates
/// whether it has been destroyed or not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool PieceBase::Attack(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    return false;
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool PieceBase::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    return this->CollideAndMove(Event);
}

/// \brief The default collide-and-move behavior for pieces.
/// \pre require(Event.GetStaticPiece().get() == this);
bool PieceBase::CollideAndMove(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    if (!this->GetMovable())
        return false;

    auto goalPos = this->GetPosition() + Event.GetOffset();
    if (!Event.GetScene()->InRange(goalPos))
        return false;

    auto other = Event.GetScene()->GetItem(goalPos);
    if (other != nullptr && !other->Collide(Collision(Event.GetScene(), Event.GetStaticPiece(), other)))
        return false;

    this->Move(this->GetPosition() + Event.GetOffset());
    return true;
}

/// \brief Moves the piece to the given target position.
/// \pre require(this->GetMovable());
/// \post ensure(this->GetPosition() == Target);
void PieceBase::Move(Vector2<int> Target)
{
    require(this->GetMovable());
    this->SetPosition(Target);
    ensure(this->GetPosition() == Target);
}

/// \brief Gets the piece's position.
Vector2<int> PieceBase::GetPosition() const
{
    return this->Position_value;
}

/// \brief Sets the piece's position.
void PieceBase::SetPosition(Vector2<int> value)
{
    this->Position_value = value;
}

/// \brief Gets the piece's X-coordinate.
int PieceBase::GetX() const
{
    return this->GetPosition().X;
}

/// \brief Gets the piece's Y-coordinate.
int PieceBase::GetY() const
{
    return this->GetPosition().Y;
}