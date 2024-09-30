// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

#ifndef _VMT_LIB_HPP_
#define _VMT_LIB_HPP_

#include <string>
#include <map>

#include "def-strings/VMT-arithmetic.hpp"
#include "def-strings/VMT-pushpop.hpp"
#include "def-strings/VMT-branching.hpp"
#include "def-strings/VMT-function_cmds.hpp"

#define C_ARITHMETIC 0
#define C_PUSH_POP 1
#define C_BRANCHING 2
#define C_FUNCTION 3
#define C_CALL 4
#define C_RETURN 5

#define MAX_TEMP_INDEX 7

#define FALSE "0"
#define TRUE "-1"

#define BOOTSTRAP_STR \
"\
@256\n\
D=A\n\
@SP\n\
M=D\n\
"\
 CALL_STR

using namespace std;

map<string, string> segment_map \
{{"local", "LCL"}, {"argument", "ARG"}, {"this", "THIS"}, \
{"that", "THAT"}, {"temp", "5"}};

// map<string, string> pointer_map;

map<string, string> arithmetic_map \
{{"add", ADD_STR}, {"sub", SUB_STR}, {"neg", NEG_STR}, \
{"eq", EQ_STR}, {"gt", GT_STR}, {"lt", LT_STR}, \
{"and", AND_STR}, {"or", OR_STR}, {"not", NOT_STR}};

map<string, string> branching_map \
{{"label", LABEL_STR}, {"goto", GOTO_STR}, {"if-goto", IFGOTO_STR}};

#endif	// _VMT_LIB_HPP_
