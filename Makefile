# -----------------------------------------------------------------------------
# Author:   Alex Brandt
# CSIS 352: Graphs
# -----------------------------------------------------------------------------

# Executable Name
EXECUTABLE = prog8

# Define the compiler to use.
CC =        g++

# All necessary objects.
OBJECTS =	main.o

# Libraries to link.
LFLAGS =	-lm

# Flags to pass to the compiler.
CFLAGS =	-Wall \
			-O2 \
			-pipe \
			-Wextra \
			-Weffc++ \
			-Wold-style-cast \
			-Woverloaded-virtual \
			-pedantic \
			-Wstrict-aliasing

# Dependencies and Rules.

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJECTS) $(EXT_OBJECTS) $(LFLAGS)

main.o : main.cpp graph.h vertex.h
	$(CC) $(CFLAGS) -c main.cpp

clean :
	rm $(OBJECTS) $(EXECUTABLE)
