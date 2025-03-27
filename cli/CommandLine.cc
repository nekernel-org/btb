
// ============================================================= //
// btb
// Copyright (C) 2024-2025, Amlal El Mahrouss, all rights reserved.
// ============================================================= //

#include <JSONManifestBuilder.h>
#include <Includes.h>

static bool kFailed	  = false;
static bool kDryRun = false;

int main(int argc, char** argv)
{
	if (argc <= 1)
		return 1;

	for (size_t index = 1; index < argc; ++index)
	{
		std::string index_path = argv[index];

		if (index_path == "-v" ||
			index_path == "--version")
		{
			std::cout << "Usage: btb <file>\n";
			std::cout << "Bugs, Issues?, check out: https://github.com/amlel-el-mahrouss/btb/issues\n";

			std::cout << "Brought to you by Amlal El Mahrouss for the NeKernel project.\n";
			std::cout << "© 2024-2025 Amlal El Mahrouss, all rights reserved.\n";

			return EXIT_SUCCESS;
		}
		else if (index_path == "--dry-run")
		{
			kDryRun = true;
			continue;
		}
		else if (index_path == "-h" ||
				 index_path == "--help")
		{
			std::cout << "btb: Build a JSON file: btb <json_path>.json\n";
			return EXIT_SUCCESS;
		}

		std::thread job_build_thread([](std::string index_path) -> void {
			IManifestBuilder* builder = nullptr;

			const auto kJsonExtension = ".json";

			if (index_path.ends_with(kJsonExtension))
			{
				builder = new JSONManifestBuilder();
			}
			else
			{
				std::cout << "btb: error: file '" << index_path << "' does not end with .json!" << std::endl;
				kFailed = true;
				return;
			}

			std::cout << "btb: building: " << index_path << std::endl;

			if (builder && !builder->buildTarget(index_path.size(), index_path.c_str(), kDryRun))
			{
				kFailed = true;
			}
			else if (!builder)
			{
				kFailed = true;
			}

			delete builder;
			builder = nullptr;
		}, index_path);

		job_build_thread.join();
	}

	return kFailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
