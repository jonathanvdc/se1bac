// Tests for version 2.0 of the specification.

#include "TestHelpers.h"

using namespace Arcade;

XML_TEST(HappyXml, Inconclusive)

FULL_TEST(Barrels, Inconclusive)
FULL_TEST(Drowning, Loss)
FULL_TEST(Victory, Victory)
FULL_TEST(Traps, Loss)
FULL_TEST(TrapsBarrels, Inconclusive)
FULL_TEST(Monsters, Loss)
FULL_TEST(Attacks, Inconclusive)
FULL_TEST(Gates, Inconclusive)
FULL_TEST(GatesTwoToOne, Inconclusive)
FULL_TEST(GatesOneToTwo, Inconclusive)
FULL_TEST(GatesBarrels, Inconclusive)
FULL_TEST(Multiplayer, Inconclusive)
FULL_TEST(MultiplayerGates, Inconclusive)
FULL_TEST(MultiplayerAttacks, Inconclusive)
FULL_TEST(Level1, Victory)
FULL_TEST(Level2, Victory)
FULL_TEST(Level3, Inconclusive)
FULL_TEST(Level4, Inconclusive)
FULL_TEST(Floor, Loss)
FULL_TEST(UnlinkedGate, Inconclusive)
FULL_TEST(UnlinkedButton, Inconclusive)

// ----------------------------
// Things we can't recover from
// ----------------------------

// There is NO test file for this test. This is intentional.
BAD_XML_BOARD_TEST(MissingBoard, "XML document error: id='3' ('XML_ERROR_FILE_NOT_FOUND') str1='Tests/MissingBoard/Board.xml'")

BAD_XML_BOARD_TEST(DuplicateTag, "<ID> kwam meer dan eens voor in <POORT>")
BAD_XML_BOARD_TEST(DuplicateName, "<NAAM> kwam meer dan eens voor in <VELD>")
BAD_XML_MOVES_TEST(DuplicateEquivalentTag, "<ID> en een equivalente tag kwamen allebei voor in <BEWEGING>")
BAD_XML_BOARD_TEST(InvalidWidth, "<BOARD> geeft via <BREEDTE> een breedte van -7 op. Een minimale breedte van 1 is vereist voor elk bord.")
BAD_XML_BOARD_TEST(InvalidLength, "<BOARD> geeft via <LENGTE> een lengte van 0 op. Een minimale lengte van 1 is vereist voor elk bord.")
BAD_XML_BOARD_TEST(BadWidthAndLength, "<BOARD> geeft via <LENGTE> een lengte van 0 op. Een minimale lengte van 1 is vereist voor elk bord.")

// --------------------------
// Things we can recover from
// --------------------------
INVALID_XML_BOARD_TEST(InvalidPosition, "Ongeldige positie (10, 1) voor ton.")
INVALID_XML_BOARD_TEST(OverlappingPosition, "Positie (5, 2) voor ton al bezet.")
INVALID_XML_BOARD_TEST(InvalidAndOverlappingPosition, "Positie (5, 2) voor ton al bezet.\nOngeldige positie (10, 4) voor ton.")
INVALID_XML_BOARD_TEST(Seafarer, "Positie (3, 1) voor water al bezet.")
INVALID_XML_MOVES_TEST(MissingPlayer, "Ongeldige naam voor monster of speler: 'Zip'.")