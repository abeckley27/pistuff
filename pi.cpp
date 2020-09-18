#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <gmp.h>

using namespace std;
#define digits 10000

void factorial(int64_t n, mpf_t output) {
	mpf_t a1;
	mpf_init_set_si(output, 1.0);
	mpf_init(a1);
	for (int64_t i = 2; i <= n; i++) {
		mpf_set_si(a1, i); 
		mpf_mul(output, output, a1);
	}
}

void term(int64_t n, mpf_t x, mpf_t output) {
	mpf_t a2, a3, a4;
	mpf_init_set_si(a2, 1.0);
	mpf_init(a3);
	mpf_init(a4);
	if (n%2) { mpf_set_si(a3, -1.0); }
	else { mpf_set_si(a3, 1.0); }

	factorial(2*n+1, a2);
	mpf_div(a2, a3, a2);

	mpf_pow_ui(a4, x, unsigned(2*n+1));
	mpf_mul(output, a4, a2);
}

void sin(mpf_t x1, mpf_t x2, int64_t n) {
	mpf_set_si(x2, 0.0);
	for (int64_t i = 0; i < n; i++) {
		mpf_t temp;
		mpf_init(temp);
		term(i, x1, temp);
		mpf_add(x2, x2, temp);
	}
}

void chud_term(int64_t k, mpf_t output) {

	//cout << "Check sign\n";
	mpf_t a6k, a2, sign;
	int64_t q = -2 * int64_t(k%2) + 1;
	mpf_init_set_si(sign, q);

	//cout << "Initialize numerator terms\n";

	mpf_init(a6k);
	factorial(6*k, a6k);
	int64_t b2 = 545140134 * k + 13591409;
	mpf_init_set_si(a2, b2);
	mpf_mul(a2, a2, a6k);
	mpf_mul(a2, a2, sign);

	//cout << "Initialize denominator terms\n";

	mpf_t a3k, ak3, a4;
	mpf_init(a3k);
	mpf_init(ak3);

	//cout << "Compute factorials\n";

	factorial(3*k, a3k);
	factorial(k, ak3);
	mpf_pow_ui(ak3, ak3, 3);
	mpf_init_set_si(a4, 262537412640768000);
	mpf_pow_ui(a4, a4, k);
	
	mpf_t denom;
	mpf_init_set_si(denom, 1.0);
	mpf_mul(denom, denom, a3k);
	mpf_mul(denom, denom, ak3);
	mpf_mul(denom, denom, a4);
	mpf_div(output, a2, denom);
}

int main() {

	clock_t t0 = clock();
	const int64_t M = int64_t(digits * (3.333));
	const int64_t N = int64_t(M / 14);
	
	mpf_set_default_prec(M);

	ofstream f;
	string fname = "pi_" + to_string(digits) + ".txt";
	f.open(fname);

	mpf_t x1, x2, x3, x4, x5, x6, one;

	cout << "Initialize x1 & x2\n";
	mpf_init_set_si(x1, 426880);
	mpf_init_set_si(x2, 10005);
	mpf_init_set_si(one, 1.0);
	mpf_sqrt(x2, x2);
	mpf_mul(x1, x1, x2);

	cout << "Initialize x4\n";
	mpf_init_set_si(x4, 0);
	
	cout << "Start summing sequence\n";
	
	for (int64_t k = 0; k < N; k++) {
		mpf_t temp;
		mpf_init_set_si(temp, 1);
		chud_term(k, temp);
		mpf_add(x4, x4, temp);
	}

	mpf_t pi;
	mpf_init(pi);
	mpf_div(pi, x1, x4);

	f << setprecision(M-2) << pi << endl;
	f.close();

	cout << "Time: " << double(clock() - t0) / CLOCKS_PER_SEC << " s\n";

	return 0;
}
