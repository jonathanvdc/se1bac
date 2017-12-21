#pragma once
#include <string>
#include "Contracts.h"
#include "PieceBase.h"
#include "Vector2.h"

namespace Arcade
{
    class Board;
    class Collision;
    struct Player;

    /// \brief Describes a piece that can move on its own.
    class Actor : public PieceBase
    {
    public:
        /// \brief Creates a new actor instance.
        /// \post ensure(this->CheckInvariants());
        Actor(std::string Name);

        /// \brief Attacks this piece. A boolean is returned which indicates
        /// whether it has been destroyed or not.
        /// \pre require(Event.GetStaticPiece().get() == this);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result);
        /// \post ensure(this->CheckInvariants());
        bool Attack(Collision Event) override;

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;

        /// \brief Gets the actor's name.
        /// \pre require(this->CheckInvariants());
        std::string GetName() const;

        /// \brief Moves the piece to the given target position.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->GetPosition() == Target);
        /// \post ensure(this->CheckInvariants());
        void Move(Vector2<int> Target) override;

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        /// \pre require(this->CheckInvariants());
        bool GetIsTerrain() const override;

        /// \brief Finds out if the given piece can be moved or not.
        /// \pre require(this->CheckInvariants());
        bool GetMovable() const override;
    protected:
        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case.
        /// \remark This method should not be called directly.
        /// It should only be called from 'CheckInvariants'.
        virtual bool CheckInvariantsCore() const;
        // {
        //     return this->GetName() != "";
        // }
    private:
        /// \brief Sets the actor's name.
        void SetName(std::string value);

        mutable bool isCheckingInvariants = false;
        std::string Name_value;
    };
}