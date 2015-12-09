
#include "poly.h"
#include<vector>
#include <algorithm>    // std::max
#include<regex>

#define DEFAULT_DEGREE 100

mpz_class Poly::get(unsigned int degree) const{
	if (degree < lowestExpoent || degree >= coeffs.size() + lowestExpoent)
		return 0;
	return coeffs[degree - lowestExpoent];
}


void Poly::updateLast(){
	bool found = false;
	for (unsigned int i = lastNonZero + 1; i > 0 && !found; i--){
		if (0 != coeffs[i - 1]){
			lastNonZero = i - 1;
			found = true;
		}
	}
	isZeroPolynomial = !found;
	/* XXX: maybe resize since I know it is zero */
}


void Poly::updateFirst(){
	bool found = false;
	for (unsigned int i = firstNonZero; i <= lastNonZero && !found; i++){
		if (0 != coeffs[i]){
			firstNonZero = i;
			found = true;
		}
	}
	isZeroPolynomial = !found;
	/* XXX: maybe resize since I know it is zero */
}

void Poly::set(unsigned int degree, mpz_class coeff){
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
	if (0 == coeff){
		if (degree == lastNonZero) // if a zero was inserted into a_n
			updateLast();
		else if (degree == firstNonZero) // if the first nonzero coefficient became zero
			updateFirst();
	}else{
		if (isZeroPolynomial){
			firstNonZero = lastNonZero = degree;
			isZeroPolynomial = false;
		}else if (degree < firstNonZero)
			firstNonZero = degree;
		else if (degree > lastNonZero)
			lastNonZero = degree;
	}
}


unsigned int Poly::indexFirstNonZeroCoeff() const{
	if (isZeroPolynomial)
		throw NullPolynomialException();
	return firstNonZero;
}

mpz_class Poly::getFinalCoeff() const{
	if (isZeroPolynomial)
		throw NullPolynomialException();
	return coeffs[firstNonZero];
}

Poly::Poly(){
	lowestExpoent = 0;
	isZeroPolynomial = true;
	coeffs = std::vector<mpz_class>(DEFAULT_DEGREE + 1);
}

Poly::Poly(unsigned int maxDegree){
	lowestExpoent = 0;
	isZeroPolynomial = true;
	coeffs = std::vector<mpz_class>(maxDegree + 1);
}


Poly::Poly(unsigned int minDegree, unsigned int maxDegree){
	lowestExpoent = minDegree;
	isZeroPolynomial = true;
	coeffs = std::vector<mpz_class>(maxDegree - minDegree + 1);
}

Poly::Poly(unsigned int degree, mpz_class coeff){ // initialize a monomial
	lowestExpoent = 0;
	if ((isZeroPolynomial = (0 != coeff)))
		firstNonZero = lastNonZero = degree;
	coeffs = std::vector<mpz_class>(degree + 1);
	coeffs[degree] = coeff;
}

Poly::Poly(std::string strPoly){
	lowestExpoent = 0;
	isZeroPolynomial = true;
	coeffs = std::vector<mpz_class>(DEFAULT_DEGREE + 1);

	unsigned int exp;
	int signal;
	mpz_class coef;
	
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
			coef = matchCoeff.str();
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


Poly Poly::encode(mpz_class intValue){
	Poly p;
	unsigned int i = 0;
	for (unsigned int i = 0; intValue > 0; i++){
		mpz_class bit = intValue % 2;
		intValue = intValue / 2;
		p.set(i, bit);
	}
	return p;
}

Poly::~Poly(){
//	delete[] coeffs;
}

unsigned int Poly::degree() const{
	if (isZeroPolynomial)
		throw NullPolynomialException(); // degree is not defined to zero polynomials
	return lastNonZero;
}

bool Poly::isZero() const{
	return isZeroPolynomial;
}

void Poly::dump() const{

	std::cout << "degree = " << degree() << std::endl;
	std::cout << "first coefficient is a_ = " << indexFirstNonZeroCoeff() << std::endl;
	std::cout << "last coefficient is a_ = " << degree() << std::endl;
	for (unsigned int i = 0; i <= coeffs.size(); i++){
		std::cout << "coeffs[" << i << "] = " << coeffs[i] << std::endl;
	}

}

Poly operator+(const Poly& p, const Poly& q) {
	if (p.isZero())
		return q;
	if (q.isZero())
		return p;
	unsigned int d = std::max(p.degree(), q.degree());
	unsigned int first = std::min(p.indexFirstNonZeroCoeff(), q.indexFirstNonZeroCoeff());
	Poly r = Poly(first, d);
	for (unsigned int i = first; i <= d; i++){
		r.set(i, p.get(i) + q.get(i));
	}
	return r;
}

Poly operator-(const Poly& p, const Poly& q){
	unsigned int d = std::max(p.degree(), q.degree());
	unsigned int first = std::min(p.indexFirstNonZeroCoeff(), q.indexFirstNonZeroCoeff());
	Poly r = Poly(first, d);
	for (unsigned int i = first; i <= d; i++){
		r.set(i, p.get(i) - q.get(i));
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
		mpz_class pCoeff = p.get(i);
		if (0 != pCoeff){
			Poly tmp = Poly(d);
			for (unsigned int j = 0; j <= qDegree; j++){
				mpz_class qCoeff = q.get(j);
				tmp.set(i + j, pCoeff * qCoeff);
			}
			r += tmp;
		}
	}
	return r;
}

Poly operator*(const mpz_class& alpha, const Poly& p){
	unsigned int first = p.indexFirstNonZeroCoeff();
	unsigned int degree = p.degree();
	Poly result = Poly(first, degree);
	for (unsigned int i = first; i <= degree; i++){
		mpz_class coeff = p.get(i);
		result.set(i, coeff * alpha);
	}
	return result;
}

Poly operator*(const Poly& p, const mpz_class& alpha){
	return alpha * p;
}

Poly operator/(const Poly& p, const Poly& q) {
	Poly remainder = p;
	Poly quot = Poly();
	mpz_class coeff_p;
	mpz_class coeff_q;
	int tmp;
	
	while (remainder.degree() >= q.degree()){
		mpz_class div = remainder.getFinalCoeff() / q.getFinalCoeff();
		unsigned int coeffDegree = remainder.degree() - q.degree();
		Poly monomial = Poly(coeffDegree, div);
		remainder = remainder - monomial * q; //XXX: it would be much more efficient if I had a monomial class
		quot.set(coeffDegree, div);
	}
	return quot;
}

bool operator==(const Poly& p, const Poly& q) {
	if (p.isZero()){
		return q.isZero();
	}
	unsigned int pDegree = p.degree();
	unsigned int firstP = p.indexFirstNonZeroCoeff();
	// if they have diffent degrees or their first coefficients don't have same index
	if (pDegree != q.degree() || firstP != q.indexFirstNonZeroCoeff()){
		return false;
	}
	for (unsigned int i = firstP; i < pDegree; i++){
		if (p.get(i) != q.get(i))
			return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Poly& p) {
	try{
		unsigned int first = p.indexFirstNonZeroCoeff();
		unsigned int degree = p.degree();
		for (unsigned int i = first; i <= degree; i++){
			mpz_class coeff = p.get(i);
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
		os << " 0";
	}
	return os;
}

