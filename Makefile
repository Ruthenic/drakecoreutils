ifndef CC
CC = gcc
endif
target := $(shell ${CC} -dumpmachine)
ifndef CC_FLAGS
#guess we gotta define this if it no exist, but imagine not needing custom cxx flags
CC_FLAGS :=
endif
ifndef PROGS
PROGS := whoami arch ls pwd basename uname yes
endif
all:
	mkdir -p bin
	for prog in ${PROGS}; do ${CC} -o bin/$$prog -Ilib ${CC_FLAGS} src/$$prog.c; done 
verbose:
	mkdir -p bin
	for prog in ${PROGS}; do ${CC} -v -o bin/$$prog ${CC_FLAGS} src/$$prog.c; done 
clean:
	@rm -rf bin
help:
	@echo 'make' - Build normal version
	@echo 'make verbose' - Build normal version with verbose compilation for debugging
	@echo 'make help' - Display this help message
