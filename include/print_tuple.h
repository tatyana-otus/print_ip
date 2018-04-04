#pragma once

#include "debug_log.h"
#include <iostream>
#include <tuple>


/*!
 Проверяет что типы Ts... одинаковые
*/
template <typename ... Ts>
struct is_same_types;

template <typename T> 
struct is_same_types<T> : std::true_type {};
 
template <typename T, typename N, typename... Ts>
struct is_same_types<T, N, Ts...>
{
    static const bool value = (std::is_same<T, N>::value) && (is_same_types<T, Ts...>::value);
};
 

 /*!
 Используется для всех типов кроме std::tuple 
 и возвращает value = false
*/
template <typename T, typename... Ts>
struct is_tuple : std::false_type {};

/*!
 Используется для типа std::tuple 
 и возвращает value = true
*/
template <typename... Ts> 
struct is_tuple<std::tuple<Ts... >> : is_same_types<Ts...> {};

template <> 
struct is_tuple<std::tuple<>> : std::true_type {};

template <typename T> 
struct is_tuple<std::tuple<T>> : std::true_type {};


/*!
 Печать std::tuple
*/
template<typename T, std::size_t N>
struct tuple_p {
    static void print(std::ostream& os, const T& t) 
    {
        tuple_p<T, N-1>::print(os, t);
        os << "." << std::get<N-1>(t);
    }
};

/*!
 Печать 0-го элемента std::tuple
*/
template<typename T>
struct tuple_p<T, 1> {
    static void print(std::ostream& os, const T& t) 
    {
        os << std::get<0>(t);
    }
};

/*!
 Печать пустого std::tuple
*/
template<typename T>
struct tuple_p<T, 0> {
    static void print(std::ostream& os, const T& t) {}
};