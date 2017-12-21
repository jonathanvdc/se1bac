#include "Obstacle.h"

#include <string>
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new obstacle object.
Obstacle::Obstacle()
{ }

/// \brief Creates a new obstacle object based on the given
/// arguments.
Obstacle::Obstacle(Vector2<int> Position, std::string ObstacleType, bool Movable)
{
    this->SetPosition(Position);
    this->SetObstacleType(ObstacleType);
    this->SetMovable(Movable);
}

/// \brief Gets a boolean value that indicates whether this piece is a
/// terrain piece, i.e. it can share its position with another
/// piece.
bool Obstacle::GetIsTerrain() const
{
    return false;
}

void Obstacle::SetMovable(bool value)
{
    this->Movable_value = value;
}

/// \brief Finds out if the given piece can be moved or not.
bool Obstacle::GetMovable() const
{
    return this->Movable_value;
}

/// \brief Sets this obstacle's obstacle type.
void Obstacle::SetObstacleType(std::string value)
{
    this->ObstacleType_value = value;
}

/// \brief Gets this obstacle's obstacle type.
std::string Obstacle::GetObstacleType() const
{
    return this->ObstacleType_value;
}