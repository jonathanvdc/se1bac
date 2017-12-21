// ArcadeGameUI.cpp : Defines the entry point for the console application.
//

#include <functional>
#include <memory>
#include <sstream>
#include <vector>
#include <FL/Fl.H>  
#include <FL/Fl_Window.H>  
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Native_File_Chooser.H>
#include "ASCIIArtUIHandler.h"
#include "AttackCommand.h"
#include "Board.h"
#include "CGUIHandler.h"
#include "CompositeCommand.h"
#include "GUIHandler.h"
#include "HtmlUIHandler.h"
#include "XmlUIHandler.h"
#include "ICommand.h"
#include "MoveCommand.h"
#include "ParseXML.h"

using namespace Arcade;

const int btnSize = 40;
const int padding = 20;
std::shared_ptr<GUIHandler> handler = nullptr;
std::vector<Fl_Button*> onLoadButtons;

void showMessage(const char* Title, const char* Message)
{
	Fl_Window window(400, 200, Title);
	window.begin();
	Fl_Box box(padding, padding, 400 - padding * 2, 200 - padding * 2, Message);
	box.align(FL_ALIGN_WRAP);
	window.end();
	window.show();
	Fl::run();
}

void applyCommand(std::function<std::shared_ptr<ICommand<std::shared_ptr<Board>>>()> Command)
{
	if (!handler->GetIsInitialized())
	{
		showMessage("Actie kon niet toegepast worden", "Acties kunnen niet toegepast worden tot het bord is ingeladen.");
		return;
	}
	if (!Command()->Execute(handler->GetScene()))
	{
		showMessage("Actie kon niet toegepast worden", "Een opgegeven actie was niet geldig.");
	}
	handler->Display();
}

void moveLeftCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<MoveCommand>(handler->GetMainActor(), Vector2<int>(-1, 0)); });
}

void moveUpCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<MoveCommand>(handler->GetMainActor(), Vector2<int>(0, 1)); });
}

void moveRightCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<MoveCommand>(handler->GetMainActor(), Vector2<int>(1, 0)); });
}

void moveDownCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<MoveCommand>(handler->GetMainActor(), Vector2<int>(0, -1)); });
}

void attackLeftCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<AttackCommand>(handler->GetMainActor(), Vector2<int>(-1, 0)); });
}

void attackUpCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<AttackCommand>(handler->GetMainActor(), Vector2<int>(0, 1)); });
}

void attackRightCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<AttackCommand>(handler->GetMainActor(), Vector2<int>(1, 0)); });
}

void attackDownCallback(Fl_Widget*, void*)
{
	applyCommand([] { return std::make_shared<AttackCommand>(handler->GetMainActor(), Vector2<int>(0, -1)); });
}

void createDirectionPad(const char* label, int X, int Y, Fl_Callback* LeftCallback, Fl_Callback* UpCallback, Fl_Callback* RightCallback, Fl_Callback* DownCallback)
{
	const int size = btnSize;
	const int offset = btnSize;
	Fl_Box* box = new Fl_Box(X, Y, size * 3, offset, label);
	box->labelsize((int)(box->labelsize() * 1.5));
	Fl_Button* left = new Fl_Button(X, Y + size + offset, size, size, "@#+44>");
	left->callback(LeftCallback);
	Fl_Button* up = new Fl_Button(X + size, Y + offset, size, size, "@#+48>");
	up->callback(UpCallback);
	Fl_Button* right = new Fl_Button(X + size * 2, Y + size + offset, size, size, "@#+46>");
	right->callback(RightCallback);
	Fl_Button* down = new Fl_Button(X + size, Y + size * 2 + offset, size, size, "@#+42>");
	down->callback(DownCallback);

	onLoadButtons.push_back(left);
	onLoadButtons.push_back(up);
	onLoadButtons.push_back(right);
	onLoadButtons.push_back(down);
}

