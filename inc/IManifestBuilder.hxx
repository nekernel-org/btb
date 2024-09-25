// ============================================================= //
//  btb
// Copyright ZKA Technologies.
// ============================================================= //

#pragma once

/// @brief Builder interface class
class IManifestBuilder
{
public:
	explicit IManifestBuilder() = default;
	virtual ~IManifestBuilder() = default;

	IManifestBuilder& operator=(const IManifestBuilder&) = default;
	IManifestBuilder(const IManifestBuilder&)			 = default;

	/// @brief Builds a target.
	/// @param arg_sz filename size
	/// @param arg_val filename path.
	/// @retval true succeeded.
	/// @retval false failed.
	virtual bool Build(int arg_sz, const char* arg_val) = 0;
};
