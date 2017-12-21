#pragma once
#include <memory>
#include "Actor.h"
#include "Board.h"
#include "Contracts.h"
#include "ICommand.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Represents a command that moves an actor by a given
    /// offset.
    class MoveCommand : public virtual ICommand<std::shared_ptr<Board>>
    {
    public:
        /// \brief Creates a new move command instance.
        /// \pre require(Target != nullptr);
        /// \pre require(Offset != Vector2<int>());
        /// \post ensure(this->CheckInvariants());
        MoveCommand(std::shared_ptr<Actor> Target, Vector2<int> Offset);

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;
        // {
        //     if (!this->isCheckingInvariants)
        //     {
        //         this->isCheckingInvariants = true;
        //         bool result = this->GetTarget() != nullptr && 
        //                       this->GetOffset() != Vector2<int>();
        //         this->isCheckingInvariants = false;
        //         return result;
        //     }
        //     return true;
        // }

        /// \brief Executes the command and returns a boolean that tells if
        /// the operation has completed successfully.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        bool Execute(std::shared_ptr<Board> TargetBoard) override;

        /// \brief Gets the move command's move offset.
        /// \pre require(this->CheckInvariants());
        Vector2<int> GetOffset() const;

        /// \brief Gets the actor to move.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<Actor> GetTarget() const;
    private:
        /// \brief Sets the move command's move offset.
        void SetOffset(Vector2<int> value);

        /// \brief Sets the actor to move.
        void SetTarget(std::shared_ptr<Actor> value);

        mutable bool isCheckingInvariants = false;
        Vector2<int> Offset_value;
        std::shared_ptr<Actor> Target_value;
    };
}