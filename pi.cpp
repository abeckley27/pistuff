#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <gmp.h>

#define digits 1000

void factorial(int64_t n, mpf_t output) {
	mpf_t a1;
	mpf_init_set_si(output, 1.0);
	mpf_init(a1);
	for (int64_t i = 2; i <= n; i++) {
		mpf_set_si(a1, i); 
		mpf_mul(output, output, a1);
	}
	mpf_clear(a1);
}

void binary_split(int a, int b, mpz_t P, mpz_t Q, mpz_t R) {
	if (b == (a + 1)) {
		mpz_set_si(P, -(6*a - 5)*(2*a - 1)*(6*a - 1));
		mpz_set_si(Q, 10939058860032000 * pow(a, 3));
		mpz_set_si(R, 545140134*a + 13591409);
		mpz_mul(R, R, P);
	}
	else {
		int m = (a + b) / 2;
		mpz_t Pam, Qam, Ram, Pmb, Qmb, Rmb, Rterm2;
		mpz_init(Pam);
		mpz_init(Qam);
		mpz_init(Ram);
		mpz_init(Pmb);
		mpz_init(Qmb);
		mpz_init(Rmb);
		mpz_init(Rterm2);

		binary_split(a, m, Pam, Qam, Ram);
		binary_split(m, b, Pmb, Qmb, Rmb);

		mpz_mul(P, Pam, Pmb);
		mpz_mul(Q, Qam, Qmb);
		mpz_mul(R, Ram, Qmb);
		mpz_mul(Rterm2, Pam, Rmb);
		mpz_add(R, R, Rterm2);

		mpz_clear(Pam); mpz_clear(Qam); mpz_clear(Ram);
		mpz_clear(Pmb); mpz_clear(Qmb); mpz_clear(Rmb);
		mpz_clear(Rterm2);
	}

}


int main() {

	clock_t t0 = clock();
	mpf_set_default_prec(digits);

	mpz_t Pab, Qab, Rab;
	mpz_init(Pab);
	mpz_init(Qab);
	mpz_init(Rab);

	binary_split(1, 80, Pab, Qab, Rab);

	mpf_t pi, radical, Q, denom;
	mpf_init(pi);
	mpf_init(radical);
	mpf_init(Q);
	mpf_init(denom);

	mpf_sqrt_ui(radical, 10005);
	mpf_mul_ui(pi, radical, 426880);
	mpf_set_z(Q, Qab);
	mpf_mul(pi, pi, Q);
	mpz_mul_ui(Qab, Qab, 13591409);
	mpz_add(Qab, Qab, Rab);
	mpf_set_z(denom, Qab);
	mpf_div(pi, pi, denom);

	mpz_clear(Pab);
	mpz_clear(Qab);
	mpz_clear(Rab);

	std::ofstream f;
	std::string fname = "pi_" + std::to_string(digits) + ".txt";
	

	f.open(fname);
	f << std::fixed << std::setprecision(digits) << pi;
	f.close();

	std::cout << "Time: " << double(clock() - t0) / CLOCKS_PER_SEC << " s\n";

	return 0;
}
