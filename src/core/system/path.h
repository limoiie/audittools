#ifndef CORE_COMMON_PATH_H
#define CORE_COMMON_PATH_H

#include <common/Result.hpp>
#include <boost/filesystem/path.hpp>

namespace path {

Result<boost::filesystem::path, bool> get_home_dir();
Result<boost::filesystem::path, bool> get_exe_dir();
Result<boost::filesystem::path, bool> get_windows_dir();
Result<boost::filesystem::path, bool> get_system_dir();
Result<boost::filesystem::path, bool> get_appdata_dir();
Result<boost::filesystem::path, bool> get_temp_dir();

}  // namespace path

#endif  // CORE_COMMON_PATH_H