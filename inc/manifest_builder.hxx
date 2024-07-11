#pragma once

class ManifestBuilder;

class ManifestBuilder final
{
public:
    explicit ManifestBuilder() = default;
    ~ManifestBuilder() = default;

    ManifestBuilder& operator=(const ManifestBuilder&) = default;
    ManifestBuilder(const ManifestBuilder&) = default;

public:
    int buildJson(int argc, const char * argv[]);

};
