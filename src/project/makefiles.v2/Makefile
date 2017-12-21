# Builds all the projects in the solution...
.PHONY: all
all: ArcadeGame ArcadeGameTest 

# Builds project 'ArcadeGame'...
.PHONY: ArcadeGame
ArcadeGame: 
	make --directory="." --file=ArcadeGame.makefile

# Builds project 'ArcadeGameTest'...
.PHONY: ArcadeGameTest
ArcadeGameTest: ArcadeGame 
	make --directory="." --file=ArcadeGameTest.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="." --file=ArcadeGame.makefile clean
	make --directory="." --file=ArcadeGameTest.makefile clean

