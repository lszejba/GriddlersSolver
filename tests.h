#ifndef GRIDDLERSTEST_H
#define GRIDDLERSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class GriddlersTest : public CppUnit::TextFixture
{
    CPPUNIT_TEST_SUITE( GriddlersTest );
    CPPUNIT_TEST( testConstructor );
    CPPUNIT_TEST_SUITE_END();

    public:
    void setUp();
    void tearDown();

    void testConstructor();
};

#endif
