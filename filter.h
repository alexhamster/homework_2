#pragma once

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

std::vector<std::string> split(const std::string &str, char d);

void printVector(const ip_vec &vec_);

void printIpPool(const ip_pool_list &list_);

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