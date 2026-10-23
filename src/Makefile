# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
GTEST_FLAGS = -lgtest -lgtest_main -pthread
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
VALGRIND_FLAGS = --leak-check=full --track-origins=yes --show-leak-kinds=all

# Пути (текущая директория - src)
CURRENT_DIR = .
BUILD_DIR = build
TESTS_DIR = tests
INCLUDE_DIR = include
DOC_DIR = docs
SRC_DIR = .

# Цели
LIBRARY = s21_containers.a
TEST_EXEC = $(BUILD_DIR)/test
GCOV_EXEC = $(BUILD_DIR)/gcov_test
GCOV_REPORT = $(BUILD_DIR)/gcov_report

# Исходные файлы для библиотеки
HEADERS = $(wildcard $(INCLUDE_DIR)/*.h) \
          $(wildcard $(INCLUDE_DIR)/*.hpp) \
          $(wildcard $(INCLUDE_DIR)/*.tpp) \
          s21_containers.hpp

# Файлы тестов (компилируем каждый .cpp отдельно)
TEST_SOURCES = $(wildcard $(TESTS_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TESTS_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_SOURCES))

# Основные цели
all: $(LIBRARY)

$(LIBRARY): $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	@echo "Creating static library $@"
	@# Создаем пустую библиотеку, так как у нас header-only
	ar rcs $@ $(HEADERS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Компилируем каждый тест отдельно, затем линкуем
$(TEST_EXEC): $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

$(BUILD_DIR)/%.o: $(TESTS_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(CURRENT_DIR) -I$(INCLUDE_DIR) -c $< -o $@

gcov_report: $(GCOV_REPORT)

$(GCOV_REPORT): $(TEST_SOURCES) $(HEADERS)
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling with coverage flags..."
	$(CXX) $(CXXFLAGS) $(GCOV_FLAGS) -I$(CURRENT_DIR) -I$(INCLUDE_DIR) $(TEST_SOURCES) -o $(GCOV_EXEC) $(GTEST_FLAGS)
	@echo "Running tests with coverage..."
	./$(GCOV_EXEC)
	@echo "Generating coverage report..."
	@mkdir -p $(BUILD_DIR)
	@lcov --capture --directory . --output-file $(BUILD_DIR)/coverage.info --ignore-errors mismatch 2>/dev/null || true
	@lcov --remove $(BUILD_DIR)/coverage.info "/usr/*" "*/tests/*" --output-file $(BUILD_DIR)/coverage.filtered.info 2>/dev/null || true
	@genhtml $(BUILD_DIR)/coverage.filtered.info --output-directory $@ 2>/dev/null || true
	@echo "Coverage report generated in $@"
	@echo "To view the report, run:"
	@echo "  open $@/index.html"
	@echo "or"
	@echo "  xdg-open $@/index.html"

valgrind: $(TEST_EXEC)
	valgrind $(VALGRIND_FLAGS) ./$(TEST_EXEC)

clang-format:
	find . -name "*.h" -o -name "*.hpp" -o -name "*.cpp" -o -name "*.tpp" | xargs clang-format -i -style=file

doxygen:
	@if [ ! -f Doxyfile ]; then \
		echo "Generating Doxyfile..."; \
		doxygen -g Doxyfile 2>/dev/null; \
		echo "PROJECT_NAME           = \"s21_containers\"" >> Doxyfile; \
		echo "INPUT                  = include ." >> Doxyfile; \
		echo "RECURSIVE              = YES" >> Doxyfile; \
		echo "EXTRACT_ALL            = YES" >> Doxyfile; \
		echo "EXTRACT_PRIVATE        = YES" >> Doxyfile; \
		echo "EXTRACT_STATIC         = YES" >> Doxyfile; \
		echo "OUTPUT_DIRECTORY       = docs" >> Doxyfile; \
		echo "GENERATE_HTML          = YES" >> Doxyfile; \
		echo "GENERATE_LATEX         = NO" >> Doxyfile; \
	fi
	@mkdir -p $(DOC_DIR)
	doxygen Doxyfile
	@echo "Documentation generated in $(DOC_DIR)"

clean:
	rm -rf $(BUILD_DIR) $(DOC_DIR) *.gcda *.gcno coverage.info $(LIBRARY) *.gcov

distclean: clean
	rm -f *.info
	rm -f Doxyfile

.PHONY: all test gcov_report valgrind clang-format doxygen clean distclean