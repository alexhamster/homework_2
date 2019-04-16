#include "filter.h"

int main()
{
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
        printIpPool(ip_pool);

        //lexicographically sort
        ip_pool.sort(std::greater<ip_vec>());
        printIpPool(ip_pool);

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