void chooseBoard(Fl_Widget*, void*)
{
	Fl_Native_File_Chooser picker;
	picker.title("Bord kiezen");
	picker.type(Fl_Native_File_Chooser::BROWSE_FILE);
	picker.filter("XML files\t*.xml");
	picker.show();
	const char* filename = picker.filename();
	if (filename == nullptr || filename == std::string(""))
	{
		return;
	}

	std::ostringstream errStream;
	std::shared_ptr<Board> board;
	try
	{
		board = std::make_shared<Board>(parseBoard(filename, errStream));
	}
	catch (std::exception)
	{
		// Catch errors here. The error stream displays them.
	}

	std::string errorMessage = errStream.str();
	if (!errorMessage.empty())
	{
		errorMessage = "Het gegeven bord is niet geldig. Dit lijkt de reden te zijn:\n" + errorMessage;
		showMessage("Oops?", errorMessage.c_str());
	}
	else
	{
		handler->Initialize(board);
		for (Fl_Button *b : onLoadButtons) b->activate();
	}
}

void chooseActions(Fl_Widget*, void*)
{
	if (!handler->GetIsInitialized())
	{
		showMessage("Bord nog niet geladen", "Acties kunnen niet toegepast worden tot het bord is ingeladen.");
		return;
	}

	Fl_Native_File_Chooser picker;
	picker.title("Acties kiezen");
	picker.type(Fl_Native_File_Chooser::BROWSE_FILE);
	picker.filter("XML files\t*.xml");
	picker.show();
	const char* filename = picker.filename();
	if (filename == nullptr || filename == std::string(""))
	{
		return;
	}

	CommandArray actions;
	std::ostringstream errStream;
	try
	{
		actions = parseMoves(filename, *handler->GetScene(), errStream);
	}
	catch (std::exception)
	{
		// Catch errors here. The error stream displays them.
	}

	std::string errorMessage = errStream.str();
	if (!errorMessage.empty())
	{
		errorMessage = "Het gegeven bord is niet geldig. Dit lijkt de reden te zijn:\n" + errorMessage;
		showMessage("Oops?", errorMessage.c_str());
	}
	else
	{
		for (int i = 0; i < actions.GetLength() && handler->GetIsInitialized(); i++)
		{
			if (!actions[i]->Execute(handler->GetScene()))
			{
				std::stringstream message;
				message << "Actie #" << i << " in bestand '" << filename << "' kon niet uitgevoerd worden." << std::endl;
				showMessage("Actie kon niet toegepast worden", message.str().c_str());
				break;
			}
			handler->Display();
		}
	}
}

void outputOK(Fl_Widget*, void* ptr) {
	// First, determine which Round_Button is selected.
	Fl_Window *w = (Fl_Window *)ptr;
	int nthRadio = 0, selection = -1;
	for (int i = 0; i < w->children(); i++) {
		if (Fl_Round_Button *b = dynamic_cast<Fl_Round_Button*>(w->child(i))) {
			if (b->value())
				selection = nthRadio;
			nthRadio++;
		}
	}

	// If none of them is, abort.
	if (selection < 0)
		return;

	// Else, we found a selected output type (0 <= selection < 4).
	// Pick an output file to write to:
	const char* filters[] = {
		"Text files\t*.txt",   // TextUIHandler
		"Text files\t*.txt",   // ASCIIArtUIHandler
		"HTML files\t*.html",  // HtmlUIHandler
		"INI files\t*.ini",    // CGUIHandler
		"XML files\t*.xml"     // XmlUIHandler
	};

	Fl_Native_File_Chooser picker;
	picker.title("Outputbestand kiezen");
	picker.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
	picker.filter(filters[selection]);
	picker.show();
	const char* filename = picker.filename();
	if (filename == nullptr || *filename == '\0')
		return;

	auto board = handler->GetScene();
	std::ofstream file(filename);
	switch (selection) {
		case 0: TextUIHandler(&file, &std::cerr, false).Initialize(board); break;
		case 1: ASCIIArtUIHandler(&file).Initialize(board); break;
		case 2: HtmlUIHandler(&file).Initialize(board); break;
		case 3: CGUIHandler(&file).Initialize(board); break;
		case 4: XmlUIHandler(&file).Initialize(board); break;
	}

	// Finally, close the dialog box.
	((Fl_Window*) w)->hide();
}

