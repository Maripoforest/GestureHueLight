#ifndef FILEOP_H
#define FILEOP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class logfile
{
private:
    std::string filename;
public:

    //constructor, with file path
    logfile(std::string _filename);
    
    //the bool return decides whether it succeeded reading the file
    bool readfile(std::vector<std::string>& lines);

    //write the log.txt if ip and username changes
    void writefile(std::string ip, std::string username);
};

#endif