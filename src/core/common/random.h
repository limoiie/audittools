#ifndef CORE_COMMON_RANDOM_H
#define CORE_COMMON_RANDOM_H

#include <string>

std::string random_filename(unsigned const rand_len,
                            std::string const& prefix = "",
                            std::string const& subfix = "") {
  std::string chars(
      "abcdefghijklmnopqrstuvwxyz"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "1234567890");
  auto const chars_cnt = chars.size();

  std::string filename(rand_len, '\0');
  for (unsigned i = 0; i < rand_len; ++i)
    filename[i] = chars[rand() % chars_cnt];
  return std::string(prefix).append(filename).append(subfix);
}

#endif  // CORE_COMMON_RANDOM_H