CXX = g++
CXXFLAGS = -g -std=c++14 -Werror=vla -Wall -MMD
EXEC = biquadris
OBJECTS = main.o block.o board.o cell.o command.o commandargs.o game.o graphicsdisplay.o inputreader.o level.o piece.o piececoords.o piecesequence.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
	
