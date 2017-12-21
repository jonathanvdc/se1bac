#include "CompositeCommand.h"

#include <memory>
#include "ArraySlice.h"
#include "ICommand.h"

using namespace Arcade;

/// \brief Creates a new composite command.
template<typename T>
CompositeCommand<T>::CompositeCommand(stdx::ArraySlice<std::shared_ptr<ICommand<T>>> Commands)
{
    this->SetCommands(Commands);
}

/// \brief Executes the command and returns a boolean that tells if
/// the operation has completed successfully.
template<typename T>
bool CompositeCommand<T>::Execute(T Target)
{
    bool result = true;
    for (auto& item : this->GetCommands())
        if (!item->Execute(Target))
            result = false;

    return result;
}

/// \brief Gets an array of commands that will be executed in
/// sequence.
template<typename T>
stdx::ArraySlice<std::shared_ptr<ICommand<T>>> CompositeCommand<T>::GetCommands() const
{
    return this->Commands_value;
}

/// \brief Sets an array of commands that will be executed in
/// sequence.
template<typename T>
void CompositeCommand<T>::SetCommands(stdx::ArraySlice<std::shared_ptr<ICommand<T>>> value)
{
    this->Commands_value = value;
}