# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=
Release_Include_Path=

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
Debug: create_folders gccDebug/tinyxml2.o gccDebug/Board.o gccDebug/Main.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/ParseXML.o gccDebug/PieceBase.o gccDebug/Player.o gccDebug/TextUIHandler.o
	$(CPP_COMPILER) gccDebug/tinyxml2.o gccDebug/Board.o gccDebug/Main.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/ParseXML.o gccDebug/PieceBase.o gccDebug/Player.o gccDebug/TextUIHandler.o $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o gccDebug/ArcadeGame

# Compiles file ../tinyxml2/tinyxml2.cpp for the Debug configuration...
-include gccDebug/tinyxml2.d
gccDebug/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) -o gccDebug/tinyxml2.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) > gccDebug/tinyxml2.d

# Compiles file Board.cpp for the Debug configuration...
-include gccDebug/Board.d
gccDebug/Board.o: Board.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Board.cpp $(Debug_Include_Path) -o gccDebug/Board.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Board.cpp $(Debug_Include_Path) > gccDebug/Board.d

# Compiles file Main.cpp for the Debug configuration...
-include gccDebug/Main.d
gccDebug/Main.o: Main.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Main.cpp $(Debug_Include_Path) -o gccDebug/Main.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Main.cpp $(Debug_Include_Path) > gccDebug/Main.d

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

# Builds the Release configuration...
.PHONY: Release
Release: create_folders gccRelease/tinyxml2.o gccRelease/Board.o gccRelease/Main.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/ParseXML.o gccRelease/PieceBase.o gccRelease/Player.o gccRelease/TextUIHandler.o
	$(CPP_COMPILER) gccRelease/tinyxml2.o gccRelease/Board.o gccRelease/Main.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/ParseXML.o gccRelease/PieceBase.o gccRelease/Player.o gccRelease/TextUIHandler.o $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/ArcadeGame

# Compiles file ../tinyxml2/tinyxml2.cpp for the Release configuration...
-include gccRelease/tinyxml2.d
gccRelease/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) -o gccRelease/tinyxml2.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) > gccRelease/tinyxml2.d

# Compiles file Board.cpp for the Release configuration...
-include gccRelease/Board.d
gccRelease/Board.o: Board.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Board.cpp $(Release_Include_Path) -o gccRelease/Board.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Board.cpp $(Release_Include_Path) > gccRelease/Board.d

# Compiles file Main.cpp for the Release configuration...
-include gccRelease/Main.d
gccRelease/Main.o: Main.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Main.cpp $(Release_Include_Path) -o gccRelease/Main.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Main.cpp $(Release_Include_Path) > gccRelease/Main.d

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

