#pragma once

#include "debug_log.h"
#include "print_tuple.h"
#include "lib.h"
#include <type_traits>
#include <vector>
#include <list>
#include <algorithm>


template <typename T>
constexpr bool is_integral_v = std::is_integral<T>::value;


/*!
 Функция печати условного ip-адреса.
 как std::string
*/
void print(std::ostream& os, const std::string& ip)
{
    D_PF_LOG(std::cout);

    os << ip;
}

/*!
 Функция печати условного ip-адреса.
 Частичная специализация для контейнеров std::list, std::vector
*/
template<typename T>
typename std::enable_if_t<is_same_v<T, std::vector<typename T::value_type>>|| 
                          is_same_v<T, std::list  <typename T::value_type>>, void> 
print(std::ostream& os, const T& ip) 
{   
    D_PF_LOG(std::cout);

    if(ip.empty()) return;

    os << *ip.cbegin();
    std::for_each(std::next(ip.cbegin()), std::cend(ip), [&os](const auto &i){ os << "." << i; });
}

/*!
 Функция печати условного ip-адреса.
 Частичная специализация для целочисленного представления
*/
template<typename T>
typename std::enable_if_t<is_integral_v<T>, void>
print (std::ostream& os, const T& ip) 
{
    D_PF_LOG(std::cout);

    std::array<uint32_t, sizeof(T)> v;
    std::generate(v.rbegin(), v.rend(), [n = ip]() mutable { auto i = (n & 0xff); n >>= 8; return i; });

    os << *v.cbegin();
    std::for_each(std::next(v.cbegin()), std::cend(v), [&os](const auto &i){ os << "." << i; });
}


/*!
 Функция печати условного ip-адреса.
 Частичная специализация для tuple
*/
template <typename T>
typename std::enable_if_t<is_tuple_v<T>, void>
print(std::ostream& os, const T& ip)
{
    D_PF_LOG(std::cout);

    tuple_p<T, std::tuple_size<T>::value>::print(os, ip);
}

/*!
 Печать адреса как char(-1)
 Печать адреса как short(0)
 Печать адреса как int(2130706433)
 Печать адреса как long(8875824491850138409)
*/
void base_print(std::ostream& os)
{
    print(os, static_cast<char>(-1));
    os << std::endl;
    print(os, static_cast<short>(0));
    os << std::endl;
    print(os,  2130706433);
    os << std::endl;
    print(os,  8875824491850138409);
    os << std::endl;
}