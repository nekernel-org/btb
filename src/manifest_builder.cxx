//
//  main.cpp
//  buildme
//
//  Created by Amlal on 6/20/24.
//

#include <cstdio>
#include <json.hxx>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <manifest_builder.hxx>

using json = nlohmann::json;

bool ManifestBuilder::buildJson(int arg_sz, const char* arg_val)
{
	std::cout << "buildme: ";
	std::string path;

	if (arg_sz < 0)
	{
		std::cout << "no files provided.\n";
		return false;
	}
	else
	{
		path = arg_val;
	}

	try
	{
		std::ifstream json_obj(path);

		if (!json_obj.good())
		{
			std::cout << "buildme: no files provided.\n";
			perror("buildme");

			return false;
		}

		json buildme = json::parse(json_obj);

		std::string compiler = buildme["compiler_path"].get<std::string>();
		std::cout << "choose toolchain: " << compiler << std::endl;

		json headerSearchPath = buildme["headers_path"];
		std::cout << "buildme: search path: " << headerSearchPath.dump() << std::endl;

		json sourceFiles = buildme["sources_path"];
		std::cout << "buildme: source files: " << sourceFiles.dump() << std::endl;

		std::string cmdLine = compiler + " ";

		for (auto& sources : sourceFiles)
		{
			cmdLine += sources.get<std::string>() + " ";
		}

		for (auto& headers : headerSearchPath)
		{
			cmdLine += "-include=" + headers.get<std::string>() + " ";
		}

		cmdLine += "-std=" + buildme["compiler_std"].get<std::string>() + " ";

		cmdLine += "-o " + buildme["output_name"].get<std::string>();

		std::cout << "buildme: running: '" << cmdLine << "'" << std::endl;

		std::system(cmdLine.c_str());
	}
	catch (std::runtime_error& err)
	{
		perror("buildme");
		std::cout << "buildme: error: " << err.what() << std::endl;

		return false;
	}

	return true;
}
