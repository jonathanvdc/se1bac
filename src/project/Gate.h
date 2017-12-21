#pragma once
#include <memory>
#include <string>
#include "ArraySlice.h"
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "Obstacle.h"
#include "Vector2.h"

namespace Arcade
{
    struct Button;

    /// \brief Describes a gate on the board.
    /// Gates use a number of "associated buttons" to decide
    /// whether they are in an opened state or not.
    class Gate : public Obstacle
    {
    public:
        /// \brief Creates a new gate piece at the given position and with
        /// the given associated buttons.
        /// \post ensure(this->CheckInvariants());
        Gate(Vector2<int> Position, std::string Name, stdx::ArraySlice<std::shared_ptr<Button>> AssociatedButtons);

        /// \brief Figures out if all of this gate's buttons are in the given
        /// board.
        /// \pre require(this->CheckInvariants());
        bool CheckButtonsInBoard(std::shared_ptr<Board> Scene) const;

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;
        // {
        //     if (!this->isCheckingInvariants)
        //     {
        //         this->isCheckingInvariants = true;
        //         bool result = !this->OverlapsWithButtons();
        //         this->isCheckingInvariants = false;
        //         return result;
        //     }
        //     return true;
        // }

        /// \brief Has a piece collide with this piece.
        /// A boolean is returned that indicates whether another piece
        /// is free to move onto this piece's (previous) position or
        /// not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        /// \pre require(this->CheckButtonsInBoard(Event.GetScene()));
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        bool Collide(Collision Event) override;

        /// \brief Gets this gate's associated buttons.
        /// \pre require(this->CheckInvariants());
        stdx::ArraySlice<std::shared_ptr<Button>> GetAssociatedButtons() const;

        /// \brief Gets the gate's name.
        /// \pre require(this->CheckInvariants());
        std::string GetName() const;

        /// \brief Determines whether the given button is one of this gate's
        /// associated buttons.
        /// \pre require(this->CheckInvariants());
        bool IsAssociatedButton(const Button* Piece) const;

        /// \brief Figures out whether the gate is currently in an opened
        /// state.
        /// \pre require(this->CheckButtonsInBoard(Scene));
        /// \pre require(this->CheckInvariants());
        bool IsOpened(std::shared_ptr<Board> Scene) const;

        /// \brief Figures out whether this gate overlaps with its own
        /// buttons.
        /// \pre require(this->CheckInvariants());
        bool OverlapsWithButtons() const;

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        /// \pre require(this->CheckInvariants());
        bool GetIsTerrain() const override;
    private:
        /// \brief Sets this gate's associated buttons.
        void SetAssociatedButtons(stdx::ArraySlice<std::shared_ptr<Button>> value);

        /// \brief Sets the gate's name.
        void SetName(std::string value);

        stdx::ArraySlice<std::shared_ptr<Button>> AssociatedButtons_value;
        mutable bool isCheckingInvariants = false;
        std::string Name_value;
    };
}