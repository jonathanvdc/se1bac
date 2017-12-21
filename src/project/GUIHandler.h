#pragma once

#include <sstream>
#include <FL/Fl_Text_Display.H>
#include "Actor.h"
#include "ASCIIArtUIHandler.h"
#include "Board.h"
#include "IUIHandler.h"

namespace Arcade
{
	/// \brief A UI handler that uses an fltk GUI to
	/// display the board and fetch input.
	class GUIHandler : public virtual IUIHandler
	{
	public:
		/// Creates a new GUI handler.
		/// \pre require(display != nullptr);
		GUIHandler(Fl_Text_Display* display);

		/// \brief Applies a command to the board.
		/// \pre require(Command != nullptr);
		/// \pre require(this->GetIsInitialized());
		void Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command) override;

		/// \brief Displays the board.
		/// \pre require(this->GetIsInitialized());
		void Display() override;

		/// \brief Initializes the UI handler and displays the board right
		/// away.
		/// \pre require(Value != nullptr);
		void Initialize(std::shared_ptr<Board> Value) override;

		/// \brief Gets a boolean flag that indicates whether the UI handler
		/// has been initialized.
		bool GetIsInitialized() const override;

		/// \brief Gets the GUI handler's board.
		/// \pre require(this->GetIsInitialized());
		std::shared_ptr<Board> GetScene() const;
		
		/// \brief Gets the GUI handler's main actor.
		/// \pre require(this->GetIsInitialized());
		std::shared_ptr<Actor> GetMainActor() const;

		/// \brief Gets a boolean value that tells if the game has ended.
		/// \pre require(this->GetIsInitialized());
		bool HasEnded() const;

	private:
		/// \brief Flushes the output stream's contents to the display,
		/// possibly ending the game and unloading the board.
		void Flush();

		/// \brief Flushes the output stream's contents to the display.
		void FlushDisplay();

		std::shared_ptr<ASCIIArtUIHandler> handler;
		std::shared_ptr<Actor> mainActor;
		std::ostringstream outputStream;
		Fl_Text_Display* display;
	};
}