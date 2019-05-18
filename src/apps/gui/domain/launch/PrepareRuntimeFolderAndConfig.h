#pragma once

#include <domain/launch/LoadMod.h>

struct PrepareRuntimeFolderAndConfig {};

class PrepareRuntimeForlderAndConfig final : public LoadMod {
 public:
  explicit PrepareRuntimeForlderAndConfig(PrepareRuntimeFolderAndConfig const& param);

  explicit PrepareRuntimeForlderAndConfig(
    std::shared_ptr<PrepareRuntimeFolderAndConfig> param);

 private:
  void run() noexcept override;
  
  void load_and_parse_config();
  void create_runtime_folders();
  void dump_parsed_config_to_runtime_config_folder();

  std::shared_ptr<PrepareRuntimeFolderAndConfig> param_;

};