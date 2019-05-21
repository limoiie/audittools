#ifndef DOMAIN_LAUNCH_LOADMODPREPAREENV_H
#define DOMAIN_LAUNCH_LOADMODPREPAREENV_H

#include <domain/launch/LoadMod.h>

struct PrepareEnvParam {

};

class LoadModPrepareEnv final : public LoadMod {
public:
  explicit LoadModPrepareEnv(PrepareEnvParam const& param);
  explicit LoadModPrepareEnv(std::shared_ptr<PrepareEnvParam> param);

private:
  void run_imp() override;
  void create_runtime_folders();

  std::shared_ptr<PrepareEnvParam> param_;

};

#endif  // DOMAIN_LAUNCH_LOADMODPREPAREENV_H