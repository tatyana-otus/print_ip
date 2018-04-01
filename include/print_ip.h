#pragma once
#include "debug_log.h"

#include "lib.h"
#include <iostream>
#include <type_traits>
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <utility>


//template<typename T, typename... Targs>
//void  print (const T& os,  const Targs&... Fargs);


template<typename T>
typename std::enable_if<std::is_same<T, std::vector<typename T::value_type>>::value || 
                        std::is_same<T, std::list  <typename T::value_type>>::value, void>::type print(std::ostream& os, const T& ip) 
{   
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    if(ip.empty()) return;

    std::for_each(std::begin(ip),        std::next(ip.begin()), [&os](const auto &i){ os << i;        });
    std::for_each(std::next(ip.begin()), std::end(ip),          [&os](const auto &i){ os << "." << i; });
}


template<class T>
typename std::enable_if<std::is_integral<T>::value, void>::type print (std::ostream& os, const T& ip) 
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    auto n = ip;
    std::vector<uint32_t> v(sizeof(T));
    std::generate(v.rbegin(), v.rend(), [&n]() { auto i = n & 0xff; n >>= 8; return i; });
    print(os, v);
}


template<class T>
typename std::enable_if<std::is_same<T, std::string>::value, void>::type print(std::ostream& os, const T& ip)
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    os << ip;
}


/*template<typename T, typename... Targs>
void  print (std::ostream& os,  const T& value, const Targs&... Fargs) 
{
    D_2_LOG(std::cout,__PRETTY_FUNCTION__);

    print(os, value);
    print(os, Fargs...);
}*/



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