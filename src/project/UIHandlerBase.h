#pragma once
#include <memory>
#include <ostream>
#include <vector>
#include "Board.h"
#include "Contracts.h"
#include "Goal.h"
#include "ICommand.h"
#include "IsInstance.h"
#include "IUIHandler.h"
#include "PieceBase.h"
#include "Player.h"

namespace Arcade
{
    /// \brief Defines a base class for UI handlers that use an output
    /// stream.
    class UIHandlerBase : public virtual IUIHandler
    {
    public:
        /// \brief Creates a new UI handler from the given output stream.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        UIHandlerBase(std::ostream* outputStream);

        /// \brief Applies a command to the board.
        /// \pre require(Command != nullptr);
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) override;

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;

        /// \brief Displays the board.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void Display() override = 0;

        /// \brief Initializes the UI handler and displays the board right
        /// away.
        /// \pre require(Value != nullptr);
        /// \pre require(!this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->GetIsInitialized());
        /// \post ensure(this->CheckInvariants());
        void Initialize(std::shared_ptr<Board> Value) override;

        /// \brief Gets a boolean value that indicates if the board contains
        /// any player at this time.
        /// \pre require(this->CheckInvariants());
        bool GetContainsPlayers() const;

        /// \brief Examines the board and figures out whether the game has
        /// ended or not.
        /// \pre require(this->CheckInvariants());
        bool GetHasEnded() const;

        /// \brief Gets a boolean flag that indicates if the UI handler has
        /// been initialized.
        /// \pre require(this->CheckInvariants());
        bool GetIsInitialized() const override;

        /// \brief Gets the UI handler's output stream.
        /// \pre require(this->CheckInvariants());
        std::ostream* GetOutputStream() const;
        /// \brief Sets the UI handler's output stream.
        /// \pre require(value != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void SetOutputStream(std::ostream* value);

        /// \brief Determines whether a player has won, i.e.
        /// whether a player is currently standing on a goal.
        /// \pre require(this->CheckInvariants());
        bool GetPlayerHasWon() const;

        /// \brief Gets the UI handler's board.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<Board> GetScene() const;
    protected:
        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case.
        /// \remark This method should not be called directly.
        /// It should only be called from 'CheckInvariants'.
        virtual bool CheckInvariantsCore() const;
        // {
        //     return this->GetOutputStream() != nullptr;
        // }

        /// \brief The UI handler's board.
        std::shared_ptr<Board> board;
        /// \brief The UI handler's output stream.
        std::ostream* outputStream;
    private:
        mutable bool isCheckingInvariants = false;
    };
}