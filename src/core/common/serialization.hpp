#ifndef CORE_COMMON_SERIALIZATION
#define CORE_COMMON_SERIALIZATION

#include <sstream>
#include <string>

#include <boost/filesystem.hpp>

// ReSharper disable once CppUnusedIncludeDirective
#include <cereal/types/memory.hpp>
// ReSharper disable once CppUnusedIncludeDirective
#include <cereal/types/string.hpp>
// ReSharper disable once CppUnusedIncludeDirective
#include <cereal/types/vector.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>

namespace serialize {

namespace json {

template <class Object>
std::string dump(Object const& obj) {
  std::ostringstream ss;
  try {
    cereal::JSONOutputArchive out_archive(ss);
    out_archive(obj);
  } catch (std::exception const& e) {
    throw std::domain_error(e.what());
  }
  return ss.str();
}

template <class Object>
Object load(std::string const& serialization) {
  Object obj{};
  load(serialization, obj);
  return std::move(obj);
}

template <class Object>
void load(std::string const& serialization, Object& obj) {
  std::istringstream ss(serialization);
  try {
    cereal::JSONInputArchive in_archive(ss);
    in_archive(obj);
  } catch (std::runtime_error const&) {
    throw std::runtime_error("Failed to load json file, maybe wrong format");
  } catch (std::domain_error const&) {
    throw std::domain_error("Failed to load json file, maybe no such file");
  }
}

template <class Object>
void dump_file(boost::filesystem::path const& file, Object const& obj) {
  std::ofstream ss(file.wstring());
  try {
    cereal::JSONOutputArchive out_archive(ss);
    out_archive(obj);
  } catch (std::exception& e) {
    throw std::domain_error(e.what());
  }
}

template <class Object>
Object load_file(std::string const& serialization) {
  Object obj{};
  load_json(serialization, obj);
  return std::move(obj);
}

template <class Object>
void load_file(boost::filesystem::path const& file, Object& obj) {
  std::ifstream ss(file.wstring());
  try {
    cereal::JSONInputArchive in_archive(ss);
    in_archive(obj);
  } catch (std::runtime_error const&) {
    throw std::runtime_error("Failed to load json file, maybe wrong format");
  } catch (std::domain_error const&) {
    throw std::domain_error("Failed to load json file, maybe no such file");
  }
}

}  // namespace json

}  // namespace serialize

#endif