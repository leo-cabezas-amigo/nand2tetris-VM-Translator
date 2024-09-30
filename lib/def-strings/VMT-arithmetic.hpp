// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

#ifndef _VMT_ARITHMETIC_HPP_
#define _VMT_ARITHMETIC_HPP_

#define ADD_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M+D\n\
M=D\n\
"

#define SUB_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M-D\n\
M=D\n\
"

#define NEG_STR \
"\
@SP\n\
A=M\n\
A=A-1\n\
M=-M\n\
"

#define EQ_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M-D\n\
M=[FALSE]\n\
@_EQ_JUMP_ID[X]_\n\
D;JNE\n\
@SP\n\
A=M\n\
A=A-1\n\
M=[TRUE]\n\
(_EQ_JUMP_ID[X]_)\n\
"

#define GT_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M-D\n\
M=[FALSE]\n\
@_GT_JUMP_ID[X]_\n\
D;JLE\n\
@SP\n\
A=M\n\
A=A-1\n\
M=[TRUE]\n\
(_GT_JUMP_ID[X]_)\n\
"

#define LT_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M-D\n\
M=[FALSE]\n\
@_LT_JUMP_ID[X]_\n\
D;JGE\n\
@SP\n\
A=M\n\
A=A-1\n\
M=[TRUE]\n\
(_LT_JUMP_ID[X]_)\n\
"

#define AND_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M&D\n\
M=D\n\
"

#define OR_STR \
"\
@SP\n\
M=M-1\n\
A=M\n\
D=M\n\
A=A-1\n\
D=M|D\n\
M=D\n\
"

#define NOT_STR \
"\
@SP\n\
A=M\n\
A=A-1\n\
M=!M\n\
"

#endif	// _VMT_ARITHMETIC_HPP_
