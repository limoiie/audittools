#pragma once

#include <vector>
#include <string>
#include <memory>

#include <common/util_traits.h>
#include <base/model/ItemType.h>

using namespace std;

namespace table
{
  struct Label {
    std::string key;
    std::string name;

    Label() = default;

    Label(std::string key, std::string name)
      : key(std::move(key))
      , name(std::move(name)) {
    }
  };

  inline
    ostream& operator<<(ostream& lhs, Label const& rhs) {
    lhs << rhs.key << ": " << rhs.name;
    return lhs;
  }

  using item_t = std::shared_ptr<ItemBase>;
  using item_const_t = std::shared_ptr<const ItemBase>;
  using row_const_t = std::vector<item_const_t>;
  using table_t = std::vector<row_const_t>;

  struct TableInterface {
    virtual ~TableInterface() = default;

    virtual Label const& label() const = 0;
    virtual std::vector<Label> const& field_labels() const = 0;

    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    // virtual row_const_t row(size_t r) = 0;
    virtual row_const_t row(size_t r) const = 0;

    // virtual std::vector<row_const_t> row(size_t s, size_t e) = 0;
    virtual std::vector<row_const_t> row(size_t s, size_t e) const = 0;

    // virtual item_const_t item(size_t r, size_t c) = 0;
    virtual item_const_t item(size_t r, size_t c) const = 0;

  };
  
  // abstract table 
  template <typename DataType>
  class Table : public TableInterface {
  public:
    Label const& label() const override {
      return DataType::label();
    }

    std::vector<Label> const& field_labels() const override {
      return DataType::field_labels();
    }

    size_t cols() const override {
      return field_labels().size();
    }

    virtual void append(DataType const& entry) = 0;
    virtual void append(DataType && entry) = 0;

    virtual void append_list(std::vector<DataType> const& entry) = 0;
    virtual void append_list(std::vector<DataType>&& entry) = 0;

    virtual void clear() = 0;

  };


#pragma region table-define-helper

#define DATA_TO_ROW make_row

#define DEF_ROWLIZE_FUNC(...) \
  table::row_const_t DATA_TO_ROW() const { \
    table::row_const_t res; \
    cast_append(res, ##__VA_ARGS__); \
    return res; \
  }

#define DEF_LABEL_FUNC(LABEL) \
  static table::Label const& label() { \
    static auto v = LABEL; \
    return v; \
  }

#define DEF_FIELD_LABELS_FUNC(...) \
  static std::vector<table::Label> const& field_labels() { \
    static std::vector<table::Label> v = { \
      __VA_ARGS__ \
    }; \
    return v; \
  }

#define DEF_TABLE_STUFF(LABEL, ...) \
  DEF_ROWLIZE_FUNC(CHOOSE_JUMP1(__VA_ARGS__)) \
  DEF_LABEL_FUNC(LABEL) \
  DEF_FIELD_LABELS_FUNC(CHOOSE_JUMP1_FROM_SECOND(__VA_ARGS__))

#pragma endregion


  template <typename DataType>
  class InMemTable final : public Table<DataType> {
    using p_data_t = std::shared_ptr<DataType>;
  public:
    size_t rows() const override {
      return table_.size();
    }
    //
    // row_const_t row(size_t const r) override {
    //   if (r < table_.size())
    //     return table_[r].DATA_TO_ROW();
    //   return {};
    // }

    row_const_t row(size_t const r) const override {
      if (r < table_.size())
        return table_[r].DATA_TO_ROW();
      return {};
    }

    std::vector<row_const_t> row(size_t const s, size_t const e) const override {
      if (s < e && e <= table_.size()) {
        std::vector<row_const_t> row_list;
        for (auto i = s; i < e; ++i)
          row_list.emplace_back(std::move(row(i)));
        return std::move(row_list);
      }
      return {};
    }

    // item_const_t item(size_t const r, size_t const c) override {
    //   return row(r)[c];
    // }

    item_const_t item(size_t const r, size_t const c) const override {
      return row(r)[c];
    }

    void append(p_data_t const& entry) override {
      table_.push_back(entry);
    }

    void append(p_data_t&& entry) override {
      table_.push_back(std::move(entry));
    }

    void append_list(std::vector<p_data_t> const& entries) override {
      for (auto const& entry : entries) {
        table_.emplace_back(entry);
      }
    }

    void append_list(std::vector<p_data_t>&& entries) override {
      for (auto &&entry : entries) {
        table_.emplace_back(entry);
      }
    }

    void clear() override {
      table_.clear();
    }

  private:
    std::vector<p_data_t> table_;

  };

}
