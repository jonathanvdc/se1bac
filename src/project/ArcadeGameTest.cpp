// Tests for version 1.0 of the specification.

#include <memory>
#include <fstream>
#include <sstream>
#include "gtest/gtest.h"
#include "Board.h"
#include "Obstacle.h"
#include "MoveCommand.h"
#include "ParseXML.h"
#include "TestHelpers.h"

using namespace Arcade;

const char AssertionFailedRegex[] = ".*";
const std::string BoardName = "Flanders' House";
const std::string PlayerName = "Ned";
const std::string ObstacleName = "wall";

TEST(HappyDay, Diddlydoodely)
{
	auto brd = Board(BoardName, { 3, 9 });
	auto flanders = std::make_shared<Player>(Vector2<int>(0, 0), PlayerName);
	auto wall = std::make_shared<Obstacle>(Vector2<int>(1, 1), ObstacleName, false);

	brd.AddPiece(flanders);
	brd.AddPiece(wall);

	EXPECT_EQ(brd.GetPieces().size(), 2);
	EXPECT_EQ(brd.GetPlayers().size(), 1);
	EXPECT_EQ(brd.GetWidth(), 3);
	EXPECT_EQ(brd.GetHeight(), 9);

	EXPECT_TRUE(brd.HasActor(PlayerName));
	auto player = brd.GetActor(PlayerName);
	EXPECT_EQ(player, flanders);
	auto item = brd.GetItem(1, 1);
	EXPECT_EQ(item, wall);
}

TEST(HappyDay, NonexistantPieceQuery)
{
	Board brd(BoardName, { 15, 15 });

	EXPECT_EQ(brd.GetItem(0, 0), nullptr);
}

TEST(HappyDay, Movement)
{
	auto brd = std::make_shared<Board>(BoardName, Vector2<int>(15, 15));
	auto flanders = std::make_shared<Player>(Vector2<int>(0, 1), PlayerName);
	auto wall = std::make_shared<Obstacle>(Vector2<int>(0, 2), ObstacleName, true); // Ned can move this wall. Never underestimate Flanders.

	brd->AddPiece(flanders);
	brd->AddPiece(wall);

	MoveCommand movement(flanders, { 0, 1 });
	EXPECT_TRUE(movement.Execute(brd)); // We expect this to succeed.
	EXPECT_EQ(flanders->GetPosition(), Vector2<int>(0, 2)); // Make sure the pieces have actually moved
	EXPECT_EQ(wall->GetPosition(), Vector2<int>(0, 3));
}

TEST(HappyDay, HappyParser)
{
	std::ostringstream errstr;

	auto board = parseBoard("Tests/HappyParserBoard.xml", errstr);
	auto moves = parseMoves("Tests/HappyParserMoves.xml", board, errstr);

	EXPECT_TRUE(errstr.str().empty());
}

TEST(HappyDay, HappyOutput)
{
	std::ostringstream errstr;
	std::stringstream expectedBoardOutput;
	expectedBoardOutput << "Bestand: " << "HappyBoardOutput.txt" << std::endl << std::endl;
	std::stringstream expectedMoveOutput;
	expectedMoveOutput << "Bestand: " << "HappyMovesOutput.txt" << std::endl << std::endl;

	auto board = std::make_shared<Board>(parseBoard("Tests/HappyBoard.xml", errstr));
	auto moves = parseMoves("Tests/HappyMoves.xml", *board, errstr);

	EXPECT_TRUE(errstr.str().empty());

	TextUIHandler handler(&expectedBoardOutput, &errstr, false);
	handler.Initialize(board);
	EXPECT_TRUE(BitwiseEquality(expectedBoardOutput, "Tests/HappyBoardOutput.txt"));
	handler.SetOutputStream(&expectedMoveOutput);
	for (auto& item : moves)
	{
		handler.Apply(item);
	}
	EXPECT_TRUE(BitwiseEquality(expectedMoveOutput, "Tests/HappyMovesOutput.txt"));
}

TEST(HappyDay, RemovePlayer)
{
	auto brd = std::make_shared<Board>(BoardName, Vector2<int>(15, 15));
	auto barrel = std::make_shared<Obstacle>(Vector2<int>(0, 0), "barrel", true);
	auto flanders = std::make_shared<Player>(Vector2<int>(0, 1), PlayerName);
	auto wall = std::make_shared<Obstacle>(Vector2<int>(0, 2), ObstacleName, false);

	brd->AddPiece(barrel);
	brd->AddPiece(flanders);
	brd->AddPiece(wall);

	EXPECT_TRUE(brd->RemovePiece(flanders));

	EXPECT_FALSE(brd->HasActor(flanders->GetName()));
	EXPECT_EQ(brd->GetPieces().size(), 2);
}

TEST(BadOutput, NullOutput)
{
	std::ostringstream errstr;
	std::ostringstream output;
	TextUIHandler handler(&output, &errstr, false);
	EXPECT_DEATH(handler.Initialize(nullptr), AssertionFailedRegex);
}

TEST(BadOutput, NullOutputStream)
{
	EXPECT_DEATH(TextUIHandler(nullptr, nullptr, false), AssertionFailedRegex);
}

TEST(BadOutput, UninitializedOutput)
{
	std::ostringstream errstr;
	std::ostringstream output;
	TextUIHandler handler(&output, &errstr, false);
	EXPECT_DEATH(handler.Display(), AssertionFailedRegex);
}

