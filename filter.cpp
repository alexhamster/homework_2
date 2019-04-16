#include "filter.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void printVector(const ip_vec &vec_)
{
    for (auto i = vec_.cbegin(); i != vec_.cend(); i++)
    {
        std::cout << +(*i);
        if (i != vec_.cend() - 1)
            std::cout << ".";
    }
    std::cout << std::endl;
}

void printIpPool(const ip_pool_list &list_)
{
    for (auto ip = list_.cbegin(); ip != list_.cend(); ip++)
        printVector(*ip);
}