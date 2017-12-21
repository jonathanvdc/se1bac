#include "Trap.h"

#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new trap object.
Trap::Trap(Vector2<int> Position)
{
    this->SetPosition(Position);
    this->SetObstacleType("valstrik");
    this->SetMovable(false);
}

/// \brief Attacks this piece. A boolean is returned which indicates
/// whether it has been destroyed or not.
/// \pre require(Event.GetStaticPiece().get() == this);
/// \post ensure(result);
bool Trap::Attack(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    bool result = Event.GetScene()->RemovePiece(Event.GetStaticPiece());
    ensure(result);
    return result;
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool Trap::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    Event.GetScene()->RemovePiece(Event.GetStaticPiece());
    return Event.GetScene()->RemovePiece(Event.GetMovingPiece());
}