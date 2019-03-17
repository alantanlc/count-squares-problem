// tests.cpp
#include "squares.cpp"
#include <gtest/gtest.h>

TEST(CountSquaresTest, TwoSquares) {
    // Initialize points
    Point p1 { 0.0, 0.0 };
    Point p2 { 0.0, 1.0 };

    Point p3 { 1.0, 0.0 };
    Point p4 { 1.0, 1.0 };

    Point p5 { 0.0, 0.0 };
    Point p6 { 1.0, 0.0 };

    Point p7 { 0.0, 1.0 };
    Point p8 { 1.0, 1.0 };

    Point p9  { 0.0, 1.0 };
    Point p10 { 1.0, 0.0 };

    Point p11 { -1.0, 0.0 };
    Point p12 { 0.0, -1.0 };

    Point p13 { -1.0, 0.0 };
    Point p14 { 0.0, 1.0 };

    Point p15 { 0.0, -1.0 };
    Point p16 { 1.0, 0.0 };

    // Lines l1 and l2 are parallel lines p1
    Line l1 { p1, p2 };
    Line l2 { p3, p4 };

    // Lines l3 and l4 are parallel lines p2
    Line l3 { p5, p6 };
    Line l4 { p7, p8 };

    // Lines l5 and l6 are parallel lines p3
    Line l5 { p9, p10 };
    Line l6 { p11, p12 };

    // Lines l7 and l8 are parallel lines p4
    Line l7 { p13, p14 };
    Line l8 { p15, p16 };

    // Parallel lines p1 and p2 form a square
    // Parallel lines p3 and p4 form a square
    vector<Line> lines { l1, l2, l3, l4, l5, l6, l7, l8 };

    ASSERT_EQ(2, countSquares(lines));
}
 
TEST(CountSquaresTest, FiveSquares) { 
    // Initialize points
    Point p1 { 0.0, 0.0 };
    Point p2 { 0.0, 1.0 };

    Point p3 { 1.0, 0.0 };
    Point p4 { 1.0, 1.0 };

    Point p5 { 0.0, 0.0 };
    Point p6 { 1.0, 0.0 };

    Point p7 { 0.0, 1.0 };
    Point p8 { 1.0, 1.0 };

    Point p17 { 0.5, -2.0 };
    Point p18 { 0.5, 2.0 };

    Point p19 { -2.0, 0.5 };
    Point p20 { 2.0, 0.5 };

    // Lines l1 and l2 are parallel lines p1
    Line l1 { p1, p2 };
    Line l2 { p3, p4 };

    // Lines l3 and l4 are parallel lines p2
    Line l3 { p5, p6 };
    Line l4 { p7, p8 };

    Line l9 { p17, p18 };
    Line l10 { p19, p20 };

    // Parallel lines p1 and p2 form a square
    // Parallel lines p3 and p4 form a square
    vector<Line> lines { l1, l2, l3, l4, l9, l10 };

    ASSERT_EQ(5, countSquares(lines));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
