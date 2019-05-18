#pragma once
#include <string>

namespace path {
namespace encode {
enum multi_char_encoding_e {
  UTF8,
  GBK,
};

enum unicode_encoding_e { UNICODE16_BE, UNICODE16_LE };

bool convert_
}  // namespace encode

class Path {
 public:
  Path(std::string const& path, encode::multi_char_encoding_e encode);
  Path(std::wstring const& path, encode::unicode_encoding_e encode);

 private:
  std::wstring path_;
};

}  // namespace path
