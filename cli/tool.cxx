#include <cstdio>
#include <manifest_builder.hxx>
#include <cstddef>
#include <string>
#include <iostream>
#include <thread>

int cJobIndex = 0;
bool cFailed = false;

int main(int argc, char** argv)
{
	cJobIndex = argc - 1;

	for (size_t index = 1; index < argc; ++index)
	{
		std::string index_json = argv[index];

		if (index_json == "/Ver" ||
			index_json == "/Version" ||
            index_json == "/?" ||
			index_json == "/Help")
		{
			std::cout << "btb: 🚀 Basic Tool for Building.\n";
			std::cout << "btb: Brought to you by Amlal El Mahrouss.\n";
			std::cout << "btb: © ZKA Technologies, all rights reserved.\n";

            std::cout << "btb: 🆘 run file: btb <json_path>.json\n";

			return 0;
		}

		std::thread job([](std::string index_json) -> void {
			std::cout << "btb: " << index_json << std::endl;

			ManifestBuilder builder;

			if (!builder.buildJson(index_json.size(), index_json.c_str()))
			{
				std::string format = "btb ";
				format += index_json;

				perror(format.c_str());

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
	}

	return cFailed ? 1 : 0;
}
