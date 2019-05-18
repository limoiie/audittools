#pragma once

#include <common/Result.hpp>
#include <string>

namespace str {

enum ansi_encoding_e { ACP, UTF8, UTF7, GBK };

Result<std::wstring, bool> ansi_to_unicode(std::string const& ansi_string,
                                           ansi_encoding_e encoding);

Result<std::string, bool> unicode_to_ansi(std::wstring const& unicode_string,
                                          ansi_encoding_e encoding);

bool ansi_to_unicode(std::string const& ansi_string, ansi_encoding_e encoding,
                     std::wstring& unicode_string);

bool unicode_to_ansi(std::wstring const& unicode_string,
                     ansi_encoding_e encoding, std::string& ansi_string);

}  // namespace str