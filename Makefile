# Diretórios e nomes de binários
BUILD_DIR = Build
EXEC     = tp1
TEST     = test_app

.PHONY: build test run clean

build:
	mkdir -p $(BUILD_DIR)
	cd $(BUILD_DIR) && cmake .. && make

run: build
	./$(BUILD_DIR)/$(EXEC)

test: build
	./$(BUILD_DIR)/$(TEST)

clean:
	rm -rf $(BUILD_DIR)
