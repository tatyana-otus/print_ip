#include "lib.h"
#include "print_ip.h"
#include <sstream>


#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;

/*!
 Вспомогательные функции для тестирования контейнеров std::list, std::vector
*/
template<typename T>
void test_contaner(const std::initializer_list<T>& in_data, const std::string& out_data)
{
    std::stringstream oss_1;
    print(oss_1, std::vector<T>{in_data});
    BOOST_CHECK( oss_1.str() == out_data );

    std::stringstream oss_2;
    print(oss_2, std::list<T>{in_data});
    BOOST_CHECK( oss_2.str() == out_data );
}

/*!
 Вспомогательные функции для тестирования std::string
*/
void test_string(const std::string& in_data, const std::string& out_data)
{
    std::stringstream oss;
    print(oss, in_data);
    BOOST_CHECK( oss.str() == out_data );
}

/*!
 Вспомогательные функции для тестирования std::tuple
*/
template<class... Types>
void test_tuple(const std::string& out_data, Types... args)
{
    std::stringstream oss;
    print(oss, std::make_tuple(args...));
    BOOST_CHECK( oss.str() == out_data );

}

BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_ip_print)

/*!
 Тестирование функции печати условного ip-адреса
 для целочисленного представления
*/
BOOST_AUTO_TEST_CASE(base_ip_print)
{
    std::string out_data =
    "255\n"
    "0.0\n"
    "127.0.0.1\n"
    "123.45.67.89.101.112.131.41\n";

    std::stringstream oss;
    base_print( oss);
    BOOST_CHECK( oss.str() == out_data );
}

/*!
 Тестирование функции печати условного ip-адреса
 для контейнеров std::list, std::vector
*/
BOOST_AUTO_TEST_CASE(contaner_ip_print)
{
    test_contaner<std::string>({}, "");
    test_contaner<int>({}, "");

    test_contaner(    {1}, "1");
    test_contaner(    {87, 34, 19, 10},           "87.34.19.10");
    test_contaner(    {1131232132, -1323, 34223}, "1131232132.-1323.34223");
    test_contaner(    {"10", "10", "10eweqwe"},   "10.10.10eweqwe");
}

/*!
 Тестирование функции печати условного ip-адреса
 для std::string
*/
BOOST_AUTO_TEST_CASE(string_ip_print)
{
    test_string("", "");
    test_string("1", "1");
    test_string("87.34.19.10", "87.34.19.10");
    test_string("1131232132.-1323.34223", "1131232132.-1323.34223");
    test_string("10.10.10eweqwe", "10.10.10eweqwe");
}

/*!
 Тестирование функции печати условного ip-адреса
 для std::tuple
*/
BOOST_AUTO_TEST_CASE(tuple_ip_print)
{
    test_tuple("");
    test_tuple("1", 1);

    test_tuple("87.34.19.10", 87, 34, 19, 10);
    test_tuple("87.34.19.10", "87", "34", "19", "10");

    test_tuple("10.10.10eweqwe", "10", "10", "10eweqwe");  
}

BOOST_AUTO_TEST_SUITE_END()