#include "TextUIHandler.h"

#include <memory>
#include <ostream>
#include "Actor.h"
#include "AttackCommand.h"
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "ICommand.h"
#include "IsInstance.h"
#include "Monster.h"
#include "MoveCommand.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "UIHandlerBase.h"
#include "Vector2.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new textual UI handler from the given output
/// stream, error stream and a boolean that indicates whether
/// commands should be applied right away or stored.
/// \pre require(outputStream != nullptr);
/// \pre require(errorStream != nullptr);
/// \post ensure(this->CheckInvariants());
TextUIHandler::TextUIHandler(std::ostream* outputStream, std::ostream* errorStream, bool ApplyCommands)
    : UIHandlerBase(outputStream), errorStream(errorStream)
{
    require(outputStream != nullptr);
    require(errorStream != nullptr);
    this->SetApplyCommands(ApplyCommands);
    ensure(this->CheckInvariants());
}

/// \brief Applies a command to the board.
/// \pre require(Command != nullptr);
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void TextUIHandler::Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
    require(Command != nullptr);
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    if (this->GetApplyCommands())
    {
        if (!Command->Execute(this->board))
            *this->errorStream << 
                "Commando kon niet uitgevoerd worden.\n\n";

    }
    else
    {
        this->Display(Command);
    }
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case.
/// \remark This method should not be called directly.
/// It should only be called from 'CheckInvariants'.
bool TextUIHandler::CheckInvariantsCore() const
{
    return this->UIHandlerBase::CheckInvariantsCore() && 
           this->GetErrorStream() != nullptr;
}

/// \brief Displays the board.
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void TextUIHandler::Display()
{
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    *this->outputStream << 
        "Het huidige speelveld is " << this->board->GetName() << 
        ":\n";
    *this->outputStream << "Eigenschappen van dit speelveld:\n";
    *this->outputStream << 
        "-Breedte " << this->board->GetWidth() << "\n";
    *this->outputStream << 
        "-Lengte " << this->board->GetHeight();
    for (auto& item : this->board->GetPieces())
    {
        *this->outputStream << "\n\n";
        this->Display(item);
    }
    ensure(this->CheckInvariants());
}

/// \brief Prints a generic command.
/// \pre require(Command != nullptr);
void TextUIHandler::Display(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
    require(Command != nullptr);
    if (stdx::isinstance<MoveCommand>(Command))
    {
        auto moveCmd = std::dynamic_pointer_cast<MoveCommand>(Command);
        this->Display(moveCmd);
    }
    else if (stdx::isinstance<AttackCommand>(Command))
    {
        auto attackCmd = std::dynamic_pointer_cast<AttackCommand>(Command);
        this->Display(attackCmd);
    }
    else
    {
        *this->outputStream << 
            "Een onbekende actie zal nog uitgevoerd worden.";
    }
    *this->outputStream << "\n\n";
}

/// \brief Prints a move command.
/// \pre require(Command != nullptr);
void TextUIHandler::Display(std::shared_ptr<MoveCommand> Command)
{
    require(Command != nullptr);
    if (stdx::isinstance<Player>(Command->GetTarget()))
        *this->outputStream << "Speler ";
    else
        *this->outputStream << "Monster ";

    *this->outputStream << Command->GetTarget()->GetName() << 
                           " zal volgende beweging nog uitvoeren:\n";
    this->DisplayOffset(Command->GetOffset());
}

/// \brief Prints an attack command.
/// \pre require(Command != nullptr);
void TextUIHandler::Display(std::shared_ptr<AttackCommand> Command)
{
    require(Command != nullptr);
    if (stdx::isinstance<Player>(Command->GetTarget()))
        *this->outputStream << "Speler ";
    else
        *this->outputStream << "Monster ";

    *this->outputStream << Command->GetTarget()->GetName() << 
                           " zal volgende aanval nog uitvoeren:\n";
    this->DisplayOffset(Command->GetOffset());
}

/// \brief Prints a piece's information.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<PieceBase> Piece)
{
    require(Piece != nullptr);
    if (stdx::isinstance<Player>(Piece))
        this->Display(std::dynamic_pointer_cast<Player>(Piece));
    else if (stdx::isinstance<Monster>(Piece))
        this->Display(std::dynamic_pointer_cast<Monster>(Piece));
    else if (stdx::isinstance<Gate>(Piece))
        this->Display(std::dynamic_pointer_cast<Gate>(Piece));
    else if (stdx::isinstance<Button>(Piece))
        this->Display(std::dynamic_pointer_cast<Button>(Piece));
    else if (stdx::isinstance<Water>(Piece))
        this->Display(std::dynamic_pointer_cast<Water>(Piece));
    else if (stdx::isinstance<Obstacle>(Piece))
        this->Display(std::dynamic_pointer_cast<Obstacle>(Piece));
    else
        *this->outputStream << 
            "Er staat een onbekend stuk op positie " << 
            Piece->GetPosition() << ".";

}

