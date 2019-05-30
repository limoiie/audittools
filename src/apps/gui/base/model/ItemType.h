#pragma once

#include <string>

// define a new ITEM, you need do follow steps:
// 1. ItemType.h add ITEM_NEW macro in enum item_e;
// 2. ItemType.h DEF_ITEM(ItemNew, new_t, ITEM_NEW)
// 3. xxx_converter.h DEF_CONVERT(xxxTag, OutType, ItemNew)
// 4. ItemType.h add case for DEF_CONVERT_DYNAMIC()

namespace detail
{
  struct ItemTag {};

  template <typename T>
  struct is_item {
    static constexpr bool value = std::is_same<typename T::type, ItemTag>::value;
  };

  template<typename T>
  constexpr bool is_item_v = is_item<T>::value;

}

enum item_e {
  ITEM_INT,
  ITEM_UINT,
  ITEM_LONG,
  ITEM_ULONG,
  ITEM_LONGLONG,
  ITEM_ULONGLONG,
  ITEM_FLOAT,
  ITEM_DOUBLE,
  ITEM_LONGDOUBLE,
  ITEM_STRING,
  ITEM_BYTES,
  ITEM_TIMESTAMP,
  ITEM_DURATION
};

struct ItemBase {
  typedef detail::ItemTag type;
  const item_e real_type;

  explicit ItemBase(item_e const t)
    : real_type(t) {
  }
  virtual ~ItemBase() = default;
};

#define DEF_ITEM(CLS_NAME, VAL_TYPE, CLS_ENUM)  \
  struct CLS_NAME final : ItemBase {  \
    CLS_NAME() : ItemBase(CLS_ENUM) {} \
    explicit CLS_NAME(VAL_TYPE const& val) /* NOLINT(modernize-pass-by-value) */ \
      : ItemBase(CLS_ENUM)  \
      , val(val) {  \
    }  \
  \
    VAL_TYPE val {};  \
  };


DEF_ITEM(ItemInt, int, ITEM_INT)
DEF_ITEM(ItemUInt, unsigned int, ITEM_UINT)
DEF_ITEM(ItemLong, long, ITEM_LONG)
DEF_ITEM(ItemULong, unsigned long, ITEM_ULONG)
DEF_ITEM(ItemLongLong, long long, ITEM_LONGLONG)
DEF_ITEM(ItemULongLong, unsigned long long, ITEM_ULONGLONG)
DEF_ITEM(ItemFloat, float, ITEM_FLOAT)
DEF_ITEM(ItemDouble, double, ITEM_DOUBLE)
DEF_ITEM(ItemLongDouble, long double, ITEM_LONGDOUBLE)
DEF_ITEM(ItemString, std::string, ITEM_STRING)
DEF_ITEM(ItemBytes, size_t, ITEM_BYTES)
DEF_ITEM(ItemTimeStamp, size_t, ITEM_TIMESTAMP)
DEF_ITEM(ItemDuration, size_t, ITEM_DURATION)


/**
 * \brief Define %class ConvertItem<TAG, OUT, IN>
 * \param C Tag identities version, e.t. Gui, Xml, Sql. Different version
 * will have special implement for the same pair <Out, Int>.
 * \param D Out type
 * \param I  In type which should be derived from %class ItemBase
 */
  template <typename C, typename O, typename I>
struct ConvertItem {
  O operator()(I const&) {
    static_assert(detail::is_item_v<I>, "In of ConvertItem() should derive from ItemBase!");
    return {};
  }
};

/**
 * \brief Define parts of %class ConvertItem<TAG, OUT, IN>
 * \param TAG Tag identities version, e.t. Gui, Xml, Sql. Different version
 * will have special implement for the same pair <Out, Int>.
 * \param OUT Out type
 * \param IN  In type which should be derived from %class ItemBase
 */
#define DEF_CONVERT(TAG, OUT, IN)  \
static_assert(detail::is_item_v<IN>, "IN of ConvertItem() should derive from ItemBase! Get: "#IN);  \
template <>  \
struct ConvertItem<TAG, OUT, IN> final { \
  std::string operator()(IN const& in) {

#define END_DEF \
  }  \
  };


#define _CONVERT_ITEM(TAG, OUT, IN)  \
  ConvertItem<TAG, OUT, IN>()(  \
      std::dynamic_pointer_cast<const IN>(item).operator*())

template <typename Tag, typename Out>
struct convert_dynamic {};

#define DEF_CONVERT_DYNAMIC(TAG, OUT)  \
  template <>  \
  struct convert_dynamic<TAG, OUT> {  \
    OUT operator()(std::shared_ptr<const ItemBase> const& item) {  \
      switch (item->real_type) {  \
        case ITEM_INT:         return _CONVERT_ITEM(TAG, OUT, ItemInt);  \
        case ITEM_UINT:        return _CONVERT_ITEM(TAG, OUT, ItemUInt);  \
        case ITEM_LONG:        return _CONVERT_ITEM(TAG, OUT, ItemLong);  \
        case ITEM_ULONG:       return _CONVERT_ITEM(TAG, OUT, ItemULong);  \
        case ITEM_LONGLONG:    return _CONVERT_ITEM(TAG, OUT, ItemLongLong);  \
        case ITEM_ULONGLONG:   return _CONVERT_ITEM(TAG, OUT, ItemULongLong);  \
        case ITEM_FLOAT:       return _CONVERT_ITEM(TAG, OUT, ItemFloat);  \
        case ITEM_DOUBLE:      return _CONVERT_ITEM(TAG, OUT, ItemDouble);  \
        case ITEM_LONGDOUBLE:  return _CONVERT_ITEM(TAG, OUT, ItemLongDouble);  \
        case ITEM_STRING:      return _CONVERT_ITEM(TAG, OUT, ItemString);  \
        case ITEM_BYTES:       return _CONVERT_ITEM(TAG, OUT, ItemBytes);  \
        case ITEM_TIMESTAMP:   return _CONVERT_ITEM(TAG, OUT, ItemTimeStamp);  \
        case ITEM_DURATION:    return _CONVERT_ITEM(TAG, OUT, ItemDuration);  \
        default:  \
          throw std::invalid_argument("Wrong real_type of item in convert_dynamic() !");  \
      }  \
    } \
  };
