#include "TestHelpers.h"

#include <algorithm>
#include <istream>
#include <fstream>
#include <string>
#include <memory>
#include <typeinfo>

#include "gtest/gtest.h"

#include "Board.h"
#include "PieceBase.h"
#include "FileNames.h"
#include "ParseXML.h"
#include "XmlUIHandler.h"
#include "HtmlUIHandler.h"
#include "TextUIHandler.h"
#include "ASCIIArtUIHandler.h"
#include "CGUIHandler.h"

namespace Arcade
{
	/// \brief Checks two input streams for bitwise equality. 
	/// If not, they are dumped to Tests/Oracle.txt and Tests/Specimen.txt for manual review.
	bool BitwiseEquality(std::istream& First, std::istream& Second)
	{
		std::istreambuf_iterator<char> eos;
		std::string s1(std::istreambuf_iterator<char>(First), eos);
		std::string s2(std::istreambuf_iterator<char>(Second), eos);
		if (s1 == s2)
			return true;

		std::ofstream specimen("Tests/Specimen.txt");
		specimen << s1;
		std::ofstream oracle("Tests/Oracle.txt");
		oracle << s2;
		return false;
	}

	/// \brief Compares an input stream to the given reference output file.
	/// If not equal, they are dumped to Tests/Oracle.txt and Tests/Specimen.txt for manual review.
	bool BitwiseEquality(std::istream& Result, const std::string& Reference)
	{
		Result.seekg(0);
		std::ifstream istr;
		istr.open(Reference);

		return BitwiseEquality(Result, istr);
	}

	bool ContainsPiece(std::shared_ptr<Board> Scene, std::shared_ptr<PieceBase> Piece)
	{
		auto pos = Piece->GetPosition();
		for (auto& item : Scene->GetPieces())
		{
			if (item->GetPosition() == pos && typeid(*item) == typeid(*Piece))
			{
				return true;
			}
		}
		return false;
	}

	bool IsSuperset(std::shared_ptr<Board> Target, std::shared_ptr<Board> Other)
	{
		for (auto& item : Target->GetPieces())
		{
			if (!ContainsPiece(Other, item))
			{
				return false;
			}
		}
		return true;
	}

	bool CheckBoardEquality(std::shared_ptr<Board> Specimen, std::shared_ptr<Board> Oracle)
	{
		return Specimen->GetName() == Oracle->GetName() &&
			Specimen->GetSize() == Oracle->GetSize() &&
			IsSuperset(Specimen, Oracle) &&
			IsSuperset(Oracle, Specimen);
	}

	bool CheckBoardEquality(std::istream& BoardStream, const char* Reference)
	{
		const char tempPath[] = "Tests/TempBoard.xml"; // Must save to temp path because
		// tinyxml does not seem to support <iostream>

		std::ofstream output(tempPath);
		char val;
		while (BoardStream.get(val))
		{
			output << val;
		}
		output.close();

		std::stringstream errstr;
		auto board = std::make_shared<Board>(parseBoard(tempPath, errstr));
		EXPECT_EQ(errstr.str(), "");

		auto refBoard = std::make_shared<Board>(parseBoard(Reference, errstr));
		EXPECT_EQ(errstr.str(), "");

		return CheckBoardEquality(board, refBoard);
	}

	GameStatus TestXmlBoard(const char* BoardPath, const char* ActionsPath, const char* OutputReferencePath)
	{
		std::ostringstream errstr;

		auto board = std::make_shared<Board>(parseBoard(BoardPath, errstr));
		EXPECT_EQ(errstr.str(), "");
		auto moves = parseMoves(ActionsPath, *board, errstr);
		EXPECT_EQ(errstr.str(), "");

		std::stringstream initialBoardOutput;
		XmlUIHandler handler(&initialBoardOutput);
		handler.Initialize(board);
		EXPECT_TRUE(CheckBoardEquality(initialBoardOutput, BoardPath));

		for (auto move : moves)
		{
			move->Execute(board);
		}

		std::stringstream expectedBoardOutput;
		handler.SetOutputStream(&expectedBoardOutput);
		handler.Display();

		EXPECT_TRUE(CheckBoardEquality(expectedBoardOutput, OutputReferencePath));

		return handler.GetHasEnded() ? (handler.GetPlayerHasWon() ? Victory : Loss) : Inconclusive;
	}

