#include "Board.h"

#include <memory>
#include <string>
#include <vector>
#include "Actor.h"
#include "Collision.h"
#include "Contracts.h"
#include "IsInstance.h"
#include "PieceBase.h"
#include "Player.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new board with the given name of the given size.
/// \pre require(Size.X > 0);
/// \pre require(Size.Y > 0);
/// \post ensure(this->CheckInvariants());
Board::Board(std::string Name, Vector2<int> Size)
{
    require(Size.X > 0);
    require(Size.Y > 0);
    this->SetName(Name);
    this->SetSize(Size);
    this->pcs = std::vector<std::shared_ptr<PieceBase>>();
    ensure(this->CheckInvariants());
}

/// \brief Creates a new board with the given name of the given size
/// containing the given pieces.
/// \pre require(Size.X > 0);
/// \pre require(Size.Y > 0);
/// \post ensure(this->CheckInvariants());
Board::Board(std::string Name, Vector2<int> Size, std::vector<std::shared_ptr<PieceBase>> Pieces)
{
    require(Size.X > 0);
    require(Size.Y > 0);
    this->SetName(Name);
    this->SetSize(Size);
    this->pcs = Pieces;
    ensure(this->CheckInvariants());
}

/// \brief Adds a piece to the board.
/// \pre require(Value->GetIsTerrain() ||
/// this->GetItem(Value->GetPosition()) == nullptr ||
/// this->GetItem(Value->GetPosition())->GetIsTerrain());
/// \pre require(this->InRange(Value->GetPosition()));
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void Board::AddPiece(std::shared_ptr<PieceBase> Value)
{
    require(Value->GetIsTerrain() || 
            this->GetItem(Value->GetPosition()) == nullptr || 
            this->GetItem(Value->GetPosition())->GetIsTerrain());
    require(this->InRange(Value->GetPosition()));
    require(this->CheckInvariants());
    this->pcs.push_back(Value);
    ensure(this->CheckInvariants());
}

/// \brief Checks if this type's invariants are being respected.
/// A boolean value is returned that indicates whether this is
/// indeed the case. This method is publically visible, and can
/// be used to verify an instance's state.
bool Board::CheckInvariants() const
{
    if (!this->isCheckingInvariants)
    {
        this->isCheckingInvariants = true;
        bool result = this->GetSize().X > 0 && this->GetSize().Y > 0;
        this->isCheckingInvariants = false;
        return result;
    }
    return true;
}

/// \brief Gets the first actor with the given name.
/// \pre require(this->HasActor(Name));
/// \pre require(this->CheckInvariants());
/// \post ensure(result != nullptr);
/// \post ensure(this->InRange(result->GetPosition()));
std::shared_ptr<Actor> Board::GetActor(std::string Name) const
{
    require(this->HasActor(Name));
    require(this->CheckInvariants());
    auto result = this->GetActorOrNull(Name);
    ensure(result != nullptr);
    ensure(this->InRange(result->GetPosition()));
    return result;
}

/// \brief Gets the first actor with the given name if they can be
/// found. Otherwise, null.
/// \pre require(this->CheckInvariants());
/// \post ensure(result == nullptr || this->InRange(result->GetPosition()));
std::shared_ptr<Actor> Board::GetActorOrNull(std::string Name) const
{
    require(this->CheckInvariants());
    for (auto& item : this->GetPieces())
        if (stdx::isinstance<Actor>(item))
        {
            auto actor = std::dynamic_pointer_cast<Actor>(item);
            if (actor->GetName() == Name)
            {
                auto result = actor;
                ensure(result == nullptr || this->InRange(result->GetPosition()));
                return result;
            }
        }
    std::shared_ptr<Actor> result = nullptr;
    ensure(result == nullptr || this->InRange(result->GetPosition()));
    return result;
}

/// \brief Gets all players on the board.
/// \pre require(this->CheckInvariants());
std::vector<std::shared_ptr<Player>> Board::GetPlayers() const
{
    require(this->CheckInvariants());
    std::vector<std::shared_ptr<Player>> results;
    for (auto& item : this->GetPieces())
        if (stdx::isinstance<Player>(item))
            results.push_back(std::dynamic_pointer_cast<Player>(item));

    return results;
}

/// \brief Gets a boolean value that tells if this board contains the
/// given actor.
/// \pre require(this->CheckInvariants());
bool Board::HasActor(std::string Name) const
{
    require(this->CheckInvariants());
    return this->GetActorOrNull(Name) != nullptr;
}

