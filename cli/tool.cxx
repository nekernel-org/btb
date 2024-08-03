#include <cstdio>
#include <manifest_builder.hxx>
#include <cstddef>
#include <string>
#include <iostream>
#include <thread>

int job_index = 0;

int main(int argc, char** argv)
{
	job_index = argc - 1;

	for (size_t index = 1; index < argc; ++index)
	{
		std::string index_json = argv[index];

		if (index_json == "/Ver" ||
			index_json == "/Version" ||
            index_json == "/?" ||
			index_json == "/Help")
		{
			std::cout << "btb: 🚀 Version 1.01.\n";
			std::cout << "btb: Brought to you by Amlal El Mahrouss.\n";
			std::cout << "btb: © ZKA Technologies, all rights reserved.\n";
			
            std::cout << "btb: 🆘 run file: btb <json_path>.json\n";

			return 0;
		}

		std::thread job([](std::string index_json) -> void {
			std::cout << "building: " << index_json << std::endl;

			ManifestBuilder builder;

			if (!builder.buildJson(index_json.size(), index_json.c_str()))
			{
				std::string format = "btb ";
				format += index_json;

				perror(format.c_str());
			}

			--job_index;
		},
						index_json);

		job.detach();
	}

	// wait for completion of all jobs.
	while (job_index)
	{
	}

	return 0;
}
