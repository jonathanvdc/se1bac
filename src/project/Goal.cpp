#include "Goal.h"

#include <memory>
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new goal piece at the given position.
Goal::Goal(Vector2<int> Position)
{
    this->SetPosition(Position);
    this->SetObstacleType("doel");
    this->SetMovable(false);
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool Goal::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    return true;
}

/// \brief Figures out whether the given player is standing on this
/// goal.
bool Goal::IsPlayerVictorious(std::shared_ptr<Board> Scene, std::shared_ptr<Player> Winner) const
{
    return Scene->GetItem(this->GetPosition()) == Winner;
}

/// \brief Gets a boolean value that indicates whether this piece is a
/// terrain piece, i.e. it can share its position with another
/// piece.
bool Goal::GetIsTerrain() const
{
    return true;
}