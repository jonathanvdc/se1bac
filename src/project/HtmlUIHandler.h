#pragma once
#include <memory>
#include <ostream>
#include <string>
#include "PieceBase.h"
#include "UIHandlerBase.h"

namespace Arcade
{
    /// \brief Defines a UI handler that outputs color-coded HTML
    /// content.
    class HtmlUIHandler : public UIHandlerBase
    {
    public:
        /// \brief Creates a new HTML UI handler.
        /// \pre require(outputStream != nullptr);
        /// \post ensure(this->CheckInvariants());
        HtmlUIHandler(std::ostream* outputStream);

        /// \brief Displays the board.
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void Display() override;
    private:
        /// \brief Displays the given piece.
        std::string showPiece(std::shared_ptr<PieceBase> piece);
    };
}