/// \brief Prints a player piece's status.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<Player> Piece)
{
    require(Piece != nullptr);
    *this->outputStream << "Speler " << Piece->GetName() << 
                           " bevindt zich in dit speeldveld op positie " << 
                           Piece->GetPosition() << ".";
}

/// \brief Prints a monster piece's status.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<Monster> Piece)
{
    require(Piece != nullptr);
    *this->outputStream << 
        "Er bevindt zich een monster op positie " << 
        Piece->GetPosition() << ".";
}

/// \brief Prints a gate piece's status.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<Gate> Piece)
{
    require(Piece != nullptr);
    *this->outputStream << 
        "Er bevindt zich een poort (met id " << Piece->GetName() << 
        ") op positie " << Piece->GetPosition() << ".";
}

/// \brief Prints a button piece's status.
/// \pre require(Piece != nullptr);
/// \pre require(this->GetIsInitialized());
void TextUIHandler::Display(std::shared_ptr<Button> Piece)
{
    require(Piece != nullptr);
    require(this->GetIsInitialized());
    auto gate = Piece->GetAssociatedGate(this->board);
    if (gate != nullptr)
        *this->outputStream << 
            "Er bevindt zich een knop (gelinkt aan poort " << 
            gate->GetName() << ") op positie " << Piece->GetPosition() << ".";
    else
        *this->outputStream << "Er bevindt zich een knop (niet gelinkt aan een poort) op positie " << Piece->GetPosition() << ".";

}

/// \brief Prints a water piece's status.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<Water> Piece)
{
    require(Piece != nullptr);
    *this->outputStream << 
        "Er bevindt zich " << Piece->GetObstacleType() << 
        " op positie " << Piece->GetPosition() << ".";
}

/// \brief Prints an obstacle piece's status.
/// \pre require(Piece != nullptr);
void TextUIHandler::Display(std::shared_ptr<Obstacle> Piece)
{
    require(Piece != nullptr);
    *this->outputStream << 
        "Er bevindt zich een " << Piece->GetObstacleType() << 
        " op positie " << Piece->GetPosition() << ".";
}

/// \brief Prints an offset.
void TextUIHandler::DisplayOffset(Vector2<int> Offset)
{
    if (Offset.X == 0 && Offset.Y == -1)
        *this->outputStream << "Omlaag";
    else if (Offset.X == 0 && Offset.Y == 1)
        *this->outputStream << "Omhoog";
    else if (Offset.X == 1 && Offset.Y == 0)
        *this->outputStream << "Rechts";
    else if (Offset.X == -1 && Offset.Y == 0)
        *this->outputStream << "Links";
    else
        *this->outputStream << Offset;

}

/// \brief "Freezes" the board: new command will no longer be
/// applied. The resulting behavior is exactly the same as
/// setting 'ApplyCommands' to false during object
/// construction.
/// \pre require(this->CheckInvariants());
/// \post ensure(!this->GetApplyCommands());
/// \post ensure(this->CheckInvariants());
void TextUIHandler::Freeze()
{
    require(this->CheckInvariants());
    this->SetApplyCommands(false);
    ensure(!this->GetApplyCommands());
    ensure(this->CheckInvariants());
}

/// \brief Gets a boolean flag that indicates whether incoming
/// commands will be applied to the board or written to an
/// output stream.
/// \pre require(this->CheckInvariants());
bool TextUIHandler::GetApplyCommands() const
{
    require(this->CheckInvariants());
    return this->ApplyCommands_value;
}

/// \brief Sets a boolean flag that indicates whether incoming
/// commands will be applied to the board or written to an
/// output stream.
void TextUIHandler::SetApplyCommands(bool value)
{
    this->ApplyCommands_value = value;
}

/// \pre require(this->CheckInvariants());
std::ostream* TextUIHandler::GetErrorStream() const
{
    require(this->CheckInvariants());
    return this->errorStream;
}

/// \pre require(value != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void TextUIHandler::SetErrorStream(std::ostream* value)
{
    require(value != nullptr);
    require(this->CheckInvariants());
    this->errorStream = value;
    ensure(this->CheckInvariants());
}