#include "Button.h"

#include <memory>
#include <string>
#include "Board.h"
#include "Collision.h"
#include "Contracts.h"
#include "Gate.h"
#include "IsInstance.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Vector2.h"

using namespace Arcade;

/// \brief Creates a new button object at the given position.
Button::Button(Vector2<int> Position)
{
    this->SetPosition(Position);
    this->SetObstacleType("knop");
    this->SetMovable(false);
}

/// \brief Has a piece collide with this piece.
/// A boolean is returned that indicates whether another piece
/// is free to move onto this piece's (previous) position or
/// not.
/// \pre require(Event.GetStaticPiece().get() == this);
bool Button::Collide(Collision Event)
{
    require(Event.GetStaticPiece().get() == this);
    return true;
}

/// \brief Gets this button's associated gate, if any.
/// Otherwise, null.
/// \pre require(Scene != nullptr);
std::shared_ptr<Gate> Button::GetAssociatedGate(std::shared_ptr<Board> Scene) const
{
    require(Scene != nullptr);
    for (auto& item : Scene->GetPieces())
        if (stdx::isinstance<Gate>(item))
        {
            auto gate = std::dynamic_pointer_cast<Gate>(item);
            if (gate->IsAssociatedButton(this))
                return gate;

        }
    return nullptr;
}

/// \brief Gets this button's associated gate's name.
/// If this button does not have an associated gate, the empty
/// string is returned.
/// \pre require(Scene != nullptr);
std::string Button::GetAssociatedGateName(std::shared_ptr<Board> Scene) const
{
    require(Scene != nullptr);
    auto gate = this->GetAssociatedGate(Scene);
    if (gate == nullptr)
        return "";
    else
        return gate->GetName();

}

/// \brief Gets a boolean value that indicates whether this piece is a
/// terrain piece, i.e. it can share its position with another
/// piece.
bool Button::GetIsTerrain() const
{
    return true;
}