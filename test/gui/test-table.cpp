#include <gtest/gtest.h>

#include <domain/data/CpuData.h>
#include <domain/data/convert/gui_converter.h>

namespace
{
  CpuData create_cpu_data(std::string const& name, std::string const& type) {
    auto cp = CpuData();
    cp.name.val = name;
    cp.type.val = type;
    return cp;
  }

  GTEST_TEST(TestItem, test_data) {
    create_cpu_data("", "");
    auto const lable = CpuData::label();
    auto const fields = CpuData::field_labels();
  }

  GTEST_TEST(TestTable, test_in_mem_table) {
    table::InMemTable<CpuData> t;
    ASSERT_EQ(t.cols(), CpuData::field_labels().size());
   
    t.append(create_cpu_data("", ""));
    ASSERT_EQ(t.rows(), static_cast<size_t>(1));
  }

  GTEST_TEST(TestItem, test_convert) {
    table::InMemTable<CpuData> t;
    t.append(create_cpu_data("Intel", "Core i7"));

    auto r = t.row(0);
    auto const x = convert_dynamic<GuiTag, std::string>()(r[0]);
    ASSERT_EQ(x, std::string("Intel"));

    auto const y = convert_dynamic<GuiTag, std::string>()(r[1]);
    ASSERT_EQ(y, std::string("Core i7"));
  }
}
