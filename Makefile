ifndef CC
CC = gcc
endif
target := $(shell ${CC} -dumpmachine)
ifndef CC_FLAGS
#guess we gotta define this if it no exist, but imagine not needing custom cxx flags
CC_FLAGS :=
endif
CC_FLAGS := -Ilib ${CC_FLAGS} 
ifndef PROGS
PROGS := whoami arch ls pwd basename uname yes
endif
all:
	@mkdir -p bin
	@for prog in ${PROGS}; do echo Building $$prog... && ${CC} -o bin/$$prog ${CC_FLAGS} src/$$prog.c; done
verbose:
	@mkdir -p bin
	@for prog in ${PROGS}; do echo Building $$prog... && ${CC} -v -o bin/$$prog ${CC_FLAGS} src/$$prog.c; done
debug:
	@mkdir -p bin
	@for prog in ${PROGS}; do echo Building $$prog... && ${CC} -g -O0 -v -o bin/$$prog ${CC_FLAGS} src/$$prog.c; done
clean:
	@rm -rf bin
help:
	@echo "Drake's Epic Coreutils Makefile Help Page™"
	@echo 'make' - build normal version.
	@echo 'make debug' - build verbosly, and with \`-g -O0\` for the lowest amount of compiler optimization, so that valgrind and such can report line numbers, and have more information in general
	@echo 'make verbose' - build normal version with verbose compilation for debugging.
	@echo 'make clean' - removes binaries.
	@echo 'make help' - display this help message.
