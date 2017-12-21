#include <iostream>
#include <functional>
#include <string>
#include <vector>
#include <sstream>
#include <chrono>
#include <thread>
#include "UIHandlerBase.h"
#include "TextUIHandler.h"
#include "ParseXML.h"
#include "ASCIIArtUIHandler.h"
#include "CGUIHandler.h"
#include "HtmlUIHandler.h"
#include "XmlUIHandler.h"
#include "IsInstance.h"
#include "FileNames.h"
#include "CommandLineUI.h"
#include "LambdaParser.h"
#include "EmptyCommand.h"
#include "CompositeCommand.h"

using namespace Arcade;

void WriteToFile(UIHandlerBase& Handler, std::string FilePath, std::function<void(UIHandlerBase&)> Function)
{
	std::string path(FilePath);

	if (path.size() == 0) // Use console as output
	{
		Handler.SetOutputStream(&std::cout);
		Function(Handler);
		std::cout << std::endl << std::endl;
	}
	else
	{
		std::ofstream target;
		target.open(FilePath);
		if (target.is_open())
		{
			if (stdx::isinstance<TextUIHandler>(Handler))
			{
				target << "Bestand: " << FilePath << std::endl << std::endl;
			}
			Handler.SetOutputStream(&target);
		}
		else
		{
			std::cout << "Het bestand '" << FilePath << "' kon niet geopend worden." << std::endl << std::endl;
			Handler.SetOutputStream(&std::cout);
		}
		Function(Handler);
		if (target.is_open())
		{
			target.close();
		}
		else
		{
			std::cout << std::endl << std::endl;
		}
	}
}

template<typename T>
T GetArgument(int Index, T Default, int argc, const char* argv[]);

template<>
bool GetArgument(int Index, bool Default, int argc, const char* argv[])
{
	return argc > Index ? std::string(argv[Index]) == "true" : Default;
}

template<>
std::string GetArgument(int Index, std::string Default, int argc, const char* argv[])
{
	return argc > Index ? std::string(argv[Index]) : Default;
}

void PrintUsage(const char* Name)
{
	std::cerr << "Usage: " << std::endl
		<< " * " << Name << " text Board.xml Commands.xml [BoardOutput.txt (CommandsOutput.txt|SlideshowOutput.txt) [simulate (true|false)] [slideshow (true|false)]]" << std::endl
		<< " * " << Name << " html Board.xml Commands.xml [BoardOutput.html [SlideshowOutput.html]]" << std::endl
        << " * " << Name << " ascii Board.xml Commands.xml [BoardOutput.txt [SlideshowOutput.txt [slideshow (true|false)]]]" << std::endl
        << " * " << Name << " cg Board.xml Commands.xml [BoardOutput.ini [SlideshowOutput.ini [slideshow (true|false)]]]" << std::endl
        << " * " << Name << " xml Board.xml Commands.xml [InitialBoardOutput.xml ResultBoardOutput.xml]" << std::endl
		<< " * " << Name << " interactive Board.xml" << std::endl;
}

std::shared_ptr<IParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>> CreateSaveCommandParser(std::shared_ptr<Board> Scene, std::function<std::shared_ptr<UIHandlerBase>()> OutputHandler)
{
	return Arcade::LambdaParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>::make_shared([=](std::string val)
	{
		auto handler = OutputHandler();
		WriteToFile(*handler, val, [=](UIHandlerBase& h)
		{
			h.Initialize(Scene);
		});

		return Arcade::EmptyCommand<std::shared_ptr<Board>>::GetInstance();
	});
}

int StartInteractive(int argc, const char* argv[])
{
	std::shared_ptr<Board> b;

	try
	{
		b = std::make_shared<Board>(parseBoard(argv[2], std::cerr));
	}
	catch (const BadXMLException& /* e */)
	{
		return 1; // Errors are displayed elsewhere
	}

	auto players = b->GetPlayers();

	if (players.empty())
	{
		std::cerr << "Het gegeven bord ('" << b->GetName() << "') bevatte geen spelers." << std::endl;
		return 1;
	}

	std::shared_ptr<Player> mainPlayer = players[0];

	CommandLineUI handler(&std::cin, std::make_shared<ASCIIArtUIHandler>(&std::cout), mainPlayer);
	auto moveParser = Arcade::LambdaParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>::make_shared<CommandLineUI>(handler, &CommandLineUI::ParseMove);
	handler.AddActionParser("m", moveParser);
	auto attackParser = Arcade::LambdaParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>::make_shared<CommandLineUI>(handler, &CommandLineUI::ParseAttack);
	handler.AddActionParser("a", attackParser);

	auto runCommandsParser = Arcade::LambdaParser<std::string, std::shared_ptr<ICommand<std::shared_ptr<Board>>>>::make_shared([=](std::string arg) -> std::shared_ptr<Arcade::ICommand<std::shared_ptr<Board>>>
	{
		try
		{
			return std::make_shared<Arcade::CompositeCommand<std::shared_ptr<Board>>>(parseMoves(arg.c_str(), *b, std::cerr));
		}
		catch (const BadXMLException& /* e */)
		{
			return Arcade::EmptyCommand<std::shared_ptr<Board>>::GetInstance(); // Errors are displayed elsewhere
		}
	});
	handler.AddActionParser("run", runCommandsParser);

	handler.AddActionParser("save", CreateSaveCommandParser(b, [] { return std::make_shared<XmlUIHandler>(&std::cout); }));
	handler.AddActionParser("xml", CreateSaveCommandParser(b, [] { return std::make_shared<XmlUIHandler>(&std::cout); }));
	handler.AddActionParser("html", CreateSaveCommandParser(b, [] { return std::make_shared<HtmlUIHandler>(&std::cout); }));
	handler.AddActionParser("ascii", CreateSaveCommandParser(b, [] { return std::make_shared<ASCIIArtUIHandler>(&std::cout); }));
	handler.AddActionParser("cg", CreateSaveCommandParser(b, [] { return std::make_shared<CGUIHandler>(&std::cout); }));
	handler.AddActionParser("text", CreateSaveCommandParser(b, [] { return std::make_shared<TextUIHandler>(&std::cout, &std::cerr, false); }));

	handler.Initialize(b); // Initialize the handler, display the board.

	handler.PlayGame();

	return 0;
}

