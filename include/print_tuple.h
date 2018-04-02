#pragma once

#include "debug_log.h"
#include <iostream>
#include <tuple>

/*!
 Используется для всех типов кроме std::tuple 
 и возвращает value=false
*/
template <typename T>
struct is_tuple : std::false_type {};

/*!
 Используется для типа std::tuple 
 и возвращает value=true
*/
template <typename... Ts> 
struct is_tuple<std::tuple<Ts... >> : std::true_type {};

/*!
 Печать std::tuple
*/
template<class T, std::size_t N>
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