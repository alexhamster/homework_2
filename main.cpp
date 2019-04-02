#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <fstream>


/*
void writeVectorToFile(std::ofstream& out_stream_, const std::vector<unsigned char> &vec_)
{
for (auto i = vec_.cbegin(); i != vec_.cend(); i++)
{
out_stream_ << +(*i);
if (i != vec_.cend() - 1)
out_stream_ << ".";
}
out_stream_ << std::endl;
}

void write2DVectorToFile(std::ofstream& out_stream_, const std::list<std::vector<unsigned char>> &list_)
{
for (auto ip = list_.cbegin(); ip != list_.cend(); ++ip)
writeVectorToFile(out_stream_, *ip);
}

std::list<std::vector<unsigned char>>* readIpFile(std::string path_)
{
std::ifstream input_stream;
input_stream.open(path_);
if (!input_stream.is_open())
throw std::exception("Can not open input file");

auto* ip_pool = new std::list<std::vector<unsigned char>>;

for (std::string line; std::getline(input_stream, line);)
{
auto t = split(split(line, '\t').at(0), '.');
std::vector<unsigned char> c;

for (auto i : t)
c.push_back(std::stoi(i));

ip_pool->push_back(c);
}
input_stream.close();
return ip_pool;
}

*/

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

void printVector(const std::vector<unsigned char> &vec_)
{
	for (auto i = vec_.cbegin(); i != vec_.cend(); i++)
	{
		std::cout << +(*i);
		if (i != vec_.cend() - 1)
			std::cout << ".";
	}
	std::cout << std::endl;
}

void printIpPool(const std::list<std::vector<unsigned char>> &list_)
{
	for (auto ip = list_.cbegin(); ip != list_.cend(); ++ip)
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
bool filterAny(const std::vector<unsigned char> &vec_, T t)
{
	for (auto i = vec_.cbegin(); i != vec_.cend(); ++i)
	{
		if (filter(*i, t))
			return true;
	}
	return false;
}


int main()
{
	try
	{
		std::list<std::vector<unsigned char>> ip_pool;

		for (std::string line; std::getline(std::cin, line);)
		{
			if (line.length() == 0)
				break;

			auto t = split(split(line, '\t').at(0), '.');
			std::vector<unsigned char> c;

			for (auto i : t)
				c.push_back(std::stoi(i));

			ip_pool.push_back(c);
		}

		//reverse lexicographically sort
		//std::sort(ip_pool.begin(), ip_pool.end());

		ip_pool.sort();
		printIpPool(ip_pool);

		//lexicographically sort
		//std::sort(ip_pool.rbegin(), ip_pool.rend());

		ip_pool.sort(std::greater<std::vector<unsigned char>>());
		printIpPool(ip_pool);

		// ip = filter(1)
		for (auto& ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
		{
			if (filter(*(ip->cbegin()), 1))
				printVector(*ip);
		}

		// ip = filter(46, 70)
		for (auto& ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
		{
			if (filter(*(ip->cbegin()), 46, 70))
				printVector(*ip);
		}

		// ip = filterAny(46)
		for (auto& ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
		{
			if (filterAny(*ip, 46))
				printVector(*ip);
		}

	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}