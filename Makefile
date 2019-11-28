CXX = g++
CXXFLAGS = -g -std=c++14 -Werror=vla -Wall -MMD
EXEC = a5
SOURCES = $(wildcard .cc) $(wildcard */.cc)
OBJECTS = $(patsubst %.cc,%.o,${SOURCES})
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}
	