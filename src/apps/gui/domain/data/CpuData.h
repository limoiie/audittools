#pragma once

#include <base/model/table.h>
#include <base/model/ItemType.h>

struct CpuTag {};

struct CpuData {
  ItemString name;
  ItemString type;

  DEF_TABLE_STUFF(table::Label("CpuData", "CpuData"),
                  name, table::Label("CpuName", "CpuName CN"),
                  type, table::Label("CpuType", "CpuType CN")
  )

};