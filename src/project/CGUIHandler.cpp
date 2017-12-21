#include "CGUIHandler.h"

#include <memory>
#include <ostream>
#include <string>
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "ICommand.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "PieceUIHandlerBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new CG UI handler that outputs to the given
/// output stream.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
CGUIHandler::CGUIHandler(std::ostream* outputStream)
    : PieceUIHandlerBase(outputStream), NrFigures(0)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Applies a command to the board.
/// \pre require(Command != nullptr);
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
    require(Command != nullptr);
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    Command->Execute(this->board);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given barrel piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayBarrel(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, -0.5, "Cylinder", 0.7, 0.4, 0.1, 
                      0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a button piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayButton(std::shared_ptr<Button> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, -0.5, "Cylinder", 0.7, 0.7, 0.1, 
                      0.2);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays an unknown piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayDefault(std::shared_ptr<PieceBase> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, 0.0, "Cube", 1.0, 1.0, 1.0, 0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays an empty cell.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayEmpty(Vector2<int> Position)
{
    require(this->CheckInvariants());
    this->WriteFloor(Position);
    ensure(this->CheckInvariants());
}

/// \brief Displays a footer.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayFooter()
{
    require(this->CheckInvariants());
    *this->outputStream << "[General]\n";
    *this->outputStream << "size = 1024\n";
    *this->outputStream << "shadowMask = 1024\n";
    *this->outputStream << "shadowEnabled = TRUE\n";
    *this->outputStream << "backgroundcolor = (0, 0, 0)\n";
    *this->outputStream << "type = \"LightedZBuffering\"\n";
    *this->outputStream << "nrLights = 1\n";
    *this->outputStream << "eye = (30, 10, 100)\n";
    *this->outputStream << 
        "nrFigures = " << this->NrFigures << "\n";
    *this->outputStream << "[Light0]\n";
    *this->outputStream << "infinity = FALSE\n";
    *this->outputStream << "location = (8, 8, 30)\n";
    *this->outputStream << "ambientLight = (1, 1, 1)\n";
    *this->outputStream << "diffuseLight = (1, 1, 1)\n";
    *this->outputStream << "specularLight = (1, 1, 1)\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayGate(std::shared_ptr<Gate> Piece, bool IsOpened)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    if (!IsOpened)
    {
        this->WriteFigure(Piece, -0.15, "Cube", 0.0, 0.6, 0.6, 0.96);
        this->WriteFloor(Piece);
    }
    else
    {
        this->WriteFigure(Piece, -1.0, "Cube", 0.0, 0.6, 0.6, 0.96);
    }
    ensure(this->CheckInvariants());
}

/// \brief Displays a goal piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayGoal(std::shared_ptr<Goal> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, 0.0, "Octahedron", 0.4, 1.0, 0.2, 
                      0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a header.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayHeader()
{
    require(this->CheckInvariants());
    this->NrFigures = 0;
    ensure(this->CheckInvariants());
}

/// \brief Displays the given monster piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayMonster(std::shared_ptr<Monster> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, 0.0, "Icosahedron", 0.8, 0.4, 0.2, 
                      0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given player piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayPlayer(std::shared_ptr<Player> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, 0.0, "Icosahedron", 0.0, 1.0, 0.2, 
                      0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the end of a row.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayRow()
{
    require(this->CheckInvariants());
    ensure(this->CheckInvariants());
}

/// \brief Displays a trap piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayTrap(std::shared_ptr<Trap> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays the given wall piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayWall(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, 0.0, "Cube", 0.0, 0.4, 1.0, 0.96);
    this->WriteFloor(Piece);
    ensure(this->CheckInvariants());
}

/// \brief Displays a water piece.
/// \pre require(Piece != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CGUIHandler::DisplayWater(std::shared_ptr<Water> Piece)
{
    require(Piece != nullptr);
    require(this->CheckInvariants());
    this->WriteFigure(Piece, -1.25, "Cube", 0.1, 0.1, 0.7, 1.0);
    ensure(this->CheckInvariants());
}

void CGUIHandler::WriteFigure(Vector2<int> Position, double Height, std::string Type, double Red, double Green, double Blue, double Scale)
{
    *this->outputStream << "[Figure" << this->NrFigures << "]\n";
    ++this->NrFigures;
    *this->outputStream << "type = \"" << Type << "\"\n";
    if (Type == "Cylinder" || Type == "Cone")
    {
        *this->outputStream << "n = 30\n";
        *this->outputStream << "height = 2\n";
    }
    else if (Type == "Sphere")
        *this->outputStream << "n = 2\n";

    *this->outputStream << "scale = " << Scale * 0.5 << "\n";
    *this->outputStream << "rotateX = 0\n";
    *this->outputStream << "rotateY = 0\n";
    *this->outputStream << "rotateZ = 0\n";
    *this->outputStream << "center = (" << -Position.Y << ", " << Position.X << ", " << Height << ")\n";
    *this->outputStream << "ambientReflection = (" << Red * 0.3 << ", " << Green * 0.3 << ", " << Blue * 0.3 << ")\n";
    *this->outputStream << "diffuseReflection = (" << Red * 0.7 << ", " << Green * 0.7 << ", " << Blue * 0.7 << ")\n";
    *this->outputStream << 
        "specularReflection = (0.4, 0.4, 0.4)\n";
    *this->outputStream << "reflectionCoefficient = 20\n";
}

void CGUIHandler::WriteFigure(std::shared_ptr<PieceBase> Piece, double Height, std::string Type, double Red, double Green, double Blue, double Scale)
{
    this->WriteFigure(Piece->GetPosition(), Height, Type, Red, 
                      Green, Blue, Scale);
}

void CGUIHandler::WriteFloor(Vector2<int> Position)
{
    this->WriteFigure(Position, -1.0, "Cube", 0.2, 0.2, 0.2, 1.0);
}

void CGUIHandler::WriteFloor(std::shared_ptr<PieceBase> Piece)
{
    this->WriteFloor(Piece->GetPosition());
}