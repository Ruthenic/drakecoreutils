ifndef CC
CC = 
endif
ifndef IP
IP := 192.168.1.10
#use my tv's ip if not passed to makefile
endif
target := $(shell ${CC} -dumpmachine)
ifeq (${target}, arm-webos-linux-gnueabi)
$(info Setting compiler include flags for webOS...)
ifndef CC_FLAGS
#guess we gotta define this if it no exist, but imagine not needing custom cxx flags
CC_FLAGS :=
endif
CC_FLAGS := ${CC_FLAGS} -I/opt/webos-sdk-x86_64/1.0.g/sysroots/armv7a-neon-webos-linux-gnueabi/usr/include --sysroot=/opt/webos-sdk-x86_64/1.0.g/sysroots/armv7a-neon-webos-linux-gnueabi
endif
ifndef PROGS
PROGS := whoami arch ls pwd
endif
make:
	mkdir -p bin
	for prog in ${PROGS}; do ${CC} -o bin/$$prog -Ilib ${CC_FLAGS} src/$$prog.c; done 
tv:
	scp hbpm root@${IP}:/media/internal/bin
verbose:
	mkdir -p bin
	for prog in ${PROGS}; do ${CC} -v -o bin/$$prog ${CC_FLAGS} src/$$prog.c; done 
clean:
	@rm -rf bin
help:
	@echo 'make' - Build normal version
	@echo 'make verbose' - Build normal version with verbose compilation for debugging
	@echo 'make help' - Display this help message
