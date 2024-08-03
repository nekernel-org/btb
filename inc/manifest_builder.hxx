#pragma once

class ManifestBuilder;

/// @brief JSON builder
class ManifestBuilder final
{
public:
	explicit ManifestBuilder() = default;
	~ManifestBuilder()		   = default;

	ManifestBuilder& operator=(const ManifestBuilder&) = default;
	ManifestBuilder(const ManifestBuilder&)			   = default;

public:
	/// @brief Builds a JSON target.
	/// @param arg_sz filename size
	/// @param arg_val filename path.
	/// @retval true succeeded.
	/// @retval false failed.
	bool buildJson(int arg_sz, const char* arg_val);
};
