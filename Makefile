CC = g++
CXXFLAGS = -Wall -std=c++11

PROGRAM = frog
OBJ = frog_main.o frog_view.o frog_tview.o position.o subjects.o frog_model.o
$(PROGRAM): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJ)

