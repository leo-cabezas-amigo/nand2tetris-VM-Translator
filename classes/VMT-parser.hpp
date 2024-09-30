// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

//#include <string>
//#include <map>
#include <vector>
#include <fstream>

#include "../lib/VMT-lib.hpp"

using namespace std;

class Parser{
	private:
		ifstream input_file;
		string command;
		vector<string> args;
		
	public:
		Parser(string input_filepath){
			this->input_file.open(input_filepath);
			if (!this->input_file) throw "Invalid input file";
		}
		
		static vector<string> commandSplit(string command){
			vector<string> args;
			size_t start, end;
			string command_substr;
			
			size_t comment_pos = command.find_first_of("//");
			if (comment_pos != string::npos){
				command_substr = command.substr(0, comment_pos);
			} else {
				command_substr = command;
			}
			
			while(true){
				start = command_substr.find_first_not_of("\t\n\v\f\r ");
				if (start == string::npos) break;
				command_substr = command_substr.substr(start);
				
				end = command_substr.find_first_of("\t\n\v\f\r ");
				if (end == string::npos) end = command_substr.size();
								
				args.push_back(command_substr.substr(0, end));
				command_substr = command_substr.substr(end);
			}
			return args;
		}
		
		bool advance(){
			while (getline(input_file, this->command)){
				if (this->command.empty()) continue;
				this->args = commandSplit(this->command);
				if (this->args.size() != 0) return true;
			}
			return false;
		}
		
		int commandType(){
			if (this->args.empty()){
				throw "Empty command";
			} else if (arithmetic_map.find(this->args[0]) != arithmetic_map.end()){
				return C_ARITHMETIC;
			} else if (this->args[0] == "push" || this->args[0] == "pop"){
				return C_PUSH_POP;
			} else if (branching_map.find(this->args[0]) != branching_map.end()){
				return C_BRANCHING;
			} else if (this->args[0] == "function"){
				return C_FUNCTION;
			} else if (this->args[0] == "call"){
				return C_CALL;
			} else if (this->args[0] == "return"){
				return C_RETURN;
			} else throw "Invalid arg0";
		}
		
		vector<string> get_args(){
			return this->args;
		}
};
