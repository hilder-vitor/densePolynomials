
#ifndef __DENSE__POLY
#define __DENSE__POLY

#include<iostream>
#include<vector>
#include "gmpxx.h"

class NullPolynomialException: public std::exception {
	virtual const char* what() const throw()
	{
		return "Trying to access coefficients of a zero polynomial.";
	}
};


class Poly{

	std::vector<mpz_class> coeffs; // array of coefficients

	// The lowest expoent accepted by the polynomial.
	// Its value is used as the expoent of the coefficient saved at position zero of coeffs.
	// For instance: if its value is 10, and coeffs is {-2, 0, 3}, then, the polynomial is -2x^10 + 0x^11 + 3x^12
	unsigned int lowestExpoent; 

	unsigned int firstNonZero;
	unsigned int lastNonZero;

	bool isZeroPolynomial;

	void updateLast();
	void updateFirst();

	public:

	Poly();
	Poly(unsigned int maxDegree);
	Poly(unsigned int minDegree, unsigned int maxDegree);
	Poly(unsigned int degree, mpz_class coeff); // initialize a monomial
	Poly(std::string strPoly);

	static Poly encode(mpz_class intValue);

	~Poly();


	mpz_class get(unsigned int degree) const;
	void set(unsigned int degree, mpz_class coeff);

	unsigned int indexFirstNonZeroCoeff() const;
	mpz_class getFinalCoeff() const;
	unsigned int degree() const;

	Poly& operator+=(const Poly& q);

	bool isZero() const;

	void dump() const;
};

Poly operator+(const Poly& p, const Poly& q);
Poly operator-(const Poly& p, const Poly& q);
Poly operator*(const Poly& p, const Poly& q);
Poly operator*(const mpz_class& alpha, const Poly& p);
Poly operator*(const Poly& p, const mpz_class& alpha);
Poly operator/(const Poly& p, const Poly& q);
bool operator==(const Poly& p, const Poly& q);
std::ostream& operator<<(std::ostream& os, const Poly& p);

#endif
