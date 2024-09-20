#pragma once

#include <IManifestBuilder.hxx>

/// @brief JSON builder
class JSONManifestBuilder final : public IManifestBuilder
{
public:
	explicit JSONManifestBuilder() = default;
	virtual ~JSONManifestBuilder() override = default;

	JSONManifestBuilder& operator=(const JSONManifestBuilder&) = default;
	JSONManifestBuilder(const JSONManifestBuilder&)			   = default;

public:
	/// @brief Builds a JSON target.
	/// @param arg_sz filename size
	/// @param arg_val filename path.
	/// @retval true succeeded.
	/// @retval false failed.
	virtual bool Build(int arg_sz, const char* arg_val) override;
};