TEST(BadOutput, TwiceInitializedOutput)
{
	std::ostringstream errstr;
	std::ostringstream output;
	TextUIHandler handler(&output, &errstr, false);
	handler.Initialize(std::make_shared<Board>(BoardName, Vector2<int>(15, 15)));
	EXPECT_DEATH(handler.Initialize(std::make_shared<Board>(BoardName, Vector2<int>(15, 15))), AssertionFailedRegex);
}

TEST(BadOutput, InvalidMovement)
{
	std::ostringstream errstr;
	std::ostringstream output;
	TextUIHandler handler(&output, &errstr, true);

	auto brd = std::make_shared<Board>(BoardName, Vector2<int>(15, 15));
	auto bart = std::make_shared<Player>(Vector2<int>(0, 1), "Bart");
	auto wall = std::make_shared<Obstacle>(Vector2<int>(0, 2), ObstacleName, false);

	brd->AddPiece(bart);
	brd->AddPiece(wall);

	handler.Initialize(brd);

	auto movement = std::make_shared<MoveCommand>(bart, Vector2<int>(0, 1));
	handler.Apply(movement);
	EXPECT_FALSE(errstr.str().empty()); // Make sure an error message has been printed
	EXPECT_EQ(bart->GetPosition(), Vector2<int>(0, 1)); // Make sure the pieces haven't actually moved
	EXPECT_EQ(wall->GetPosition(), Vector2<int>(0, 2));
}

TEST(BadDay, InvalidMovement)
{
	auto brd = std::make_shared<Board>(BoardName, Vector2<int>(15, 15));
	auto bart = std::make_shared<Player>(Vector2<int>(0, 1), "Bart");
	auto wall = std::make_shared<Obstacle>(Vector2<int>(0, 2), ObstacleName, false);

	brd->AddPiece(bart);
	brd->AddPiece(wall);

	MoveCommand movement(bart, { 0, 1 });
	EXPECT_FALSE(movement.Execute(brd)); // We expect this to fail.
	EXPECT_EQ(bart->GetPosition(), Vector2<int>(0, 1)); // Make sure the pieces haven't actually moved
	EXPECT_EQ(wall->GetPosition(), Vector2<int>(0, 2));
}

TEST(BadDay, EmptyName)
{
	EXPECT_DEATH(Player(Vector2<int>(0, 0), ""), AssertionFailedRegex);
}

TEST(BadDay, OutOfBoundsQuery)
{
	Board brd(BoardName, { 4, 6 });

	EXPECT_DEATH(brd.GetItem(10, 2), AssertionFailedRegex);
	EXPECT_DEATH(brd.GetItem(-3, 0), AssertionFailedRegex);
	EXPECT_DEATH(brd.GetItem(4, 6), AssertionFailedRegex);
}

TEST(BadDay, OutOfBoundsPiece)
{
	Board brd(BoardName, { 4, 6 });

	auto wall = std::make_shared<Obstacle>(Vector2<int>(-1, -1), ObstacleName, false);
	EXPECT_DEATH(brd.AddPiece(wall), AssertionFailedRegex);
	EXPECT_DEATH(brd.GetItem(-1, -1), AssertionFailedRegex);
}

TEST(BadDay, ZeroDimensions)
{
	EXPECT_DEATH(Board(BoardName, { 0, 0 }), AssertionFailedRegex);
}

TEST(BadDay, NegativeXDimension)
{
	EXPECT_DEATH(Board(BoardName, { -1, 5 }), AssertionFailedRegex);
}

TEST(BadDay, NegativeYDimension)
{
	EXPECT_DEATH(Board(BoardName, { 2, -5 }), AssertionFailedRegex);
}

TEST(BadDay, InvalidPlayerQuery)
{
	Board brd(BoardName, { 10, 10 });

	auto player = brd.GetActorOrNull(PlayerName);
	EXPECT_EQ(player, nullptr);
	EXPECT_FALSE(brd.HasActor(PlayerName));
	EXPECT_DEATH(brd.GetActor(PlayerName), AssertionFailedRegex);
}

TEST(BadDay, Overlap)
{
	auto brd = Board(BoardName, { 10, 10 });
	brd.AddPiece(std::make_shared<Player>(Vector2<int>(0, 0), PlayerName));
	auto obstacle = std::make_shared<Obstacle>(Vector2<int>(0, 0), ObstacleName, false);
	EXPECT_DEATH(brd.AddPiece(obstacle), AssertionFailedRegex);
}

TEST(HorribleDay, BadXML)
{
	std::ostringstream errstr;
	EXPECT_THROW(parseBoard("Tests/HorribleBoard.xml", errstr), BadXMLException);
	EXPECT_EQ(trimString(errstr.str()), "XML document error: id='16' ('XML_ERROR_MISMATCHED_ELEMENT') str1='NAAM'");
}

TEST(HorribleDay, MissingTags)
{
	std::ostringstream errstr;
	EXPECT_THROW(parseBoard("Tests/MissingTagsBoard.xml", errstr), MissingTagException);
	EXPECT_EQ(trimString(errstr.str()), "Verwachtte <NAAM> tag binnen <VELD>.");
}

TEST(HorribleDay, MissingAttributes)
{
	std::ostringstream errstr;
	EXPECT_THROW(parseBoard("Tests/MissingAttributesBoard.xml", errstr), BadXMLException);
	EXPECT_EQ(trimString(errstr.str()), "Verwachtte \"x\" attribute binnen <SPELER>."); // This should print an error to the error stream.
}

TEST(MaliciousDay, ModifiedBits)
{
	char data[sizeof(Board)] = { 0 };
	Board* badPtr = (Board*)data;
	EXPECT_DEATH(badPtr->CheckInvariants(), AssertionFailedRegex);
}