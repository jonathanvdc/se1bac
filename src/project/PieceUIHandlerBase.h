#pragma once
#include <memory>
#include <ostream>
#include "Actor.h"
#include "Button.h"
#include "Gate.h"
#include "Goal.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

namespace Arcade
{
    /// \brief Defines a base class for UI handlers that use an output
    /// stream and write items based on their type.
    class PieceUIHandlerBase : public UIHandlerBase
    {
    public:
        /// \brief Creates a new UI handler from the given output stream.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        PieceUIHandlerBase(std::ostream* outputStream);

        /// \brief Displays the board.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void Display() override;
    protected:
        /// \brief Displays an actor piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayActor(std::shared_ptr<Actor> Piece);

        /// \brief Displays the given barrel piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayBarrel(std::shared_ptr<Obstacle> Piece);

        /// \brief Displays a button piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayButton(std::shared_ptr<Button> Piece);

        /// \brief Applies the default display action to the given piece.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayDefault(std::shared_ptr<PieceBase> Piece) = 0;

        /// \brief Displays an empty cell.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayEmpty(Vector2<int> Position);

        /// \brief Displays a footer.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayFooter();

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened);

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayGoal(std::shared_ptr<Goal> Piece);

        /// \brief Displays a header.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayHeader();

        /// \brief Displays the given monster piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayMonster(std::shared_ptr<Monster> Piece);

        /// \brief Displays the given obstacle piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayObstacle(std::shared_ptr<Obstacle> Piece);

        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayPiece(std::shared_ptr<PieceBase> Piece, Vector2<int> Position);

        /// \brief Displays the given player piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayPlayer(std::shared_ptr<Player> Piece);

        /// \brief Displays the end of a row.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayRow();

        /// \brief Displays a trap piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayTrap(std::shared_ptr<Trap> Piece);

        /// \brief Displays the given wall piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayWall(std::shared_ptr<Obstacle> Piece);

        /// \brief Displays a water piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayWater(std::shared_ptr<Water> Piece);
    };
}