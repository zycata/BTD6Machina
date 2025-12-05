# this program should compile with gcc version 6.3.0 or higher (works with 15.2.0) clang has been tested with 21.1.0


# you can replace both CC and CXX with clang or clang++ if you want to use clang btw
CC = gcc
CXX = gcc

# unfortunately this program is gonna be windows exclusive anyways so the makefile will be windows exclusive too
CFLAGS = -Wall -Wextra -g # -static 

# -lstdc++ to manually link standard c library for gcc compiler
LDFLAGS =  -lstdc++ -lUser32

TARGET_MAIN = release\aitd6.exe
SOURCES = src\GenerationHandler.cpp src\gameTypes.cpp src\StrategyMaker.cpp src\jsonHandlers\GameReader.cpp src\mouseControl\mouseControl.cpp
SOURCES_MAIN_OBJS = $(SOURCES:.cpp=.o)

ICON_SOURCE = crossbowmaster.res

aitd6: $(TARGET_MAIN)
$(TARGET_MAIN): $(SOURCES_MAIN_OBJS)
	$(CC) $(CFLAGS) $(SOURCES_MAIN_OBJS) $(ICON_SOURCE) -o $(TARGET_MAIN) $(LDFLAGS)
clean_main:
	del $(TARGET_MAIN)
clean_objs:
	del $(SOURCES_MAIN_OBJS)
clean_all: clean_objs clean_main
	@echo "-------- Cleaned all -----------"


#--------------------------Test GameTypes-----------------------------------# 
TEST_GAMETYPES_SOURCES = src\gameTypes.cpp test\gameTypesTest.cpp 
TEST_GAMETYPES_TARGET = test\gameTypesTest.exe
TEST_GAMETYPES_OBJS = $(TEST_GAMETYPES_SOURCES:.cpp=.o) 

# omg why do you have to use \ instead of / bruh
test_gametypes: $(TEST_GAMETYPES_TARGET)
$(TEST_GAMETYPES_TARGET): $(TEST_GAMETYPES_OBJS)
	$(CC) $(CFLAGS) $(TEST_GAMETYPES_OBJS) -o $(TEST_GAMETYPES_TARGET) $(LDFLAGS)

clean_gametypes: 	# idk why it doesnt work
	del $(TEST_GAMETYPES_OBJS) $(TEST_GAMETYPES_TARGET)

#--------------------------Jsonhandler Test-----------------------------------# 
# uhh refactor the hpp file to be a .h and a cpp file
TEST_JSONHANDLERS = test\jsonHandlerTest\jsonHandlerTest.cpp src\gameTypes.cpp
TEST_JSONHANDLERS_TARGET = test\jsonHandlerTest\jsonHandlerTest.exe
TEST_JSONHANDLERS_OBJS = $(TEST_JSONHANDLERS:.cpp=.o)

test_jsonhandler: $(TEST_JSONHANDLERS_TARGET)
$(TEST_JSONHANDLERS_TARGET): $(TEST_JSONHANDLERS_OBJS)
	$(CC) $(CFLAGS) $(TEST_JSONHANDLERS_OBJS) -o $(TEST_JSONHANDLERS_TARGET) $(LDFLAGS)

clean_jsonhandler:
	del $(TEST_JSONHANDLERS_OBJS) $(TEST_JSONHANDLERS_TARGET) 
#--------------------------GameReaderTest-----------------------------------# 
TEST_GAMEREADER_SOURCES = test\GameReaderTest\GameReaderTest.cpp src\jsonHandlers\GameReader.cpp src\mouseControl\mouseControl.cpp
TEST_GAMEREADER_TARGET = test\gameReaderTest\gameReaderTest.exe
TEST_GAMEREADER_OBJS = $(TEST_GAMEREADER_SOURCES:.cpp=.o)

test_gamereader: $(TEST_GAMEREADER_TARGET)
$(TEST_GAMEREADER_TARGET): $(TEST_GAMEREADER_OBJS)
	$(CC) $(CFLAGS) $(TEST_GAMEREADER_OBJS) -o $(TEST_GAMEREADER_TARGET) $(LDFLAGS)
clean_gamereader:
	del $(TEST_GAMEREADER_OBJS) $(TEST_GAMEREADER_TARGET)
#--------------------------Clean-----------------------------------# 



tests: test_gamereader test_jsonhandler test_gametypes
	@echo "----all tests built----"

clean_tests: clean_gametypes clean_jsonhandler clean_gamereader
	@echo "----cleaning all----"
