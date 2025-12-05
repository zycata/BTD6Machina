CC = gcc #clang
#CXX = clang
# gcc you need to include the fuckass linked to folders n shit because gcc is real
# clang works too i think
CFLAGS = -Wall -Wextra -g

# -lstdc++ to manually link standard c library for gcc compiler
LDFLAGS =  -lstdc++ -lUser32

TARGET_MAIN = # todo
SOURCES = # todo


all: $(TARGET_MAIN)

$(TARGET_MAIN): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET_MAIN) $(LDFLAGS)


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



clean:
	del $(TARGET_MAIN)



clean_all: clean_gametypes clean_jsonhandler clean_gamereader
	@echo "----cleaning all----"
