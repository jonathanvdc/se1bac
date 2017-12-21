#include "Player.h"

#include <string>
#include "Actor.h"
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "IsInstance.h"
#include "Monster.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new player instance from the given name.
/// \pre require(Name != "");
/// \post ensure(this->CheckInvariants());
Player::Player(Vector2<int> Position, std::string Name)
    : Actor(Name)
{
    require(Name != "");
    this->SetPosition(Position);
    ensure(this->CheckInvariants());
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
bool Player::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    require(this->CheckInvariants());
    if (stdx::isinstance<Monster>(Event.GetMovingPiece()))
    {
        bool result = Event.GetScene()->RemovePiece(Event.GetStaticPiece());
        ensure(this->CheckInvariants());
        return result;
    }
    else
    {
        bool result = this->CollideAndMove(Event);
        ensure(this->CheckInvariants());
        return result;
    }
}