// -*- coding: utf-8 -*-

// Author: Leo Cabezas Amigo
// Course: nand2tetris II

//#include <string>
//#include <map>
//#include <vector>
//#include <fstream>
//#include <iostream>
//#include <dirent.h>

#include "./classes/VMT-translator.hpp"

using namespace std;

int main(int argc, char** argv){
	string directory_path = argv[1];
	string output_filepath = Translator::set_extension(argv[1], ".asm");
	
	try{
		Translator translator;
		
		translator.clear_file(output_filepath);
		//translator.inject_bootstrap(output_filepath);
		translator.translate_directory(directory_path, output_filepath);
		
		cout << ">>> Translation of '" << directory_path << \
			"' successful!" << endl;
		cout << ">>> Path to output file: '" << output_filepath << \
			"'." << endl;
	} catch(const char* exception){
		cerr << ">>> Exception: " << exception << endl;
		remove(&output_filepath[0]);
	}
	
	return 0;
}
