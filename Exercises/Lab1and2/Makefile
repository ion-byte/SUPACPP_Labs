# Default target: compile everything
all: analyse

# Compile your C++ files into executable named "analyse"
# $^ means all dependencies
analyse: AnalyseData.cpp CustomFunctions.cpp CustomFunctions.h
	g++ AnalyseData.cpp CustomFunctions.cpp -o analyse

# Run the program
run: analyse
	./analyse

# Optional: clean up the compiled executable
clean:
	rm -f analyse
