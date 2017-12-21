#pragma once
#include <string>
#include "Actor.h"
#include "Collision.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Describes a monster in the game.
    struct Monster : public Actor
    {
        /// \brief Creates a new monster instance from the given name.
        /// \pre require(Name != "");
        /// \post ensure(this->CheckInvariants());
        Monster(Vector2<int> Position, std::string Name);

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual bool Collide(Collision Event) override;
    };
}