#pragma once

#include <string>
#include <numeric>
#include <type_traits>

template <typename T>
using is_float = typename std::is_same<T, float>::value;

template <typename T>
using is_double = typename std::is_same<T, double>::value;

template <typename T>
using is_string = typename std::is_same<T, std::string>::value;

template <typename T>
using is_integer = typename std::numeric_limits<T>::is_integer;