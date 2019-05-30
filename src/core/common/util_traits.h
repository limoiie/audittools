#pragma once

#include <vector>
#include <memory>

template <typename ...Args>
struct count_args {
};

template <typename T, typename ...Args>
struct count_args<T, Args...> : count_args<Args...> {
  static constexpr unsigned value = count_args<Args...>::real_type + 1;
};

template <>
struct count_args<> {
  static constexpr unsigned value = 0;
};

template <typename T>
struct remove_vector {
  typedef T type;
};

template <typename T>
struct remove_vector<std::vector<T>> {
  typedef T type;
};

template <typename T>
using remove_vector_t = typename remove_vector<T>::type;

template <typename T>
struct remove_shared_ptr {
  typedef T type;
};

template <typename T>
struct remove_shared_ptr<std::shared_ptr<T>> {
  typedef T type;
};

template <typename T>
using remove_shared_ptr_t = typename remove_shared_ptr<T>::type;


template <typename V>
void cast_append(V&) {
}

template <typename V, typename T, typename ...Args>
void cast_append(V& v, T const& t, Args... remain) {
  typedef remove_shared_ptr_t<remove_vector_t<V>> _item_t;
  v.emplace_back(std::static_pointer_cast<const _item_t>(std::make_shared<T>(t)));
  cast_append(v, remain...);
}


#define EXPAND(x) x

#define CONCAT(a, b) a ## b
#define CONCAT2(a, b) CONCAT(a, b)

#define ARG42( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32, A33, A34, A35, A36, A37, A38, A39, A40,  \
	A41, A42, ...) A42

#define COUNT_ARGS(...) EXPAND(ARG42(PH, ## __VA_ARGS__,  \
	40, 39, 38, 37, 36, 35, 34, 33, 32, 31,  \
	30, 29, 28, 27, 26, 25, 24, 23, 22, 21,  \
	20, 19, 18, 17, 16, 15, 14, 13, 12, 11,  \
	10, 9, 8, 7, 6, 5, 4, 3, 2, 1,  \
	0))

#define CHOOSE_JUMP1_2( \
	A1, A2)  \
	A1

#define CHOOSE_JUMP1_4( \
	A1, A2, A3, A4)  \
	A1, A3

#define CHOOSE_JUMP1_6( \
	A1, A2, A3, A4, A5, A6)  \
	A1, A3, A5

#define CHOOSE_JUMP1_8( \
	A1, A2, A3, A4, A5, A6, A7, A8)  \
	A1, A3, A5, A7

#define CHOOSE_JUMP1_10( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10)  \
	A1, A3, A5, A7, A9

#define CHOOSE_JUMP1_12( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12)  \
	A1, A3, A5, A7, A9, A11

#define CHOOSE_JUMP1_14( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14)  \
	A1, A3, A5, A7, A9, A11, A13

#define CHOOSE_JUMP1_16( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16)  \
	A1, A3, A5, A7, A9, A11, A13, A15

#define CHOOSE_JUMP1_18( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17

#define CHOOSE_JUMP1_20( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19

#define CHOOSE_JUMP1_22( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21

#define CHOOSE_JUMP1_24( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23

#define CHOOSE_JUMP1_26( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25

#define CHOOSE_JUMP1_28( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27

#define CHOOSE_JUMP1_30( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29

#define CHOOSE_JUMP1_32( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29, A31

#define CHOOSE_JUMP1_34( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32, A33, A34)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29, A31, A33

#define CHOOSE_JUMP1_36( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32, A33, A34, A35, A36)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29, A31, A33, A35

#define CHOOSE_JUMP1_38( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32, A33, A34, A35, A36, A37, A38)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29, A31, A33, A35, A37

#define CHOOSE_JUMP1_40( \
	A1, A2, A3, A4, A5, A6, A7, A8, A9, A10,  \
	A11, A12, A13, A14, A15, A16, A17, A18, A19, A20,  \
	A21, A22, A23, A24, A25, A26, A27, A28, A29, A30,  \
	A31, A32, A33, A34, A35, A36, A37, A38, A39, A40)  \
	A1, A3, A5, A7, A9, A11, A13, A15, A17, A19,  \
	A21, A23, A25, A27, A29, A31, A33, A35, A37, A39

#define CHOOSE_JUMP1(...) \
	EXPAND(CONCAT2(CHOOSE_JUMP1_, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__))

#define CHOOSE_JUMP1_FROM_SECOND(PH, ...) \
	CHOOSE_JUMP1(__VA_ARGS__, PH)