//
//  main.cpp
//  btb
//
//  Created by Amlal on 6/20/24.
//

#include <JSONManifestBuilder.hxx>

#include <json.hxx>

#include <cstdlib>
#include <cstdio>

#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;

/// @brief Builds a JSON target.
/// @param arg_sz filename size
/// @param arg_val filename path.
/// @retval true succeeded.
/// @retval false failed.
bool JSONManifestBuilder::Build(int arg_sz, const char* arg_val)
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
		json sourceFiles	  = buildme["sources_path"];

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

		if (buildme["compiler_std"].is_string())
			cmdLine += "-std=" + buildme["compiler_std"].get<std::string>() + " ";

		cmdLine += "-o " + buildme["output_name"].get<std::string>();

		std::system(cmdLine.c_str());

		try
		{
			if (buildme["run_after_build"].get<bool>())
			{
				auto target = buildme["output_name"].get<std::string>();

				if (target.ends_with(".so") ||
					target.ends_with(".dll"))
				{
					std::cout << "btb: error: can't open DLL/SO, it mayn't contain an entrypoint." << std::endl;
					return true;
				}
				else if (target.ends_with(".dll"))
				{
					auto			  file = std::ifstream(target);
					std::stringstream ss;
					ss << file.rdbuf();

					if (ss.str()[0] == 'J' &&
						ss.str()[1] == 'o' &&
						ss.str()[2] == 'y' &&
						ss.str()[3] == '!')
						std::cout << "btb: error: can't open Joy! DLL, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == '!' &&
							 ss.str()[1] == 'y' &&
							 ss.str()[2] == 'o' &&
							 ss.str()[3] == 'J')
						std::cout << "btb: error: can't open !yoJ DLL, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == 'M' &&
							 ss.str()[1] == 'Z')
						std::cout << "btb: error: can't open MZ DLL, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == 0x7F &&
							 ss.str()[1] == 'E')
					{
						std::cout << "btb: error: can't open ELF DLL, it maynt't contain an entrypoint." << std::endl;
					}

					return true;
				}

				std::system(("./" + target).c_str());
			}
		}
		catch (...)
		{
			// ignore error...
		}
	}
	catch (std::runtime_error& err)
	{
		std::cout << "btb: error: " << err.what() << std::endl;
		perror("btb");

		return false;
	}

	return true;
}
