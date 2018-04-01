
//#define DEBUG_INFO_ALL
#include "print_ip.h"


int main(int, char**)
{
    base_print(std::cout);

    print(std::cout, std::vector<int>{ 192,168,137,1 });
    std::cout << std::endl;
    print(std::cout, std::list<int>  { 192,168,137,1 });
    std::cout << std::endl;
    print(std::cout, std::string     {"192.168.137.1"});
    std::cout << std::endl;
    print(std::cout, std::make_tuple ( 192,168,137,1 ));
    std::cout << std::endl;

    return 0;
}