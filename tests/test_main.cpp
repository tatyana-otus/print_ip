#include "lib.h"
#include <sstream>
#include "print_ip.h"
#include <sstream>


#define BOOST_TEST_MODULE test_main

#include <boost/test/unit_test.hpp>
#include <boost/test/execution_monitor.hpp> 
#include <boost/test/output_test_stream.hpp>

using boost::test_tools::output_test_stream;


BOOST_AUTO_TEST_SUITE(test_suite_main)

BOOST_AUTO_TEST_CASE(test_version_valid)
{
    BOOST_CHECK( (major_version() >= 0) &&  (minor_version() >= 0) && (patch_version() >= 0) );
    BOOST_CHECK( (major_version() >  0) ||  (minor_version() >  0) || (patch_version() >  0) );
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(test_suite_ip_print)

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
BOOST_AUTO_TEST_CASE(vector_ip_print)
{
    std::stringstream oss_1;
    print(oss_1, std::vector<int>{});
    BOOST_CHECK( oss_1.str() == "" );

    std::stringstream oss_2;
    print(oss_2, std::vector<int>{1});
    BOOST_CHECK( oss_2.str() == "1" );

    std::stringstream oss_3;
    print(oss_3, std::vector<int>{87, 34, 19, 10});
    BOOST_CHECK( oss_3.str() == "87.34.19.10" );

    std::stringstream oss_4;
    print(oss_4, std::vector<int>{1131232132, -1323, 34223});
    BOOST_CHECK( oss_4.str() == "1131232132.-1323.34223" );

    std::stringstream oss_5;
    print(oss_5, std::vector<std::string>{"10", "10", "10eweqwe"});
    BOOST_CHECK( oss_5.str() == "10.10.10eweqwe" );
}


BOOST_AUTO_TEST_CASE(list_ip_print)
{
    std::stringstream oss_1;
    print(oss_1, std::vector<int>{});
    BOOST_CHECK( oss_1.str() == "" );

    std::stringstream oss_2;
    print(oss_2, std::list<int>{1});
    BOOST_CHECK( oss_2.str() == "1" );

    std::stringstream oss_3;
    print(oss_3, std::list<int>{87, 34, 19, 10});
    BOOST_CHECK( oss_3.str() == "87.34.19.10" );

    std::stringstream oss_4;
    print(oss_4, std::list<int>{1131232132, -1323, 34223});
    BOOST_CHECK( oss_4.str() == "1131232132.-1323.34223" );

    std::stringstream oss_5;
    print(oss_5, std::list<std::string>{"10", "10", "10eweqwe"});
    BOOST_CHECK( oss_5.str() == "10.10.10eweqwe" );
}

BOOST_AUTO_TEST_CASE(string_ip_print)
{
    std::stringstream oss_1;
    print(oss_1, std::string{});
    BOOST_CHECK( oss_1.str() == "" );

    std::stringstream oss_2;
    print(oss_2, std::string{"1"});
    BOOST_CHECK( oss_2.str() == "1" );

    std::stringstream oss_3;
    print(oss_3, std::string{"87.34.19.10"});
    BOOST_CHECK( oss_3.str() == "87.34.19.10" );

    std::stringstream oss_4;
    print(oss_4, std::string{"1131232132.-1323.34223"});
    BOOST_CHECK( oss_4.str() == "1131232132.-1323.34223" );

    std::stringstream oss_5;
    print(oss_5, std::string{"10.10.10eweqwe"});
    BOOST_CHECK( oss_5.str() == "10.10.10eweqwe" );
}

BOOST_AUTO_TEST_SUITE_END()