void outputCancel(Fl_Widget*, void* w) {
	// Closes the dialog box.
	((Fl_Window*) w)->hide();
}

void chooseOutput(Fl_Widget*, void*)
{
	// Window dimensions:
	//
	//         pad             pad
	//          |  optionWidth  |
	//         +-----------------+
	//         |                 | } pad
	//         | o Option 1      | } optionHeight
	//         |                 | } pad
	//         | o Option 2      | } optionHeight
	//         |                 | } ... (nrOptions + 1 times)
	//         | o Option 3      |
	//         |                 |
	//         | [ OK  ] [Cncl.] |
	//         |                 | } pad
	//         +-----------------+
	//          |       |       |
	//         pad     pad     pad
	//           \__ __/
	//              '-> = okWidth
	//                  = (optionWidth - pad) / 2.

	const int pad = 10;
	const int optionWidth = 200;
	const int okWidth = (optionWidth - pad) / 2;
	const int optionHeight = 30;
	const std::vector<std::string> options({
		"Text output", "ASCII output", "HTML output", "CGI output", "XML output"
	});
	const int nrOptions = options.size();

	Fl_Window window(optionWidth + pad * 2,
	                 (nrOptions + 1) * (pad + optionHeight) + pad,
	                 "Bord output");
	window.begin();

	int nth = 0;
	for (auto opt : options) {
		int y = (nth++) * (pad + optionHeight) + pad;
		Fl_Round_Button* radio = new Fl_Round_Button(pad, y, optionWidth, optionHeight, opt.c_str());
		radio->type(FL_RADIO_BUTTON);
	}

	int y = nth * (pad + optionHeight) + pad;
	Fl_Button* ok = new Fl_Button(pad, y, okWidth, optionHeight, "OK");
	ok->callback(outputOK, &window);
	Fl_Button* cancel = new Fl_Button(2 * pad + okWidth, y, okWidth, optionHeight, "Cancel");
	cancel->callback(outputCancel, &window);

	window.end();
	window.show();
	Fl::run();
}

void createLoadButtons()
{
	const int actionBtnWidth = 79;
	const int offset = 0;

	Fl_Button* boardBtn = new Fl_Button(offset + padding, padding, actionBtnWidth, padding, "Bord laden");
	boardBtn->callback(chooseBoard);
	Fl_Button* actionsBtn = new Fl_Button(offset + padding * 2 + actionBtnWidth, padding, actionBtnWidth, padding, "Acties laden");
	actionsBtn->callback(chooseActions);
	Fl_Button* outputBtn = new Fl_Button(offset + padding * 3 + actionBtnWidth * 2, padding, actionBtnWidth, padding, "Bord output");
	outputBtn->callback(chooseOutput);

	actionsBtn->deactivate();
	onLoadButtons.push_back(actionsBtn);
	outputBtn->deactivate();
	onLoadButtons.push_back(outputBtn);
}

int main(int argc, char* argv[])
{
	Fl_Window* window = new Fl_Window(320, 500, "Arcade Game");
	createLoadButtons();
	Fl_Text_Display* boardDisplay = new Fl_Text_Display(padding, padding * 3, 280, 240);
	boardDisplay->textfont(FL_SCREEN);
	Fl_Text_Buffer buf;
	boardDisplay->buffer(buf);
	handler = std::make_shared<GUIHandler>(boardDisplay);
	createDirectionPad("Move", padding, 500 - btnSize * 4 - padding, moveLeftCallback, moveUpCallback, moveRightCallback, moveDownCallback);
	createDirectionPad("Attack", padding * 2 + btnSize * 3, 500 - btnSize * 4 - padding, attackLeftCallback, attackUpCallback, attackRightCallback, attackDownCallback);
	for (Fl_Button *b : onLoadButtons) b->deactivate();
	window->end();
	window->show(argc, argv);
	return Fl::run();
}
