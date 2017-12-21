#pragma once
#include <memory>
#include <ostream>
#include <string>
#include "Button.h"
#include "Gate.h"
#include "Goal.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Trap.h"
#include "UnorderedPieceUIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

namespace Arcade
{
    /// \brief A UI handler that outputs XML files which can be parsed by
    /// the XML parser. This type of output handler may be useful
    /// when creating savegames.
    class XmlUIHandler : public UnorderedPieceUIHandlerBase
    {
    public:
        /// \brief Creates a new XML UI handler that writes to the given
        /// output stream.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        XmlUIHandler(std::ostream* outputStream);
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

        /// \brief Displays a footer.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayFooter() override;

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

        /// \brief Displays a header.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayHeader() override;

        /// \brief Displays the given monster piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayMonster(std::shared_ptr<Monster> Piece) override;

        /// \brief Displays the given obstacle piece.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayObstacle(std::shared_ptr<Obstacle> Piece) override;

        /// \brief Displays the given player piece.
        /// \pre require(Piece != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void DisplayPlayer(std::shared_ptr<Player> Piece) override;

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
        /// \brief Displays an obstacle, which consists of a name tag, a
        /// boolean that states whether the piece is movable or not,
        /// and a position.
        /// \pre require(Piece != nullptr);
        void DisplayObstacle(std::shared_ptr<PieceBase> Piece, std::string Name);

        /// \brief Displays a simple obstacle, which consists of a name tag
        /// and a position.
        /// \pre require(Piece != nullptr);
        void DisplaySimpleObstacle(std::shared_ptr<PieceBase> Piece, std::string Name);

        /// \brief Gets a string representation of the movable attribute set
        /// to the given boolean argument.
        std::string showMovable(bool Movable) const;

        /// \brief Gets a string representation of the 'x' and 'y' position
        /// attributes set to this position.
        std::string showPosition(Vector2<int> Position) const;

        /// \brief Gets a string representation of an XML element that
        /// contains a string.
        std::string showStringElement(std::string Key, std::string Value) const;

        /// \brief Write an upper-case name to the output stream.
        void WriteUpperName(std::string Name);
    };
}