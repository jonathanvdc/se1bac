#pragma once
#include <istream>
#include <memory>
#include <string>
#include <unordered_map>
#include "Actor.h"
#include "Board.h"
#include "Contracts.h"
#include "ICommand.h"
#include "InteractiveUIHandler.h"
#include "IParser.h"
#include "UIHandlerBase.h"
#include "Vector2.h"

namespace Arcade
{
    /// \brief A UI handler implementation that manages a command-line
    /// UI.
    class CommandLineUI : public InteractiveUIHandler
    {
    public:
        /// \brief Creates a new command-line UI handler that outputs to the
        /// given output stream, based on the given other UI handler.
        /// \pre require(Handler != nullptr);
        /// \pre require(inputStream != nullptr);
        /// \pre require(MainActor != nullptr);
        /// \post ensure(this->CheckInvariants());
        CommandLineUI(std::istream* inputStream, std::shared_ptr<UIHandlerBase> Handler, std::shared_ptr<Actor> MainActor);

        /// \brief Associates the given action parser with the given key.
        /// \pre require(Parser != nullptr);
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void AddActionParser(std::string Key, std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>> Parser);

        /// \brief Checks if this type's invariants are being respected.
        /// A boolean value is returned that indicates whether this is
        /// indeed the case. This method is publically visible, and can
        /// be used to verify an instance's state.
        bool CheckInvariants() const;
        // {
        //     if (!this->isCheckingInvariants)
        //     {
        //         this->isCheckingInvariants = true;
        //         bool result = this->GetHandler() != nullptr && 
        //                       this->inputStream != nullptr && 
        //                       this->GetMainActor() != nullptr;
        //         this->isCheckingInvariants = false;
        //         return result;
        //     }
        //     return true;
        // }

        /// \brief Converts the given direction to an offset.
        /// \pre require(this->CheckInvariants());
        Vector2<int> DirectionToOffset(std::string Direction) const;

        /// \brief Displays the board.
        /// \pre require(this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void Display() override;

        /// \brief Gets the command-line UI's inner UI handler.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<UIHandlerBase> GetHandler() const;

        /// \brief Gets the main actor for this UI dialog.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<Actor> GetMainActor() const;

        /// \brief Initializes the UI handler and displays the board right
        /// away.
        /// \pre require(Value != nullptr);
        /// \pre require(!this->GetIsInitialized());
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->GetIsInitialized());
        /// \post ensure(this->CheckInvariants());
        void Initialize(std::shared_ptr<Board> Value) override;

        /// \brief Parses an action.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<ICommand<std::shared_ptr<Board>>> ParseAction(std::string Key, std::string Arg) const;

        /// \brief Parses an attack action.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<ICommand<std::shared_ptr<Board>>> ParseAttack(std::string Arg) const;

        /// \brief Parses a move action.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<ICommand<std::shared_ptr<Board>>> ParseMove(std::string Arg) const;

        /// \brief Plays the game until the player either wins or loses.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void PlayGame();

        /// \brief Reads an action from the input stream.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        std::shared_ptr<ICommand<std::shared_ptr<Board>>> ReadAction();

        /// \brief Gets the command-line UI's action parsers.
        /// \pre require(this->CheckInvariants());
        std::unordered_map<std::string, std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>>> GetActionParsers() const;

        /// \brief Gets a boolean flag that indicates whether the UI handler
        /// has been initialized.
        /// \pre require(this->CheckInvariants());
        bool GetIsInitialized() const override;

        /// \brief Gets the interactive UI handler's board.
        /// \pre require(this->CheckInvariants());
        std::shared_ptr<Board> GetScene() const override;
    protected:
        /// \brief Logs an error message.
        /// \pre require(this->CheckInvariants());
        /// \post ensure(this->CheckInvariants());
        void LogError(std::string Message) override;
    private:
        /// \brief Sets the command-line UI's inner UI handler.
        void SetHandler(std::shared_ptr<UIHandlerBase> value);

        /// \brief Sets the main actor for this UI dialog.
        void SetMainActor(std::shared_ptr<Actor> value);

        std::unordered_map<std::string, std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>>> allParsers;
        std::shared_ptr<UIHandlerBase> Handler_value;
        std::istream* inputStream;
        mutable bool isCheckingInvariants = false;
        std::shared_ptr<Actor> MainActor_value;
    };
}