int main(int argc, const char* argv[])
{
	if (argc < 3)
	{
		std::cerr << "This incident will be reported." << std::endl
				  << "Just kidding. ";
		PrintUsage(argv[0]);
		return 0;
	}

	auto mode = GetArgument<std::string>(1, "ascii", argc, argv);

	if (mode == "interactive")
	{
		return StartInteractive(argc, argv);
	}

	bool simulate, slideshow;
	std::shared_ptr<UIHandlerBase> handler;
	std::string outputCommandsPath;
	if (mode == "html")
	{
		outputCommandsPath = GetArgument<std::string>(5, "", argc, argv);
		simulate = true;
		slideshow = true;
		handler = std::make_shared<HtmlUIHandler>(&std::cout);
	}
	else if (mode == "text")
	{
		outputCommandsPath = GetArgument<std::string>(5, "", argc, argv);
		simulate = GetArgument<bool>(6, true, argc, argv);
		slideshow = GetArgument<bool>(7, true, argc, argv);
		handler = std::make_shared<TextUIHandler>(&std::cout, &std::cerr, simulate);
	}
    else if (mode == "ascii")
    {
        outputCommandsPath = GetArgument<std::string>(5, "", argc, argv);
        simulate = true;
        slideshow = GetArgument<bool>(6, true, argc, argv);
        handler = std::make_shared<ASCIIArtUIHandler>(&std::cout);
    } else if (mode == "cg")
    {
        outputCommandsPath = GetArgument<std::string>(5, "", argc, argv);
        simulate = true;
        slideshow = GetArgument<bool>(6, true, argc, argv);
        handler = std::make_shared<CGUIHandler>(&std::cout);
    } else if (mode == "xml")
	{
		outputCommandsPath = GetArgument<std::string>(5, "", argc, argv);
		simulate = true;
		slideshow = false;
		handler = std::make_shared<XmlUIHandler>(&std::cout);
	}
	else
	{
		std::cout << "Mode not recognized." << std::endl;
		PrintUsage(argv[0]);
		return 1;
	}

	std::shared_ptr<Board> b;
	CommandArray moves;

	try
	{
		b = std::make_shared<Board>(parseBoard(argv[2], std::cerr));
		moves = parseMoves(argv[3], *b, std::cerr);
	}
	catch (const BadXMLException& /* e */)
	{
		return 1; // Errors are displayed elsewhere
	}

	auto outputPath = GetArgument<std::string>(4, "", argc, argv);

	WriteToFile(*handler, outputPath, [&](UIHandlerBase& h)
	{
		h.Initialize(b);
	});

	if (outputCommandsPath == "")
	{
		return 0;
	}

	if (mode == "ascii" && slideshow)
	{
		WriteToFile(*handler, outputCommandsPath, [&](UIHandlerBase& h)
		{
			for (auto item : moves)
			{
				h.Apply(item);
				h.Display();
				*h.GetOutputStream() << std::endl;
			}
		});
	}
	else if (slideshow)
	{
		for (int i = 0; i < moves.GetLength(); i++)
		{
			WriteToFile(*handler, AppendToFilename(outputCommandsPath, std::to_string(i)), [&](UIHandlerBase& h)
			{
				h.Apply(moves[i]);
				h.Display();
			});
		}
	}
	else
	{
		WriteToFile(*handler, outputCommandsPath, [&](UIHandlerBase& h)
		{
			if (moves.GetLength() == 0 && !simulate && mode == "text")
			{
				*h.GetOutputStream() << "Geen bewegingen.";
			}
			for (auto item : moves)
			{
				h.Apply(item);
			}
			if (simulate)
			{
				h.Display();
			}
		});
	}

	return 0;
}
