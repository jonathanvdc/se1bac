#pragma once
#include <memory>
#include <string>
#include "Board.h"
#include "ICommand.h"
#include "IUIHandler.h"

namespace Arcade
{
    /// \brief A base class for interactive UI handlers.
    class InteractiveUIHandler : public virtual IUIHandler
    {
    public:
        InteractiveUIHandler();

        /// \brief Applies a command to the board.
        /// \pre require(Command != nullptr);
        /// \pre require(this->GetIsInitialized());
        virtual void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) override;

        /// \brief Displays the board.
        virtual void Display() override = 0;

        /// \brief Initializes the UI handler and displays the board right
        /// away.
        virtual void Initialize(std::shared_ptr<Board> Value) override = 0;

        /// \brief Gets a boolean flag that indicates whether the UI handler
        /// has been initialized.
        virtual bool GetIsInitialized() const override = 0;

        /// \brief Gets the interactive UI handler's board.
        virtual std::shared_ptr<Board> GetScene() const = 0;
    protected:
        /// \brief Logs an error message.
        virtual void LogError(std::string Message) = 0;
    };
}