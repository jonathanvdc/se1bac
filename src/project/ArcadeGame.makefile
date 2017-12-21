# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-I"gtest-1.7.0/include"
Release_Include_Path=-I"gtest-1.7.0/include"

# Library paths...
Debug_Library_Path=
Release_Library_Path=

# Additional libraries...
Debug_Libraries=
Release_Libraries=

# Preprocessor definitions...
Debug_Preprocessor_Definitions=-D GCC_BUILD -D _DEBUG -D _CONSOLE -D _LIB
Release_Preprocessor_Definitions=-D GCC_BUILD -D NDEBUG -D _CONSOLE -D _LIB

# Implictly linked object files...
Debug_Implicitly_Linked_Objects=
Release_Implicitly_Linked_Objects=

# Compiler flags...
Debug_Compiler_Flags=-O0 -std=c++11 -g
Release_Compiler_Flags=-O2 -std=c++11

# Builds all configurations for this project...
.PHONY: build_all_configurations
build_all_configurations: Debug Release

# Builds the Debug configuration...
.PHONY: Debug
Debug: create_folders gccDebug/tinyxml2.o gccDebug/Actor.o gccDebug/ASCIIArtUIHandler.o gccDebug/AttackCommand.o gccDebug/Board.o gccDebug/Button.o gccDebug/CGUIHandler.o gccDebug/Collision.o gccDebug/CommandLineUI.o gccDebug/FileNames.o gccDebug/Gate.o gccDebug/Goal.o gccDebug/HtmlUIHandler.o gccDebug/InteractiveUIHandler.o gccDebug/Main.o gccDebug/Monster.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/ParseXML.o gccDebug/PieceBase.o gccDebug/PieceUIHandlerBase.o gccDebug/Player.o gccDebug/TextUIHandler.o gccDebug/Trap.o gccDebug/UIHandlerBase.o gccDebug/UnorderedPieceUIHandlerBase.o gccDebug/Water.o gccDebug/XmlUIHandler.o
	$(CPP_COMPILER) gccDebug/tinyxml2.o gccDebug/Actor.o gccDebug/ASCIIArtUIHandler.o gccDebug/AttackCommand.o gccDebug/Board.o gccDebug/Button.o gccDebug/CGUIHandler.o gccDebug/Collision.o gccDebug/CommandLineUI.o gccDebug/FileNames.o gccDebug/Gate.o gccDebug/Goal.o gccDebug/HtmlUIHandler.o gccDebug/InteractiveUIHandler.o gccDebug/Main.o gccDebug/Monster.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/ParseXML.o gccDebug/PieceBase.o gccDebug/PieceUIHandlerBase.o gccDebug/Player.o gccDebug/TextUIHandler.o gccDebug/Trap.o gccDebug/UIHandlerBase.o gccDebug/UnorderedPieceUIHandlerBase.o gccDebug/Water.o gccDebug/XmlUIHandler.o $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o gccDebug/ArcadeGame

# Compiles file ../tinyxml2/tinyxml2.cpp for the Debug configuration...
-include gccDebug/tinyxml2.d
gccDebug/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) -o gccDebug/tinyxml2.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) > gccDebug/tinyxml2.d

# Compiles file Actor.cpp for the Debug configuration...
-include gccDebug/Actor.d
gccDebug/Actor.o: Actor.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Actor.cpp $(Debug_Include_Path) -o gccDebug/Actor.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Actor.cpp $(Debug_Include_Path) > gccDebug/Actor.d

# Compiles file ASCIIArtUIHandler.cpp for the Debug configuration...
-include gccDebug/ASCIIArtUIHandler.d
gccDebug/ASCIIArtUIHandler.o: ASCIIArtUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ASCIIArtUIHandler.cpp $(Debug_Include_Path) -o gccDebug/ASCIIArtUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ASCIIArtUIHandler.cpp $(Debug_Include_Path) > gccDebug/ASCIIArtUIHandler.d

