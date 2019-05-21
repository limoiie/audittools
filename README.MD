# AuditTools

## Dependency

- googletest
- rxcpp
- cereal
- spdlog
- boost

## TODO

- consider replace ExternalProject with git submodule
- check if rxcpp works well
- add spdlog, persist-layer

## Note

### boost

version 1.70.0

### everything

consider using everything to index filesystem

## Develop Notes

### Develop Mind Flow

LoadMod --> PrepareRuntimeFolder -> Raw/AppConfig -> Path/Folder Operation -> boost
        |            |                            -> Persist -> cereal
        |            +-> **CheckInteger** & RuntimeConfig & PrepareEnv
        |
        +-> InitialLog

### Load Chain

- launch:
  - DumpHandler: -> todo: CheckInteger -> RuntimeConfig -> PrepareEnv -> InitLog

- shutdown:
  - todo: ClearTempFolder -> todo: ClearEnv

### Module Dependency

Basic dependency chain would be like:

>> test -> apps -> libs -> core -.-> ext

The `-.->' means not all the super layers would totally dependent on ext. The dependency on ext should be as less as possible.

Up to now, the dependency of ext list below:

>> test -> apps -> libs -> core   -> ext/boost
>> test                           -> ext/googletest
>> apps/gui                       -> ext/rxcpp
>> core/common/log                -> ext/spdlog
>> core/common/serialization      -> ext/cereal

## Todo

- model + sqlite
- little-tools
- filecheck
  - 7z: list + uncompress
  - everything: query + index
- shutdown::ClearEnv
- shutdown::ClearTempFolder
- launch::CheckInteger