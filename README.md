# drakecoreutils
the best coreutils since toybox
#### building
1. reconsider your life decisions
2. use glibc (unless something has changed since i've last tried, it breaks on musl and serenityos's libc)
3. run `make`
4. congrats, all the programs are now in `./bin`
#### todo
- fix memory issues in everything (but `ls` specifically)
- proper formatting in `ls`
- allow a way to manually use multi-binary mode?