	GameStatus TestSlideshowBoard(const char* BoardPath, const char* ActionsPath, 
								  const char* ReferenceInitialBoardPath, const char* ReferenceOutputBoardPath, 
								  std::function<std::shared_ptr<UIHandlerBase>(std::ostream*)> HandlerBuilder)
	{
		std::ostringstream errstr;

		auto board = std::make_shared<Board>(parseBoard(BoardPath, errstr));
		EXPECT_TRUE(errstr.str().empty());
		auto moves = parseMoves(ActionsPath, *board, errstr);
		EXPECT_TRUE(errstr.str().empty());

		std::stringstream initialBoardOutput;
		auto handlerPtr = HandlerBuilder(&initialBoardOutput);
		UIHandlerBase& handler = *handlerPtr;
		handler.Initialize(board);
		EXPECT_TRUE(BitwiseEquality(initialBoardOutput, ReferenceInitialBoardPath));

		for (int i = 0; i < moves.GetLength(); i++)
		{
			std::stringstream expectedBoardOutput;
			handler.SetOutputStream(&expectedBoardOutput);

			moves[i]->Execute(board);
			handler.Display();

			EXPECT_TRUE(BitwiseEquality(expectedBoardOutput, AppendToFilename(ReferenceOutputBoardPath, std::to_string(i))));
		}

		return handler.GetHasEnded() ? (handler.GetPlayerHasWon() ? Victory : Loss) : Inconclusive;
	}

	GameStatus TestHtmlBoard(const char* BoardPath, const char* ActionsPath, const char* ReferenceInitialBoardPath, const char* ReferenceOutputBoardPath)
	{
		return TestSlideshowBoard(BoardPath, ActionsPath,
			ReferenceInitialBoardPath, ReferenceOutputBoardPath,
			[](std::ostream* output) { return std::make_shared<HtmlUIHandler>(output); });
	}

	GameStatus TestASCIIBoard(const char* BoardPath, const char* ActionsPath, const char* ReferenceInitialBoardPath, const char* ReferenceOutputBoardPath)
	{
		std::ostringstream errstr;

		auto board = std::make_shared<Board>(parseBoard(BoardPath, errstr));
		EXPECT_TRUE(errstr.str().empty());
		auto moves = parseMoves(ActionsPath, *board, errstr);
		EXPECT_TRUE(errstr.str().empty());

		std::stringstream initialBoardOutput;
		ASCIIArtUIHandler handler(&initialBoardOutput);
		handler.Initialize(board);
		EXPECT_TRUE(BitwiseEquality(initialBoardOutput, ReferenceInitialBoardPath));

		std::stringstream expectedBoardOutput;
		handler.SetOutputStream(&expectedBoardOutput);

		for (auto move : moves)
		{
			move->Execute(board);
			handler.Display();
			*handler.GetOutputStream() << std::endl;
		}

		EXPECT_TRUE(BitwiseEquality(expectedBoardOutput, ReferenceOutputBoardPath));

		return handler.GetHasEnded() ? (handler.GetPlayerHasWon() ? Victory : Loss) : Inconclusive;
	}

	GameStatus TestCgBoard(const char* BoardPath, const char* ActionsPath, const char* ReferenceInitialBoardPath, const char* ReferenceOutputBoardPath)
	{
		return TestSlideshowBoard(BoardPath, ActionsPath,
			ReferenceInitialBoardPath, ReferenceOutputBoardPath,
			[](std::ostream* output) { return std::make_shared<CGUIHandler>(output); });
	}
}