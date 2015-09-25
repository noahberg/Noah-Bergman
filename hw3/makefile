C_FLAGS = -g -Wall
BIN_DIR = bin
CC = g++
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/.dirstamp $(BIN_DIR)/boolevaluator $(BIN_DIR)/stackinttest $(BIN_DIR)/alisttest

$(BIN_DIR)/boolevaluator: src/boolevaluator.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o
	$(CC) $(C_FLAGS) $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o src/boolevaluator.cpp -o $(BIN_DIR)/boolevaluator

boolevaluator: $(BIN_DIR)/.dirstamp $(BIN_DIR)/boolevaluator

runstackinttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/stackinttest
	valgrind --tool=memcheck --leak-check=yes ./bin/stackinttest

stackint: $(BIN_DIR)/.dirstamp $(BIN_DIR)/stackint.o

alistint: $(BIN_DIR)/.dirstamp $(BIN_DIR)/alistint.o 

stackinttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/stackinttest

$(BIN_DIR)/stackinttest: src/stackinttest.cpp $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o
	$(CC) $(C_FLAGS)  $(BIN_DIR)/stackint.o $(BIN_DIR)/alistint.o src/stackinttest.cpp -o $(BIN_DIR)/stackinttest

$(BIN_DIR)/stackint.o: src/stackint.cpp
	$(CC) $(C_FLAGS) -c src/stackint.cpp -o $(BIN_DIR)/stackint.o

runalisttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/alisttest
	valgrind --tool=memcheck --leak-check=yes ./bin/alisttest

alisttest: $(BIN_DIR)/.dirstamp $(BIN_DIR)/alisttest

$(BIN_DIR)/alistint.o: src/alistint.cpp
	$(CC) $(C_FLAGS) -c src/alistint.cpp -o $(BIN_DIR)/alistint.o

$(BIN_DIR)/alisttest: src/alisttest.cpp $(BIN_DIR)/alistint.o
	$(CC) $(C_FLAGS) $^ $(GTEST_LL) -o $(BIN_DIR)/alisttest

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	mkdir $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp



