#pragma once
#include <string>
class FileLoader
{
public:
    static std::string readRawFromFile(const std::string& fileName);
};