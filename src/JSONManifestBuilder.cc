// ============================================================= //
// btb
// Copyright (C) 2024, Theater Quality Inc, all rights reserved.
// ============================================================= //

#include <JSONManifestBuilder.h>

using String = std::string;
using JSON = nlohmann::json;
namespace FS = std::filesystem;

/// @brief Builds a JSON target from a JSON file.
/// @param arg_sz filename size (must be 1 or greater).
/// @param arg_val filename path (must be a valid JSON file).
/// @retval true succeeded building.
/// @retval false failed to build.
bool JSONManifestBuilder::buildTarget(int arg_sz, const char* arg_val, const bool dry_run)
{
	String path;

	if (arg_sz < 0)
	{
		std::cout << "btb: error: file path is empty." << std::endl;
		return false;
	}
	else
	{
		path = arg_val;

		if (!FS::exists(path))
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

		String compiler = json_obj["compiler_path"].get<String>();

		JSON header_search_path = json_obj["headers_path"];
		JSON sources_files		= json_obj["sources_path"];

		String command = compiler + " ";

		for (auto& sources : sources_files)
		{
			command += sources.get<String>() + " ";
		}

		for (auto& headers : header_search_path)
		{
			command += "-I" + headers.get<String>() + " ";
		}

		JSON macros_list = json_obj["cpp_macros"];

		for (auto& macro : macros_list)
		{
			command += "-D" + macro.get<String>() + " ";
		}

		JSON compiler_flags = json_obj["compiler_flags"];

		for (auto& flag : compiler_flags)
		{
			command += flag.get<String>() + " ";
		}

		if (json_obj["compiler_std"].is_string())
			command += "-std=" + json_obj["compiler_std"].get<String>() + " ";

		command += "-o " + json_obj["output_name"].get<String>();

		auto target = json_obj["output_name"].get<String>();

		std::cout << "btb: output path: " << target << "\n";
		std::cout << "btb: command: " << command << "\n";

		try
		{
			if (json_obj["dry_run"].get<bool>())
				return true;
		}
		catch (...)
		{
			
		}

		if (dry_run)
		{
			return true;
		}

		auto ret_exec = std::system(command.c_str());

		if (ret_exec > 0)
		{
			std::cout << "btb: error: exec exit with code: " << ret_exec << "." << std::endl;
			return false;
		}

		try
		{
			if (json_obj["run_after_build"].get<bool>())
			{
				if (target.ends_with(".so"))
				{
					std::cout << "btb: error: can't open dynamic library, it may not have an entrypoint." << std::endl;
					return true;
				}
				else if (target.ends_with(".dll"))
				{
					std::ifstream file = std::ifstream(target);

					std::stringstream ss;
					ss << file.rdbuf();

					if (ss.str()[0] == 'J' &&
						ss.str()[1] == 'o' &&
						ss.str()[2] == 'y' &&
						ss.str()[3] == '!')
						std::cout << "btb: error: can't open Joy! dynamic library, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == '!' &&
							 ss.str()[1] == 'y' &&
							 ss.str()[2] == 'o' &&
							 ss.str()[3] == 'J')
						std::cout << "btb: error: can't open !yoJ dynamic library, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == 'M' &&
							 ss.str()[1] == 'Z')
						std::cout << "btb: error: can't open MZ dynamic library, it maynt't contain an entrypoint." << std::endl;
					else if (ss.str()[0] == 0x7F &&
							 ss.str()[1] == 'E')
					{
						std::cout << "btb: error: can't open ELF dynamic library, it maynt't contain an entrypoint." << std::endl;
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

const char* JSONManifestBuilder::buildSystem()
{
	return "json";
}
