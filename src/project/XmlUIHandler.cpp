#include "XmlUIHandler.h"

#include <cctype>
#include <memory>
#include <ostream>
#include <string>
#include "Actor.h"
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "UnorderedPieceUIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new XML UI handler that writes to the given
/// output stream.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
XmlUIHandler::XmlUIHandler(std::ostream* outputStream)
    : UnorderedPieceUIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given barrel piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayBarrel(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayObstacle(Piece, Piece->GetObstacleType());
    ensure(this->CheckInvariants());
}

/// \brief Displays a button piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayButton(std::shared_ptr<Button> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    std::string gateId = Piece->GetAssociatedGateName(this->board);
    *this->outputStream << "<KNOP id=\"" << gateId << "\" " << 
                           this->showPosition(Piece->GetPosition()) << "/>\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays an unknown piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayDefault(std::shared_ptr<PieceBase> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayObstacle(Piece, "ONBEKEND");
    ensure(this->CheckInvariants());
}

/// \brief Displays a footer.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayFooter()
{
    require(this->CheckInvariants());
    *this->outputStream << "</VELD>" << "\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << "<POORT " << this->showMovable(Piece->GetMovable()) << " " << this->showPosition(Piece->GetPosition()) << ">\n";
    *this->outputStream << 
        this->showStringElement("ID", Piece->GetName()) << "\n";
    *this->outputStream << "</POORT>\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayGoal(std::shared_ptr<Goal> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplaySimpleObstacle(Piece, "DOEL");
    ensure(this->CheckInvariants());
}

/// \brief Displays a header.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayHeader()
{
    require(this->CheckInvariants());
    *this->outputStream << 
        "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n";
    *this->outputStream << "<VELD>\n";
    *this->outputStream << 
        this->showStringElement("NAAM", this->board->GetName()) << 
        "\n";
    *this->outputStream << 
        "<BREEDTE>" << this->board->GetWidth() << "</BREEDTE>\n";
    *this->outputStream << 
        "<LENGTE>" << this->board->GetHeight() << "</LENGTE>\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays the given monster piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayMonster(std::shared_ptr<Monster> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << 
        "<MONSTER " << this->showPosition(Piece->GetPosition()) << 
        ">\n";
    *this->outputStream << 
        this->showStringElement("ID", Piece->GetName()) << "\n";
    *this->outputStream << "</MONSTER>\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays the given obstacle piece.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayObstacle(std::shared_ptr<Obstacle> Piece)
{
    require(this->CheckInvariants());
    this->DisplayObstacle(Piece, Piece->GetObstacleType());
    ensure(this->CheckInvariants());
}

/// \brief Displays an obstacle, which consists of a name tag, a
/// boolean that states whether the piece is movable or not,
/// and a position.
/// \pre require(Piece != nullptr);
void XmlUIHandler::DisplayObstacle(std::shared_ptr<PieceBase> Piece, std::string Name)
{
    require(Piece != nullptr);
    *this->outputStream << "<";
    this->WriteUpperName(Name);
    *this->outputStream << 
        " " << this->showMovable(Piece->GetMovable()) << " " << 
        this->showPosition(Piece->GetPosition()) << "/>\n";
}

/// \brief Displays the given player piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayPlayer(std::shared_ptr<Player> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    *this->outputStream << 
        "<SPELER " << this->showPosition(Piece->GetPosition()) << 
        ">\n";
    *this->outputStream << 
        this->showStringElement("NAAM", Piece->GetName()) << "\n";
    *this->outputStream << "</SPELER>\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays a simple obstacle, which consists of a name tag
/// and a position.
/// \pre require(Piece != nullptr);
void XmlUIHandler::DisplaySimpleObstacle(std::shared_ptr<PieceBase> Piece, std::string Name)
{
    require(Piece != nullptr);
    *this->outputStream << "<";
    this->WriteUpperName(Name);
    *this->outputStream << 
        " " << this->showPosition(Piece->GetPosition()) << "/>\n";
}

/// \brief Displays a trap piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayTrap(std::shared_ptr<Trap> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplaySimpleObstacle(Piece, "VALSTRIK");
    ensure(this->CheckInvariants());
}

/// \brief Displays the given wall piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayWall(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayObstacle(Piece, Piece->GetObstacleType());
    ensure(this->CheckInvariants());
}

/// \brief Displays a water piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void XmlUIHandler::DisplayWater(std::shared_ptr<Water> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->DisplayObstacle(Piece, Piece->GetObstacleType());
    ensure(this->CheckInvariants());
}

/// \brief Gets a string representation of the movable attribute set
/// to the given boolean argument.
std::string XmlUIHandler::showMovable(bool Movable) const
{
    if (Movable)
        return "beweegbaar=\"true\"";
    else
        return "beweegbaar=\"false\"";

}

/// \brief Gets a string representation of the 'x' and 'y' position
/// attributes set to this position.
std::string XmlUIHandler::showPosition(Vector2<int> Position) const
{
    return "x=\"" + std::to_string(Position.X) + "\" y=\"" + 
           std::to_string(Position.Y) + "\"";
}

/// \brief Gets a string representation of an XML element that
/// contains a string.
std::string XmlUIHandler::showStringElement(std::string Key, std::string Value) const
{
    return "<" + Key + ">" + Value + "</" + Key + ">";
}

/// \brief Write an upper-case name to the output stream.
void XmlUIHandler::WriteUpperName(std::string Name)
{
    for (auto& item : Name)
        *this->outputStream << (char)std::toupper((int)item);
}