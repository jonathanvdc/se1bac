#pragma once
#include <memory>
#include <string>
#include "Board.h"
#include "Collision.h"
#include "Obstacle.h"
#include "Vector2.h"

namespace Arcade
{
    class Gate;

    /// \brief Describes a button on the board.
    /// A button is a terrain piece that gates may use to decide
    /// whether they are in an opened state or not.
    struct Button : public Obstacle
    {
        /// \brief Creates a new button object at the given position.
        Button(Vector2<int> Position);

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        bool Collide(Collision Event) override;

        /// \brief Gets this button's associated gate, if any.
        /// Otherwise, null.
        /// \pre require(Scene != nullptr);
        std::shared_ptr<Gate> GetAssociatedGate(std::shared_ptr<Board> Scene) const;

        /// \brief Gets this button's associated gate's name.
        /// If this button does not have an associated gate, the empty
        /// string is returned.
        /// \pre require(Scene != nullptr);
        std::string GetAssociatedGateName(std::shared_ptr<Board> Scene) const;

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        bool GetIsTerrain() const override;
    };
}