#include <system/register_dump.h>

#include <string>

#include <Windows.h>
#include <DbgHelp.h>
#include <ShlObj.h>

#include <common/path.h>
#include <common/random.h>

static
boost::filesystem::path kDumpFolder;

static
std::string kDumpPrefix;

static
long __stdcall pretend_handle(_EXCEPTION_POINTERS* exception) {
  MINIDUMP_EXCEPTION_INFORMATION exp_param;

  auto const res = path::get_temp_dir();
  if (res.has_error()) return EXCEPTION_EXECUTE_HANDLER;

  auto const h_dump_file = CreateFileW(
    random_unique_file(10, res.value, kDumpPrefix, ".dmp").wstring().c_str(),
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_WRITE | FILE_SHARE_READ,
    nullptr, CREATE_ALWAYS, 0, nullptr
  );

  exp_param.ThreadId = GetCurrentThreadId();
  exp_param.ExceptionPointers = exception;
  exp_param.ClientPointers = TRUE;

  auto const mini_dump_with_data_segs = static_cast<MINIDUMP_TYPE>(MiniDumpNormal
    | MiniDumpWithHandleData
    | MiniDumpWithUnloadedModules
    | MiniDumpWithIndirectlyReferencedMemory
    | MiniDumpScanMemory
    | MiniDumpWithProcessThreadData
    | MiniDumpWithThreadInfo);

  MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
    h_dump_file, mini_dump_with_data_segs, &exp_param, nullptr, nullptr);
  return EXCEPTION_EXECUTE_HANDLER;
}

void register_dump(boost::filesystem::path const& dump_folder, std::string const& prefix) {
  kDumpFolder = dump_folder;
  kDumpPrefix = prefix;
  SetUnhandledExceptionFilter(pretend_handle);
}
