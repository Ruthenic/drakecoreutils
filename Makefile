VERSION = "\"0.3.2\\n© Ruthenic, 2021\""

CC ?= gcc
target ?= $(shell ${CC} -dumpmachine)
CC_FLAGS ?=
CC_FLAGS := -Ilib
PROGS ?= arch basename cat chroot cp ls pwd rm uname whoami yes
EXCLUDE_PROGS ?= rm
DESTDIR ?= /

.PHONY: all debug clean build-release install
all: $(shell mkdir -p bin)
all: ${PROGS}

${PROGS}:
	@echo Building $@..
	@${CC} -o bin/$@ -DDRAKECU_VERSION=${VERSION} ${CC_FLAGS} src/$@.c

debug: CC_FLAGS:=-g -O0 -v ${CC_FLAGS}
debug: all

clean:
	@rm -rf bin

build-release: CC_FLAGS:=-O3 ${CC_FLAGS}
build-release: all
build-release:
	@strip bin/*
	tar -czf release.tar.gz bin/*

#TODO: fix this, this is terrible oh god help me
install:
	@for prog in ${EXCLUDE_PROGS}; do \
	  mv bin/$$prog /tmp; \
	done
	install -m 777 bin/* ${DESTDIR}usr/local/bin
	@for prog in ${EXCLUDE_PROGS}; do \
	  mv /tmp/$$prog bin; \
	done

