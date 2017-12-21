#pragma once
#include "Collision.h"
#include "Obstacle.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Describes a trap on the board.
    struct Trap : public Obstacle
    {
        /// \brief Creates a new trap object.
        Trap(Vector2<int> Position);

        /// \brief Attacks this piece. A boolean is returned which indicates
        /// whether it has been destroyed or not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        /// \post ensure(result);
        bool Attack(Collision Event) override;

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        bool Collide(Collision Event) override;
    };
}