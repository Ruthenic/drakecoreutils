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
all: main.c

${PROGS}:
	@echo Building $@..
	@${CC} -c -o bin/$@.o -DDRAKECU_VERSION=${VERSION} ${CC_FLAGS} src/$@.c

main.c:
	@${CC} -o bin/dbox src/main.c $(wildcard bin/*.o)

debug: CC_FLAGS:=-g -O0 -v ${CC_FLAGS}
debug: all

clean:
	@rm -rf bin

build-release: CC_FLAGS:=-O3 ${CC_FLAGS}
build-release: all
build-release:
	@strip bin/*
	tar -czf release.tar.gz bin/*

install:
	@install -m 777 bin/dbox ${DESTDIR}/usr/local/bin 
	@for prog in ${PROGS}; do \
		ln ${DESTDIR}/usr/local/bin/dbox ${DESTDIR}/usr/local/bin/$$prog; \
	done
	@for prog in ${EXCLUDE_PROGS}; do \
		rm ${DESTDIR}/usr/local/bin/$$prog; \
	done
