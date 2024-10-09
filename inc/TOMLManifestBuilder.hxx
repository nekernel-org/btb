// ============================================================= //
// btb
// Copyright ZKA Technologies.
// ============================================================= //

#pragma once

#include <IManifestBuilder.hxx>

/// @brief TOML builder
class TOMLManifestBuilder final : public IManifestBuilder
{
public:
	explicit TOMLManifestBuilder() = default;
	virtual ~TOMLManifestBuilder() override = default;

	TOMLManifestBuilder& operator=(const TOMLManifestBuilder&) = default;
	TOMLManifestBuilder(const TOMLManifestBuilder&)			   = default;

public:
	/// @brief Builds a TOML target.
	/// @param arg_sz filename size
	/// @param arg_val filename path.
	/// @retval true succeeded.
	/// @retval false failed.
	virtual bool Build(int arg_sz, const char* arg_val) override;
};
