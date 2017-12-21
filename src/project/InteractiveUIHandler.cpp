#include "InteractiveUIHandler.h"

#include <memory>
#include <string>
#include "Board.h"
#include "CompositeCommand.h"
#include "Contracts.h"
#include "EmptyCommand.h"
#include "ICommand.h"
#include "IsInstance.h"
#include "IUIHandler.h"

using namespace Arcade;

InteractiveUIHandler::InteractiveUIHandler()
{ }

/// \brief Applies a command to the board.
/// \pre require(Command != nullptr);
/// \pre require(this->GetIsInitialized());
void InteractiveUIHandler::Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
    require(Command != nullptr);
    require(this->GetIsInitialized());
    if (stdx::isinstance<EmptyCommand<std::shared_ptr<Board>>>(Command))
        return;
    else if (stdx::isinstance<CompositeCommand<std::shared_ptr<Board>>>(Command))
    {
        auto compCommand = std::dynamic_pointer_cast<CompositeCommand<std::shared_ptr<Board>>>(Command);
        for (auto& item : compCommand->GetCommands())
            this->Apply(item);
    }
    else if (!Command->Execute(this->GetScene()))
        this->LogError("Actie kon niet uitgevoerd worden.");
    else
        this->Display();

}