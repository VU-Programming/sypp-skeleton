# Do not modify this file, as it is overwritten by the default file in the
# code grade testing environment

# If you need to include extra libraries for your gui or debugger,
# please provide list the extra compiler arguments (i.e. "lgtk-4") in
# debugger_libs or gui_libs.

.PHONY: clean testall run_test% zip tools

IDIR=include
CC = clang
USERFLAGS+=
override CFLAGS+=-I$(IDIR) -g -Wall -Wpedantic $(USERFLAGS) -std=c11 -Wformat-extra-args
PEDANTIC_CFLAGS=-std=c11 -Werror -Wpedantic -Wall -Wextra -Wformat=2 -O -Wuninitialized -Winit-self -Wswitch-enum -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Waggregate-return -Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations -Wredundant-decls -Wnested-externs -Wno-long-long  -Wglobal-constructors -Wshorten-64-to-32
TESTS := test1 test2 test3 test4 test5 testadvanced1 testadvanced2 testadvanced3 testadvanced4 testadvanced5 testadvanced6 testadvanced7 testadvanced8
GOJASM ?= tools/gojasm

ODIR=obj
LDIR =lib
SRCDIR=src
TSTDIR=tests

LIBS=-lm -ldl
DEBUGGER_LIBS=`cat debugger_libs.txt`
GUI_LIBS=`cat gui_libs.txt`

DEPS = $(wildcard $(IDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.c)
_OBJ = $(patsubst $(SRCDIR)/%,$(ODIR)/%,$(SRCS:.c=.o))
OBJ = $(filter-out $(ODIR)/main.o $(ODIR)/debugger.o $(ODIR)/gui.o,$(_OBJ))

DEPS2 := $(OBJ:.o=.d)

all: ijvm

$(OBJ) $(ODIR)/main.o $(ODIR)/debugger.o $(ODIR)/gui.o: $(DEPS)

-include $(DEPS2)

$(ODIR)/%.o: $(SRCDIR)/%.c
	+@[ -d $(ODIR) ] || mkdir -p $(ODIR)
	$(CC) -MMD $(CFLAGS) -c -o $@ $<

ijvm: $(OBJ) $(ODIR)/main.o
	echo $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

debugger: $(OBJ) $(ODIR)/debugger.o
	echo $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(DEBUGGER_LIBS)

gui: $(OBJ) $(ODIR)/gui.o
	echo $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(GUI_LIBS)

# computes grade of basic and advanced tests, requires python
grade: 
	python3 tools/grade.py
	

clean:
	-rm -f $(ODIR)/*.o *~ core.* $(INCDIR)/*~
	-rm -f $(ODIR)/*.d
	-rm -f ijvm gui debugger
	-rm -f test1 test2 test3 test4 test5 testadvanced* testbonusheap testbonustail testbonusgarbage
	-rm -f dist.zip
	-rm -rf profdata/
	-rm -rf obj/ *.dSYM
	-rm -f valgrind-*.txt

tools:
	make -C tools/


files/%.ijvm: files/%.jas
	which $(GOJASM) # Check that GoJasm binary exists
	echo $(GOJASM) -o $@ $<

JAS_FILES = $(wildcard files/task*/*.jas files/advanced/*.jas)
IJVM_FILES = $(JAS_FILES:.jas=.ijvm)
ijvm_binaries: tools $(IJVM_FILES)


UNAME_S := $(shell uname -s)

zip: 
	zip dist.zip bonus.md `find src include -iname "*.c" -o -iname "*.h"`

example-exam-zip:
	rm -rf example-exam-tmp
	git clone --depth 1 -b example-exam https://github.com/VU-Programming/sypp-skeleton.git example-exam-tmp
	cp src/*.c example-exam-tmp/src/
	mv example-exam-tmp/include/ijvm.h example-exam-tmp/ijvm.h.bak
	cp include/*.h example-exam-tmp/include/
	mv example-exam-tmp/ijvm.h.bak example-exam-tmp/include/ijvm.h
	cp -r example-exam-tmp/include  example-exam-tmp/include-backup
	cp -r example-exam-tmp/src example-exam-tmp/src-backup 
	rm -rf example-exam-tmp/.git
	cd example-exam-tmp && zip -r ../example-exam-submission.zip .
	rm -rf example-exam-tmp

	

test%: $(OBJ) $(TSTDIR)/test%.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

run_test%: test%
	./$<



testbasic: run_test1 run_test2 run_test3 run_test4 run_test5
testadvanced: run_testadvanced1 run_testadvanced2 run_testadvanced3 run_testadvanced4 run_testadvanced5 run_testadvanced6  run_testadvanced7 run_testadvanced8
testall: testbasic testadvanced
build_tests: test1 test2 test3 test4 test5 testadvanced1 testadvanced2 testadvanced3 testadvanced4 testadvanced5 testadvanced6 testadvanced7 testadvanced8


# Uses LLVM sanitizers
testasan: CC=clang
testasan: CFLAGS += -fsanitize=undefined,address
testasan: clean testall

testmemsan: CC=clang
testmemsan: CFLAGS += -fsanitize=undefined,memory
testmemsan: clean testall

testsanitizers: testasan testmemsan

pedantic: CFLAGS+=$(PEDANTIC_CFLAGS)
pedantic: clean ijvm


testleaks: clean build_tests
	for test in $(TESTS); do \
		valgrind --leak-check=full ./$$test; \
	done

# redirects valgrind output to file
saveleaks: clean build_tests
	for test in $(TESTS); do \
		valgrind --leak-check=full ./$$test 2> valgrind-$$test.txt; \
	done

coverage: CFLAGS+=-fprofile-instr-generate -fcoverage-mapping
coverage: CC=clang
coverage: clean ijvm build_tests
	LLVM_PROFILE_FILE="profdata/profile-%p.profraw" make testall
	llvm-profdata merge -sparse profdata/*.profraw -o profdata/testcoverage.profdata
	llvm-cov report ./ijvm -instr-profile=profdata/testcoverage.profdata
