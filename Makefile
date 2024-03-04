PROG = main.exe
TEST = test.exe
SOURCES = src/main.cpp src/catflap.cpp src/rfid_reader.cpp src/led_control.cpp
TEST_SOURCES = test_catflap.cpp
DEPS = src/catflap.h src/rfid_reader.h src/led_control.h
CC = g++
CFLAGS = -Wall -Werror -std=c++11
DEBUG ?= 1
GTEST = gtest
LIBGTEST = C:\msys64\mingw64\lib\libgtest_main.a C:\msys64\mingw64\lib\libgtest.a

ifeq ($(DEBUG), 1)
	CFLAGS += -g 
	OUTPUTDIR = bin/debug
	PROG = main-debug.exe
else
	CFLAGS += -O3
	OUTPUTDIR = bin/release
endif

OBJS = $(addprefix $(OUTPUTDIR)/,$(notdir $(SOURCES:.cpp=.o)))
TEST_OBJS := $(addprefix $(OUTPUTDIR)/,$(notdir $(TEST_SOURCES:.cpp=.o)))

$(OUTPUTDIR)/main.o: src/main.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

$(PROG): $(OUTPUTDIR) $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

$(OUTPUTDIR)/%.o: src/%.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -rf "$(OUTPUTDIR)"
	@rm -f $(PROG)
	@rm -f $(TEST)

$(OUTPUTDIR):
	@mkdir -p "$(OUTPUTDIR)"

$(TEST): $(OBJS) $(TEST_OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I $(GTEST) $(LIBGTEST)

test: $(TEST)
	./$(TEST)

.PHONY: clean test $(PROG) $(TEST) $(OUTPUTDIR)