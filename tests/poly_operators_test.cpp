#include "gtest/gtest.h"
#include "../src/poly.h"
#include <stdio.h>

TEST (PolyAddition, TwoAdditions) { 
	Poly a = Poly("        2*x^4 + 4*x^2      -1");
	Poly b = Poly("1*x^5         + 4*x^2 -1*x^1    ");
	Poly a_plus_b = Poly("1*x^5 + 2*x^4 + 8*x^2 -1*x^1 - 1");
	EXPECT_EQ (a_plus_b, a + b);
	EXPECT_EQ (a_plus_b, b + a); // commutative

	Poly c = Poly("191231239232222221231*x^28 - 92*x^12 + 80*x^2");
	Poly c_plus_a = Poly("191231239232222221231*x^28 - 92*x^12 + 2*x^4 + 84*x^2 -1");

	EXPECT_EQ (c_plus_a, c + a);

	Poly c_plus_c = Poly("382462478464444442462*x^28 - 184*x^12 + 160*x^2");
	EXPECT_EQ (c_plus_c, c + c);

	Poly zero = Poly("0");
	EXPECT_EQ (b, b + zero);
	EXPECT_EQ (b, zero + b);

}

TEST (PolyAddition, MoreThanTwoAdditions) { 
	Poly a = Poly("                                       2*x^4 + 4*x^3      -1");
	Poly b = Poly("              -1*x^10 + 5*x^8 -2*x^5         - 4*x^3");
	Poly c = Poly("1234567891011121314151617*x^50 + 1918292*x^8 + 123*x^3  - 4");
	Poly ten = Poly("10");
	Poly zero = Poly("0");
	Poly a_plus_b_plus_a = Poly("-1*x^10 + 5*x^8 -2*x^5 + 4*x^4 + 4*x^3 - 2");
	Poly a_plus_b_plus_c = Poly("1234567891011121314151617*x^50 -1*x^10 + 1918297*x^8 -2*x^5 + 2*x^4 + 123*x^3 -5");
	Poly a_plus_c_plus_ten = Poly("1234567891011121314151617*x^50 + 1918292*x^8 + 2*x^4 + 127*x^3 +5");
	EXPECT_EQ (a_plus_b_plus_c, (a + b) + c);
	EXPECT_EQ (a_plus_b_plus_c, b + (c + a));
	EXPECT_EQ (a_plus_b_plus_c, c + a + b);
	EXPECT_EQ (a_plus_b_plus_a, a + b + a);
	EXPECT_EQ (a_plus_b_plus_a, a + b + a + zero);
	EXPECT_EQ (a_plus_c_plus_ten, a + c + ten);
}

TEST (PolySubtraction, ManySubtractions) { 
	Poly zero = Poly("0");
	Poly a = Poly("23*x^6 + 4*x^5 + 2*x^3     -1");
	EXPECT_EQ (a, a - zero);
	
	Poly b = Poly("11*x^5 + 5*x^2 -1*x^1");
	EXPECT_EQ (a, a - zero);

	Poly a_minus_b = Poly("23*x^6 - 7*x^5 + 2*x^3 -5*x^2 +1*x^1 - 1");
	Poly b_minus_a = Poly("-23*x^6 + 7*x^5 -2*x^3 +5*x^2 -1*x^1 + 1");
	EXPECT_EQ (a_minus_b, a - b);
	EXPECT_EQ (b_minus_a, b - a);

	Poly ten = Poly("10");
	Poly c = Poly("191231239232222221231*x^28 - 92*x^12 + 80*x^2");
	Poly c_minus_a = Poly("191231239232222221231*x^28 - 92*x^12 -23*x^6 -4*x^5 -2*x^3 + 80*x^2 +1");

	EXPECT_EQ (c_minus_a, c - a);

	Poly c_minus_a_minus_ten = Poly("191231239232222221231*x^28 - 92*x^12 -23*x^6 -4*x^5 -2*x^3 + 80*x^2 -9");
	EXPECT_EQ (c_minus_a_minus_ten, c - a - ten);
	EXPECT_EQ (c_minus_a_minus_ten, c - a - ten - zero);
}

TEST (PolyComparision, PolyEquality) {
	Poly a = Poly("12343210*x^100 + 897*x^98 + 184*x^89 + 1*x^85");
	Poly b = Poly("890*x^98 + 100*x^75 - 50");
	Poly c = Poly("-50");
	Poly d = Poly("1*x^5");
	Poly zero = Poly("0");

	EXPECT_TRUE(a == a);
	EXPECT_FALSE(b == a);
	EXPECT_FALSE(a == b);
	EXPECT_FALSE(a == zero);
	EXPECT_FALSE(zero == a);
	EXPECT_FALSE(zero == b);
	EXPECT_TRUE(zero == zero);
	EXPECT_FALSE(b == c);
	c.set(98, 890);
	c.set(75, 100);
	EXPECT_TRUE(b == c);
	EXPECT_FALSE(c == a);
	a.set(89, 0);
	a.set(85, 0);
	a.set(0, -50);
	c.set(100, 12343210);
	c.set(75, 0);
	c.set(98, 897);
	EXPECT_TRUE(a == c);
	EXPECT_FALSE(a == d);
	EXPECT_FALSE(b == d);
	EXPECT_FALSE(c == d);
}

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

