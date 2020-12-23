#include <stdio.h>

#include "resman.h"

int main() {
	struct resman *res = init_resman();

	const int N = 10;
	for(int i = 0; i < N; i++) {
		float *p = malloc(sizeof(float));
		dodaj_resman(res, p, free);
	}

	FILE *p = fopen("/dev/zero", "r");
	dodaj_resman(res, p, (void(*)(void*))fclose);

	oslobodi_resman(res);
}
