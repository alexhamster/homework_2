#define BOOST_TEST_MODULE ip_test_module
#include <boost/test/unit_test.hpp>

#include "filter.h"

BOOST_AUTO_TEST_SUITE(helloworld_test_suite)

BOOST_AUTO_TEST_CASE(filter_test)
{
    ip_vec t;
    t.push_back(46);
    t.push_back(70);
    t.push_back(20);
    t.push_back(0);

    BOOST_CHECK(filter(*(t.cbegin()), 46, 70, 20));
    BOOST_CHECK(!filter(*(t.cbegin()), 46, 24));
    BOOST_CHECK(!filter(*(t.cbegin()), 56, 70, 70, 0));
}

BOOST_AUTO_TEST_CASE(filterAny_test)
{
    ip_vec t;
    t.push_back(46);
    t.push_back(70);
    t.push_back(20);
    t.push_back(0);

    BOOST_CHECK(filterAny(t, 46));
    BOOST_CHECK(filterAny(t, 0));
    BOOST_CHECK(!filterAny(t, 228));
}

BOOST_AUTO_TEST_SUITE_END()