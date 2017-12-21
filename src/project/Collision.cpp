#include "Collision.h"

#include <memory>
#include "Actor.h"
#include "Board.h"
#include "Contracts.h"
#include "PieceBase.h"
#include "Player.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new collision instance from the given arguments.
/// \pre require(Scene != nullptr);
/// \pre require(MovingPiece != nullptr);
/// \pre require(StaticPiece != nullptr);
/// \pre require(Scene->HasPiece(MovingPiece));
/// \pre require(Scene->HasPiece(StaticPiece));
/// \post ensure(this->CheckInvariants());
Collision::Collision(std::shared_ptr<Board> Scene, std::shared_ptr<PieceBase> MovingPiece, std::shared_ptr<PieceBase> StaticPiece)
{
    require(Scene != nullptr);
    require(MovingPiece != nullptr);
    require(StaticPiece != nullptr);
    require(Scene->HasPiece(MovingPiece));
    require(Scene->HasPiece(StaticPiece));
    this->SetScene(Scene);
    this->SetMovingPiece(MovingPiece);
    this->SetStaticPiece(StaticPiece);
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool Collision::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->GetScene() != nullptr && 
                      this->GetMovingPiece() != nullptr && 
                      this->GetStaticPiece() != nullptr;
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Gets the piece that moves and encounters another piece.
/// \pre require(this->CheckInvariants());
std::shared_ptr<PieceBase> Collision::GetMovingPiece() const
{
    require(this->CheckInvariants());
    return this->MovingPiece_value;
}

/// \brief Sets the piece that moves and encounters another piece.
void Collision::SetMovingPiece(std::shared_ptr<PieceBase> value)
{
    this->MovingPiece_value = value;
}

/// \brief Calculates the offset between the static piece and the
/// moving piece.
/// \pre require(this->CheckInvariants());
Vector2<int> Collision::GetOffset() const
{
    require(this->CheckInvariants());
    return this->GetStaticPiece()->GetPosition() - 
           this->GetMovingPiece()->GetPosition();
}

/// \brief Gets the board where the collision takes place.
/// \pre require(this->CheckInvariants());
std::shared_ptr<Board> Collision::GetScene() const
{
    require(this->CheckInvariants());
    return this->Scene_value;
}

/// \brief Sets the board where the collision takes place.
void Collision::SetScene(std::shared_ptr<Board> value)
{
    this->Scene_value = value;
}

/// \brief Gets the piece the moving piece collides with.
/// \pre require(this->CheckInvariants());
std::shared_ptr<PieceBase> Collision::GetStaticPiece() const
{
    require(this->CheckInvariants());
    return this->StaticPiece_value;
}

/// \brief Sets the piece the moving piece collides with.
void Collision::SetStaticPiece(std::shared_ptr<PieceBase> value)
{
    this->StaticPiece_value = value;
}