# Compiles file AttackCommand.cpp for the Debug configuration...
-include gccDebug/AttackCommand.d
gccDebug/AttackCommand.o: AttackCommand.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c AttackCommand.cpp $(Debug_Include_Path) -o gccDebug/AttackCommand.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM AttackCommand.cpp $(Debug_Include_Path) > gccDebug/AttackCommand.d

# Compiles file Board.cpp for the Debug configuration...
-include gccDebug/Board.d
gccDebug/Board.o: Board.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Board.cpp $(Debug_Include_Path) -o gccDebug/Board.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Board.cpp $(Debug_Include_Path) > gccDebug/Board.d

# Compiles file Button.cpp for the Debug configuration...
-include gccDebug/Button.d
gccDebug/Button.o: Button.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Button.cpp $(Debug_Include_Path) -o gccDebug/Button.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Button.cpp $(Debug_Include_Path) > gccDebug/Button.d

# Compiles file CGUIHandler.cpp for the Debug configuration...
-include gccDebug/CGUIHandler.d
gccDebug/CGUIHandler.o: CGUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c CGUIHandler.cpp $(Debug_Include_Path) -o gccDebug/CGUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM CGUIHandler.cpp $(Debug_Include_Path) > gccDebug/CGUIHandler.d

# Compiles file Collision.cpp for the Debug configuration...
-include gccDebug/Collision.d
gccDebug/Collision.o: Collision.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Collision.cpp $(Debug_Include_Path) -o gccDebug/Collision.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Collision.cpp $(Debug_Include_Path) > gccDebug/Collision.d

# Compiles file CommandLineUI.cpp for the Debug configuration...
-include gccDebug/CommandLineUI.d
gccDebug/CommandLineUI.o: CommandLineUI.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c CommandLineUI.cpp $(Debug_Include_Path) -o gccDebug/CommandLineUI.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM CommandLineUI.cpp $(Debug_Include_Path) > gccDebug/CommandLineUI.d

# Compiles file FileNames.cpp for the Debug configuration...
-include gccDebug/FileNames.d
gccDebug/FileNames.o: FileNames.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c FileNames.cpp $(Debug_Include_Path) -o gccDebug/FileNames.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM FileNames.cpp $(Debug_Include_Path) > gccDebug/FileNames.d

# Compiles file Gate.cpp for the Debug configuration...
-include gccDebug/Gate.d
gccDebug/Gate.o: Gate.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Gate.cpp $(Debug_Include_Path) -o gccDebug/Gate.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Gate.cpp $(Debug_Include_Path) > gccDebug/Gate.d

# Compiles file Goal.cpp for the Debug configuration...
-include gccDebug/Goal.d
gccDebug/Goal.o: Goal.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Goal.cpp $(Debug_Include_Path) -o gccDebug/Goal.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Goal.cpp $(Debug_Include_Path) > gccDebug/Goal.d

# Compiles file HtmlUIHandler.cpp for the Debug configuration...
-include gccDebug/HtmlUIHandler.d
gccDebug/HtmlUIHandler.o: HtmlUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c HtmlUIHandler.cpp $(Debug_Include_Path) -o gccDebug/HtmlUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM HtmlUIHandler.cpp $(Debug_Include_Path) > gccDebug/HtmlUIHandler.d

# Compiles file InteractiveUIHandler.cpp for the Debug configuration...
-include gccDebug/InteractiveUIHandler.d
gccDebug/InteractiveUIHandler.o: InteractiveUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c InteractiveUIHandler.cpp $(Debug_Include_Path) -o gccDebug/InteractiveUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM InteractiveUIHandler.cpp $(Debug_Include_Path) > gccDebug/InteractiveUIHandler.d

# Compiles file Main.cpp for the Debug configuration...
-include gccDebug/Main.d
gccDebug/Main.o: Main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Main.cpp $(Debug_Include_Path) -o gccDebug/Main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Main.cpp $(Debug_Include_Path) > gccDebug/Main.d

# Compiles file Monster.cpp for the Debug configuration...
-include gccDebug/Monster.d
gccDebug/Monster.o: Monster.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Monster.cpp $(Debug_Include_Path) -o gccDebug/Monster.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Monster.cpp $(Debug_Include_Path) > gccDebug/Monster.d

