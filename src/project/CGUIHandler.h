#pragma once
#include <memory>
#include <ostream>
#include <string>
#include "Board.h"
#include "Button.h"
#include "Gate.h"
#include "Goal.h"
#include "ICommand.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "PieceUIHandlerBase.h"
#include "Player.h"
#include "Trap.h"
#include "Vector2.h"
#include "Water.h"

namespace Arcade
{
    /// \brief Describes a Computer Graphics UI handler: a UI handler
    /// that outputs an .ini file that our own 3D graphics engine
    /// can turn into a bitmap.
    class CGUIHandler : public PieceUIHandlerBase
    {
    public:
        /// \brief Creates a new CG UI handler that outputs to the given
        /// output stream.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        CGUIHandler(std::ostream* outputStream);

        /// \brief Applies a command to the board.
        /// \pre require(Command != nullptr);
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) override;
    protected:
        /// \brief Displays the given barrel piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayBarrel(std::shared_ptr<Obstacle> Piece) override;

        /// \brief Displays a button piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayButton(std::shared_ptr<Button> Piece) override;

        /// \brief Displays an unknown piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayDefault(std::shared_ptr<PieceBase> Piece) override;

        /// \brief Displays an empty cell.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayEmpty(Vector2<int> Position) override;

        /// \brief Displays a footer.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayFooter() override;

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened) override;

        /// \brief Displays a goal piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayGoal(std::shared_ptr<Goal> Piece) override;

        /// \brief Displays a header.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayHeader() override;

        /// \brief Displays the given monster piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayMonster(std::shared_ptr<Monster> Piece) override;

        /// \brief Displays the given player piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayPlayer(std::shared_ptr<Player> Piece) override;

        /// \brief Displays the end of a row.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayRow() override;

        /// \brief Displays a trap piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayTrap(std::shared_ptr<Trap> Piece) override;

        /// \brief Displays the given wall piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayWall(std::shared_ptr<Obstacle> Piece) override;

        /// \brief Displays a water piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void DisplayWater(std::shared_ptr<Water> Piece) override;
    private:
        void WriteFigure(Vector2<int> Position, double Height, std::string Type, double Red, double Green, double Blue, double Scale);

        void WriteFigure(std::shared_ptr<PieceBase> Piece, double Height, std::string Type, double Red, double Green, double Blue, double Scale);

        void WriteFloor(Vector2<int> Position);

        void WriteFloor(std::shared_ptr<PieceBase> Piece);

        /// \brief Counts the number of 3D figures drawn.
        int NrFigures = 0;
    };
}