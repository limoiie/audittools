#include <common/str.h>

#include <Windows.h>

#define CP_GB2312 936
#define CP_GB18030 54936

namespace str {

UINT codepage(ansi_encoding_e const encoding) {
  switch (encoding) {
    case ACP:
      return CP_ACP;
    case UTF8:
      return CP_UTF8;
    case UTF7:
      return CP_UTF7;
    case GBK:
      return CP_GB2312;
  }
  return CP_ACP;
}

Result<std::wstring, bool> ansi_to_unicode(std::string const& ansi_string,
                                           ansi_encoding_e const encoding) {
  auto result = make_result(std::wstring(), false);
  result.error = !ansi_to_unicode(ansi_string, encoding, result.value);
  return result;
}

Result<std::string, bool> unicode_to_ansi(std::wstring const& unicode_string,
                                          ansi_encoding_e const encoding) {
  auto result = make_result(std::string(), false);
  result.error = !unicode_to_ansi(unicode_string, encoding, result.value);
  return result;
}

bool ansi_to_unicode(std::string const& ansi_string,
                     ansi_encoding_e const encoding,
                     std::wstring& unicode_string) {
  // get windows code page and make sure that is valid
  auto const code_page = codepage(encoding);
  if (FALSE == IsValidCodePage(code_page)) return false;

  // check how much wchars we need to store the result
  auto dw_min_size = MultiByteToWideChar(code_page, 0, ansi_string.c_str(),
                                         ansi_string.size(), nullptr, 0);
  if (0 == dw_min_size) return false;

  // allocate wstring and convert
  unicode_string.assign(dw_min_size, '\0');

  dw_min_size = MultiByteToWideChar(
      code_page, 0, ansi_string.c_str(), ansi_string.size(),
      const_cast<LPWCH>(unicode_string.c_str()), dw_min_size);

  return 0 != dw_min_size;
}

bool unicode_to_ansi(std::wstring const& unicode_string,
                     ansi_encoding_e const encoding, std::string& ansi_string) {
  // get windows code page and make sure that is valid
  auto const code_page = codepage(encoding);
  if (FALSE == IsValidCodePage(code_page)) return false;

  // check how much chars we need to store the result
  auto dw_min_size =
      WideCharToMultiByte(code_page, 0, unicode_string.c_str(),
                          unicode_string.size(), nullptr, 0, nullptr, nullptr);
  if (0 == dw_min_size) return false;

  // allocate wstring and convert
  ansi_string.assign(dw_min_size, '\0');

  dw_min_size = WideCharToMultiByte(
      code_page, 0, unicode_string.c_str(), unicode_string.size(),
      const_cast<LPCH>(ansi_string.c_str()), dw_min_size, nullptr, nullptr);

  return 0 != dw_min_size;
}
}  // namespace str
