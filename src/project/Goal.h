#pragma once
#include <memory>
#include "Board.h"
#include "Collision.h"
#include "Obstacle.h"
#include "Player.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Describes the board's goal square.
    /// When the player walks on here, the simulation ends.
    struct Goal : public Obstacle
    {
        /// \brief Creates a new goal piece at the given position.
        Goal(Vector2<int> Position);

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        bool Collide(Collision Event) override;

        /// \brief Figures out whether the given player is standing on this
        /// goal.
        bool IsPlayerVictorious(std::shared_ptr<Board> Scene, std::shared_ptr<Player> Winner) const;

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        bool GetIsTerrain() const override;
    };
}