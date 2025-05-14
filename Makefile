CCX = g++
CXXFLAGS = -Wall -std=c++11 

PROGRAM = frog

LIBRARY = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = frog_main.o frog_terminal.o frog_view.o frog_tview.o position.o subjects.o frog_model.o sfml_render.o 

$(PROGRAM): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJ) $(LIBRARY)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAM)  *.o


