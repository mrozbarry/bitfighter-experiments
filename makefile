CC=g++
CFLAGS=-c -O3 -Wall `sdl2-config --cflags`
LDFLAGS=`sdl2-config --libs` -L/usr/local/lib -lGL -lSDL2main -lSDL2_ttf
OTHERFLAGS=-g
SOURCES=bitfighter1.0/application.cpp bitfighter1.0/menuitem.cpp bitfighter1.0/bitfighter1.0.cpp bitfighter1.0/renderable_box.cpp bitfighter1.0/renderable.cpp bitfighter1.0/exceptions.cpp bitfighter1.0/sdlutil.cpp bitfighter1.0/font.cpp bitfighter1.0/thread.cpp bitfighter1.0/menu.cpp bitfighter1.0/window.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=./Debug/bitfighter

all: $(SOURCES) $(EXECUTABLE)

clean-object:
	rm -f *.o

clean-executable:
	rm -f $(EXECUTABLE);

clean: clean-object clean-executable

rebuild: clean all

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OTHERFLAGS) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(OTHERFLAGS) $(CFLAGS) $< -o $@
