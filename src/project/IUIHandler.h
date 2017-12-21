#pragma once
#include <memory>
#include "Board.h"
#include "ICommand.h"

namespace Arcade
{
    /// \brief Defines a common interface for UI handlers: objects that
    /// manage and display the state of a board.
    /// \remark This interface is not particularly clear about its
    /// preconditions and postconditions.
    /// This is by design: IUIHandler objects are rarely (if ever)
    /// used by this interface. Classes like UIHandlerBase, which
    /// implement this interface, should be used instead.
    /// This interface exists mainly to prevent API divergence of
    /// the UI handler types.
    struct IUIHandler
    {
        /// \brief Applies a command to the board.
        virtual void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) = 0;

        /// \brief Displays the board.
        virtual void Display() = 0;

        /// \brief Initializes the UI handler and displays the board right
        /// away.
        virtual void Initialize(std::shared_ptr<Board> Value) = 0;

        /// \brief Gets a boolean flag that indicates whether the UI handler
        /// has been initialized.
        virtual bool GetIsInitialized() const = 0;
    };
}