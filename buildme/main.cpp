//
//  main.cpp
//  buildme
//
//  Created by Amlal on 6/20/24.
//

#include <iostream>
#include <fstream>

#include "json.hpp"

using json = nlohmann::json;

int main(int argc, const char * argv[])
{
    std::cout << "buildme: ";
    std::string path;
    
    if (argc == 1)
    {
        std::cout << "no files, defaulting to build.json\n";
        path = "./build.json";
    }
    else
    {
        path = argv[1];
    }
    
    try
    {
        std::ifstream fJson(path);
        json buildme = json::parse(fJson);
        
        std::string compiler = buildme["compiler_path"].get<std::string>();
        std::cout << "choose toolchain: " << compiler << std::endl;
        
        json headerSearchPath = buildme["headers_path"];
        std::cout << "search path: " << headerSearchPath.dump() << std::endl;
        
        json sourceFiles = buildme["sources_path"];
        std::cout << "source files: " << sourceFiles.dump() << std::endl;
        
        std::string cmdLine = compiler + " ";
        
        for (auto sources : sourceFiles)
        {
            cmdLine += sources.get<std::string>() + " ";
        }
        
        for (auto sources : sourceFiles)
        {
            cmdLine += "-include=" + sources.get<std::string>() + " ";
        }
        
        cmdLine += "-std=" + buildme["compiler_std"].get<std::string>() + " ";
        
        std::cout << "running: " << cmdLine << std::endl;
        
        std::system(cmdLine.c_str());
    }
    catch (...)
    {
        return 1;
    }
    
    return 0;
}
