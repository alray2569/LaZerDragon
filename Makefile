#
# Makefile for saucer shoot game using Dragonfly
#
# Copyright Mark Claypool and WPI, 2015
#
# 'make depend' to generate new dependency list
# 'make clean' to remove all constructed files
# 'make' to build executable
#
# Variables of interest:
#   GAMESRC is the source code files for the game
#   GAME is the game main() source
#

CC= g++
EXECUTABLE= bin/game
BUILDDIR= build
ENGINEDIR= dragonfly
INCLUDEDIR= src
SRCDIR= src

LINK= -L/usr/local/Cellar/sfml/2.3/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio #-lrt
INCLUDE= -I../$(ENGINEDIR)/include -I/usr/local/Cellar/sfml/2.3/include \
    -I./$(INCLUDEDIR) # path to dragonfly includes
ENGINE= ../$(ENGINEDIR)/lib/libdragonfly-mac64.a # location of dragonfly engine
GAMESRC= $(wildcard $(SRCDIR)/*.cpp)
OBJECTS= $(patsubst $(SRCDIR)/%,build/%,$(GAMESRC:.cpp=.o))

all: $(EXECUTABLE) Makefile

$(EXECUTABLE): $(ENGINE) $(OBJECTS) $(GAMESRC)
	@echo "Linking object files and creating executable"
	@$(CC) $(OBJECTS) $(ENGINE) -o $@ $(INCLUDE) $(LINK)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling $<"
	@$(CC) -c $(INCLUDE) $< -o $@

clean:
	@echo "Removing binaries, backups, and intermediary files"
	@rm -rf $(OBJECTS) $(EXECUTABLE) core dragonfly.log Makefile.bak *~

depend:
	makedepend *.cpp 2> /dev/null

# DO NOT DELETE
