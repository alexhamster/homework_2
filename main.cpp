#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <fstream>
#include <cassert>

using ip_vec = std::vector<unsigned char>;

using ip_pool_list = std::list<std::vector<unsigned char>>;

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

void printIpPool(const ip_pool_list &list_, bool reversed = false)
{
    if(reversed)
        for (auto ip = list_.crbegin(); ip != list_.crend(); ip++)
            printVector(*ip);
    else
        for (auto ip = list_.cbegin(); ip != list_.cend(); ip++)
            printVector(*ip);
}

template<typename... Args>
bool filter(const unsigned char &iter_, Args... args)
{


    unsigned char filters[sizeof...(args)] = { (static_cast<unsigned char>(args))... };
    for (size_t i = 0; i < sizeof...(args); ++i)
    {
        auto it = std::next(&iter_, i);
        if (*it != filters[i])
            return false;
    }

    return true;
}

template<typename T>
bool filterAny(const ip_vec &vec_, T t)
{
    for (auto i : vec_)
    {
        if (filter(i, t))
            return true;
    }
    return false;
}

void filter_test()
{
    ip_vec t;
    t.push_back(46);
    t.push_back(70);
    t.push_back(20);
    t.push_back(0);

    assert(filter(*(t.cbegin()), 46, 70, 20));
    assert(!filter(*(t.cbegin()), 46, 24));
    assert(!filter(*(t.cbegin()), 56, 70, 70, 0));
}

void filterAny_test()
{
    ip_vec t;
    t.push_back(46);
    t.push_back(70);
    t.push_back(20);
    t.push_back(0);

    assert(filterAny(t, 46));
    assert(filterAny(t, 0));
    assert(!filterAny(t, 228));
}


int main()
{

    filter_test();

    filterAny_test();

    try
    {
        ip_pool_list ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            if (line.length() == 0)
               break;

            auto t = split(split(line, '\t').at(0), '.');
            ip_vec c;

            for (auto& i : t)
                c.push_back(std::stoi(i));

            ip_pool.push_back(c);
        }

        //reverse lexicographically sort
        ip_pool.sort();
        printIpPool(ip_pool, true);

        //lexicographically sort
        printIpPool(ip_pool, false);

        // ip = filter(1)
        for (auto ip : ip_pool)
        {
            if (filter(*(ip.cbegin()), 1))
                printVector(ip);
        }

        // ip = filter(46, 70)
        for (auto ip : ip_pool)
        {
            if (filter(*(ip.cbegin()), 46, 70))
                printVector(ip);
        }

        // ip = filterAny(46)
        for (auto ip : ip_pool)
        {
            if (filterAny(ip, 46))
                printVector(ip);
        }

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
