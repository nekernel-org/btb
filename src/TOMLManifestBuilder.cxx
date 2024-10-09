// ============================================================= //
//  btb
// Copyright ZKA Technologies.
// ============================================================= //

#include <TOMLManifestBuilder.hxx>
#include <toml.hxx>
#include <filesystem>
#include <iostream>

/// @brief Builds a TOML target.
/// @param arg_sz filename size
/// @param arg_val filename path.
/// @retval true succeeded to build.
/// @retval false failed to build.
bool TOMLManifestBuilder::Build(int arg_sz, const char* arg_val)
{
	toml::table tbl;

	try
	{
		tbl = toml::parse_file(arg_val);

		if (tbl["CPlusPlus"].is_table())
		{
			auto				  cxx		  = tbl["CPlusPlus"];
			std::string			  output_name = cxx["cxx_output_name"].value_or("assembly_out.exe");
			std::filesystem::path output_path = std::filesystem::current_path() / std::filesystem::path(output_name);

			std::vector<std::string> source_files_array;

			if (cxx["cxx_source_files"].is_array())
			{
				auto header_files = cxx["cxx_source_files"].as_array();

				for (size_t i = 0; i < header_files->size(); ++i)
				{
					source_files_array.push_back(header_files[i].as_string()->value_or(std::filesystem::current_path().string() + "*.cxx"));
				}
			}

			std::vector<std::string> include_directories_array;

			if (cxx["cxx_include_directories"].is_array())
			{
				auto header_files = cxx["cxx_include_directories"].as_array();

				for (size_t i = 0; i < header_files->size(); ++i)
				{
					include_directories_array.push_back(header_files[i].as_string()->value_or(std::filesystem::current_path().string()));
				}
			}

			std::vector<std::string> compiler_flags_array;

			if (cxx["cxx_compiler_flags"].is_array())
			{
				auto header_files = cxx["cxx_compiler_flags"].as_array();

				for (size_t i = 0; i < header_files->size(); ++i)
				{
					compiler_flags_array.push_back(header_files[i].as_string()->value_or(std::filesystem::current_path().string()));
				}
			}

			std::vector<std::string> linker_flags_array;

			if (cxx["cxx_linker_flags"].is_array())
			{
				auto header_files = cxx["cxx_linker_flags"].as_array();

				for (size_t i = 0; i < header_files->size(); ++i)
				{
					linker_flags_array.push_back(header_files[i].as_string()->value_or(std::filesystem::current_path().string()));
				}
			}

			// TODO: build the target

#ifdef _WIN32
			std::string command = cxx["cxx_compiler"].value_or("g++.exe");
#else
			std::string command = cxx["cxx_compiler"].value_or("g++");
#endif

			for (const auto& source_file : source_files_array)
			{
				command += " " + source_file;
			}

			for (const auto& include_directory : include_directories_array)
			{
				command += " -I" + include_directory;
			}

			for (const auto& compiler_flag : compiler_flags_array)
			{
				command += " " + compiler_flag;
			}

			command += "-Wl,";

			for (const auto& linker_flag : linker_flags_array)
			{
				command += "," + linker_flag;
			}

			command += " -o " + output_path.string();

			std::cout << "btb: command: " << command << "\n";
			std::cout << "btb: output path: " << output_path << "\n";

			std::system(command.c_str());
		}

		return true;
	}
	catch (const toml::parse_error& err)
	{
		std::cerr << "btb: error:" << err << "\n";
		return false;
	}

	return false;
}
