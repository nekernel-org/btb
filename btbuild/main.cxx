#include <manifest_builder.hxx>
#include <cstddef>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    ManifestBuilder builder;

    for (size_t index = 1; index < argc; ++index)
    {
        std::string index_json = argv[index];

        if (index_json == "-v")
        {
            std::cout << "btb: version 1.00\n";
            continue;
        }

        builder.buildJson(index_json.size(), index_json.c_str());
    }

    return 0;
}
