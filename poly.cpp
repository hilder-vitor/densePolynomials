
#include "poly.h"
#include<vector>
#include <algorithm>    // std::max
#include<regex>

#define DEFAULT_DEGREE 100

int Poly::get(unsigned int degree) const{
	if (degree < lowestExpoent || degree >= coeffs.size())
		return 0;
	return coeffs[degree - lowestExpoent];
}

void Poly::set(unsigned int degree, unsigned int coeff){
	if (degree < lowestExpoent){
		unsigned int oldSize = coeffs.size();
		unsigned int spaceRequired = lowestExpoent - degree;
		unsigned int newSize = oldSize + spaceRequired;
		coeffs.resize(newSize);
		for (int i = oldSize - 1; i >= 0; i--){
			coeffs[i + spaceRequired] = coeffs[i];
		}
		lowestExpoent = degree;
	}else if(degree >= coeffs.size() + lowestExpoent){
		unsigned int oldSize = coeffs.size();
		unsigned int spaceRequired = degree - (lowestExpoent + coeffs.size());
		unsigned int newSize = oldSize + spaceRequired + 100;
		coeffs.resize(newSize);
	}

	coeffs[degree - lowestExpoent] = coeff;
}


unsigned int Poly::firstNonZeroCoeff() const{
	for (unsigned int i = 0; i < coeffs.size(); i++)
		if (0 != coeffs[i])
			return i + lowestExpoent;
	throw NullPolynomialException();
}

Poly::Poly(){
	lowestExpoent = 0;
	coeffs = std::vector<int>(DEFAULT_DEGREE + 1);

}

Poly::Poly(unsigned int maxDegree){
	lowestExpoent = 0;
	coeffs = std::vector<int>(maxDegree + 1);
}


Poly::Poly(unsigned int minDegree, unsigned int maxDegree){
	lowestExpoent = minDegree;
	coeffs = std::vector<int>(maxDegree - minDegree + 1);
}


Poly::Poly(std::string strPoly){
	lowestExpoent = 0;
	coeffs = std::vector<int>(DEFAULT_DEGREE + 1);

	unsigned int exp;
	int signal, coef;
	
	try {
		std::regex regexToMonomial("[+-]?\\s*\\d+(\\*?x\\^\\d+)?");
	    std::sregex_iterator next(strPoly.begin(), strPoly.end(), regexToMonomial);
		std::sregex_iterator end;
		while (next != end) {
			std::smatch match = *next;
			std::string monomial = match.str();
			next++;
			if (0 == monomial.find("-")){
				signal = -1;
			}else{
				signal = 1;
			}
			std::regex regexToCoeffDegree("\\d+");
	   	 	std::sregex_iterator nextCD(monomial.begin(), monomial.end(), regexToCoeffDegree);
			std::smatch matchCoeff = *nextCD;
			coef = std::stoi(matchCoeff.str());
			nextCD++;
			std::smatch matchExp = *nextCD;
			if (nextCD == end){
				exp = 0;
			}else{
				exp = std::stoi(matchExp.str());
			}
			this->set(exp, signal*coef);
		} 
	} catch (std::regex_error& e) {
	  // Syntax error in the regular expression
	}
}







Poly::~Poly(){
//	delete[] coeffs;
}

unsigned int Poly::degree() const{
	for (unsigned int i = coeffs.size(); i > 0; i--)
		if (0 != coeffs[i])
			return i + lowestExpoent;
	return 0;
}

Poly operator+(const Poly& p, const Poly& q) {
	unsigned int d = std::max(p.degree(), q.degree());
	Poly r = Poly(d);
	for (unsigned int i = 0; i <= d; i++){
		r.set(i, p.get(i) + q.get(i));
	}
	return r;
}

Poly& Poly::operator+=(const Poly& q) {
	unsigned int d = std::max(this->degree(), q.degree());
	for (unsigned int i = 0; i <= d; i++){
		this->set(i, this->get(i) + q.get(i));
	}
	return *this;
}

Poly operator*(const Poly& p, const Poly& q) {
	unsigned int pDegree = p.degree();
	unsigned int qDegree = q.degree();
	unsigned int d = pDegree + qDegree;
	Poly r = Poly(d);
	for (unsigned int i = 0; i <= pDegree; i++){
		int pCoeff = p.get(i);
		if (0 != pCoeff){
			Poly tmp = Poly(d);
			for (unsigned int j = 0; j <= qDegree; j++){
				int qCoeff = q.get(j);
				tmp.set(i + j, pCoeff * qCoeff);
			}
			r += tmp;
		}
	}
	return r;
}


std::ostream& operator<<(std::ostream& os, const Poly& p) {
	
	try{
		unsigned int first = p.firstNonZeroCoeff();
		unsigned int degree = p.degree();
		for (unsigned int i = first; i <= degree; i++){
			int coeff = p.get(i);
			if (coeff != 0){
				if (coeff > 0)
					os << " +" << coeff;
				else
					os << " " << coeff;

				if (i > 0)
					os << "x^" << i;
			}
		}
	}catch (NullPolynomialException& e){
		// if p is a null polynomial 
		os << "0";
	}

	return os;	
}

