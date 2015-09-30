
#include<iostream>
#include<vector>

class NullPolynomialException: public std::exception {
	virtual const char* what() const throw()
	{
		return "Trying to access coefficients of a zero polynomial.";
	}
};


class Poly{

	std::vector<int> coeffs; // array of coefficients

	// expoent associated with the first non-zero coefficient 
	// For instance: to x^2 + 3x^5 - 6x^9, this variable stores 2
	unsigned int lowestExpoent; 

	unsigned int firstNonZero;

	public:

	Poly();
	Poly(unsigned int maxDegree);
	Poly(unsigned int minDegree, unsigned int maxDegree);
	Poly(std::string strPoly);

	~Poly();



	int get(unsigned int degree) const;
	void set(unsigned int degree, unsigned int coeff);

	unsigned int firstNonZeroCoeff() const;
	unsigned int degree() const;

	Poly& operator+=(const Poly& q);
};

Poly operator+(const Poly& p, const Poly& q);
Poly operator*(const Poly& p, const Poly& q);
std::ostream& operator<<(std::ostream& os, const Poly& p);
