#pragma once
#include <istream>
#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "ParseXML.h"
#include "Board.h"

namespace Arcade
{
	/// \brief Describes a game's status.
	enum GameStatus
	{
		Victory,
		Inconclusive,
		Loss
	};

	/// \brief Checks two input streams for bitwise equality. 
	/// If not, they are dumped to Tests/Oracle.txt and Tests/Specimen.txt for manual review.
	bool BitwiseEquality(std::istream& First, std::istream& Second);
	/// \brief Compares an input stream to the given reference output file.
	/// If not equal, they are dumped to Tests/Oracle.txt and Tests/Specimen.txt for manual review.
	bool BitwiseEquality(std::istream& Result, const std::string& Reference);

	/// \brief Performs an xml board test.
	GameStatus TestXmlBoard(const char* BoardPath, const char* ActionsPath, 
							const char* OutputReferencePath);

	/// \brief Performs an html board test.
	GameStatus TestHtmlBoard(const char* BoardPath, const char* ActionsPath,
							 const char* ReferenceInitialBoardPath, 
							 const char* ReferenceOutputBoardPath);

	/// \brief Performs an ascii board test.
	GameStatus TestASCIIBoard(const char* BoardPath, const char* ActionsPath, 
							  const char* ReferenceInitialBoardPath, 
							  const char* ReferenceOutputBoardPath);

	/// \brief Performs a cg board test.
	GameStatus TestCgBoard(const char* BoardPath, const char* ActionsPath,
						   const char* ReferenceInitialBoardPath,
						   const char* ReferenceOutputBoardPath);

	/// \brief Verifies a board's xml, comparing its error message to the expected message
	/// and checking whether an exception is thrown as expected.
	/// True is returned if the test performs as expected. Otherwise, false.
	bool VerifyBoardXml(const char* Path, bool ExpectException, const char* ExpectedMessage);

#define TEST_XML_BOARD(NAME)								\
    TestXmlBoard("Tests/" #NAME "/Board.xml",				\
                 "Tests/" #NAME "/Moves.xml",				\
                 "Tests/" #NAME "/Output.xml")				\

#define XML_TEST(NAME, OUTCOME)								\
    TEST(Xml, NAME)											\
	{														\
		EXPECT_EQ(TEST_XML_BOARD(NAME), OUTCOME);			\
	}

#define TEST_HTML_BOARD(NAME)								\
    TestHtmlBoard("Tests/" #NAME "/Board.xml",				\
                  "Tests/" #NAME "/Moves.xml",				\
                  "Tests/" #NAME "/InitialBoard.html",		\
                  "Tests/" #NAME "/Output.html")

#define HTML_TEST(NAME, OUTCOME)							\
    TEST(Html, NAME)										\
	{														\
		EXPECT_EQ(TEST_HTML_BOARD(NAME), OUTCOME);			\
	}

#define TEST_ASCII_BOARD(NAME)								\
    TestASCIIBoard("Tests/" #NAME "/Board.xml",				\
                   "Tests/" #NAME "/Moves.xml",				\
                   "Tests/" #NAME "/InitialBoard.txt",		\
                   "Tests/" #NAME "/Output.txt")

#define ASCII_TEST(NAME, OUTCOME)							\
    TEST(Simulation, NAME)									\
	{														\
        EXPECT_EQ(TEST_ASCII_BOARD(NAME), OUTCOME);			\
	}

#define TEST_CG_BOARD(NAME)									\
    TestCgBoard("Tests/" #NAME "/Board.xml",				\
                "Tests/" #NAME "/Moves.xml",				\
                "Tests/" #NAME "/InitialBoard.ini",			\
                "Tests/" #NAME "/Output.ini")

#define CG_TEST(NAME, OUTCOME)								\
    TEST(Cg, NAME)											\
	{														\
		EXPECT_EQ(TEST_CG_BOARD(NAME), OUTCOME);			\
	}

#define FULL_TEST(NAME, OUTCOME)							\
	ASCII_TEST(NAME, OUTCOME)								\
	HTML_TEST(NAME, OUTCOME)								\
	XML_TEST(NAME, OUTCOME)									\
	CG_TEST(NAME, OUTCOME)

// For errors we can't recover from
#define BAD_XML_BOARD_TEST(NAME, MESSAGE)					\
	TEST(BadXml, NAME)										\
	{														\
		std::ostringstream errstr;							\
		EXPECT_THROW(										\
			parseBoard("Tests/" #NAME "/Board.xml",			\
			errstr),										\
			BadXMLException);								\
		EXPECT_EQ(trimString(errstr.str()), MESSAGE);		\
	}

// For errors we can recover from
#define INVALID_XML_BOARD_TEST(NAME, MESSAGE)				\
	TEST(InvalidXml, NAME)									\
	{														\
		std::ostringstream errstr;							\
		parseBoard("Tests/" #NAME "/Board.xml",			    \
				   errstr);								    \
		EXPECT_EQ(trimString(errstr.str()), MESSAGE);		\
	}

// For errors we can recover from
#define BAD_XML_MOVES_TEST(NAME, MESSAGE)					\
	TEST(BadXml, NAME)										\
	{														\
		std::ostringstream errstr;							\
		auto board = std::make_shared<Arcade::Board>(		\
			parseBoard("Tests/" #NAME "/Board.xml",			\
			errstr));										\
		EXPECT_EQ(trimString(errstr.str()), "");			\
		EXPECT_THROW(parseMoves(							\
			"Tests/" #NAME "/Moves.xml",					\
			*board, errstr),								\
			BadXMLException);								\
		EXPECT_EQ(trimString(errstr.str()), MESSAGE);		\
	}

// For errors we can recover from
#define INVALID_XML_MOVES_TEST(NAME, MESSAGE)				\
	TEST(InvalidXml, NAME)									\
	{														\
		std::ostringstream errstr;							\
		auto board = std::make_shared<Arcade::Board>(		\
			parseBoard("Tests/" #NAME "/Board.xml",			\
			errstr));										\
		EXPECT_EQ(trimString(errstr.str()), "");			\
		parseMoves("Tests/" #NAME "/Moves.xml",				\
				   *board, errstr);							\
		EXPECT_EQ(trimString(errstr.str()), MESSAGE);		\
	}
}