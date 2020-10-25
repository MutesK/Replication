#pragma once

#include <string>
#include <numeric>
#include <type_traits>

template <typename T>
using is_float = std::is_same<T, float>::value;

template <typename T>
using is_double = std::is_same<T, double>::value;

template <typename T>
using is_string = std::is_same<T, std::string>::value;

template <typename T>
using is_integer = std::numeric_limits<T>::is_integer;