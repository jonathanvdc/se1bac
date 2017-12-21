#pragma once
#include <string>
#include "PieceBase.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief Describes an obstacle on the board.
    class Obstacle : public PieceBase
    {
    public:
        /// \brief Creates a new obstacle object based on the given
        /// arguments.
        Obstacle(Vector2<int> Position, std::string ObstacleType, bool Movable);

        /// \brief Finds out if the given piece can be moved or not.
        bool GetMovable() const override;

        /// \brief Gets this obstacle's obstacle type.
        std::string GetObstacleType() const;

        /// \brief Gets a boolean value that indicates whether this piece is a
        /// terrain piece, i.e. it can share its position with another
        /// piece.
        virtual bool GetIsTerrain() const override;
    protected:
        /// \brief Creates a new obstacle object.
        Obstacle();

        void SetMovable(bool value);

        /// \brief Sets this obstacle's obstacle type.
        void SetObstacleType(std::string value);
    private:
        bool Movable_value = false;
        std::string ObstacleType_value;
    };
}