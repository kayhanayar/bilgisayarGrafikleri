#include "FileLoader.hpp"
#include<fstream>
#include<iostream>
std::string FileLoader::getRawData(const std::string& fileName)
{
    std::ifstream dosya(fileName);


    if(!dosya.is_open())
    {
        std::cout<<fileName<<" - Dosya Acilamadi"<<std::endl;
        return  0;
    }

    std::string strData;
    char siradaki;
    while((siradaki=dosya.get())!=EOF)
    {
        strData +=siradaki;
    }

    return strData;
}