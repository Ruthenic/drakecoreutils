#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
BSD 3-Clause License

Copyright (c) 2021, Ruthenic
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

int matchExec(char *name, int argc, char *argv[]) {
	if (!strcmp(name,"arch")) {
		arch(argc, argv);
	}
	if (!strcmp(name,"basename")) {
		bn(argc, argv);
	}
	if (!strcmp(name,"cat")) {
		cat(argc, argv);
	}
	if (!strcmp(name,"chroot")) {
		chr(argc, argv);
	}
	if (!strcmp(name,"cp")) {
		cp(argc, argv);
	}
	if (!strcmp(name,"ls")) {
		ls(argc, argv);
	}
	if (!strcmp(name,"pwd")) {
		pwd(argc, argv);
	}
	if (!strcmp(name,"rm")) {
		rm(argc, argv);
	}
	if (!strcmp(name,"uname")) {
		un(argc, argv);
	}
	if (!strcmp(name,"whoami")) {
		whoami(argc, argv);
	}
	if (!strcmp(name,"yes")) {
		yes(argc, argv);
	}
	if (!strcmp(name,"dbox")) {
		char **newArgv = argv + 1;
		matchExec(newArgv[0], argc-1, newArgv);
	}
	return 0; //TODO: return return of exec files
}

int main(int argc, char *argv[])
{
	char *linkName = basename(argv[0]);
	printf("%s\n", linkName);
	printf("Executing %s...\n", linkName);
	matchExec(linkName, argc, argv);
	return 0;
}
