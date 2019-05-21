#ifndef DOMAIN_LAUNCH_LOADMODREGISTERDUMP_H
#define DOMAIN_LAUNCH_LOADMODREGISTERDUMP_H

#include <domain/launch/LoadMod.h>
#include <boost/filesystem/path.hpp>

struct RegisterDumpParam {
  boost::filesystem::path dump_folder;
  std::string dump_filename;

  RegisterDumpParam(boost::filesystem::path dump_folder, 
                    std::string dump_filename)
    : dump_folder(std::move(dump_folder))
    , dump_filename(std::move(dump_filename)) {
  }
};

class LoadModRegisterDump final : public LoadMod {
public:
  explicit LoadModRegisterDump(RegisterDumpParam const& param);
  explicit LoadModRegisterDump(std::shared_ptr<RegisterDumpParam> param);

private:
  void run_imp() override;
  void register_dump_catcher();

  std::shared_ptr<RegisterDumpParam> param_;

};

#endif // DOMAIN_LAUNCH_LOADMODREGISTERDUMP_H