/// \brief Gets a boolean value that tells if this board contains the
/// given piece.
/// \pre require(this->CheckInvariants());
bool Board::HasPiece(std::shared_ptr<PieceBase> Value) const
{
    require(this->CheckInvariants());
    for (auto& p : this->GetPieces())
        if (p == Value)
            return true;

    return false;
}

/// \brief Gets a boolean value that indicates whether the given
/// point is in the board or not.
/// \pre require(this->CheckInvariants());
bool Board::InRange(Vector2<int> Point) const
{
    require(this->CheckInvariants());
    return Point.X >= 0 && Point.Y >= 0 && Point.X < this->GetWidth() && Point.Y < this->GetHeight();
}

/// \brief Removes a piece from the board, and returns a boolean that
/// tells if the piece has been removed.
/// \pre require(this->CheckInvariants());
/// \post ensure(!this->HasPiece(Value));
/// \post ensure(this->CheckInvariants());
bool Board::RemovePiece(std::shared_ptr<PieceBase> Value)
{
    require(this->CheckInvariants());
    if (!this->HasPiece(Value))
    {
        bool result = false;
        ensure(!this->HasPiece(Value));
        ensure(this->CheckInvariants());
        return result;
    }
    int i = 0;
    while (this->pcs[i] != Value)
        ++i;
    while (i < (int)this->pcs.size() - 1)
    {
        this->pcs[i] = this->pcs[i + 1];
        ++i;
    }
    this->pcs.pop_back();
    bool result = true;
    ensure(!this->HasPiece(Value));
    ensure(this->CheckInvariants());
    return result;
}

/// \brief Gets the board's height.
/// \pre require(this->CheckInvariants());
/// \post ensure(result > 0);
int Board::GetHeight() const
{
    require(this->CheckInvariants());
    int result = this->GetSize().Y;
    ensure(result > 0);
    return result;
}

/// \brief Find the piece at the given coordinates.
/// If no piece is found, return null.
/// If the given position contains one or more terrain pieces
/// and one other piece, the latter is returned.
/// \pre require(this->InRange(pos));
/// \pre require(this->CheckInvariants());
std::shared_ptr<PieceBase> Board::GetItem(Vector2<int> pos) const
{
    require(this->InRange(pos));
    require(this->CheckInvariants());
    std::shared_ptr<PieceBase> terrainPiece = nullptr;
    for (auto& p : this->GetPieces())
        if (p->GetPosition() == pos)
        {
            if (p->GetIsTerrain())
                terrainPiece = p;
            else
                return p;

        }
    return terrainPiece;
}

/// \brief Find the piece at the given coordinates.
/// If no piece is found, return null.
/// \pre require(this->InRange(Vector2<int>(X, Y)));
/// \pre require(this->CheckInvariants());
std::shared_ptr<PieceBase> Board::GetItem(int X, int Y) const
{
    require(this->InRange(Vector2<int>(X, Y)));
    require(this->CheckInvariants());
    return this->GetItem(Vector2<int>(X, Y));
}

/// \brief Sets the field's name.
void Board::SetName(std::string value)
{
    this->Name_value = value;
}

/// \brief Gets the field's name.
/// \pre require(this->CheckInvariants());
std::string Board::GetName() const
{
    require(this->CheckInvariants());
    return this->Name_value;
}

/// \brief Gets all pieces on the board.
/// \pre require(this->CheckInvariants());
std::vector<std::shared_ptr<PieceBase>> Board::GetPieces() const
{
    require(this->CheckInvariants());
    return this->pcs;
}

/// \brief Gets the board's dimensions.
/// \pre require(this->CheckInvariants());
/// \post ensure(result.X > 0);
/// \post ensure(result.Y > 0);
Vector2<int> Board::GetSize() const
{
    require(this->CheckInvariants());
    auto result = this->Size_value;
    ensure(result.X > 0);
    ensure(result.Y > 0);
    return result;
}

/// \brief Sets the board's dimensions.
void Board::SetSize(Vector2<int> value)
{
    this->Size_value = value;
}

/// \brief Gets the board's width.
/// \pre require(this->CheckInvariants());
/// \post ensure(result > 0);
int Board::GetWidth() const
{
    require(this->CheckInvariants());
    int result = this->GetSize().X;
    ensure(result > 0);
    return result;
}