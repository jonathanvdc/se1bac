#include "GUIHandler.h"

#include <sstream>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include "CompositeCommand.h"
#include "EmptyCommand.h"
#include "IUIHandler.h"

using namespace Arcade;

/// Creates a new GUI handler.
/// \pre require(display != nullptr);
GUIHandler::GUIHandler(Fl_Text_Display* display)
	: display(display)
{
	require(display != nullptr);
}

/// \brief Applies a command to the board.
/// \pre require(Command != nullptr);
/// \pre require(this->GetIsInitialized());
void GUIHandler::Apply(std::shared_ptr<ICommand<std::shared_ptr<Board>>> Command)
{
	require(Command != nullptr);
	require(this->GetIsInitialized());
	this->handler->Apply(Command);
}

/// \brief Displays the board.
/// \pre require(this->GetIsInitialized());
void GUIHandler::Display()
{
	require(this->GetIsInitialized());
	this->handler->Display();

	Flush();
}

/// \brief Initializes the UI handler and displays the board right
/// away.
/// \pre require(Value != nullptr);
void GUIHandler::Initialize(std::shared_ptr<Board> Value)
{
	require(Value != nullptr);
	this->outputStream.str("");
	this->outputStream.clear();
	this->handler = std::make_shared<ASCIIArtUIHandler>(&outputStream);
	this->handler->Initialize(Value);
	auto players = Value->GetPlayers();
	if (players.empty())
	{
		this->mainActor = nullptr;
	}
	else
	{
		this->mainActor = players[0];
	}
	Flush();
}

/// \brief Gets a boolean flag that indicates whether the UI handler
/// has been initialized.
bool GUIHandler::GetIsInitialized() const
{
	return this->handler != nullptr;
}

/// \brief Gets the GUI handler's board.
/// \pre require(this->GetIsInitialized());
/// \post ensure(result != nullptr);
std::shared_ptr<Board> GUIHandler::GetScene() const
{
	require(this->GetIsInitialized());
	auto result = this->handler->GetScene();
	ensure(result != nullptr);
	return result;
}

/// \brief Gets the GUI handler's main actor.
/// \pre require(this->GetIsInitialized());
std::shared_ptr<Actor> GUIHandler::GetMainActor() const
{
	require(this->GetIsInitialized());
	return mainActor;
}

bool GUIHandler::HasEnded() const
{
	return this->handler->GetHasEnded();
}

void GUIHandler::Flush()
{
	if (this->HasEnded())
	{
		this->outputStream << std::endl;
		if (this->handler->GetScene()->HasPiece(this->GetMainActor()))
			this->outputStream << "Gefeliciteerd! Je wint!\n";
		else
			this->outputStream << "Je bent verloren. :(\n";

		this->handler = nullptr;
		this->mainActor = nullptr;
		this->FlushDisplay();
		this->outputStream.str("");
		this->outputStream.clear();
	}
	else
	{
		this->FlushDisplay();
	}
}

void GUIHandler::FlushDisplay()
{
	auto buf = this->display->buffer();
	buf->text(this->outputStream.str().c_str());
	this->display->scroll(buf->count_lines(0, buf->length()), 0);
	this->outputStream << std::endl;
}
