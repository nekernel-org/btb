// ============================================================= //
//  btb
// Copyright ZKA Web Services.
// ============================================================= //

#include <JSONManifestBuilder.h>
#include <json.h>

#include <sstream>
#include <iostream>
#include <fstream>

using JSON = nlohmann::json;

/// @brief Builds a JSON target from a JSON file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid JSON file).
/// @retval true succeeded building.
/// @retval false failed to build.
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

		if (!std::filesystem::exists(path))
		{
			std::cout << "btb: error: file '" << path << "' does not exist." << std::endl;
			return false;
		}
	}

	try
	{
		std::ifstream json(path);

		if (!json.good())
		{
			return false;
		}

		JSON json_obj = JSON::parse(json);

		std::string compiler = json_obj["compiler_path"].get<std::string>();

		JSON header_search_path = json_obj["headers_path"];
		JSON sources_files		= json_obj["sources_path"];

		std::string command = compiler + " ";

		for (auto& sources : sources_files)
		{
			command += sources.get<std::string>() + " ";
		}

		for (auto& headers : header_search_path)
		{
			command += "-I" + headers.get<std::string>() + " ";
		}

		JSON macros_list = json_obj["cpp_macros"];

		for (auto& macro : macros_list)
		{
			command += "-D" + macro.get<std::string>() + " ";
		}

		JSON compiler_flags = json_obj["compiler_flags"];

		for (auto& flag : compiler_flags)
		{
			command += flag.get<std::string>() + " ";
		}

		if (json_obj["compiler_std"].is_string())
			command += "-std=" + json_obj["compiler_std"].get<std::string>() + " ";

		command += "-o " + json_obj["output_name"].get<std::string>();

		auto target = json_obj["output_name"].get<std::string>();

		std::cout << "btb: output path: " << target << "\n";
		std::cout << "btb: command: " << command << "\n";

		std::system(command.c_str());

		try
		{
			if (json_obj["run_after_build"].get<bool>())
			{
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

#ifdef _WIN32
				std::system((".\\" + target).c_str());
#else
				std::system(("./" + target).c_str());
#endif
			}
		}
		catch (...)
		{
			return true;
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
