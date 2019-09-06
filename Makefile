BIN := main

SRC_DIR := ./src
OBJ_DIR := ./objs
INCLUDES := -I./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# TEST_DIR := ./tests
# TEST_BIN_DIR := ./tests/bin
# TEST_OBJ_FILES := $(filter-out $(OBJ_DIR)/main.o,$(OBJ_FILES))
# TEST_SRC_FILES := $(wildcard $(TEST_DIR)/*.c)
# TEST_TARGETS := $(patsubst $(TEST_DIR)/%.c,$(TEST_BIN_DIR)/%,$(TEST_SRC_FILES))
# TEST_INCLUDES := -I./tests

PERF_FILES := aisteroids.gprof gmon.out perf.data perf.data.old report
SUP_FILES = $(wildcard $(UTIL_DIR)/*.supp)

CC = gcc

ifeq ($(DEBUG),"yes")
	@echo "We have debug"
	DEBUG_CPPFLAGS = -DDEBUG
	DEBUG_CFLAGS := -g -ggdb
endif

#DEBUG_CPPFLAGS = -DDEBUG
# TEST_CFLAGS = 
PROF_CFLAGS := -pg
OPTMIZATION_CFLAGS := -O2 
DEBUG_CFLAGS := -g -ggdb
PEDANTIC_CFLAGS := -std=c11 -pedantic -Werror -Wall -W
MATH_CFLAGS := -Wmissing-prototypes -Wstrict-prototypes \
  -Wconversion -Wshadow -Wpointer-arith \
  -Wcast-qual -Wcast-align \
  -Wwrite-strings -Wnested-externs \
  -fshort-enums -fno-common -Dinline= 


# COMMENT FLAGS DECLARATION ABOVE NOT ASSINGMENT BELOW
# #####################################################

# CPP Flags
CPPFLAGS :=
CPPFLAGS += $(DEBUG_CPPFLAGS)

# GCC Flags
CFLAGS :=
CFLAGS += $(DEBUG_CFLAGS)
CFLAGS += $(OPTMIZATION_CFLAGS)
CFLAGS += $(PROF_CFLAGS)
CFLAGS += $(PEDANTIC_CFLAGS)
CFLAGS += $(MATH_CFLAGS)

# Linker Flags
#PROF_LDFLAGS := -pg
# TEST_LDFLAGS = -lcunit

LDFLAGS := -lm -lgsl
LDFLAGS += $(PROF_LDFLAGS) 

# Valgrind suppression files
SUPFLAGS = $(foreach file,$(SUP_FILES), --suppressions=$(file))

all: $(BIN)

##################################
# MAIN TARGETS
##################################
$(BIN): $(OBJ_FILES)
	$(CC) $(INCLUDES) -o $@ $^ $(LDFLAGS) 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(INCLUDES) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 

clean: 
	rm -rf $(BIN) $(OBJ_FILES) $(PERF_FILES) gmon*.out

# distclean: stud_clean clean tests_clean
distclean: clean 

install:
	@echo "There is no install..." 

run: all
	./main data/matrix.txt

###################################
# TEST TARGETS
###################################
# run_tests: tests
# 	./run_tests.sh
# 
# tests: $(TEST_TARGETS)
# 
# tests_clean:
# 	rm -rf $(TEST_TARGETS)
# 
# $(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(TEST_OBJ_FILES)
# 	$(CC) $(INCLUDES) $(TEST_INCLUDES) $(CFLAGS) $(TEST_CFLAGS) $(LDFLAGS) $(TEST_LDFLAGS) $^ -o $@
# 
##################################
# PROFILING TARGETS
##################################
# check_static: clean
# 	scan-build-3.8 make 
# 
# check_leaks: clean $(BIN)
# 	valgrind $(SUPFLAGS) --leak-check=full --track-origins=yes ./$(BIN)
# 
# valg_gen_supp:
# 	valgrind --leak-check=full $(SUPFLAGS) --gen-suppressions=all --error-limit=no ./$(BIN) > $(UTIL_DIR)/new.supp
# 
# valg_supp_merge:
# 	$(UTIL_DIR)/parse_supress.sh $(UTIL_DIR)/new.supp > $(UTIL_DIR)/new_proc.supp
# 	valgrind $(SUPFLAGS) --leak-check=full --track-origins=yes ./$(BIN) | \
# 	$(UTIL_DIR)/grindmerge.pl -f $(UTIL_DIR)/new_proc.supp > $(UTIL_DIR)/new_merged.supp
# 	rm -rf $(UTIL_DIR)/new.supp $(UTIL_DIR)/new_proc.supp
# 
# profile_perf: $(BIN)
# 	perf_4.19 record -g ./$(BIN)
# 	perf_4.19 report
# 
# profile_gprof: $(BIN)
# 	gprof ./aisteroids  > $(BIN).gprof
# 

#################################
# STUDY FILES
#################################
# stud:
# 	make -C stud
# 
# stud_clean:
# 	make -C stud clean


#################################
# PHONY
#################################
.PHONY: all clean distclean install \
	stud stud_clean \
	tests tests_clean run_tests \
	check_static check_leaks \
	valg_gen_supp valg_supp_merge \
	profile_perf profile_gprof






# all: io main
# 	gcc $(OPTIONS) io.o main.o -o main -lgsl
# 
# io:
# 	gcc $(OPTIONS) -g -O -c io.c
# 
# main:
# 	gcc $(OPTIONS) -g -O -c main.c
# 
# 
# clean:
# 	rm -rf *.o main
