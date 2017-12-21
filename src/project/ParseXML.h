#pragma once
#include "../tinyxml2/tinyxml2.h"
#include "Board.h"
#include "Player.h"
#include "Obstacle.h"
#include "Contracts.h"
#include "MoveCommand.h"
#include "TextUIHandler.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <functional>

using namespace tinyxml2;

namespace Arcade
{
	typedef stdx::ArraySlice<std::shared_ptr<ICommand<std::shared_ptr<Board>>>> CommandArray;

    class BadPieceException : public std::runtime_error {
    public:
        BadPieceException(std::string s);
    };

    class BadXMLException : public std::runtime_error {
    public:
        BadXMLException(std::string s);
    };

    class MissingTagException : public BadXMLException {
	public:
		MissingTagException(std::string parent, std::string tag);
	};

	class MissingAttributeException : public BadXMLException {
	public:
		MissingAttributeException(std::string parent, std::string attr);
	};

	Board parseBoard(const char *filename, std::ostream &error_stream);

	CommandArray parseMoves(const char *filename, const Board &board, std::ostream &error_stream);

	/// \brief "Trims" a word in a string, removing all whitespace around it.
	std::string trimString(std::string s);
}
