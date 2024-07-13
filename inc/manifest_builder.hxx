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
    bool buildJson(int arg_sz, const char * arg_val);

};
