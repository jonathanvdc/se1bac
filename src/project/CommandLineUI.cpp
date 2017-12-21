#include "CommandLineUI.h"

#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include "Actor.h"
#include "AttackCommand.h"
#include "Board.h"
#include "Contracts.h"
#include "ICommand.h"
#include "InteractiveUIHandler.h"
#include "IParser.h"
#include "MoveCommand.h"
#include "UIHandlerBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new command-line UI handler that outputs to the
/// given output stream, based on the given other UI handler.
/// \pre require(Handler != nullptr);
/// \pre require(inputStream != nullptr);
/// \pre require(MainActor != nullptr);
/// \post ensure(this->CheckInvariants());
CommandLineUI::CommandLineUI(std::istream* inputStream, std::shared_ptr<UIHandlerBase> Handler, std::shared_ptr<Actor> MainActor)
{
    require(Handler != nullptr);
    require(inputStream != nullptr);
    require(MainActor != nullptr);
    this->inputStream = inputStream;
    this->SetHandler(Handler);
    this->SetMainActor(MainActor);
    ensure(this->CheckInvariants());
}

/// \brief Associates the given action parser with the given key.
/// \pre require(Parser != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CommandLineUI::AddActionParser(std::string Key, std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>> Parser)
{
    require(Parser != nullptr);
    require(this->CheckInvariants());
    this->allParsers[Key] = Parser;
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool CommandLineUI::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->GetHandler() != nullptr && 
                      this->inputStream != nullptr && 
                      this->GetMainActor() != nullptr;
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Converts the given direction to an offset.
/// \pre require(this->CheckInvariants());
Vector2<int> CommandLineUI::DirectionToOffset(std::string Direction) const
{
    require(this->CheckInvariants());
    if (Direction == "l")
        return Vector2<int>(-1, 0);
    else if (Direction == "r")
        return Vector2<int>(1, 0);
    else if (Direction == "u")
        return Vector2<int>(0, 1);
    else if (Direction == "d")
        return Vector2<int>(0, -1);
    else
        return Vector2<int>(0, 0);

}

/// \brief Displays the board.
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CommandLineUI::Display()
{
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    this->GetHandler()->Display();
    *this->GetHandler()->GetOutputStream() << "\n";
    ensure(this->CheckInvariants());
}

/// \brief Initializes the UI handler and displays the board right
/// away.
/// \pre require(Value != nullptr);
/// \pre require(!this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->GetIsInitialized());
/// \post ensure(this->CheckInvariants());
void CommandLineUI::Initialize(std::shared_ptr<Board> Value)
{
    require(Value != nullptr);
    require(!this->GetIsInitialized());
    require(this->CheckInvariants());
    this->GetHandler()->Initialize(Value);
    *this->GetHandler()->GetOutputStream() << "\n";
    ensure(this->GetIsInitialized());
    ensure(this->CheckInvariants());
}

/// \brief Logs an error message.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CommandLineUI::LogError(std::string Message)
{
    require(this->CheckInvariants());
    *this->GetHandler()->GetOutputStream() << Message << "\n";
    ensure(this->CheckInvariants());
}

/// \brief Parses an action.
/// \pre require(this->CheckInvariants());
std::shared_ptr<ICommand<std::shared_ptr<Board>>> CommandLineUI::ParseAction(std::string Key, std::string Arg) const
{
    require(this->CheckInvariants());
    auto parser = this->GetActionParsers()[Key];
    if (parser == nullptr)
    {
        *this->GetHandler()->GetOutputStream() << 
            "Onbekend type actie. Bestaande types:\n";
        for (auto& item : this->GetActionParsers())
            *this->GetHandler()->GetOutputStream() << 
                " * " << item.first << "\n";
        return nullptr;
    }
    return (std::shared_ptr<ICommand<std::shared_ptr<Board>>>)parser->Parse(Arg);
}

/// \brief Parses an attack action.
/// \pre require(this->CheckInvariants());
std::shared_ptr<ICommand<std::shared_ptr<Board>>> CommandLineUI::ParseAttack(std::string Arg) const
{
    require(this->CheckInvariants());
    return std::make_shared<AttackCommand>(this->GetMainActor(), 
                                           this->DirectionToOffset(Arg));
}

/// \brief Parses a move action.
/// \pre require(this->CheckInvariants());
std::shared_ptr<ICommand<std::shared_ptr<Board>>> CommandLineUI::ParseMove(std::string Arg) const
{
    require(this->CheckInvariants());
    return std::make_shared<MoveCommand>(this->GetMainActor(), 
                                         this->DirectionToOffset(Arg));
}

/// \brief Plays the game until the player either wins or loses.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void CommandLineUI::PlayGame()
{
    require(this->CheckInvariants());
    while (!this->GetHandler()->GetHasEnded() && this->GetHandler()->GetScene()->HasPiece(this->GetMainActor()))
    {
        auto move = this->ReadAction();
        if (move == nullptr)
            continue;

        this->Apply(move);
    }
    if (this->GetHandler()->GetScene()->HasPiece(this->GetMainActor()))
        *this->GetHandler()->GetOutputStream() << 
            "Gefeliciteerd! Je wint!\n";
    else
        *this->GetHandler()->GetOutputStream() << 
            "Je bent verloren. :(\n";

    ensure(this->CheckInvariants());
}

/// \brief Reads an action from the input stream.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
std::shared_ptr<ICommand<std::shared_ptr<Board>>> CommandLineUI::ReadAction()
{
    require(this->CheckInvariants());
    std::string name;
    *this->inputStream >> name;
    std::string arg;
    *this->inputStream >> arg;
    auto result = this->ParseAction(name, arg);
    ensure(this->CheckInvariants());
    return result;
}

/// \brief Gets the command-line UI's action parsers.
/// \pre require(this->CheckInvariants());
std::unordered_map<std::string, std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>>> CommandLineUI::GetActionParsers() const
{
    require(this->CheckInvariants());
    return this->allParsers;
}

/// \brief Gets the command-line UI's inner UI handler.
/// \pre require(this->CheckInvariants());
std::shared_ptr<UIHandlerBase> CommandLineUI::GetHandler() const
{
    require(this->CheckInvariants());
    return this->Handler_value;
}

/// \brief Sets the command-line UI's inner UI handler.
void CommandLineUI::SetHandler(std::shared_ptr<UIHandlerBase> value)
{
    this->Handler_value = value;
}

/// \brief Gets a boolean flag that indicates whether the UI handler
/// has been initialized.
/// \pre require(this->CheckInvariants());
bool CommandLineUI::GetIsInitialized() const
{
    require(this->CheckInvariants());
    return this->GetHandler()->GetIsInitialized();
}

/// \brief Gets the main actor for this UI dialog.
/// \pre require(this->CheckInvariants());
std::shared_ptr<Actor> CommandLineUI::GetMainActor() const
{
    require(this->CheckInvariants());
    return this->MainActor_value;
}

/// \brief Sets the main actor for this UI dialog.
void CommandLineUI::SetMainActor(std::shared_ptr<Actor> value)
{
    this->MainActor_value = value;
}

/// \brief Gets the interactive UI handler's board.
/// \pre require(this->CheckInvariants());
std::shared_ptr<Board> CommandLineUI::GetScene() const
{
    require(this->CheckInvariants());
    return this->GetHandler()->GetScene();
}