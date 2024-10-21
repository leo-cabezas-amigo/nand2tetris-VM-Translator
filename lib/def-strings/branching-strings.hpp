// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

#ifndef _VMT_BRANCHING_HPP_
#define _VMT_BRANCHING_HPP_

#define LABEL_STR \
"\
(LABEL)\n\
"

#define GOTO_STR \
"\
@LABEL\n\
0;JMP\n\
"

#define IFGOTO_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
@LABEL\n\
D;JNE\n\
"

#endif	// _VMT_BRANCHING_HPP_
