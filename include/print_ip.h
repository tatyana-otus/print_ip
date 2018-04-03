#pragma once

#include "debug_log.h"
#include "print_tuple.h"
#include "lib.h"
#include <type_traits>
#include <vector>
#include <list>
#include <algorithm>


/*!
 Функция печати условного ip-адреса.
 как std::string
*/
void print(std::ostream& os, const std::string& ip)
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    os << ip;
}

/*!
 Функция печати условного ip-адреса.
 Частичная специализация для контейнеров std::list, std::vector
*/
template<typename T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value || 
                        std::is_same<T, std::list  <typename T::value_type>>::value, void>::type print(std::ostream& os, const T& ip) 
{   
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    if(ip.empty()) return;

    std::for_each(std::cbegin(ip),        std::next(ip.cbegin()), [&os](const auto &i){ os << i;        });
    std::for_each(std::next(ip.cbegin()), std::cend(ip),          [&os](const auto &i){ os << "." << i; });
}

/*!
 Функция печати условного ip-адреса.
 Частичная специализация для целочисленного представления
*/
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type print (std::ostream& os, const T& ip) 
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    auto n = ip;
    std::vector<uint32_t> v(sizeof(T));
    std::generate(v.rbegin(), v.rend(), [&n]() { auto i = (n & 0xff); n >>= 8; return i; });
    print(os, v);
}


/*!
 Функция печати условного ip-адреса.
 Частичная специализация для tuple
*/
template <typename T>
typename std::enable_if<is_tuple<T>::value, void>::type print(std::ostream& os, const T& ip)
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

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
    print(os, (char)-1);
    os << std::endl;
    print(os, short(0));
    os << std::endl;
    print(os,  2130706433);
    os << std::endl;
    print(os,  8875824491850138409);
    os << std::endl;
}