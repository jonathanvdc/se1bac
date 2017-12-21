# Builds all the projects in the solution...
.PHONY: all
all: ArcadeGame ArcadeGameTest ArcadeGameUI 

# Builds project 'ArcadeGame'...
.PHONY: ArcadeGame
ArcadeGame: 
	make --directory="." --file=ArcadeGame.makefile

# Builds project 'ArcadeGameTest'...
.PHONY: ArcadeGameTest
ArcadeGameTest: ArcadeGame 
	make --directory="." --file=ArcadeGameTest.makefile

# Builds project 'ArcadeGameUI'...
.PHONY: ArcadeGameUI
ArcadeGameUI: 
	make --directory="." --file=ArcadeGameUI.makefile

# Cleans all projects...
.PHONY: clean
clean:
	make --directory="." --file=ArcadeGame.makefile clean
	make --directory="." --file=ArcadeGameTest.makefile clean
	make --directory="." --file=ArcadeGameUI.makefile clean

