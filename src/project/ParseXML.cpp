#include "../tinyxml2/tinyxml2.h"
#include "ParseXML.h"
#include "Board.h"
#include "Player.h"
#include "Obstacle.h"
#include "Contracts.h"
#include "MoveCommand.h"
#include "TextUIHandler.h"
#include "Water.h"
#include "Button.h"
#include "Gate.h"
#include "Goal.h"
#include "Trap.h"

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

using namespace tinyxml2;

namespace std {
	template<typename T>
	string to_string(Vector2<T> value) {
		ostringstream o;
		o << value;
		return o.str();
	}
}

namespace Arcade
{

	typedef std::unordered_map<std::string, std::vector<std::shared_ptr<Button>>> ButtonMap;

	const char BOARD_TAG[] = "VELD";
	const char BOARD_NAME_TAG[] = "NAAM";
	const char BOARD_LENGTH_TAG[] = "LENGTE";
	const char BOARD_WIDTH_TAG[] = "BREEDTE";
	const char BOARD_ID_TAG[] = "ID";

	const char BOARD_PLAYER_TAG[] = "SPELER";
	const char BOARD_OBSTACLE_TAG[] = "OBSTAKEL"; // deprecated
	const char BOARD_WALL_TAG[] = "MUUR";
	const char BOARD_BARREL_TAG[] = "TON";
	const char BOARD_GOAL_TAG[] = "DOEL";
	const char BOARD_BUTTON_TAG[] = "KNOP";
	const char BOARD_GATE_TAG[] = "POORT";
	const char BOARD_WATER_TAG[] = "WATER";
	const char BOARD_MONSTER_TAG[] = "MONSTER";
	const char BOARD_TRAP_TAG[] = "VALSTRIK";

	const char PLAYER_NAME_TAG[] = "NAAM";
	const char OBSTACLE_TYPE_TAG[] = "TYPE";

	const char PIECE_MOVABLE_ATTR[] = "beweegbaar";
	const char PIECE_ID_ATTR[] = "id";

	const char MOVES_TAG[] = "BEWEGINGEN";
	const char ACTIONS_TAG[] = "ACTIES";
	const char MOVES_MOVE_TAG[] = "BEWEGING";
	const char MOVES_ATTACK_TAG[] = "AANVAL";
	const char MOVE_NAME_TAG[] = "SPELERNAAM";
	const char MOVE_DIRECTION_TAG[] = "RICHTING";

	const char DIRECTION_LEFT[] = "LINKS";
	const char DIRECTION_RIGHT[] = "RECHTS";
	const char DIRECTION_UP[] = "OMHOOG";
	const char DIRECTION_DOWN[] = "OMLAAG";

	int toInt(const char *s) {
		return std::strtol(s, nullptr, 10);
	}

	BadPieceException::BadPieceException(std::string s) : runtime_error(s) {}

	BadXMLException::BadXMLException(std::string s) : runtime_error(s) {}

	MissingTagException::MissingTagException(std::string parent, std::string tag)
		: BadXMLException("Verwachtte <" + tag + "> tag binnen <"
		+ parent + ">.") { }

	MissingAttributeException::MissingAttributeException(std::string parent, std::string attr)
		: BadXMLException("Verwachtte \"" + attr + "\" attribute binnen <"
		+ parent + ">.") { }

	const XMLElement *anyChild(const XMLNode *e, std::vector<const char*> names)
	{
		require(e != nullptr);
		const XMLElement *result = nullptr;
		for (auto item : names)
		{
			auto elem = e->FirstChildElement(item);
			if (elem != nullptr)
			{
				if (result == nullptr)
				{
					result = elem;
					if (result->NextSiblingElement(item))
					{
						throw BadXMLException("<" + std::string(item) +
							"> kwam meer dan eens voor in <" +
							e->Value() + ">");
					}
				}
				else
				{
					// It's not over 'till the fat lady sings, 
					// or we encounter a duplicate equivalent tag.
					throw BadXMLException("<" + std::string(item) +
						"> en een equivalente tag kwamen allebei voor in <" +
						e->Value() + ">");
				}
			}
		}
		if (result == nullptr)
		{
			auto val = e->Value();
			throw MissingTagException(val ? val : "", names.at(0));
		}

		return result;
	}

	const XMLElement *child(const XMLNode *e, const char *name) {
		require(e != nullptr);
		return anyChild(e, { name });
	}

	const char *attribute(const XMLElement *e, const char *name) {
		require(e != nullptr);
		const char *attr = e->Attribute(name);
		if (attr == nullptr)
			throw MissingAttributeException(e->Value(), name);
		return attr;
	}

	/// \brief Prints exceptions from the given function to the error stream.
	void RedirectFeedback(std::function<void()> Function, std::ostream &error_stream)
	{
		try
		{
			Function();
		}
		catch (const BadXMLException &e)
		{
			error_stream << e.what() << std::endl;
			throw; // Bad XML is not something we can hope to rectify. We're done here.
		}
		catch (const BadPieceException &e)
		{
			error_stream << e.what() << std::endl;
			// Inform the user that something went wrong, but try to keep on parsing
		}
	}

