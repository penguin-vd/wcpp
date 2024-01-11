# Define the compiler to use
CXX = g++

# Define any compile-time flags
CXXFLAGS = -Wall -Wextra -g

# Define the C++ source files
SRCS = main.cpp 

# Define the C++ object files 
OBJS = $(SRCS:.cpp=.o)

# Define the executable file 
MAIN = wcpp

.PHONY: depend clean run

all:    $(MAIN)
	@echo  $(MAIN) has been compiled

$(MAIN): $(OBJS) 
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJS)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)

run: $(MAIN)
	./$(MAIN)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it

