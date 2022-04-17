/*
Arthor: Xiangmin XU (Maripoforest)
logfile operation for Hue
*/

#ifndef FILEOP_H
#define FILEOP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class logfile
{
private:
    std::string filename = "../log.txt";
public:

    //constructor, with file path
    logfile(std::string _filename);
    logfile(void);
    
    //the bool return decides whether it succeeded reading the file
    bool readfile(std::vector<std::string>& lines);

    // write the log.txt if ip and username changes
    // void writefile(std::string ip, std::string username);
};

#endif