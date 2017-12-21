#pragma once
#include "Vector2.h"

namespace Arcade
{
    class Actor;
    class Board;
    class Collision;
    struct Player;

    /// \brief A base class for pieces on the board.
    class PieceBase
    {
    public:
        /// \brief Creates a new piece at the origin.
        PieceBase();
        /// \brief Creates a new piece at the given position.
        PieceBase(Vector2<int> Position);

        /// \brief Attacks this piece. A boolean is returned which indicates
        /// whether it has been destroyed or not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        virtual bool Attack(Collision Event);

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        virtual bool Collide(Collision Event);

        /// \brief Gets the piece's position.
        Vector2<int> GetPosition() const;

        /// \brief Moves the piece to the given target position.
        /// \pre require(this->GetMovable());
        /// \post ensure(this->GetPosition() == Target);
        virtual void Move(Vector2<int> Target);

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        virtual bool GetIsTerrain() const = 0;

        /// \brief Finds out if the given piece can be moved or not.
        virtual bool GetMovable() const = 0;

        /// \brief Gets the piece's X-coordinate.
        int GetX() const;

        /// \brief Gets the piece's Y-coordinate.
        int GetY() const;
    protected:
        /// \brief The default collide-and-move behavior for pieces.
        /// \pre require(Event.GetStaticPiece().get() == this);
        bool CollideAndMove(Collision Event);

        /// \brief Sets the piece's position.
        void SetPosition(Vector2<int> value);
    private:
        Vector2<int> Position_value;
    };
}