#include <Macros.hxx>
#include <JSONManifestBuilder.hxx>
#include <cstdio>
#include <cstddef>
#include <string>
#include <iostream>
#include <thread>

int	 cJobIndex = 0;
bool cFailed   = false;

static IManifestBuilder* cBuilder = new JSONManifestBuilder();

int main(int argc, char** argv)
{
    LIKELY(cBuilder == nullptr);
	cJobIndex = argc - 1;

	for (size_t index = 1; index < argc; ++index)
	{
		std::string index_json = argv[index];

		if (index_json == "/Ver" ||
			index_json == "/Version")
		{
			std::cout << "Usage: btb <file>\n";
			std::cout << "Check for issues at: www.el-mahrouss-logic.com/btb/issues\n";

			std::cout << "Brought to you by Amlal El Mahrouss.\n";
			std::cout << "© ZKA Technologies, all rights reserved.\n";

			return 0;
		}
		else if (index_json == "/?" ||
				 index_json == "/Help")
		{
			std::cout << "btb: Build a JSON file: btb <json_path>.json\n";
			std::cout << "btb: Build a TOML file: btb <toml_path>.toml\n";

			return 0;
		}

		std::thread job([](std::string index_json) -> void {
			std::cout << "btb: Building " << index_json << std::endl;

			if (!cBuilder->Build(index_json.size(), index_json.c_str()))
			{
				std::string format = "btb ";
				format += index_json;

				cFailed = true;
			}

			--cJobIndex;
		},
						index_json);

		job.detach();
	}

	// wait for completion of all jobs.
	while (cJobIndex)
	{
	    BTB_UNUSED(0);
	}

	delete cBuilder;

	return cFailed ? 1 : 0;
}