# Compiles file MoveCommand.cpp for the Debug configuration...
-include gccDebug/MoveCommand.d
gccDebug/MoveCommand.o: MoveCommand.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c MoveCommand.cpp $(Debug_Include_Path) -o gccDebug/MoveCommand.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM MoveCommand.cpp $(Debug_Include_Path) > gccDebug/MoveCommand.d

# Compiles file Obstacle.cpp for the Debug configuration...
-include gccDebug/Obstacle.d
gccDebug/Obstacle.o: Obstacle.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Obstacle.cpp $(Debug_Include_Path) -o gccDebug/Obstacle.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Obstacle.cpp $(Debug_Include_Path) > gccDebug/Obstacle.d

# Compiles file ParseXML.cpp for the Debug configuration...
-include gccDebug/ParseXML.d
gccDebug/ParseXML.o: ParseXML.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ParseXML.cpp $(Debug_Include_Path) -o gccDebug/ParseXML.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ParseXML.cpp $(Debug_Include_Path) > gccDebug/ParseXML.d

# Compiles file PieceBase.cpp for the Debug configuration...
-include gccDebug/PieceBase.d
gccDebug/PieceBase.o: PieceBase.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c PieceBase.cpp $(Debug_Include_Path) -o gccDebug/PieceBase.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM PieceBase.cpp $(Debug_Include_Path) > gccDebug/PieceBase.d

# Compiles file PieceUIHandlerBase.cpp for the Debug configuration...
-include gccDebug/PieceUIHandlerBase.d
gccDebug/PieceUIHandlerBase.o: PieceUIHandlerBase.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c PieceUIHandlerBase.cpp $(Debug_Include_Path) -o gccDebug/PieceUIHandlerBase.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM PieceUIHandlerBase.cpp $(Debug_Include_Path) > gccDebug/PieceUIHandlerBase.d

# Compiles file Player.cpp for the Debug configuration...
-include gccDebug/Player.d
gccDebug/Player.o: Player.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Player.cpp $(Debug_Include_Path) -o gccDebug/Player.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Player.cpp $(Debug_Include_Path) > gccDebug/Player.d

# Compiles file TextUIHandler.cpp for the Debug configuration...
-include gccDebug/TextUIHandler.d
gccDebug/TextUIHandler.o: TextUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c TextUIHandler.cpp $(Debug_Include_Path) -o gccDebug/TextUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM TextUIHandler.cpp $(Debug_Include_Path) > gccDebug/TextUIHandler.d

# Compiles file Trap.cpp for the Debug configuration...
-include gccDebug/Trap.d
gccDebug/Trap.o: Trap.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Trap.cpp $(Debug_Include_Path) -o gccDebug/Trap.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Trap.cpp $(Debug_Include_Path) > gccDebug/Trap.d

# Compiles file UIHandlerBase.cpp for the Debug configuration...
-include gccDebug/UIHandlerBase.d
gccDebug/UIHandlerBase.o: UIHandlerBase.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c UIHandlerBase.cpp $(Debug_Include_Path) -o gccDebug/UIHandlerBase.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM UIHandlerBase.cpp $(Debug_Include_Path) > gccDebug/UIHandlerBase.d

# Compiles file UnorderedPieceUIHandlerBase.cpp for the Debug configuration...
-include gccDebug/UnorderedPieceUIHandlerBase.d
gccDebug/UnorderedPieceUIHandlerBase.o: UnorderedPieceUIHandlerBase.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c UnorderedPieceUIHandlerBase.cpp $(Debug_Include_Path) -o gccDebug/UnorderedPieceUIHandlerBase.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM UnorderedPieceUIHandlerBase.cpp $(Debug_Include_Path) > gccDebug/UnorderedPieceUIHandlerBase.d

# Compiles file Water.cpp for the Debug configuration...
-include gccDebug/Water.d
gccDebug/Water.o: Water.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Water.cpp $(Debug_Include_Path) -o gccDebug/Water.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Water.cpp $(Debug_Include_Path) > gccDebug/Water.d

