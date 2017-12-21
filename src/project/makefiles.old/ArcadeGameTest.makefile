# Compiler flags...
CPP_COMPILER = g++
C_COMPILER = gcc

# Include paths...
Debug_Include_Path=-Igtest-1.7.0/include
Release_Include_Path=-Igtest-1.7.0/include

# Library paths...
Debug_Library_Path=-Lgtest-1.7.0/lib/.libs
Release_Library_Path=-Lgtest-1.7.0/lib/.libs

# Additional libraries...
Debug_Libraries=-Wl,--start-group gtest-1.7.0/lib/.libs/libgtest.a gtest-1.7.0/lib/.libs/libgtest_main.a -lgtest -lgtest_main -pthread -Wl,--end-group
Release_Libraries=$(Debug_Libraries)

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
Debug: create_folders gccDebug/tinyxml2.o gccDebug/ArcadeGameTest.o gccDebug/Board.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/PieceBase.o gccDebug/Player.o gccDebug/TextUIHandler.o
	$(CPP_COMPILER) gccDebug/tinyxml2.o gccDebug/ArcadeGameTest.o gccDebug/Board.o gccDebug/MoveCommand.o gccDebug/Obstacle.o gccDebug/PieceBase.o gccDebug/Player.o gccDebug/TextUIHandler.o $(Debug_Library_Path) $(Debug_Libraries) -Wl,-rpath,./ -o gccDebug/ArcadeGameTest

# Compiles file ../tinyxml2/tinyxml2.cpp for the Debug configuration...
-include gccDebug/tinyxml2.d
gccDebug/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) -o gccDebug/tinyxml2.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Debug_Include_Path) > gccDebug/tinyxml2.d

# Compiles file ArcadeGameTest.cpp for the Debug configuration...
-include gccDebug/ArcadeGameTest.d
gccDebug/ArcadeGameTest.o: ArcadeGameTest.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c ArcadeGameTest.cpp $(Debug_Include_Path) -o gccDebug/ArcadeGameTest.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM ArcadeGameTest.cpp $(Debug_Include_Path) > gccDebug/ArcadeGameTest.d

# Compiles file Board.cpp for the Debug configuration...
-include gccDebug/Board.d
gccDebug/Board.o: Board.cpp
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -c Board.cpp $(Debug_Include_Path) -o gccDebug/Board.o
	$(CPP_COMPILER) $(Debug_Preprocessor_Definitions) $(Debug_Compiler_Flags) -MM Board.cpp $(Debug_Include_Path) > gccDebug/Board.d

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
Release: create_folders gccRelease/tinyxml2.o gccRelease/ArcadeGameTest.o gccRelease/Board.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/PieceBase.o gccRelease/Player.o gccRelease/TextUIHandler.o
	$(CPP_COMPILER) gccRelease/tinyxml2.o gccRelease/ArcadeGameTest.o gccRelease/Board.o gccRelease/MoveCommand.o gccRelease/Obstacle.o gccRelease/PieceBase.o gccRelease/Player.o gccRelease/TextUIHandler.o $(Release_Library_Path) $(Release_Libraries) -Wl,-rpath,./ -o gccRelease/ArcadeGameTest

# Compiles file ../tinyxml2/tinyxml2.cpp for the Release configuration...
-include gccRelease/tinyxml2.d
gccRelease/tinyxml2.o: ../tinyxml2/tinyxml2.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) -o gccRelease/tinyxml2.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ../tinyxml2/tinyxml2.cpp $(Release_Include_Path) > gccRelease/tinyxml2.d

# Compiles file ArcadeGameTest.cpp for the Release configuration...
-include gccRelease/ArcadeGameTest.d
gccRelease/ArcadeGameTest.o: ArcadeGameTest.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c ArcadeGameTest.cpp $(Release_Include_Path) -o gccRelease/ArcadeGameTest.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM ArcadeGameTest.cpp $(Release_Include_Path) > gccRelease/ArcadeGameTest.d

# Compiles file Board.cpp for the Release configuration...
-include gccRelease/Board.d
gccRelease/Board.o: Board.cpp
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -c Board.cpp $(Release_Include_Path) -o gccRelease/Board.o
	$(CPP_COMPILER) $(Release_Preprocessor_Definitions) $(Release_Compiler_Flags) -MM Board.cpp $(Release_Include_Path) > gccRelease/Board.d

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

