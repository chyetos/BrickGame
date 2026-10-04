CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
LDFLAGS = -lncursesw

TARGET = tetris
SOURCES = src/main.c src/brick_game/tetris/backend.c src/gui/cli/frontend.c
OBJECTS = $(SOURCES:.c=.o)
GCOV_FILES = $(SOURCES:.c=.gcno) $(SOURCES:.c=.gcda) $(SOURCES:.c=.gcov)

BUILD_DIR = build

.PHONY: all install uninstall clean dvi dist test gcov_report

all: $(BUILD_DIR)/$(TARGET) dvi

$(BUILD_DIR)/$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

install: $(BUILD_DIR)/$(TARGET)
	@echo "Программа собрана в папке $(BUILD_DIR)/"

uninstall: clean

clean:
	rm -f $(OBJECTS)
	rm -rf $(BUILD_DIR)
	rm -rf *.gcda *.gcno test logs
	rm -rf doc

dist: clean
	mkdir -p $(TARGET)_zip
	cp -r src Makefile README.md $(TARGET)_zip/
	tar -czf $(TARGET)_zip.tar.gz $(TARGET)_zip/
	rm -rf $(TARGET)_zip

test:
	@$(CC) $(GCOV_FLAGS) src/tests/test.c src/brick_game/tetris/backend.c -lcheck -lm -lsubunit -o test
	@./test

gcov_report: test clean_test
	@mkdir logs
	@gcovr --html-self-contained --html-details -o logs/report.html
	@echo "Building report..."
	@open logs/report.html

clean_test:
	@rm -rf test-test.gcda test-test.gcno logs

clang:
	cp materials/linters/.clang-format src/.clang-format
	clang-format -i $(SOURCES)
	clang-format -i src/inc/*.h


clang_test:
	cp materials/linters/.clang-format src/.clang-format
	clang-format -n $(SOURCES)
	clang-format -n src/inc/*.h

dvi:
	mkdir -p doc
	cp README.md doc/README.txt
	cp materials/fsm_diagram.png doc/fsm_diagram.png
	@echo "Tetris Game Instructions" > doc/tetris_instructions.txt
	@echo "========================" >> doc/tetris_instructions.txt
	@echo "" >> doc/tetris_instructions.txt
	@echo "Controls:" >> doc/tetris_instructions.txt
	@echo "  Enter       - Start game" >> doc/tetris_instructions.txt
	@echo "  Left Arrow  - Move piece left" >> doc/tetris_instructions.txt
	@echo "  Right Arrow - Move piece right" >> doc/tetris_instructions.txt
	@echo "  Down Arrow  - Move piece down" >> doc/tetris_instructions.txt
	@echo "  Up Arrow    - Rotate piece" >> doc/tetris_instructions.txt
	@echo "  P           - Pause game" >> doc/tetris_instructions.txt
	@echo "  Backspace   - End game" >> doc/tetris_instructions.txt
	@echo "" >> doc/tetris_instructions.txt
	@echo "Scoring:" >> doc/tetris_instructions.txt
	@echo "  1 line  - 100 points" >> doc/tetris_instructions.txt
	@echo "  2 lines - 300 points" >> doc/tetris_instructions.txt
	@echo "  3 lines - 700 points" >> doc/tetris_instructions.txt
	@echo "  4 lines - 1500 points" >> doc/tetris_instructions.txt
	@echo "Documentation generated in doc/ directory"