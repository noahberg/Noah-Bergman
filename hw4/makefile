C_FLAGS = -g -Wall
BIN_DIR = bin
CC = g++
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/.dirstamp

myset.o: $(BIN_DIR)/.dirstamp $(BIN_DIR)/myset.o

pageparsermarkdown.o: $(BIN_DIR)/.dirstamp $(BIN_DIR)/pageparsermarkdown.o

webpage.o: $(BIN_DIR)/.dirstamp $(BIN_DIR)/webpage.o

mysettest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/mysettest

webpagetest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/webpagetest

util.o: $(BIN_DIR)/.dirstamp $(BIN_DIR)/util.o

search: $(BIN_DIR)/.dirstamp $(BIN_DIR)/search 

searcheng.o: $(BIN_DIR)/.dirstamp $(BIN_DIR)/searcheng.o

$(BIN_DIR)/searcheng.o: src/searcheng.cpp
	$(CC) $(C_FLAGS) -c src/searcheng.cpp -o $(BIN_DIR)/searcheng.o

$(BIN_DIR)/search: src/search.cpp $(BIN_DIR)/searcheng.o $(BIN_DIR)/myset.o $(BIN_DIR)/pageparsermarkdown.o $(BIN_DIR)/webpage.o $(BIN_DIR)/util.o
	$(CC) $(C_FLAGS) src/search.cpp $(BIN_DIR)/searcheng.o $(BIN_DIR)/myset.o $(BIN_DIR)/pageparsermarkdown.o $(BIN_DIR)/webpage.o $(BIN_DIR)/util.o -o $(BIN_DIR)/search


$(BIN_DIR)/webpagetest: testing/webpagetest.cpp $(BIN_DIR)/myset.o $(BIN_DIR)/pageparsermarkdown.o $(BIN_DIR)/webpage.o
	$(CC) $(C_FLAGS) testing/webpagetest.cpp $(BIN_DIR)/myset.o $(BIN_DIR)/pageparsermarkdown.o $(BIN_DIR)/webpage.o -o $(BIN_DIR)/webpagetest

$(BIN_DIR)/mysettest: testing/mysettest.cpp $(BIN_DIR)/myset.o
	$(CC) $(C_FLAGS) testing/mysettest.cpp $(BIN_DIR)/myset.o -o $(BIN_DIR)/mysettest

$(BIN_DIR)/myset.o: src/myset.cpp
	$(CC) $(C_FLAGS) -c src/myset.cpp -o $(BIN_DIR)/myset.o

$(BIN_DIR)/util.o: src/util.o
	$(CC) $(C_FLAGS) -c src/util.cpp -o $(BIN_DIR)/util.o

$(BIN_DIR)/pageparsermarkdown.o: src/pageparsermarkdown.cpp $(BIN_DIR)/myset.o
	$(CC) $(C_FLAGS) -c src/pageparsermarkdown.cpp -o $(BIN_DIR)/pageparsermarkdown.o

$(BIN_DIR)/webpage.o: src/webpage.cpp $(BIN_DIR)/pageparsermarkdown.o
	$(CC) $(C_FLAGS) -c src/webpage.cpp -o $(BIN_DIR)/webpage.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	mkdir $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp