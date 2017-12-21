#include "UIHandlerBase.h"

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

using namespace Arcade;

/// \brief Creates a new UI handler from the given output stream.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
UIHandlerBase::UIHandlerBase(std::ostream* outputStream)
    : outputStream(outputStream)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Applies a command to the board.
/// \pre require(Command != nullptr);
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void UIHandlerBase::Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
    require(Command != nullptr);
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    Command->Execute(this->board);
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool UIHandlerBase::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->CheckInvariantsCore();
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case.
/// \remark This method should not be called directly.
/// It should only be called from 'CheckInvariants'.
bool UIHandlerBase::CheckInvariantsCore() const
{
    return this->GetOutputStream() != nullptr;
}

/// \brief Initializes the UI handler and displays the board right
/// away.
/// \pre require(Value != nullptr);
/// \pre require(!this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->GetIsInitialized());
/// \post ensure(this->CheckInvariants());
void UIHandlerBase::Initialize(std::shared_ptr<Board> Value)
{
    require(Value != nullptr);
    require(!this->GetIsInitialized());
    require(this->CheckInvariants());
    this->board = Value;
    this->Display();
    ensure(this->GetIsInitialized());
    ensure(this->CheckInvariants());
}

/// \brief Gets a boolean value that indicates if the board contains
/// any player at this time.
/// \pre require(this->CheckInvariants());
bool UIHandlerBase::GetContainsPlayers() const
{
    require(this->CheckInvariants());
    auto players = this->board->GetPlayers();
    return !players.empty();
}

/// \brief Examines the board and figures out whether the game has
/// ended or not.
/// \pre require(this->CheckInvariants());
bool UIHandlerBase::GetHasEnded() const
{
    require(this->CheckInvariants());
    return !this->GetContainsPlayers() || this->GetPlayerHasWon();
}

/// \brief Gets a boolean flag that indicates if the UI handler has
/// been initialized.
/// \pre require(this->CheckInvariants());
bool UIHandlerBase::GetIsInitialized() const
{
    require(this->CheckInvariants());
    return this->board != nullptr;
}

/// \brief Gets the UI handler's output stream.
/// \pre require(this->CheckInvariants());
std::ostream* UIHandlerBase::GetOutputStream() const
{
    require(this->CheckInvariants());
    return this->outputStream;
}

/// \brief Sets the UI handler's output stream.
/// \pre require(value != nullptr);
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void UIHandlerBase::SetOutputStream(std::ostream* value)
{
    require(value != nullptr);
    require(this->CheckInvariants());
    this->outputStream = value;
    ensure(this->CheckInvariants());
}

/// \brief Determines whether a player has won, i.e.
/// whether a player is currently standing on a goal.
/// \pre require(this->CheckInvariants());
bool UIHandlerBase::GetPlayerHasWon() const
{
    require(this->CheckInvariants());
    for (auto& item : this->board->GetPieces())
        if (stdx::isinstance<Goal>(item))
        {
            auto goal = std::dynamic_pointer_cast<Goal>(item);
            for (auto& player : this->board->GetPlayers())
                if (goal->IsPlayerVictorious(this->board, player))
                    return true;

        }
    return false;
}

/// \brief Gets the UI handler's board.
/// \pre require(this->CheckInvariants());
std::shared_ptr<Board> UIHandlerBase::GetScene() const
{
    require(this->CheckInvariants());
    return this->board;
}