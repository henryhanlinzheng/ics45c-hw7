// ------------------------- Your tests - student_gtests.cpp ----------------------------- //
// Your own GoogleTest suite for the Array of int in int_array.hpp. It is graded: the
// autograder runs it against a correct Array and against several with one bug each. A test is
// worth something only when it passes on the correct Array and fails on a broken one, so a
// test that always fails (or that tests nothing) earns nothing.
//
// Two examples are given. Add tests of your own for the constructors, the copy and move
// operations, operator[] in and out of range, fill, and length.
// --------------------------------------------------------------------------------------- //

#include <gtest/gtest.h>

#include "int_array.hpp"
#include "alloc.hpp"

TEST(IntArrayTests, DefaultArrayIsEmpty) {
    const Array a;
    EXPECT_EQ(a.length(), 0);
}

TEST(IntArrayTests, SizedArrayReportsItsLength) {
    const Array a{5};
    EXPECT_EQ(a.length(), 5);
}

// ADD YOUR TESTS HERE:

TEST(IntArrayTests, FillSetsEveryElement) {
    Array a{5};
    a.fill(7);
    for (int i = 0; i < a.length(); ++i) {
        EXPECT_EQ(a[i], 7);
    }
}

TEST(IntArrayTests, SubscriptBounds) {
    Array a{3};
    const Array& c = a;
    EXPECT_NO_THROW(a[0]);
    EXPECT_NO_THROW(a[2]);
    EXPECT_THROW(a[-1], std::string);
    EXPECT_THROW(a[3], std::string);
    EXPECT_THROW(c[-1], std::string);
    EXPECT_THROW(c[3], std::string);
}

TEST(IntArrayTests, CopyIsDeep) {
    Array a{3};
    a.fill(1);
    Array b{a};
    b[0] = 9;
    EXPECT_EQ(b.length(), 3);
    EXPECT_EQ(b[1], 1);
    EXPECT_EQ(a[0], 1);
}

TEST(IntArrayTests, MoveTakesBufferWithoutAllocating) {
    AllocationTracker tracker;
    Array a{3};
    a.fill(4);
    std::size_t before = tracker.get_num_allocations();
    Array b{std::move(a)};
    EXPECT_EQ(tracker.get_num_allocations(), before);
    EXPECT_EQ(b.length(), 3);
    EXPECT_EQ(b[2], 4);
}

TEST(IntArrayTests, DestructorFreesBuffer) {
    AllocationTracker tracker;
    {
        Array a{3};
        Array b{a};
        Array c{std::move(b)};
    }
    EXPECT_TRUE(tracker.get_allocations().empty());
    EXPECT_EQ(tracker.get_mismatching_deletes(), 0u);
}