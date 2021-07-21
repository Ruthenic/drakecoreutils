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

#define ANSI_BASE(n) "\e[" #n "m"

#define ANSI_RESET ANSI_BASE(0)
#define ANSI_BOLD ANSI_BASE(1)
#define ANSI_FAINT ANSI_BASE(2)
#define ANSI_ITALIC ANSI_BASE(3)
#define ANSI_UNDERLINE ANSI_BASE(4)
#define ANSI_BLINK ANSI_BASE(5)
#define ANSI_REVERSE ANSI_BASE(7)
#define ANSI_CROSSED ANSI_BASE(9)

#define ANSI_DOUBLE_UNDERLINE ANSI_BASE(21)
#define ANSI_DISABLE_BOLD ANSI_BASE(22)
#define ANSI_DISABLE_FAINT ANSI_DISABLE_BOLD
#define ANSI_DISABLE_ITALIC ANSI_BASE(23)
#define ANSI_DISABLE_UNDERLINE ANSI_BASE(24)
#define ANSI_DISABLE_BLINK ANSI_BASE(25)
#define ANSI_DISABLE_REVERSE ANSI_BASE(27)
#define ANSI_DISABLE_CROSSED ANSI_BASE(29)

#define ANSI_BLACK ANSI_BASE(30)
#define ANSI_RED ANSI_BASE(31)
#define ANSI_GREEN ANSI_BASE(32)
#define ANSI_YELLOW ANSI_BASE(33)
#define ANSI_BLUE ANSI_BASE(34)
#define ANSI_MAGENTA ANSI_BASE(35)
#define ANSI_CYAN ANSI_BASE(36)
#define ANSI_WHITE ANSI_BASE(37)
#define ANSI_BRIGHT_BLACK ANSI_BASE(90)
#define ANSI_BRIGHT_RED ANSI_BASE(91)
#define ANSI_BRIGHT_GREEN ANSI_BASE(92)
#define ANSI_BRIGHT_YELLOW ANSI_BASE(93)
#define ANSI_BRIGHT_BLUE ANSI_BASE(94)
#define ANSI_BRIGHT_MAGENTA ANSI_BASE(95)
#define ANSI_BRIGHT_CYAN ANSI_BASE(96)
#define ANSI_BRIGHT_WHITE ANSI_BASE(97)
