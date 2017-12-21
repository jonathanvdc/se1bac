#pragma once
#include "Collision.h"
#include "Obstacle.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Describes some water in the game.
    struct Water : public Obstacle
    {
        /// \brief Creates a new water object.
        Water(Vector2<int> Position, bool Movable);

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether this piece
        /// has moved or not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        bool Collide(Collision Event) override;
    };
}