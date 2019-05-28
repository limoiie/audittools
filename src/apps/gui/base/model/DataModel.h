#ifndef BASE_DATAMODEL_H
#define BASE_DATAMODEL_H

#include <string>
#include <vector>
#include <memory>
#include <map>
// ReSharper disable once CppUnusedIncludeDirective
#include <cassert>

// ReSharper disable once CppUnusedIncludeDirective
#include <Windows.h>

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

  struct DataCol {
    std::string key;
    void *p_val;

    std::string str();

    int to_int() const;
    long to_long() const;
    long long to_llong() const;
    float to_float() const;
    double to_double() const;
    char const *to_text() const;
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
  class DeductiveData {
  public:
    std::wstring const& deduction() const {
      return deduction_;
    }

    void set_deduction(std::wstring const& deduction) {
      deduction_ = deduction;
    }

  protected:
    std::wstring deduction_;

  };

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

  template <typename DataType>
  std::string const& key_of_data_mod() {
    static std::string default_value = "default_key";
    return default_value;
  }

  template <typename DataType>
  std::wstring const& name_of_data_mod() {
    static std::wstring default_value = L"default_key";
    return default_value;
  }

  template <typename DataType>
  std::vector<std::string> const& field_keys_of_data_mod() {
    static std::vector<std::string> default_value;
    return default_value;
  }

  template <typename DataType>
  std::vector<std::wstring> const& field_names_of_data_mod() {
    static std::vector<std::wstring> default_value;
    return default_value;
  }

  template <typename DataType>
  size_t num_of_fileds() {
    return 0;
  }

  template <typename DataType>
  class DataMod : public DataModInterface<DataType> {
  public:
    DataMod() = default;

    explicit DataMod(std::vector<std::shared_ptr<DataType>> shared_ptrs)
      : datas_(std::move(shared_ptrs)) {
    }

    ~DataMod() override = default;

    std::string const& data_mod_key() const override {
      return key_of_data_mod<DataType>();
    }

    std::wstring const& data_mod_name() const override {
      return name_of_data_mod<DataType>();
    }

    std::vector<std::string> const& field_keys() const override {
      return field_keys_of_data_mod<DataType>();
    }

    std::vector<std::wstring> const& field_names() const override {
      return field_names_of_data_mod<DataType>();
    }

    int rowCount() const override {
      return datas_.size();
    }

    int columnCount() const override {
      return num_of_fileds<DataType>();
    }

    void append_data(DataType* p_data) override {
      datas_.push_back(std::shared_ptr<DataType>(p_data));
    }

    void append_data(std::shared_ptr<DataType> const& p_data) override {
      datas_.push_back(p_data);
    }

    void clear_all() override {
      datas_.clear();
    }

    std::shared_ptr<DataType> item(int const row) const override {
      return datas_[row];
    }

    std::vector<std::shared_ptr<DataType>> const& items() const {
      return datas_;
    }

    bool is_out_of_rule(std::shared_ptr<DataType> const& p_data) override {
      return !p_data->deduction().empty();
    }

    std::wstring out_of_rule_info(std::shared_ptr<DataType> const& p_data) override {
      return p_data->deduction();
    }

    bool is_out_of_rule(int const row) override {
      auto const p_data = item(row);
      return is_out_of_rule(p_data);
    }

    std::wstring out_of_rule_info(int const row) override {
      auto const p_data = item(row);
      return out_of_rule_info(p_data);
    }

  private:
    std::vector<std::shared_ptr<DataType>> datas_;

  };

  template <typename ToFieldDataType>
  struct DataModIterator {
    virtual ~DataModIterator() = default;
    virtual ToFieldDataType data_item(int row, int col) const = 0;
    virtual std::string const& data_mod_key() const = 0;
    virtual std::wstring const&  data_mod_name() const = 0;
    virtual std::vector<std::string> const& field_keys() const = 0;
    virtual std::vector<std::wstring> const& field_names() const = 0;
    virtual bool is_out_of_rule(int row) = 0;
    virtual std::wstring out_of_rule_info(int row) = 0;
    virtual int rowCount() const = 0;
    virtual int columnCount() const = 0;

    virtual std::vector<ToFieldDataType> data_row(int const row) const {
      std::vector<ToFieldDataType> fields;
      for (auto i = 0; i < columnCount(); ++i)
        fields.push_back(data_item(row, i));
      return fields;
    }

    virtual std::map<std::string, ToFieldDataType> data_row_in_map(int const row) const {
      auto & keys = field_keys();
      std::map<std::string, ToFieldDataType> key_field_map;
      for (auto i = 0; i < columnCount(); ++i)
        key_field_map[keys[i]] = data_item(row, i);
      return key_field_map;
    }

  };

  template <typename DataType, typename ToFieldDataType>
  struct DataModTransformer {
    virtual ~DataModTransformer() = default;
    virtual ToFieldDataType data_item(std::shared_ptr<DataType> const& obj, int col) const = 0;
  };

  template <typename T>
  std::vector<T> filter_items(std::vector<T> const&items, std::vector<size_t> const&indexs) {
    std::vector<T> filtered_items;
    for (auto const & idx : indexs)
      filtered_items.push_back(items[idx]);
    return filtered_items;
  }

  template <typename DataType, typename ToFieldDataType>
  class DataModColFilterProxy : public DataModInterface<DataType>,
    public DataModIterator<ToFieldDataType>,
    public DataModTransformer<DataType, ToFieldDataType> {
  public:

    DataModColFilterProxy(std::shared_ptr<DataModTransformer<DataType, ToFieldDataType>> xfmr,
                          const std::shared_ptr<DataModInterface<DataType>>& data_mod,
                          std::vector<size_t> indexes = {})
      : xfmr_(std::move(xfmr)), data_mod_(data_mod), indexes_(std::move(indexes)) {
      if (indexes_.empty()) {
        for (auto i = 0; i < data_mod->columnCount(); ++i)
          indexes_.push_back(i);
      }

      field_keys_ = filter_items(data_mod->field_keys(), indexes_);
      field_names_ = filter_items(data_mod->field_names(), indexes_);
    }

    std::string const& data_mod_key() const override {
      return data_mod_->data_mod_key();
    }

    std::wstring const& data_mod_name() const override {
      return data_mod_->data_mod_name();
    }

    std::vector<std::string> const& field_keys() const override {
      return field_keys_;
    }

    std::vector<std::wstring> const& field_names() const override {
      return field_names_;
    }

    int rowCount() const override {
      return data_mod_->rowCount();
    }

    int columnCount() const override {
      return indexes_.size();
    }

    void append_data(DataType *p_data) override {
      data_mod_->append_data(p_data);
    }

    void append_data(std::shared_ptr<DataType> const& p_data) override {
      data_mod_->append_data(p_data);
    }

    std::shared_ptr<DataType> item(int const row) const override {
      return data_mod_->item(row);
    }

    ToFieldDataType data_item(int const row, int const col) const override {
      auto p_data = item(row);
      return xfmr_->data_item(p_data, indexes_[col]);
    }

    ToFieldDataType data_item(std::shared_ptr<DataType> const& obj, int const col) const override {
      return xfmr_->data_item(obj, indexes_[col]);
    }

    std::vector<ToFieldDataType> data(std::shared_ptr<DataType> const& obj) const {
      std::vector<ToFieldDataType> fields;
      for (auto i = 0; i < columnCount(); ++i) {
        fields.push_back(xfmr_->data_item(obj, i));
      }
      return fields;
    }

    std::map<std::string, ToFieldDataType> data_in_map(std::shared_ptr<DataType> const& obj) const {
      auto & keys = field_keys();
      std::map<std::string, ToFieldDataType> key_field_map;
      for (auto i = 0; i < columnCount(); ++i)
        key_field_map[keys[i]] = data_item(obj, i);
      return key_field_map;
    }

    void clear_all() override {
      data_mod_->clear_all();
    }

    bool is_out_of_rule(std::shared_ptr<DataType> const& p_data) override {
      return data_mod_->is_out_of_rule(p_data);
    }

    std::wstring out_of_rule_info(std::shared_ptr<DataType> const& p_data) override {
      return data_mod_->out_of_rule_info(p_data);
    }

    bool is_out_of_rule(int const row) override {
      return data_mod_->is_out_of_rule(row);
    }

    std::wstring out_of_rule_info(int const row) override {
      return data_mod_->out_of_rule_info(row);
    }

  private:
    std::shared_ptr<DataModTransformer<DataType, ToFieldDataType>> xfmr_;
    std::shared_ptr<DataModInterface<DataType>> data_mod_;
    std::vector<std::string> field_keys_;
    std::vector<std::wstring> field_names_;
    std::vector<size_t> indexes_;

  };

#define IMPL_KEY_OF_DATA_MOD(DataType, Key) \
    template <> \
	inline std::string const& key_of_data_mod<DataType>() { \
		static std::string default_value = Key; \
        return default_value; \
	}

#define IMPL_NAME_OF_DATA_MOD(DataType, Name) \
    template <> \
	inline std::wstring const& name_of_data_mod<DataType>() { \
		static std::wstring default_value = Name; \
        return default_value; \
	}

#define IMPL_NUM_OF_DATA_MOD(DataType) \
    template <> \
	inline size_t num_of_fileds<DataType>() { \
        assert(field_keys_of_data_mod<DataType>().size() == field_names_of_data_mod<DataType>().size()); \
        return field_keys_of_data_mod<DataType>().size(); \
	}

  /**
   * \brief the key will be used in report xml and html (e.t. basic info check), to represent
   * the table for indexing purpose; the name will bu used as the display name of the table
   */
#define IMPL_KEY_NAME_NUM_OF_DATA_MOD(DataType, Key, Name) \
    IMPL_KEY_OF_DATA_MOD(DataType, Key) \
    IMPL_NAME_OF_DATA_MOD(DataType, Name) \
    IMPL_NUM_OF_DATA_MOD(DataType)


#define IMPL_KEYS_OF_DATA_MOD(DataType, ...) \
    template <> \
	inline std::vector<std::string> const& field_keys_of_data_mod<DataType>() { \
        static std::vector<std::string> default_value = __VA_ARGS__; \
        return default_value; \
	}

#define IMPL_NAMES_OF_DATA_MOD(DataType, ...) \
    template <> \
	inline std::vector<std::wstring> const& field_names_of_data_mod<DataType>() { \
        static std::vector<std::wstring> default_value = __VA_ARGS__; \
        return default_value; \
	}

#define IMPL_DATA_MOD_XFMR_HEAD(DataType, ToFieldDataType, GuiOrXml) \
    class DataType##GuiOrXml##Xfmr : public DataModTransformer<DataType, ToFieldDataType> { \
    public: \
	    ToFieldDataType data_item(std::shared_ptr<DataType> const& obj, int col) const override {

#define IMPL_DATA_MOD_XFMR_TAIL \
		} \
	};

  inline std::string to_utf8(std::wstring const& wstr) {
    std::string utf8_string;
    np_limo::str::ConvertWideCharToMultiBytes(utf8_string, wstr.c_str(), wstr.size(), CP_UTF8);
    return utf8_string;
  }

#define TO_UTF8(String) \
    to_utf8(String);

#define TO_QSTR(String) \
    QString::fromStdWString(String);


  template <typename DataType>
  std::vector<size_t> gui_show_indexes() {
    return {};
  }

  template <typename DataType>
  std::vector<size_t> xml_show_indexes() {
    return {};
  }

#define IMPL_GUI_SHOW_INDEXES(DataType, ...) \
    template <> \
	inline std::vector<size_t> gui_show_indexes<DataType>() { \
		return std::vector<size_t>(__VA_ARGS__); \
	}

#define IMPL_XML_SHOW_INDEXES(DataType, ...) \
    template <> \
	inline std::vector<size_t> xml_show_indexes<DataType>() { \
		return std::vector<size_t>(__VA_ARGS__); \
	}

  auto const kTimeTemplate = "yyyy-MM-dd hh:mm:ss";

}

#endif  // BASE_DATAMODEL_H