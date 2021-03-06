#pragma once

#include "debug_log.h"
#include <iostream>
#include <tuple>

template< class T, class U >
constexpr bool is_same_v = std::is_same<T, U>::value;

/*!
 Проверяет что типы Ts... одинаковые
*/

template <typename ... Args>
struct is_same_types : std::true_type{};

template <typename T, typename ... Args>
struct is_same_types<T, T, Args...> : is_same_types<T, Args...>{};

template <typename T, typename U, typename ... Args>
struct is_same_types<T, U, Args...> : std::false_type{};
 

 /*!
 Используется для всех типов кроме std::tuple 
 и возвращает value = false
*/
template <typename... Ts>
struct is_tuple : std::false_type {};

/*!
 Используется для типа std::tuple 
 и возвращает value = true
*/
template <typename... Ts> 
struct is_tuple<std::tuple<Ts... >> : is_same_types<Ts...> {};


template< typename... Ts>
constexpr bool is_tuple_v = is_tuple<Ts...>::value;

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