# Compiles file XmlUIHandler.cpp for the Debug configuration...
-include gccDebug/XmlUIHandler.d
gccDebug/XmlUIHandler.o: XmlUIHandler.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c XmlUIHandler.cpp $(Debug_Include_Path) -o gccDebug/XmlUIHandler.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM XmlUIHandler.cpp $(Debug_Include_Path) > gccDebug/XmlUIHandler.d

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/tinyxml2.o gccRelease/Actor.o gccRelease/ASCIIArtUIHandler.o gccRelease/AttackCommand.o gccRelease/Board.o gccRelease/Button.o gccRelease/CGUIHandler.o gccRelease/Collision.o gccRelease/CommandLineUI.o gccRelease/FileNames.o gccRelease/Gate.o gccRelease/Goal.o gccRelease/HtmlUIHandler.o gccRelease/InteractiveUIHandler.o gccRelease/Main.o gccRelease/Monster.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/ParseXML.o gccRelease/PieceBase.o gccRelease/PieceUIHandlerBase.o gccRelease/Player.o gccRelease/TextUIHandler.o gccRelease/Trap.o gccRelease/UIHandlerBase.o gccRelease/UnorderedPieceUIHandlerBase.o gccRelease/Water.o gccRelease/XmlUIHandler.o
	$(CPP_COMPILER) gccRelease/tinyxml2.o gccRelease/Actor.o gccRelease/ASCIIArtUIHandler.o gccRelease/AttackCommand.o gccRelease/Board.o gccRelease/Button.o gccRelease/CGUIHandler.o gccRelease/Collision.o gccRelease/CommandLineUI.o gccRelease/FileNames.o gccRelease/Gate.o gccRelease/Goal.o gccRelease/HtmlUIHandler.o gccRelease/InteractiveUIHandler.o gccRelease/Main.o gccRelease/Monster.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/ParseXML.o gccRelease/PieceBase.o gccRelease/PieceUIHandlerBase.o gccRelease/Player.o gccRelease/TextUIHandler.o gccRelease/Trap.o gccRelease/UIHandlerBase.o gccRelease/UnorderedPieceUIHandlerBase.o gccRelease/Water.o gccRelease/XmlUIHandler.o $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/ArcadeGame

# Compiles file ../tinyxml2/tinyxml2.cpp for the Release configuration...
-include gccRelease/tinyxml2.d
gccRelease/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) -o gccRelease/tinyxml2.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) > gccRelease/tinyxml2.d

# Compiles file Actor.cpp for the Release configuration...
-include gccRelease/Actor.d
gccRelease/Actor.o: Actor.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Actor.cpp $(Release_Include_Path) -o gccRelease/Actor.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Actor.cpp $(Release_Include_Path) > gccRelease/Actor.d

# Compiles file ASCIIArtUIHandler.cpp for the Release configuration...
-include gccRelease/ASCIIArtUIHandler.d
gccRelease/ASCIIArtUIHandler.o: ASCIIArtUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ASCIIArtUIHandler.cpp $(Release_Include_Path) -o gccRelease/ASCIIArtUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ASCIIArtUIHandler.cpp $(Release_Include_Path) > gccRelease/ASCIIArtUIHandler.d

# Compiles file AttackCommand.cpp for the Release configuration...
-include gccRelease/AttackCommand.d
gccRelease/AttackCommand.o: AttackCommand.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c AttackCommand.cpp $(Release_Include_Path) -o gccRelease/AttackCommand.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM AttackCommand.cpp $(Release_Include_Path) > gccRelease/AttackCommand.d

# Compiles file Board.cpp for the Release configuration...
-include gccRelease/Board.d
gccRelease/Board.o: Board.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Board.cpp $(Release_Include_Path) -o gccRelease/Board.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Board.cpp $(Release_Include_Path) > gccRelease/Board.d

# Compiles file Button.cpp for the Release configuration...
-include gccRelease/Button.d
gccRelease/Button.o: Button.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Button.cpp $(Release_Include_Path) -o gccRelease/Button.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Button.cpp $(Release_Include_Path) > gccRelease/Button.d

