#ifndef CORE_COMMON_RANDOM_H
#define CORE_COMMON_RANDOM_H

#include <string>

#include <boost/filesystem/path.hpp>

std::string 
random_filename(unsigned const rand_len,
                std::string const& prefix = "",
                std::string const& subfix = "");

boost::filesystem::path 
random_unique_file(unsigned rand_len,
                   boost::filesystem::path const& folder,
                   std::string const& prefix = "", 
                   std::string const& subfix = "");

#endif  // CORE_COMMON_RANDOM_H