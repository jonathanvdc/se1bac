#pragma once
#include <memory>
#include <ostream>
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "PieceUIHandlerBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

namespace Arcade
{
    /// \brief Describes an ASCII art UI handler: a UI handler that
    /// outputs ASCII art to display the current state of the
    /// board.
    class ASCIIArtUIHandler : public PieceUIHandlerBase
    {
    public:
        /// \brief Creates a new ASCII art UI handler that outputs to the
        /// given output stream. Traps are hidden by default.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        ASCIIArtUIHandler(std::ostream* outputStream);
        /// \brief Creates a new ASCII art UI handler that outputs to the
        /// given output stream. Traps can be hidden or displayed, as
        /// per the 'HideTraps' boolean argument.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        ASCIIArtUIHandler(std::ostream* outputStream, bool HideTraps);

        /// \brief Gets a boolean value that indicates whether traps are to be
        /// displayed or hidden.
        /// \pre require(this->CheckInvariants());
        bool GetHideTraps() const;
    protected:
        /// \brief Displays the given barrel piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayBarrel(std::shared_ptr<Obstacle> Piece) override;

        /// \brief Displays a button piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayButton(std::shared_ptr<Button> Piece) override;

        /// \brief Displays an unknown piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayDefault(std::shared_ptr<PieceBase> Piece) override;

        /// \brief Displays an empty cell.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayEmpty(Vector2<int> Position) override;

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened) override;

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayGoal(std::shared_ptr<Goal> Piece) override;

        /// \brief Displays the given monster piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayMonster(std::shared_ptr<Monster> Piece) override;

        /// \brief Displays the given player piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayPlayer(std::shared_ptr<Player> Piece) override;

        /// \brief Displays the end of a row.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayRow() override;

        /// \brief Displays a trap piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayTrap(std::shared_ptr<Trap> Piece) override;

        /// \brief Displays the given wall piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayWall(std::shared_ptr<Obstacle> Piece) override;

        /// \brief Displays a water piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayWater(std::shared_ptr<Water> Piece) override;
    private:
        /// \brief Sets a boolean value that indicates whether traps are to be
        /// displayed or hidden.
        void SetHideTraps(bool value);

        bool HideTraps_value = false;
    };
}