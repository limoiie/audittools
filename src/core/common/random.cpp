#include <common/random.h>
#include <boost/filesystem/operations.hpp>

std::string random_filename(unsigned const rand_len,
                            std::string const& prefix,
                            std::string const& subfix) {
  std::string chars(
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "1234567890"
  );

  auto const chars_cnt = chars.size();

  std::string filename(rand_len, '\0');
  for (unsigned i = 0; i < rand_len; ++i)
    filename[i] = chars[rand() % chars_cnt];
  return std::string(prefix).append(filename).append(subfix);
}

boost::filesystem::path 
random_unique_file(unsigned const rand_len, 
                   boost::filesystem::path const& folder, 
                   std::string const& prefix, 
                   std::string const& subfix) {
  while (true) {
    auto const filename = random_filename(rand_len, prefix, subfix);
    auto filepath = boost::filesystem::path(folder).append(filename);
    if (!exists(filepath))
      return filepath;
  }
}