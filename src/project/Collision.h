#pragma once
#include <memory>
#include "Contracts.h"
#include "Vector2.h"

namespace Arcade
{
    class Actor;
    class Board;
    class PieceBase;
    struct Player;

    /// \brief Represents a collision of two pieces on the board.
    class Collision
    {
    public:
        /// \brief Creates a new collision instance from the given arguments.
        /// \pre require(Scene != nullptr);
        /// \pre require(MovingPiece != nullptr);
        /// \pre require(StaticPiece != nullptr);
        /// \pre require(Scene->HasPiece(MovingPiece));
        /// \pre require(Scene->HasPiece(StaticPiece));
        /// \post ensure(this->CheckInvariants());
        Collision(std::shared_ptr<Board> Scene, std::shared_ptr<PieceBase> MovingPiece, std::shared_ptr<PieceBase> StaticPiece);

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;
        // {
        //     if (!this->isCheckingInvariants)
        //     {
        //         this->isCheckingInvariants = true;
        //         bool result = this->GetScene() != nullptr && 
        //                       this->GetMovingPiece() != nullptr && 
        //                       this->GetStaticPiece() != nullptr;
        //         this->isCheckingInvariants = false;
        //         return result;
        //     }
        //     return true;
        // }

        /// \brief Gets the piece that moves and encounters another piece.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<PieceBase> GetMovingPiece() const;

        /// \brief Gets the board where the collision takes place.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<Board> GetScene() const;

        /// \brief Gets the piece the moving piece collides with.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<PieceBase> GetStaticPiece() const;

        /// \brief Calculates the offset between the static piece and the
        /// moving piece.
        /// \pre require(this->CheckInvariants());
        Vector2<int> GetOffset() const;
    private:
        /// \brief Sets the piece that moves and encounters another piece.
        void SetMovingPiece(std::shared_ptr<PieceBase> value);

        /// \brief Sets the board where the collision takes place.
        void SetScene(std::shared_ptr<Board> value);

        /// \brief Sets the piece the moving piece collides with.
        void SetStaticPiece(std::shared_ptr<PieceBase> value);

        mutable bool isCheckingInvariants = false;
        std::shared_ptr<PieceBase> MovingPiece_value;
        std::shared_ptr<Board> Scene_value;
        std::shared_ptr<PieceBase> StaticPiece_value;
    };
}