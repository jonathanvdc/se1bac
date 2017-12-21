#pragma once
#include <ostream>
#include "PieceUIHandlerBase.h"

namespace Arcade
{
    /// \brief Defines a base class for unordered UI handlers that use an
    /// output stream and write items based on their type, without
    /// any particular order.
    struct UnorderedPieceUIHandlerBase : public PieceUIHandlerBase
    {
        /// \brief Creates a new UI handler from the given output stream.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        UnorderedPieceUIHandlerBase(std::ostream* outputStream);

        /// \brief Displays the board.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        virtual void Display() override;
    };
}