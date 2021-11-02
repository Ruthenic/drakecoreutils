# drakecoreutils
the best coreutils since minix
#### building
1. reconsider your life decisions
2. use glibc (unless something has changed since i've last tried, it breaks on musl and serenityos's libc ~~because they actually do it right~~)
3. run `make` to produce the `dbox` executable (CC,CC_FLAGS,LD_FLAGS are the env variables i use for compiler settings)
4. similar to busybox, you can either manually invoke dbox with the name of the executable (i.e. `bin/dbox ls -cCa`), or link the dbox executable to whatever you want to use (i.e. `ln bin/dbox bin/ls; bin/ls -cCa`)
5. congrats, you have built the best set of coreutils since minix
#### todo
- fix memory issues in everything (but `ls` specifically)
- proper formatting in `ls`
- allow a way to manually use multi-binary mode? (currently you can (in theory) just rename the `dbox` executable to whatever program you want, albiet with the slight overhead of `dbox`)
- better name for the executable than `dbox`
