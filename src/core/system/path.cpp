#include <system/path.h>

#include <ShlObj.h>
#include <Windows.h>

#include <boost/filesystem/path.hpp>

namespace path {

Result<boost::filesystem::path, bool> get_home_dir() {
  WCHAR home_path[MAX_PATH + 2] = {0};
  auto const len = GetEnvironmentVariableW(L"USERPROFILE", home_path, MAX_PATH);
  if (len <= 0 || len > MAX_PATH)
    return make_result(boost::filesystem::path(), true);
  return make_result(boost::filesystem::path(home_path), false);
}

Result<boost::filesystem::path, bool> get_exe_dir() {
  WCHAR exe_path[MAX_PATH + 2] = {0};
  auto const len = ::GetModuleFileNameW(nullptr, exe_path, MAX_PATH + 1);
  if (len <= 0 || len > MAX_PATH)
    return make_result(boost::filesystem::path(), true);
  return make_result(boost::filesystem::path(exe_path).parent_path(), false);
}

Result<boost::filesystem::path, bool> get_windows_dir() {
  WCHAR win_dir[MAX_PATH + 2] = {0};
  auto const len = ::GetWindowsDirectoryW(win_dir, MAX_PATH + 1);
  if (len <= 0 || len > MAX_PATH)
    return make_result(boost::filesystem::path(), true);
  return make_result(boost::filesystem::path(win_dir), false);
}

Result<boost::filesystem::path, bool> get_system_dir() {
  WCHAR sys_path[MAX_PATH + 2] = {0};
  auto const len = ::GetSystemDirectoryW(sys_path, MAX_PATH + 1);
  if (len <= 0 || len > MAX_PATH)
    return make_result(boost::filesystem::path(), true);
  return make_result(boost::filesystem::path(sys_path), false);
}

Result<boost::filesystem::path, bool> get_appdata_dir() {
  WCHAR app_data_path[MAX_PATH + 2];
  WCHAR short_app_data_path[MAX_PATH + 2] = {0};
  memset(app_data_path, 0, _MAX_PATH + 2);

  LPITEMIDLIST pidl = nullptr;
  SHGetSpecialFolderLocation(nullptr, CSIDL_LOCAL_APPDATA, &pidl);
  if (pidl && SHGetPathFromIDListW(pidl, short_app_data_path)) {
    GetLongPathNameW(short_app_data_path, app_data_path, _MAX_PATH);
    return make_result(boost::filesystem::path(app_data_path), false);
  }
  return make_result(boost::filesystem::path(), true);
}

Result<boost::filesystem::path, bool> get_temp_dir() {
  WCHAR temp[MAX_PATH + 2] = {0};
  auto const len = ::GetTempPathW(MAX_PATH + 1, temp);

  if (len <= 0 || len > MAX_PATH)
    return make_result(boost::filesystem::path(), true);
  return make_result(boost::filesystem::path(temp), false);
}

}  // namespace path
