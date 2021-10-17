#include "FileLoader.hpp"
#include <fstream>
#include <iostream>
std::string FileLoader::readRawFromFile(const std::string& fileName)
{
    std::ifstream file(fileName);

    std::string rawData;

    if(file.is_open())
    {
        char readChar;

        while((readChar=file.get())!=EOF)
        {
            rawData+=readChar;
        }
        file.close();
    }
    else
    {
        std::cout<<fileName<<" file cannot be opened"<<std::endl;
    }
    return rawData;
}