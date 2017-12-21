#include "UnorderedPieceUIHandlerBase.h"

#include <memory>
#include <ostream>
#include "Board.h"
#include "Contracts.h"
#include "PieceBase.h"
#include "PieceUIHandlerBase.h"
#include "UIHandlerBase.h"

using namespace Arcade;

/// \brief Creates a new UI handler from the given output stream.
/// \pre require(outputStream != nullptr);
/// \post ensure(this->CheckInvariants());
UnorderedPieceUIHandlerBase::UnorderedPieceUIHandlerBase(std::ostream* outputStream)
    : PieceUIHandlerBase(outputStream)
{
    require(outputStream != nullptr);
    ensure(this->CheckInvariants());
}

/// \brief Displays the board.
/// \pre require(this->CheckInvariants());
/// \post ensure(this->CheckInvariants());
void UnorderedPieceUIHandlerBase::Display()
{
    require(this->CheckInvariants());
    this->DisplayHeader();
    for (auto& item : this->board->GetPieces())
        this->DisplayPiece(item, item->GetPosition());
    this->DisplayFooter();
    ensure(this->CheckInvariants());
}