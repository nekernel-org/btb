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
	std::string path;

	if (arg_sz < 0)
	{
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
			return false;
		}

		json buildme = json::parse(json_obj);

		std::string compiler = buildme["compiler_path"].get<std::string>();

		json headerSearchPath = buildme["headers_path"];
		json sourceFiles = buildme["sources_path"];

		std::string cmdLine = compiler + " ";

		for (auto& sources : sourceFiles)
		{
			cmdLine += sources.get<std::string>() + " ";
		}

		for (auto& headers : headerSearchPath)
		{
			cmdLine += "-I" + headers.get<std::string>() + " ";
		}

		json macrosList = buildme["cpp_macros"];

		for (auto& macro : macrosList)
		{
			cmdLine += "-D" + macro.get<std::string>() + " ";
		}

		json compilerFlags = buildme["compiler_flags"];

		for (auto& flag : compilerFlags)
		{
			cmdLine += flag.get<std::string>() + " ";
		}

		cmdLine += "-std=" + buildme["compiler_std"].get<std::string>() + " ";
		cmdLine += "-o " + buildme["output_name"].get<std::string>();

		std::system(cmdLine.c_str());
	}
	catch (std::runtime_error& err)
	{
		std::cout << "buildme: error: " << err.what() << std::endl;
		perror("buildme");

		return false;
	}

	return true;
}
