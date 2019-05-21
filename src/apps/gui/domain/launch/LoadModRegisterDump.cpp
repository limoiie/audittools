#include <domain/launch/LoadModRegisterDump.h>

#include <system/register_dump.h>
#include <domain/AppConfig.h>

LoadModRegisterDump::
LoadModRegisterDump(RegisterDumpParam const& param)
  : param_(std::make_shared<RegisterDumpParam>(param)) {
}

LoadModRegisterDump::
LoadModRegisterDump(std::shared_ptr<RegisterDumpParam> param)
  : param_(std::move(param)) {
}

void LoadModRegisterDump::run_imp() {
  register_dump_catcher();
}

void LoadModRegisterDump::register_dump_catcher() {
  register_dump(param_->dump_folder, param_->dump_filename);
  log(std::string("Register dump catcher, dump file will looks like: ")
      .append(param_->dump_folder.string()).append(param_->dump_filename));
}