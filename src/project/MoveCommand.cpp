#include "MoveCommand.h"

#include <memory>
#include "Actor.h"
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "ICommand.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new move command instance.
/// \pre require(Target != nullptr);
/// \pre require(Offset != Vector2<int>());
/// \post ensure(this->CheckInvariants());
MoveCommand::MoveCommand(std::shared_ptr<Actor> Target, Vector2<int> Offset)
{
    require(Target != nullptr);
    require(Offset != Vector2<int>());
    this->SetTarget(Target);
    this->SetOffset(Offset);
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool MoveCommand::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->GetTarget() != nullptr && 
                      this->GetOffset() != Vector2<int>();
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Executes the command and returns a boolean that tells if
/// the operation has completed successfully.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
bool MoveCommand::Execute(std::shared_ptr<Board> TargetBoard)
{
    require(this->CheckInvariants());
    auto goalPos = this->GetTarget()->GetPosition() + this->GetOffset();
    if (!TargetBoard->InRange(goalPos))
    {
        bool result = false;
        ensure(this->CheckInvariants());
        return result;
    }
    auto obstacle = TargetBoard->GetItem(goalPos);
    if (obstacle != nullptr)
    {
        Collision collision(TargetBoard, this->GetTarget(), obstacle);
        if (!obstacle->Collide(collision))
        {
            bool result = !TargetBoard->HasPiece(this->GetTarget());
            ensure(this->CheckInvariants());
            return result;
        }
    }
    this->GetTarget()->Move(goalPos);
    bool result = true;
    ensure(this->CheckInvariants());
    return result;
}

/// \brief Gets the move command's move offset.
/// \pre require(this->CheckInvariants());
Vector2<int> MoveCommand::GetOffset() const
{
    require(this->CheckInvariants());
    return this->Offset_value;
}

/// \brief Sets the move command's move offset.
void MoveCommand::SetOffset(Vector2<int> value)
{
    this->Offset_value = value;
}

/// \brief Gets the actor to move.
/// \pre require(this->CheckInvariants());
std::shared_ptr<Actor> MoveCommand::GetTarget() const
{
    require(this->CheckInvariants());
    return this->Target_value;
}

/// \brief Sets the actor to move.
void MoveCommand::SetTarget(std::shared_ptr<Actor> value)
{
    this->Target_value = value;
}