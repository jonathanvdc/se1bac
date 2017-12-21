#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Contracts.h"
#include "Vector2.h"

namespace Arcade
{
    class Actor;
    class Collision;
    class PieceBase;
    struct Player;

    /// \brief Describes a board in the game.
    class Board
    {
    public:
        /// \brief Creates a new board with the given name of the given size.
        /// \pre require(Size.X > 0);
        /// \pre require(Size.Y > 0);
        /// \post ensure(this->CheckInvariants());
        Board(std::string Name, Vector2<int> Size);
        /// \brief Creates a new board with the given name of the given size
        /// containing the given pieces.
        /// \pre require(Size.X > 0);
        /// \pre require(Size.Y > 0);
        /// \post ensure(this->CheckInvariants());
        Board(std::string Name, Vector2<int> Size, std::vector<std::shared_ptr<PieceBase>> Pieces);

        /// \brief Adds a piece to the board.
        /// \pre require(Value->GetIsTerrain() ||
        /// this->GetItem(Value->GetPosition()) == nullptr ||
        /// this->GetItem(Value->GetPosition())->GetIsTerrain());
        /// \pre require(this->InRange(Value->GetPosition()));
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void AddPiece(std::shared_ptr<PieceBase> Value);

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;
        // {
        //     if (!this->isCheckingInvariants)
        //     {
        //         this->isCheckingInvariants = true;
        //         bool result = this->GetSize().X > 0 && this->GetSize().Y > 0;
        //         this->isCheckingInvariants = false;
        //         return result;
        //     }
        //     return true;
        // }

        /// \brief Gets the first actor with the given name.
        /// \pre require(this->HasActor(Name));
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result != nullptr);
        /// \post ensure(this->InRange(result->GetPosition()));
        std::shared_ptr<Actor> GetActor(std::string Name) const;

        /// \brief Gets the first actor with the given name if they can be
        /// found. Otherwise, null.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result == nullptr || this->InRange(result->GetPosition()));
        std::shared_ptr<Actor> GetActorOrNull(std::string Name) const;

        /// \brief Gets the field's name.
        /// \pre require(this->CheckInvariants());
        std::string GetName() const;

        /// \brief Gets all players on the board.
        /// \pre require(this->CheckInvariants());
        std::vector<std::shared_ptr<Player>> GetPlayers() const;

        /// \brief Gets the board's dimensions.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result.X > 0);
        /// \post ensure(result.Y > 0);
        Vector2<int> GetSize() const;

        /// \brief Gets a boolean value that tells if this board contains the
        /// given actor.
        /// \pre require(this->CheckInvariants());
        bool HasActor(std::string Name) const;

        /// \brief Gets a boolean value that tells if this board contains the
        /// given piece.
        /// \pre require(this->CheckInvariants());
        bool HasPiece(std::shared_ptr<PieceBase> Value) const;

        /// \brief Gets a boolean value that indicates whether the given
        /// point is in the board or not.
        /// \pre require(this->CheckInvariants());
        bool InRange(Vector2<int> Point) const;

        /// \brief Removes a piece from the board, and returns a boolean that
        /// tells if the piece has been removed.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(!this->HasPiece(Value));
        /// \post ensure(this->CheckInvariants());
        bool RemovePiece(std::shared_ptr<PieceBase> Value);

        /// \brief Gets the board's height.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result > 0);
        int GetHeight() const;

        /// \brief Find the piece at the given coordinates.
        /// If no piece is found, return null.
        /// If the given position contains one or more terrain pieces
        /// and one other piece, the latter is returned.
        /// \pre require(this->InRange(pos));
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<PieceBase> GetItem(Vector2<int> pos) const;

        /// \brief Find the piece at the given coordinates.
        /// If no piece is found, return null.
        /// \pre require(this->InRange(Vector2<int>(X, Y)));
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<PieceBase> GetItem(int X, int Y) const;

        /// \brief Gets all pieces on the board.
        /// \pre require(this->CheckInvariants());
        std::vector<std::shared_ptr<PieceBase>> GetPieces() const;

        /// \brief Gets the board's width.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(result > 0);
        int GetWidth() const;
    private:
        /// \brief Sets the field's name.
        void SetName(std::string value);

        /// \brief Sets the board's dimensions.
        void SetSize(Vector2<int> value);

        mutable bool isCheckingInvariants = false;
        std::string Name_value;
        std::vector<std::shared_ptr<PieceBase>> pcs;
        Vector2<int> Size_value;
    };
}