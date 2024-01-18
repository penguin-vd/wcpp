CXX = g++
CXXFLAGS = -Wall -g
SRCS = main.cpp parse_file.cpp parse_dir.cpp
BUILD_DIR = build

MAIN = $(BUILD_DIR)/wcpp

.PHONY: depend clean run

all:    $(MAIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MAIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(SRCS)

clean:
	$(RM) -r $(BUILD_DIR)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it

