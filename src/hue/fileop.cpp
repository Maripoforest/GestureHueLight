/*
Arthor: Xiangmin XU (Maripoforest)
logfile operation for Hue
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "fileop.h"


logfile::logfile(std::string _filename) {
    this->filename = _filename;
}


logfile::logfile(void) {
    this->filename = "../log.txt";
}

bool logfile::readfile(std::vector<std::string>& lines) {
    std::ifstream input_file(this->filename);
    std::string line;
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << filename << "'" << std::endl;
        return false;
    }

	while (std::getline(input_file, line)){
        lines.push_back(line);
    }
    
    return true;
}

void logfile::writefile(std::string ip, std::string username) {
    std::ofstream output_file(filename, std::ios::trunc);
	output_file << ip << "\n" << username;
	output_file.close();
}
