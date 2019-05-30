#ifndef BASE_DATAMODEL_H
#define BASE_DATAMODEL_H

#include <string>
#include <vector>
#include <memory>

namespace model
{
  struct DataLabel {
    std::string key;
    std::string name;
  };

  enum col_type {
    BOOL,
    INT,
    LONG,
    LONG_LONG,
    FLOAT,
    DOUBLE,
    TEXT,
    TIME_STAMP
  };

template<typename T>
struct DataCol {
};

  struct ColTag {
    virtual void test() {}
  };

  struct DataCol<void> {
    void *p_val;
    std::string to_string() const;
  };

  struct DataModel {
    DataLabel label;

    unsigned rows_num() const;
    unsigned cols_num() const;

    std::vector<DataLabel> const& col_labels() const;
  };
}

namespace data_mod
{
  template <typename DataType>
  struct DataModInterface {
    virtual ~DataModInterface() = default;
    virtual std::string const& data_mod_key() const = 0;
    virtual std::wstring const&  data_mod_name() const = 0;
    virtual std::vector<std::string> const& field_keys() const = 0;
    virtual std::vector<std::wstring> const& field_names() const = 0;
    virtual int rowCount() const = 0;
    virtual int columnCount() const = 0;
    virtual void append_data(DataType*) = 0;
    virtual void append_data(std::shared_ptr<DataType> const&) = 0;
    virtual void clear_all() = 0;
    virtual bool is_out_of_rule(std::shared_ptr<DataType> const&) = 0;
    virtual std::wstring out_of_rule_info(std::shared_ptr<DataType> const&) = 0;
    virtual bool is_out_of_rule(int row) = 0;
    virtual std::wstring out_of_rule_info(int row) = 0;
    virtual std::shared_ptr<DataType> item(int row) const = 0;
  };

  auto const kTimeTemplate = "yyyy-MM-dd hh:mm:ss";

}

#endif  // BASE_DATAMODEL_H