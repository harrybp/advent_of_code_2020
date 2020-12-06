OBJ = $(shell find . -name "*.cpp" | sed 's/.cpp//g')
CCFLAGS = -std=c++11

% : %.cpp
	g++ $< -o $@ $(CCFLAGS)

all: $(OBJ)

clean:
	rm */part1 */part2