# Compiles file CGUIHandler.cpp for the Release configuration...
-include gccRelease/CGUIHandler.d
gccRelease/CGUIHandler.o: CGUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c CGUIHandler.cpp $(Release_Include_Path) -o gccRelease/CGUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM CGUIHandler.cpp $(Release_Include_Path) > gccRelease/CGUIHandler.d

# Compiles file Collision.cpp for the Release configuration...
-include gccRelease/Collision.d
gccRelease/Collision.o: Collision.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Collision.cpp $(Release_Include_Path) -o gccRelease/Collision.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Collision.cpp $(Release_Include_Path) > gccRelease/Collision.d

# Compiles file CommandLineUI.cpp for the Release configuration...
-include gccRelease/CommandLineUI.d
gccRelease/CommandLineUI.o: CommandLineUI.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c CommandLineUI.cpp $(Release_Include_Path) -o gccRelease/CommandLineUI.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM CommandLineUI.cpp $(Release_Include_Path) > gccRelease/CommandLineUI.d

# Compiles file FileNames.cpp for the Release configuration...
-include gccRelease/FileNames.d
gccRelease/FileNames.o: FileNames.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c FileNames.cpp $(Release_Include_Path) -o gccRelease/FileNames.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM FileNames.cpp $(Release_Include_Path) > gccRelease/FileNames.d

# Compiles file Gate.cpp for the Release configuration...
-include gccRelease/Gate.d
gccRelease/Gate.o: Gate.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Gate.cpp $(Release_Include_Path) -o gccRelease/Gate.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Gate.cpp $(Release_Include_Path) > gccRelease/Gate.d

# Compiles file Goal.cpp for the Release configuration...
-include gccRelease/Goal.d
gccRelease/Goal.o: Goal.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Goal.cpp $(Release_Include_Path) -o gccRelease/Goal.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Goal.cpp $(Release_Include_Path) > gccRelease/Goal.d

# Compiles file HtmlUIHandler.cpp for the Release configuration...
-include gccRelease/HtmlUIHandler.d
gccRelease/HtmlUIHandler.o: HtmlUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c HtmlUIHandler.cpp $(Release_Include_Path) -o gccRelease/HtmlUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM HtmlUIHandler.cpp $(Release_Include_Path) > gccRelease/HtmlUIHandler.d

# Compiles file InteractiveUIHandler.cpp for the Release configuration...
-include gccRelease/InteractiveUIHandler.d
gccRelease/InteractiveUIHandler.o: InteractiveUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c InteractiveUIHandler.cpp $(Release_Include_Path) -o gccRelease/InteractiveUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM InteractiveUIHandler.cpp $(Release_Include_Path) > gccRelease/InteractiveUIHandler.d

# Compiles file Main.cpp for the Release configuration...
-include gccRelease/Main.d
gccRelease/Main.o: Main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Main.cpp $(Release_Include_Path) -o gccRelease/Main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Main.cpp $(Release_Include_Path) > gccRelease/Main.d

# Compiles file Monster.cpp for the Release configuration...
-include gccRelease/Monster.d
gccRelease/Monster.o: Monster.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Monster.cpp $(Release_Include_Path) -o gccRelease/Monster.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Monster.cpp $(Release_Include_Path) > gccRelease/Monster.d

# Compiles file MoveCommand.cpp for the Release configuration...
-include gccRelease/MoveCommand.d
gccRelease/MoveCommand.o: MoveCommand.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c MoveCommand.cpp $(Release_Include_Path) -o gccRelease/MoveCommand.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM MoveCommand.cpp $(Release_Include_Path) > gccRelease/MoveCommand.d

# Compiles file Obstacle.cpp for the Release configuration...
-include gccRelease/Obstacle.d
gccRelease/Obstacle.o: Obstacle.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Obstacle.cpp $(Release_Include_Path) -o gccRelease/Obstacle.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Obstacle.cpp $(Release_Include_Path) > gccRelease/Obstacle.d

# Compiles file ParseXML.cpp for the Release configuration...
-include gccRelease/ParseXML.d
gccRelease/ParseXML.o: ParseXML.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ParseXML.cpp $(Release_Include_Path) -o gccRelease/ParseXML.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ParseXML.cpp $(Release_Include_Path) > gccRelease/ParseXML.d

