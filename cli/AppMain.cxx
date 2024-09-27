#include <Macros.hxx>
#include <JSONManifestBuilder.hxx>
#include <TOMLManifestBuilder.hxx>
#include <cstdio>
#include <cstddef>
#include <string>
#include <iostream>
#include <thread>

int	 cJobIndex = 0;
bool cFailed   = false;

static IManifestBuilder* cBuilder = nullptr;

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

		std::thread job([](std::string index_path) -> void {
			if (index_path.ends_with(".json"))
			{
				delete cBuilder;
				cBuilder = nullptr;

				if (!cBuilder)
					cBuilder = new JSONManifestBuilder();
			}
			else if (index_path.ends_with(".toml"))
			{
				delete cBuilder;
				cBuilder = nullptr;

				if (!cBuilder)
					cBuilder = new TOMLManifestBuilder();
			}
			else
			{
				cFailed = true;
				return;
			}

			std::cout << "btb: Building: " << index_path << std::endl;

			if (!cBuilder->Build(index_path.size(), index_path.c_str()))
			{
				cFailed = true;
			}

			--cJobIndex;
		},
						index_path);

		job.detach();
	}

	// wait for completion of all jobs.
	while (cJobIndex)
	{
		if (cFailed)
		{
			std::cout << "btb: Build failed." << std::endl;
			return EXIT_FAILURE;
		}
	}

	delete cBuilder;

	return cFailed ? EXIT_FAILURE : EXIT_SUCCESS;
}
