CC = gcc 
EFLAGS = -Wall -Wextra -Werror -std=c11
CFLAGS = $(EFLAGS) -c
OFLAGS = $(EFLAGS) -o
TEST_FLAGS = -lcheck -lm -lpthread
S21_STRING_C = $(wildcard functions/*.c)
S21_STRING_O = $(S21_STRING_C:.c=.o)

S21_SPECIFICATORS_C = $(wildcard functions/specificators/*.c)
S21_SPECIFICATORS_O = $(S21_SPECIFICATORS_C:.c=.o)

S21_SUITE_C = $(wildcard tests/*.c)
S21_SUITE_O = $(S21_SUITE_C:.c=.o)

ifeq ($(shell uname -s),Linux)
	TEST_FLAGS += -lrt -lsubunit
endif

all: clean test

valgrind: s21_string.a $(S21_SUITE_O)
	$(CC) $(OFLAGS) test $(S21_SUITE_O) s21_string.a $(TEST_FLAGS) 
	valgrind --leak-check=full -s ./test
	# make clean

style_check:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.c *.h functions/*.c functions/*.h tests/*.c tests/*.h functions/specificators/*.c functions/specificators/*.h
	rm .clang-format

style_fix:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.c *.h functions/*.c functions/*.h tests/*.c tests/*.h functions/specificators/*.c functions/specificators/*.h
	rm .clang-format

clean:
	rm -rf *.o *.a test tgtests *.gcda *.gcno *.gcov *.html *.css *.ou
	rm -rf *.o functions/*.o functions/specificators/*.o tests/*.o
	rm -rf report/ *.info

s21_string.a: $(S21_STRING_O) $(S21_SPECIFICATORS_O)
	$(CC) $(CFLAGS) $(S21_STRING_C) $(S21_SPECIFICATORS_C)
	ar r s21_string.a $(S21_STRING_O) $(S21_SPECIFICATORS_O)
	ranlib s21_string.a
	

test: s21_string.a $(S21_SUITE_O)
	$(CC) $(OFLAGS) test $(S21_SUITE_O) s21_string.a $(TEST_FLAGS)
	./test
	# rm -rf *.o *.a
	# make clean

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

tests/main.o: tests/main.c
	$(CC) $(CFLAGS) $< -o $@

gcov_report: $(S21_SUITE_O)
	$(CC) --coverage $(S21_SUITE_O) $(S21_SPECIFICATORS_C) $(S21_STRING_C) $(TEST_FLAGS) -o test
	./test
	gcov *.gcno
	lcov -t "s21_string" -o s21_string.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o report s21_string.info --rc lcov_branch_coverage=1
	open report/index.html