# Compiles file PieceBase.cpp for the Release configuration...
-include gccRelease/PieceBase.d
gccRelease/PieceBase.o: PieceBase.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c PieceBase.cpp $(Release_Include_Path) -o gccRelease/PieceBase.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM PieceBase.cpp $(Release_Include_Path) > gccRelease/PieceBase.d

# Compiles file PieceUIHandlerBase.cpp for the Release configuration...
-include gccRelease/PieceUIHandlerBase.d
gccRelease/PieceUIHandlerBase.o: PieceUIHandlerBase.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c PieceUIHandlerBase.cpp $(Release_Include_Path) -o gccRelease/PieceUIHandlerBase.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM PieceUIHandlerBase.cpp $(Release_Include_Path) > gccRelease/PieceUIHandlerBase.d

# Compiles file Player.cpp for the Release configuration...
-include gccRelease/Player.d
gccRelease/Player.o: Player.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Player.cpp $(Release_Include_Path) -o gccRelease/Player.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Player.cpp $(Release_Include_Path) > gccRelease/Player.d

# Compiles file TextUIHandler.cpp for the Release configuration...
-include gccRelease/TextUIHandler.d
gccRelease/TextUIHandler.o: TextUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c TextUIHandler.cpp $(Release_Include_Path) -o gccRelease/TextUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM TextUIHandler.cpp $(Release_Include_Path) > gccRelease/TextUIHandler.d

# Compiles file Trap.cpp for the Release configuration...
-include gccRelease/Trap.d
gccRelease/Trap.o: Trap.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Trap.cpp $(Release_Include_Path) -o gccRelease/Trap.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Trap.cpp $(Release_Include_Path) > gccRelease/Trap.d

# Compiles file UIHandlerBase.cpp for the Release configuration...
-include gccRelease/UIHandlerBase.d
gccRelease/UIHandlerBase.o: UIHandlerBase.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c UIHandlerBase.cpp $(Release_Include_Path) -o gccRelease/UIHandlerBase.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM UIHandlerBase.cpp $(Release_Include_Path) > gccRelease/UIHandlerBase.d

# Compiles file UnorderedPieceUIHandlerBase.cpp for the Release configuration...
-include gccRelease/UnorderedPieceUIHandlerBase.d
gccRelease/UnorderedPieceUIHandlerBase.o: UnorderedPieceUIHandlerBase.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c UnorderedPieceUIHandlerBase.cpp $(Release_Include_Path) -o gccRelease/UnorderedPieceUIHandlerBase.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM UnorderedPieceUIHandlerBase.cpp $(Release_Include_Path) > gccRelease/UnorderedPieceUIHandlerBase.d

# Compiles file Water.cpp for the Release configuration...
-include gccRelease/Water.d
gccRelease/Water.o: Water.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Water.cpp $(Release_Include_Path) -o gccRelease/Water.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Water.cpp $(Release_Include_Path) > gccRelease/Water.d

# Compiles file XmlUIHandler.cpp for the Release configuration...
-include gccRelease/XmlUIHandler.d
gccRelease/XmlUIHandler.o: XmlUIHandler.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c XmlUIHandler.cpp $(Release_Include_Path) -o gccRelease/XmlUIHandler.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM XmlUIHandler.cpp $(Release_Include_Path) > gccRelease/XmlUIHandler.d

# Creates the intermediate and output folders for each configuration...
.PHONY: create_folders
create_folders:
	mkdir -p gccDebug
	mkdir -p gccRelease

# Cleans intermediate and output files (objects, libraries, executables)...
.PHONY: clean
clean:
	rm -f gccDebug/*.o
	rm -f gccDebug/*.d
	rm -f gccDebug/*.a
	rm -f gccDebug/*.so
	rm -f gccDebug/*.dll
	rm -f gccDebug/*.exe
	rm -f gccRelease/*.o
	rm -f gccRelease/*.d
	rm -f gccRelease/*.a
	rm -f gccRelease/*.so
	rm -f gccRelease/*.dll
	rm -f gccRelease/*.exe

