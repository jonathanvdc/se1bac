#pragma once
#include <memory>
#include <ostream>
#include "AttackCommand.h"
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "ICommand.h"
#include "Monster.h"
#include "MoveCommand.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

namespace Arcade
{
    /// \brief Describes a textual UI handler: a UI handler that outputs
    /// text to display the current state of the board.
    class TextUIHandler : public UIHandlerBase
    {
    public:
        /// \brief Creates a new textual UI handler from the given output
        /// stream, error stream and a boolean that indicates whether
        /// commands should be applied right away or stored.
        /// \pre require(outputStream != nullptr);
        /// \pre require(errorStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        TextUIHandler(std::ostream* outputStream, std::ostream* errorStream, bool ApplyCommands);

        /// \brief Applies a command to the board.
        /// \pre require(Command != nullptr);
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) override;

        /// \brief Displays the board.
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void Display() override;

        /// \brief "Freezes" the board: new command will no longer be
        /// applied. The resulting behavior is exactly the same as
        /// setting 'ApplyCommands' to false during object
        /// construction.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(!this->GetApplyCommands());
        /// \post ensure(this->CheckInvariants());
        void Freeze();

        /// \brief Gets a boolean flag that indicates whether incoming
        /// commands will be applied to the board or written to an
        /// output stream.
        /// \pre require(this->CheckInvariants());
        bool GetApplyCommands() const;

        /// \pre require(this->CheckInvariants());
        std::ostream* GetErrorStream() const;
        /// \pre require(value != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void SetErrorStream(std::ostream* value);
    private:
        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case.
        /// \remark This method should not be called directly.
        /// It should only be called from 'CheckInvariants'.
        bool CheckInvariantsCore() const override;
        // {
        //     return this->UIHandlerBase::CheckInvariantsCore() && 
        //            this->GetErrorStream() != nullptr;
        // }

        /// \brief Prints a generic command.
        /// \pre require(Command != nullptr);
        void Display(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command);

        /// \brief Prints a move command.
        /// \pre require(Command != nullptr);
        void Display(std::shared_ptr<MoveCommand> Command);

        /// \brief Prints an attack command.
        /// \pre require(Command != nullptr);
        void Display(std::shared_ptr<AttackCommand> Command);

        /// \brief Prints a piece's information.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<PieceBase> Piece);

        /// \brief Prints a player piece's status.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<Player> Piece);

        /// \brief Prints a monster piece's status.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<Monster> Piece);

        /// \brief Prints a gate piece's status.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<Gate> Piece);

        /// \brief Prints a button piece's status.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->GetIsInitialized());
        void Display(std::shared_ptr<Button> Piece);

        /// \brief Prints a water piece's status.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<Water> Piece);

        /// \brief Prints an obstacle piece's status.
        /// \pre require(Piece != nullptr);
        void Display(std::shared_ptr<Obstacle> Piece);

        /// \brief Prints an offset.
        void DisplayOffset(Vector2<int> Offset);

        /// \brief Sets a boolean flag that indicates whether incoming
        /// commands will be applied to the board or written to an
        /// output stream.
        void SetApplyCommands(bool value);

        bool ApplyCommands_value = false;
        std::ostream* errorStream;
    };
}