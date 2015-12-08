#include "gtest/gtest.h"
#include "../src/poly.h"
#include <stdio.h>

double square(double x){
	return x*x;
}

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

GTEST_API_ int main(int argc, char **argv) {
	printf("Running main() from gtest_main.cc\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

