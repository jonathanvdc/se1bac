#include "EmptyCommand.h"

#include <memory>
#include "ICommand.h"

using namespace Arcade;

template<typename T>
EmptyCommand<T>::EmptyCommand()
{ }

/// \brief Executes the command and returns a boolean that tells if
/// the operation has completed successfully.
template<typename T>
bool EmptyCommand<T>::Execute(T Target)
{
    return true;
}

template<typename T>
std::shared_ptr<EmptyCommand<T>> EmptyCommand<T>::GetInstance()
{
    if (EmptyCommand<T>::EmptyCommand_instance_value == nullptr)
        EmptyCommand<T>::EmptyCommand_instance_value = std::shared_ptr<EmptyCommand<T>>(new EmptyCommand<T>());

    return EmptyCommand<T>::EmptyCommand_instance_value;
}

template<typename T>
std::shared_ptr<EmptyCommand<T>> EmptyCommand<T>::EmptyCommand_instance_value = nullptr;