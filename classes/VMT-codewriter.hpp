// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

//#include <string>
//#include <map>
#include <vector>
#include <fstream>

#include "../lib/VMT-lib.hpp"

using namespace std;

class CodeWriter{
	private:
		ofstream output_file;
	
	public:
		CodeWriter(string output_filepath = "./output.asm", bool overwrite = false){
			if (overwrite){
				this->output_file.open(output_filepath);
			} else {
				this->output_file.open(output_filepath, ios::app);
			}
			if (!this->output_file) throw "Invalid output file";
		}
		
		static void replaceAll(string& str, string from, string to){
		    size_t q, p = 0;
			    
		    while (true){
		    	q = str.substr(p).find(from);
		        if (q != string::npos){
		        	str.replace(p + q, from.length(), to);
		        	p += q + to.length();
				} else break;
    		}
		}
		
		void writeBootstrap(int command_count){
			string return_address, bootstrap_str = BOOTSTRAP_STR;
			
			return_address = "Sys.init$" + to_string(command_count);
			
			CodeWriter::replaceAll(bootstrap_str, "FUNCTION_NAME", "Sys.init");
			CodeWriter::replaceAll(bootstrap_str, "NARGS", "0");
			CodeWriter::replaceAll(bootstrap_str, "RETURN_ADDRESS", return_address);
			
			this->output_file << bootstrap_str;
		}
		
		void writeArithmetic(vector<string> args, int command_count){
			string arithmetic_str = arithmetic_map[args[0]];
			
			if (args[0] == "eq" or args[0] == "gt" or args[0] == "lt"){
				CodeWriter::replaceAll(arithmetic_str, "[TRUE]", TRUE);
				CodeWriter::replaceAll(arithmetic_str, "[FALSE]", FALSE);
				CodeWriter::replaceAll(arithmetic_str, "[X]", to_string(command_count));	
			}
			
			this->output_file << arithmetic_str;
		}
		
		void writePushPop(vector<string> args, string input_filename_wex){
			string pushpop_str, temp_str, segment, index, reg;
			int int_index;
			bool is_std_str, is_push, is_temp = false;
			
			is_push = (args[0] == "push") ? true : false;
			
			// Rewrite!
			try{
				index = args[2];
				int_index = stoi(index);
			} catch(...){throw "Non-int index";}
			if (int_index < 0) throw "Negative index";
			
			// Rewrite in a cleaner format!
			if (segment_map.find(args[1]) != segment_map.end()){
				is_std_str = true;
				segment = segment_map[args[1]];
				
				// Might be unnecessary!
				if (args[1] == "temp"){
					if (int_index > MAX_TEMP_INDEX) throw "Invalid index (TEMP)";
					is_temp = true;
				}
			} else if (args[1] == "pointer"){
				is_std_str = false;
				reg = "M";
				
				// Maybe rewrite this!
				if (index == "0"){
					segment = "THIS";
				} else if (index == "1"){
					segment = "THAT";
				} else throw "Invalid index (POINTER)";
			} else if (args[1] == "constant" && is_push){
				is_std_str = false;
				reg = "A";
				segment = index;
			} else if (args[1] == "static"){
				is_std_str = false;
				reg = "M";
				segment = input_filename_wex + "." + index;
			} else throw "Invalid arg1";
			
			if (is_std_str){
				pushpop_str = is_push ? PUSH_STR : POP_STR;
				CodeWriter::replaceAll(pushpop_str, "SEGMENT", segment);
				CodeWriter::replaceAll(pushpop_str, "INDEX", index);
				
				temp_str = is_temp ? "" : "A=M\n";
				CodeWriter::replaceAll(pushpop_str, "[A=M\n]", temp_str);
			} else {
				pushpop_str = is_push ? ALT_PUSH_STR : ALT_POP_STR;
				CodeWriter::replaceAll(pushpop_str, "SEGMENT", segment);
				CodeWriter::replaceAll(pushpop_str, "[M|A]", reg);
			}
			
			this->output_file << pushpop_str;
		}
		
		void writeBranching(vector<string> args, string function_name){
			string branching_str, label;
			
			if (branching_map.find(args[0]) != branching_map.end()){
				branching_str = branching_map[args[0]];
			}
			string prefix = function_name + ((function_name != "") ? "$" : "");
			label = prefix + args[1];
			
			CodeWriter::replaceAll(branching_str, "LABEL", label);
			
			this->output_file << branching_str;	
		}
		
		void writeFunction(vector<string> args, int command_count){
			string function_str = FUNCTION_STR;
			
			CodeWriter::replaceAll(function_str, "FUNCTION_NAME", args[1]);
			CodeWriter::replaceAll(function_str, "NVARS", args[2]);
			CodeWriter::replaceAll(function_str, "[X]", to_string(command_count));
			
			this->output_file << function_str;
		}
		
		void writeCall(vector<string> args, string function_name, int command_count){
			string return_address, call_str = CALL_STR;
			
			string prefix = function_name + ((function_name != "") ? "$" : "");
			return_address = prefix + "ret." + to_string(command_count);
			
			CodeWriter::replaceAll(call_str, "FUNCTION_NAME", args[1]);
			CodeWriter::replaceAll(call_str, "NARGS", args[2]);
			CodeWriter::replaceAll(call_str, "RETURN_ADDRESS", return_address);
			
			this->output_file << call_str;
		}
		
		void writeReturn(){
			this->output_file << RETURN_STR;
		}
		
		void close(){
			this->output_file.close();
		}
};
