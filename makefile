CC = g++
# gcc you need to include the fuckass linked to folders n shit because gcc is real
# clang works too i think
CFLAGS = -Wall -Wextra -g

# -lstdc++ to manually link standard c library for gcc compiler
LDFLAGS =  #-lstdc++

TARGET = # todo
SOURCES = # todo


all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET) $(LDFLAGS)


#--------------------------Test GameTypes-----------------------------------# 
TEST_GAMETYPES_SOURCES = src\gameTypes.cpp test\gameTypesTest.cpp 
TEST_GAMETYPES_TARGET = test\gameTypesTest.exe
TEST_GAMETYPES_OBJS = $(TEST_GAMETYPES_SOURCES:.cpp=.o) 


test_gametypes: $(TEST_GAMETYPES_TARGET)
$(TEST_GAMETYPES_TARGET): $(TEST_GAMETYPES_OBJS)
	$(CC) $(CFLAGS) $(TEST_GAMETYPES_OBJS) -o $(TEST_GAMETYPES_TARGET) $(LDFLAGS)


#--------------------------Test tbd-----------------------------------# 
TEST_SOURCES = test.cpp my_heap.cpp
TEST_TARGET = test/test.exe
test_test: $(TEST_TARGET)

$(TEST_TARGET): $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(TEST_SOURCES) -o $(TEST_TARGET) $(LDFLAGS)
#--------------------------Clean-----------------------------------# 



clean:
	del $(TARGET)
clean_gametypes: 	# idk why it doesnt work
	del $(TEST_GAMETYPES_OBJS) $(TEST_GAMETYPES_TARGET)
clean_test:
	del $(TEST_TARGET)