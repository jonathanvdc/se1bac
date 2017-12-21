#pragma once
#include <memory>
#include "ICommand.h"

namespace Arcade
{
    /// \brief Defines an empty command, i.e.
    /// a command that does nothing.
    template<typename T>
    class EmptyCommand : public virtual ICommand<T>
    {
    public:
        /// \brief Executes the command and returns a boolean that tells if
        /// the operation has completed successfully.
        bool Execute(T Target) override;

        static std::shared_ptr<EmptyCommand<T>> GetInstance();
    private:
        EmptyCommand();

        static std::shared_ptr<EmptyCommand<T>> EmptyCommand_instance_value;
    };
}

#include "EmptyCommand.hxx"