VERSION="0.3.2\\nCopyright (c) 2021, Ruthenic. Licensed under BSD-3-Clause."
ifndef CC
CC = gcc
endif
target := $(shell ${CC} -dumpmachine)
ifndef CC_FLAGS
#guess we gotta define this if it no exist, \
    but imagine not needing custom cxx flags
CC_FLAGS :=
endif
CC_FLAGS := -Ilib ${CC_FLAGS} 
ifndef PROGS
PROGS := arch basename cat ls pwd uname whoami yes
endif
ifndef DESTDIR
DESTDIR := /
endif

.PHONY: all
.DEFAULT: all
all: ${PROGS}

${PROGS}: %: src/%.c
	@#for some idiotic reason, i can't define 2 `all` targets, one of which can make this directory
	@mkdir -p bin
	@echo Building $@.. 
	@${CC} -o bin/$@ -DDRAKECU_VERSION=\"${VERSION}\" ${CC_FLAGS} $<

.PHONY: debug
debug: CC_FLAGS:=-g -O0 -v ${CC_FLAGS}
debug: all

.PHONY: clean
clean:
	@rm -rf bin

.PHONY: install
install:
	install -m 777 bin/* ${DESTDIR}usr/local/bin

.PHONY: help
help:
	@echo "Drake's Epic Coreutils Makefile Help Page™"
	@echo 'make' - build normal version.
	@echo 'make debug' - build verbosly, and with \`-g -O0\` for the lowest amount of compiler optimization, so that valgrind and such can report line numbers, and have more information in general.
	@echo 'make clean' - removes binaries.
	@echo 'make help' - display this help message.
