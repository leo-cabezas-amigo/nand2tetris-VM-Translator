// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

//#include <string>
//#include <map>
//#include <vector>
//#include <fstream>
#include <iostream>
#include <dirent.h>

#include "./VMT-parser.hpp"
#include "./VMT-codewriter.hpp"

class Translator{
	private:
		int command_count = 0;
		
	public:
		static string get_filename(string filepath, bool strip_extension = false){
			string filename;
			
			size_t separator_pos = filepath.find_last_of("/\\");
			if (separator_pos != string::npos){
				filename = filepath.substr(separator_pos + 1);
			} else {
				filename = filepath;
			}
			
			if (!strip_extension) return filename;
			
			size_t extension_pos = filename.find_first_of(".");
			if (extension_pos != string::npos){
				filename = filename.substr(0, extension_pos);
			}
			return filename;
		}
		
		static string get_extension(string filepath){
			string extension;
			
			size_t separator_pos = filepath.find_last_of("/\\");
			size_t extension_pos = filepath.find_last_of(".");
			if (extension_pos != string::npos && separator_pos < extension_pos){
				extension = filepath.substr(extension_pos);
			} else {
				extension = "";
			}
			return extension;
		}
		
		static string set_extension(string filepath, string extension){
			string new_filepath;
			
			size_t separator_pos = filepath.find_last_of("/\\");
			size_t extension_pos = filepath.find_last_of(".");			
			if (extension_pos != string::npos && separator_pos < extension_pos){
				new_filepath = filepath.substr(0, extension_pos) + extension;
			} else {
				new_filepath = filepath + extension;
			}
			return new_filepath;
		}
		
		void clear_file(string output_filepath){
			CodeWriter code_writer(output_filepath, true);
		}
		
		void inject_bootstrap(string output_filepath){
			CodeWriter code_writer(output_filepath);
			code_writer.writeBootstrap(this->command_count);
		}
		
		void translate_file(string input_filepath, string output_filepath = ""){
			string input_extension = Translator::get_extension(input_filepath);
			if (input_extension != ".vm") throw "Invalid file extension";
			
			Parser parser(input_filepath);
			
			if (output_filepath == ""){
				output_filepath = Translator::set_extension(input_filepath, ".asm");
			}
			CodeWriter code_writer(output_filepath);
			
			string input_filename_wex = get_filename(input_filepath, true);
			string current_function = "";
			vector<string> args;
			int command_type;
						
			while (parser.advance()){
				args = parser.get_args();
				command_type = parser.commandType();
				
				switch(command_type){
					case C_ARITHMETIC:
						code_writer.writeArithmetic(args, this->command_count);
						break;
					case C_PUSH_POP:
						code_writer.writePushPop(args, input_filename_wex);
						break;
					case C_BRANCHING:
						code_writer.writeBranching(args, current_function);
						break;
					case C_FUNCTION:
						code_writer.writeFunction(args, this->command_count);
						current_function = args[1];
						break;
					case C_CALL:
						code_writer.writeCall(args, current_function, this->command_count);
						break;
					case C_RETURN:
						code_writer.writeReturn();
						break;
				}
				this->command_count++;
			}
			cout << "... Sucessfully translated '" << input_filename_wex << ".vm'!" << endl;
			code_writer.close();
		}
		
		void translate_directory(string directory_path, string output_filepath = ""){
			DIR* directory;
			struct dirent* entry;
			
			try{
				directory = opendir(&directory_path[0]);
			} catch(...){
				throw "Invalid directory path";
			}
			
			string extension = get_extension(directory_path);
			if (!directory && extension == ".vm"){
				translate_file(directory_path, output_filepath);
				return;
			}
			
			string next_directory_path;
			while(entry = readdir(directory)){
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
					continue;
				}	
				next_directory_path = directory_path + "/" + entry->d_name;
				translate_directory(next_directory_path, output_filepath);
			}
		}
};
