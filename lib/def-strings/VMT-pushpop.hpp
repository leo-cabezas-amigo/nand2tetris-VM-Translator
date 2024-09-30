// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

#ifndef _VMT_PUSHPOP_HPP_
#define _VMT_PUSHPOP_HPP_

#define PUSH_STR \
"\
@INDEX\n\
D=A\n\
@SEGMENT\n\
[A=M\n]\
A=A+D\n\
D=M\n\
@SP\n\
M=M+1\n\
A=M\n\
A=A-1\n\
M=D\n\
"

#define ALT_PUSH_STR \
"\
@SEGMENT\n\
D=[M|A]\n\
@SP\n\
M=M+1\n\
A=M\n\
A=A-1\n\
M=D\n\
"

#define POP_STR \
"\
@INDEX\n\
D=A\n\
@SEGMENT\n\
[A=M\n]\
A=A+D\n\
D=A\n\
@SP\n\
M=M-1\n\
A=M\n\
D=D+M\n\
A=D-M\n\
M=D-A\n\
"

#define ALT_POP_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@SEGMENT\n\
M=D\n\
"

#endif	// _VMT_PUSHPOP_HPP_
