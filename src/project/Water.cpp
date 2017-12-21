#include "Water.h"

#include <memory>
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "IsInstance.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new water object.
Water::Water(Vector2<int> Position, bool Movable)
{
    this->SetPosition(Position);
    this->SetMovable(Movable);
    this->SetObstacleType("water");
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether this piece
/// has moved or not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool Water::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    auto mp = Event.GetMovingPiece();
    auto sp = Event.GetStaticPiece();
    auto scene = Event.GetScene();
    if (stdx::isinstance<Obstacle>(mp))
    {
        scene->RemovePiece(mp);
        scene->RemovePiece(sp);
        return true;
    }
    scene->RemovePiece(mp);
    return false;
}