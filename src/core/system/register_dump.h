#ifndef CORE_SYSTEM_REGISTER_DUMP_H
#define CORE_SYSTEM_REGISTER_DUMP_H

#include <string>
#include <boost/filesystem/path.hpp>

void register_dump(
  boost::filesystem::path const& dump_folder, 
  std::string const& prefix);

#endif  // CORE_SYSTEM_REGISTER_DUMP_H
