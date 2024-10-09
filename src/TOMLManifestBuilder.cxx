// ============================================================= //
//  btb
// Copyright ZKA Technologies.
// ============================================================= //

#include <TOMLManifestBuilder.hxx>
#include <toml.hxx>
#include <iostream>

/// @brief Builds a TOML target.
/// @param arg_sz filename size
/// @param arg_val filename path.
/// @retval true succeeded.
/// @retval false failed.
bool TOMLManifestBuilder::Build(int arg_sz, const char* arg_val)
{
    toml::table tbl;
    
    try
    {
        tbl = toml::parse_file(arg_val);
        std::cout << tbl << "\n";
    
        return true;
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "btb: error:" << err << "\n";
        return false;
    }

    return false;
}
