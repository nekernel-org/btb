// ============================================================= //
// btb
// Copyright ZKA Technologies.
// ============================================================= //

#include <Macros.hxx>
#include <JSONManifestBuilder.hxx>
#include <cstdio>
#include <cstddef>
#include <string>
#include <iostream>
#include <thread>

static int	cJobIndex = 0;
static bool cFailed	  = false;

int main(int argc, char** argv)
{
	cJobIndex = argc - 1;

	for (size_t index = 1; index < argc; ++index)
	{
		std::string index_path = argv[index];

		if (index_path == "/Ver" ||
			index_path == "/Version")
		{
			std::cout << "Usage: btb <file>\n";
			std::cout << "Check for issues at: www.el-mahrouss-logic.com/btb/issues\n";

			std::cout << "Brought to you by Amlal El Mahrouss.\n";
			std::cout << "© ZKA Technologies, all rights reserved.\n";

			return 0;
		}
		else if (index_path == "/?" ||
				 index_path == "/Help")
		{
			std::cout << "btb: Build a JSON file: btb <json_path>.json\n";
			std::cout << "btb: Build a TOML file: btb <toml_path>.toml\n";

			return 0;
		}

		std::thread job_build_thread([](std::string index_path) -> void {
			IManifestBuilder* builder = nullptr;

			const auto cJsonExt = ".json";

			if (index_path.ends_with(cJsonExt))
			{
				builder = new JSONManifestBuilder();
			}
			else
			{
				cFailed = true;
				return;
			}

			std::cout << "btb: building: " << index_path << std::endl;

			if (builder && !builder->Build(index_path.size(), index_path.c_str()))
			{
				cFailed = true;
			}
			else if (!builder)
			{
				cFailed = true;
			}

			delete builder;

			--cJobIndex;
		},
									 index_path);

		job_build_thread.detach();
	}

	// wait for completion of all jobs.
	while (cJobIndex)
	{
		if (cFailed)
		{
			std::cout << "btb: build failed: " << errno << "." << std::endl;
			return EXIT_FAILURE;
		}
	}

	return cFailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
