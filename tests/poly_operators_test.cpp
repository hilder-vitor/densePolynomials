#include "gtest/gtest.h"
#include "../src/poly.h"
#include <stdio.h>

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
    //std::cout << "EXPECT_EQ (a_plus_b_plus_c, (a + b) + c);" << std::endl;
	EXPECT_EQ (a_plus_b_plus_c, (a + b) + c);
	//std::cout << "EXPECT_EQ (a_plus_b_plus_c, b + (c + a));" << std::endl;
	EXPECT_EQ (a_plus_b_plus_c, b + (c + a));
	//std::cout << "EXPECT_EQ (a_plus_b_plus_c, c + a + b);" << std::endl;
	EXPECT_EQ (a_plus_b_plus_c, c + a + b);
	//std::cout << "EXPECT_EQ (a_plus_b_plus_a, a + b + a);" << std::endl;
	EXPECT_EQ (a_plus_b_plus_a, a + b + a);
	//std::cout << "EXPECT_EQ (a_plus_b_plus_a, a + b + a + zero);" << std::endl;
	EXPECT_EQ (a_plus_b_plus_a, a + b + a + zero);
	//std::cout << "EXPECT_EQ (a_plus_c_plus_ten, a + c + ten);" << std::endl;
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

TEST (PolyMultiplication, ManyProducts) { 
	Poly zero = Poly("0");
	Poly a = Poly("192*x^10 + 72*x^9 -19282*x^8 - 1*x^7 + 831*x^5 -4*x^4 + 5829*x^3 + 77*x^2 - 91*x^1 + 9");
	EXPECT_EQ (zero, a * zero);
	EXPECT_EQ (zero, zero * a);
	
	Poly b = Poly("291*x^13 + 22*x^12 -29291*x^11 - 1*x^10 - 138*x^8 -4*x^7 + 9825*x^6 - 19*x^5 - 46*x^4");
	Poly a_times_b = Poly("55872*x^23 + 25176*x^22 - 11233350*x^21 - 2533639*x^20 + 564788968*x^19 + 263898*x^18+ 6415*x^17 - 18097642*x^16 + 1047996*x^15 - 360217868*x^14 - 2022076*x^13 + 3549821*x^12 + 7096707*x^11 - 89040*x^10 + 57244025*x^9 + 645080*x^8 -1163708*x^7 + 86612*x^6+4015*x^5 - 414*x^4");
	EXPECT_EQ (a_times_b, a * b);
	EXPECT_EQ (a_times_b, b * a);

	Poly c = Poly("9187123123399411234552*x^19 + 12*x^16 + 11*x^15 - 1*x^10");

	Poly a_times_c = Poly("-9*x^10 + 91*x^11 - 77*x^12 - 5829*x^13 + 4*x^14 - 732*x^15 - 893*x^16 - 244*x^17 + 84325*x^18 + 82684108110594701180800*x^19 - 836028204229346422335331*x^20 + 707408480501754665070476*x^21 + 53551740686295168086203597*x^22 - 36748492493597645150322*x^23 + 7634499315544910735682120*x^24 + 2976*x^25 - 9187123123399411232248*x^26 - 177146108065387447424631664*x^27 + 661472864884757608887744*x^28 + 1763927639692686957033984*x^29");

	EXPECT_EQ (a_times_c, a * c);
	EXPECT_EQ (a_times_c, c * a);


	EXPECT_EQ (zero, c * a * zero);

}


GTEST_API_ int main(int argc, char **argv) {
	printf("----- Polynomial operations tests\n");
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

