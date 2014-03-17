#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>
 
int add(int i, int j)
{
    return i + j;
}
 
BOOST_AUTO_TEST_CASE(universeInOrder)
{
    BOOST_CHECK(add(2, 2) == 4);
}

BOOST_AUTO_TEST_CASE(sum1)
{
    BOOST_CHECK(5*5 == 10+15);
}

BOOST_AUTO_TEST_CASE(sum2)
{
    BOOST_CHECK(4.4*6 - 24 <= 0);
}
