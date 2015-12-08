#include"poly.h"
#include<string>
#include<regex>


using namespace std;

const unsigned int N = 52;
vector<Poly> polys(N);

inline unsigned int index(char charRead){
	return charRead - 'a';
}

void showPolynomial(char letter){
	unsigned int i = index(letter);
	cout << letter << "(x) = " << polys[i] << endl;
}

int main(){
	string expLetter = "\\s*([a-z])\\s*";
	string expMonomial = "\\s*\\d+(\\*?x\\^\\d+)?";
	string expPoly = "[+-]?" + expMonomial + "(\\s*[+-]" + expMonomial + ")*";
	string expPlus = "\\s*\\+\\s*";
	string expMinus = "\\s*\\-\\s*";
	string expMult = "\\s*\\*\\s*";
	string expDiv = "\\s*\\/\\s*";
	string expCmdList = "\\s*[Ll][Ii][Ss][Tt]\\s*";
	string line;
	smatch matches;

	do{
		cout << ">> ";
		getline (cin, line);
		// if it's a definition of a new polynomial
		if (regex_match (line, matches, regex(expLetter + ":=\\s*(" + expPoly + ")") )){
			unsigned int i = index(matches[1].str().at(0));
			polys[i] = Poly(matches[2]); 
		// if it's a definition of a polynomial from a encoding of a integer
		}else if (regex_match (line, matches, regex(expLetter + ":=\\s*encode\\s*([0-9]+)") )){
			unsigned int i = index(matches[1].str().at(0));
			mpz_class intVal = mpz_class(matches[2].str());
			polys[i] = Poly::encode(intVal); 
		// if it's a sum, for instance:  c = a + b
		}else if (regex_match (line, matches, regex(expLetter + "=" + expLetter + expPlus + expLetter) )){
			unsigned int i0 = index(matches[1].str().at(0));
			unsigned int i1 = index(matches[2].str().at(0));
			unsigned int i2 = index(matches[3].str().at(0));
			polys[i0] = polys[i1] + polys[i2];
			showPolynomial(matches[1].str().at(0));
		}else if (regex_match (line, matches, regex(expLetter + "=" + expLetter + expMinus + expLetter) )){
			unsigned int i0 = index(matches[1].str().at(0));
			unsigned int i1 = index(matches[2].str().at(0));
			unsigned int i2 = index(matches[3].str().at(0));
			polys[i0] = polys[i1] - polys[i2];
			showPolynomial(matches[1].str().at(0));
		}else if (regex_match (line, matches, regex(expLetter + "=" + expLetter + expMult + expLetter) )){
			unsigned int i0 = index(matches[1].str().at(0));
			unsigned int i1 = index(matches[2].str().at(0));
			unsigned int i2 = index(matches[3].str().at(0));
			polys[i0] = polys[i1] * polys[i2];
			showPolynomial(matches[1].str().at(0));
		}else if (regex_match (line, matches, regex(expLetter + "=" + expLetter + expDiv + expLetter) )){
			unsigned int i0 = index(matches[1].str().at(0));
			unsigned int i1 = index(matches[2].str().at(0));
			unsigned int i2 = index(matches[3].str().at(0));
			polys[i0] = polys[i1] / polys[i2];
			showPolynomial(matches[1].str().at(0));
		}else if (regex_match (line, matches, regex(expLetter + "\\?\\s*") )){
			showPolynomial(matches[1].str().at(0));
		}else if (regex_match (line, matches, regex(expCmdList))){
			for (char l = 'a'; l <= 'z'; l++){
				showPolynomial(l);
			}
		}else{
			cout << "ERROR: command not recognized" << endl;
		}
	}while(line != "exit");

	cout << "OUT" << endl;

	for (unsigned int i = 0; i < N; i++){
		cout << "polys[" << i << "] = " << polys[i] << endl;
	}

	return 0;
}
