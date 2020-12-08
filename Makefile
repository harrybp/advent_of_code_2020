# Find all the part1 and part2 cpp files
OBJ = $(shell find . -name "*part*.cpp" | sed 's/.cpp//g')

CCFLAGS = -std=c++11

# Some of the days have additional classes which need to be included
# Get all cpp class files
EXTRAS = $(shell find . -name "*.h" | sed 's/.h/.cpp/g')

# Filter all cpp class files to just the ones for this day
DAY = $(shell echo $< | cut -d'/' -f 1)
DAY_EXTRAS = $(shell echo "$(EXTRAS)" | tr ' ' '\n' | sed '/$(DAY)/!d' | tr '\n' ' ')

# Compile part1 or 2 for a given day
% : %.cpp
	g++ $< $(DAY_EXTRAS) -o $@ $(CCFLAGS)

# Compile all
all: $(OBJ)

# Remove all binaries
clean:
	rm */part1 */part2
