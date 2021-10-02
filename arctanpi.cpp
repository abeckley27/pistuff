#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <cstdint>
#include <cstdio>
#include <gmp.h>

using namespace std;

int main(int argc, char* argv[]) {

	clock_t t0 = clock();
	int64_t digits = 2000;
	int64_t N = 1000000;
	int64_t M = 1000;

	cout << argc << endl;
	if (argc > 1) {
		N = stoi(argv[1]);
		M = stoi(argv[2]);
	}

	string fname = "pi_" + to_string(digits) + ".txt";
	digits = digits * 1.442 * log(10);
	mpf_set_default_prec(digits);
	
	mpf_t x1, x2, one, two;
	int64_t k;

	//cout << "Initialize x1 & x2\n";
	mpf_init_set_si(x1, 1.0);
	mpf_init_set_si(x2, -1.0);
	mpf_init_set_si(one, 1.0);
	
	cout << "Start summing sequence\n";
	
	for (k = 1; k < N; k++) {
		mpf_t temp;
		mpf_init_set_si(temp, 2 * k + 1);
		mpf_div(temp, one, temp);
		if ( k % 2 ) mpf_sub(x1, x1, temp);
		else mpf_add(x1, x1, temp);
		mpf_clear(temp);
	}

	int64_t n1 = 2 * N + 1;
	mpf_t* partsum_array = new mpf_t[M];
	
	cout << "Time: " << double(clock() - t0) / CLOCKS_PER_SEC << " s\n";
	cout << "start averaging partial sums: \n";

	for (k = N; k < N + M; k++) {
		mpf_t temp;
		mpf_init_set_si(temp, 2 * k  + 1);
		mpf_init(partsum_array[k-N]);

		mpf_div(temp, one, temp);
		if ( k % 2 ) mpf_sub(x1, x1, temp);
		else mpf_add(x1, x1, temp);
		mpf_set(partsum_array[k-N], x1);
		mpf_clear(temp);
	}

	for (int j = 0; j < M - 1; j++) {
		for (k = 0; k < M - 1 - j; k++) {
			mpf_add(partsum_array[k], partsum_array[k], partsum_array[k+1]);
			mpf_div_ui(partsum_array[k], partsum_array[k], 2);
		}
	}

	mpf_mul_ui(x1, partsum_array[0], 4);
	ofstream f;
	f.open(fname);
	f << setprecision(digits) << x1 << endl;
	f.close();

	cout << "Time: " << double(clock() - t0) / CLOCKS_PER_SEC << " s\n";

	return 0;
}
