#include "HtmlUIHandler.h"

#include <memory>
#include <ostream>
#include <string>
#include "Board.h"
#include "Button.h"
#include "Contracts.h"
#include "Gate.h"
#include "Goal.h"
#include "IsInstance.h"
#include "Monster.h"
#include "Obstacle.h"
#include "PieceBase.h"
#include "Player.h"
#include "Trap.h"
#include "UIHandlerBase.h"
#include "Water.h"

using namespace Arcade;

/// \brief Creates a new HTML UI handler.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
HtmlUIHandler::HtmlUIHandler(std::ostream* outputStream)
    : UIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Displays the board.
/// \pre require(this->GetIsInitialized());
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void HtmlUIHandler::Display()
{
    require(this->GetIsInitialized());
    require(this->CheckInvariants());
    *this->outputStream << "<!DOCTYPE html>" << "\n";
    *this->outputStream << "<html>" << "\n";
    *this->outputStream << "<head>" << "\n";
    *this->outputStream << "<style>" << "\n";
    *this->outputStream << 
        "td {" << "\n" << "text-align: center;" << "\n" << "}" << 
        "\n";
    *this->outputStream << ".water {" << "\n" << "background-color: lightblue;" << "\n" << "}" << "\n";
    *this->outputStream << ".player {" << "\n" << "background-color: yellow;" << "\n" << "}" << "\n";
    *this->outputStream << ".monster {" << "\n" << "background-color: orange;" << "\n" << "}" << "\n";
    *this->outputStream << ".goal {" << "\n" << "background-color: lightgreen;" << "\n" << "}" << "\n";
    *this->outputStream << ".trap {" << "\n" << "background-color: darkred;" << "\n" << "}" << "\n";
    *this->outputStream << ".button {" << "\n" << "background-color: purple;" << "\n" << "}" << "\n";
    *this->outputStream << ".obstacle {" << "\n" << "background-color: gray;" << "\n" << "}" << "\n";
    *this->outputStream << ".movableobstacle {" << "\n" << 
                           "background-color: lightgray;" << "\n" << "}" << "\n";
    *this->outputStream << 
        ".gate {" << "\n" << "background-color: brown;" << "\n" << 
        "}" << "\n";
    *this->outputStream << "</style>" << "\n";
    *this->outputStream << "</head>" << "\n";
    *this->outputStream << "<body>" << "\n";
    *this->outputStream << 
        "<table style=\"width:100%\">" << "\n";
    for (int y = this->board->GetHeight() - 1; y >= 0; --y)
    {
        *this->outputStream << "<tr>" << "\n";
        for (int x = 0; x < this->board->GetWidth(); ++x)
            *this->outputStream << 
                this->showPiece(this->board->GetItem(x, y));
        *this->outputStream << "</tr>" << "\n";
    }
    *this->outputStream << "</table>" << "\n";
    *this->outputStream << "</body>" << "\n";
    *this->outputStream << "</html>" << "\n";
    ensure(this->CheckInvariants());
}

/// \brief Displays the given piece.
std::string HtmlUIHandler::showPiece(std::shared_ptr<PieceBase> piece)
{
    if (piece == nullptr)
        return "<td/>";
    else if (stdx::isinstance<Player>(piece))
        return "<td class=\"player\">Y</td>";
    else if (stdx::isinstance<Goal>(piece))
        return "<td class=\"goal\">X</td>";
    else if (stdx::isinstance<Water>(piece))
        return "<td class=\"water\">~</td>";
    else if (stdx::isinstance<Button>(piece))
        return "<td class=\"button\">.</td>";
    else if (stdx::isinstance<Gate>(piece))
    {
        if (std::dynamic_pointer_cast<Gate>(piece)->IsOpened(this->board))
            return "<td class=\"gate\">| |</td>";
        else
            return "<td class=\"gate\">|=|</td>";

    }
    else if (stdx::isinstance<Monster>(piece))
        return "<td class=\"monster\">(V)(;,,;)(V)</td>";
    else if (stdx::isinstance<Trap>(piece))
        return "<td class=\"trap\">\\^/</td>";
    else if (stdx::isinstance<Obstacle>(piece))
    {
        auto obs = std::dynamic_pointer_cast<Obstacle>(piece);
        std::string name;
        if (obs->GetObstacleType() == "ton")
            name = "O";
        else if (obs->GetObstacleType() == "muur")
            name = "#";
        else
            name = "?";

        if (obs->GetMovable())
            return "<td class=\"movableobstacle\">" + name + "</td>";
        else
            return "<td class=\"obstacle\">" + name + "</td>";

    }
    return "<td>?</td>";
}