	/// \brief "Trims" a word in a string, removing all whitespace around it.
	std::string trimString(std::string s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(),
			std::not1(std::ptr_fun<int, int>(std::isspace))));
		s.erase(std::find_if(s.rbegin(), s.rend(),
			std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	/// \brief Reads the string contents of the given XML element, trimming whitespace in the process.
	std::string readStringContents(const XMLElement *e)
	{
		const char* val = e->GetText();
		if (val == nullptr) return "";
		return trimString(val);
	}

	// \brief Utility functions to read a position from an XML element.
	Vector2<int> readPosition(const XMLElement *e) {
		int x = toInt(attribute(e, "x"));
		int y = toInt(attribute(e, "y"));
		return Vector2<int>(x, y);
	}

	/// \brief Reads a position from the given XML element and cross-references it with the board.
	/// If the position is invalid, an exception is thrown.
	Vector2<int> readBoardPosition(const XMLElement *e,
		const Board &board,
		const std::string &what,
		bool IsTerrain)
	{
		auto pos = readPosition(e);
		if (!board.InRange(pos))
			throw BadPieceException("Ongeldige positie " + std::to_string(pos)
			+ " voor " + what + ".");

		bool pos_open = IsTerrain ||
			board.GetItem(pos) == nullptr ||
			board.GetItem(pos)->GetIsTerrain();
		if (!pos_open)
			throw BadPieceException("Positie " + std::to_string(pos)
			+ " voor " + what + " al bezet.");
		return pos;
	}

	/// \brief Parses a string that represents a direction vector.
	Vector2<int> directionVector(const std::string &direction) {
		if (direction == DIRECTION_LEFT)
			return Vector2<int>(-1, 0);
		else if (direction == DIRECTION_RIGHT)
			return Vector2<int>(1, 0);
		else if (direction == DIRECTION_UP)
			return Vector2<int>(0, 1);
		else if (direction == DIRECTION_DOWN)
			return Vector2<int>(0, -1);
		else
			throw BadXMLException("'" + direction + "' is geen geldige richting.");
	}

	/// \brief Reads a boolean value from a string.
	bool readBool(std::string s) {
		if (s != "true" && s != "false") {
			throw BadPieceException("Ongeldige booleaanse waarde '" + s + "'");
		}
		return (s == "true");
	}

	/// \brief Prints an XML error to the given error stream.
	void writeError(XMLDocument& doc, std::ostream& error_stream)
	{
		error_stream << "XML document error: ";
		error_stream << "id='" << doc.ErrorID() << "' ";
		error_stream << "('" << doc.ErrorName() << "') ";
		if (doc.GetErrorStr1())
		{
			error_stream << "str1='" << doc.GetErrorStr1() << "' ";
		}
		if (doc.GetErrorStr2())
		{
			error_stream << "str2='" << doc.GetErrorStr2() << "' ";
		}
		error_stream << std::endl;
	}

	/// \brief Parses all buttons in the board.
	/// \remark This has to be done in advance to allow gates to bind to buttons later on.
	ButtonMap ParseButtons(const XMLElement *root, Board &board, std::ostream& error_stream)
	{
		ButtonMap results;
		for (auto e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			std::string elemName = e->Name();
			if (elemName == BOARD_BUTTON_TAG)
			{
				RedirectFeedback([&]()
				{
					auto pos = readBoardPosition(e, board, "knop", true);
					auto id = trimString(attribute(e, PIECE_ID_ATTR));
					auto pc = std::make_shared<Button>(pos);
					results[id].push_back(pc);
					board.AddPiece(pc);
				}, error_stream);
			}
		}
		return results;
	}

	/// \brief Parses a piece in the board.
	std::shared_ptr<PieceBase> parsePiece(const XMLElement *e, const Board &board, ButtonMap &Buttons)
	{
		std::string value(e->Name());
		if (value == BOARD_PLAYER_TAG) {
			std::string name(readStringContents(child(e, PLAYER_NAME_TAG)));
			Vector2<int> pos = readBoardPosition(e, board, "speler " + name, false);
			return std::make_shared<Player>(pos, name);
		}
		else if (value == BOARD_WALL_TAG || value == BOARD_BARREL_TAG) {
			std::string type = (value == BOARD_WALL_TAG) ? "muur" : "ton";
			Vector2<int> pos = readBoardPosition(e, board, type, false);
			bool canMove = readBool(attribute(e, PIECE_MOVABLE_ATTR));
			return std::make_shared<Obstacle>(pos, type, canMove);
		}
		else if (value == BOARD_OBSTACLE_TAG) // For legacy purposes
		{
			bool canMove = readBool(attribute(e, PIECE_MOVABLE_ATTR));
			std::string type = canMove ? "ton" : "muur";
			Vector2<int> pos = readBoardPosition(e, board, type, false);
			return std::make_shared<Obstacle>(pos, type, canMove);
		}
		else if (value == BOARD_WATER_TAG) {
			Vector2<int> pos = readBoardPosition(e, board, "water", false);
			bool canMove = readBool(attribute(e, PIECE_MOVABLE_ATTR));
			return std::make_shared<Water>(pos, canMove);
		}
		else if (value == BOARD_GOAL_TAG) {
			Vector2<int> pos = readBoardPosition(e, board, "doel", true);
			return std::make_shared<Goal>(pos);
		}
		else if (value == BOARD_GATE_TAG) {
			auto pos = readBoardPosition(e, board, "poort", false);
			auto name = readStringContents(child(e, BOARD_ID_TAG));
			return std::make_shared<Gate>(pos, name, Buttons[name]);
		}
		else if (value == BOARD_MONSTER_TAG) {
			Vector2<int> pos = readBoardPosition(e, board, "monster", false);
			std::string name(readStringContents(child(e, BOARD_ID_TAG)));
			return std::make_shared<Monster>(pos, name);
		}
		else if (value == BOARD_TRAP_TAG) {
			Vector2<int> pos = readBoardPosition(e, board, "valstrik", false);
			return std::make_shared<Trap>(pos);
		}
		// TODO: other pieces
		else if (value != BOARD_NAME_TAG && value != BOARD_LENGTH_TAG
			&& value != BOARD_WIDTH_TAG && value != BOARD_BUTTON_TAG)
			throw BadPieceException("Onherkenbaar element: " + value + ".");

		return nullptr;
	}

	const XMLElement* getRootElement(const XMLDocument* doc, std::ostream& error_stream)
	{
		const XMLElement *root = nullptr;
		RedirectFeedback([&]()
		{
			root = child(doc, BOARD_TAG);
		}, error_stream);
		return root;
	}

	Board parseBoardHeader(const XMLElement* root, std::ostream& error_stream)
	{
		Board result("Board", { 1, 1 });

		RedirectFeedback([&]()
		{
			// Parse Board data.
			std::string name = readStringContents(child(root, BOARD_NAME_TAG));
			int length = toInt(child(root, BOARD_LENGTH_TAG)->GetText());
			if (length <= 0)
			{
				throw BadXMLException("<BOARD> geeft via <LENGTE> een lengte van " + std::to_string(length) + " op. "
									  "Een minimale lengte van 1 is vereist voor elk bord.");
			}
			int width = toInt(child(root, BOARD_WIDTH_TAG)->GetText());
			if (width <= 0)
			{
				throw BadXMLException("<BOARD> geeft via <BREEDTE> een breedte van " + std::to_string(width) + " op. "
									  "Een minimale breedte van 1 is vereist voor elk bord.");
			}
			Vector2<int> size(width, length);

			result = Board(name, size);
		}, error_stream);

		return result;
	}

	/// \brief Parses a board.
	Board parseBoard(const char *filename, std::ostream &error_stream) {
		XMLDocument doc;
		doc.LoadFile(filename);
		if (doc.Error())
		{
			writeError(doc, error_stream);
			throw BadXMLException("Ongeldige XML in bestand '" + std::string(filename) + "'");
		}

		// Parse Board data.
		const XMLElement *root = getRootElement(&doc, error_stream);
		Board board = parseBoardHeader(root, error_stream);

		auto buttons = ParseButtons(root, board, error_stream);

		// Parse pieces.
		for (auto e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			RedirectFeedback([&]()
			{
				auto pc = parsePiece(e, board, buttons);
				if (pc != nullptr)
				{
					board.AddPiece(pc);
				}
			}, error_stream);
		}

		return board;
	}

	/// \brief Parses a move command document.
	CommandArray parseMoves(const char *filename, const Board &board, std::ostream &error_stream) {
		XMLDocument doc;
		doc.LoadFile(filename);

		if (doc.Error())
		{
			writeError(doc, error_stream);
			RedirectFeedback([&]() // This will print the exception and make the exception bubble up the call stack
			{
				throw BadXMLException("Ongeldige XML in bestand '" + std::string(filename) + "'");
			}, error_stream);
		}

		std::vector<std::shared_ptr<ICommand<std::shared_ptr<Board>>>> moveList;

		// Parse Board data.
		const XMLElement *moves = anyChild(&doc, { ACTIONS_TAG, MOVES_TAG });
		for (auto e = moves->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
		{
			std::string value(e->Name());

			RedirectFeedback([&]()
			{
				if (value != MOVES_MOVE_TAG && value != MOVES_ATTACK_TAG)
				{
					throw BadPieceException("Onherkenbaar element: '" + value + "'.");
				}

				std::string name(readStringContents(anyChild(e, { MOVE_NAME_TAG, BOARD_ID_TAG })));

				auto player = board.GetActorOrNull(name);
				if (player == nullptr)
				{
					throw BadPieceException("Ongeldige naam voor monster of speler: '" + name + "'.");
				}

				std::string dir(child(e, MOVE_DIRECTION_TAG)->GetText());
				Vector2<int> direction = directionVector(dir);

				if (value == MOVES_MOVE_TAG)
				{
					moveList.push_back(std::make_shared<MoveCommand>(player, direction));
				}
				else
				{
					moveList.push_back(std::make_shared<AttackCommand>(player, direction));
				}
			}, error_stream);
		}

		return moveList;
	}
}
