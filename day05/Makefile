.SILENT:

CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++17 -O2
CXX_DEBUG_FLAGS = -Wall -Werror -std=c++17 -g
CXX_PROFILE_FLAGS = -Wall -Werror -std=c++17 -pg
LIBS =
BIN = bin

default: p1r p2r
all: p1 p1r p1g p1p p2 p2r p2g p1p

%: %.cpp
	mkdir -p ${BIN}
	$(CXX) $(CXX_FLAGS) $< -o ${BIN}/$@ ${LIBS}

%.nostrip: %.cpp
	mkdir -p ${BIN}
	$(CXX) $(CXX_DEBUG_FLAGS) $< -o ${BIN}/$@ ${LIBS}

%.prof: %.cpp
	mkdir -p ${BIN}
	$(CXX) $(CXX_PROFILE_FLAGS) $< -o $(BIN)/$@ ${LIBS}

p1 : puzzle1
p2 : puzzle2

p1r : p1
	${BIN}/puzzle1
p2r : p2
	${BIN}/puzzle2

p1g : puzzle1.nostrip
p2g : puzzle2.nostrip

p1p : puzzle1.prof
	${BIN}/puzzle1.prof
p2p : puzzle2.prof
	${BIN}/puzzle2.prof
