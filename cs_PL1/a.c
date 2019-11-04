#include <stdio.h>

int factorial2(int n) {
	int i, m;
	m= 1;
	for (i= 1; i<=n; i++)
		m*= i;
	return m;
}

int main() {
	printf("%zu\n%zu\n", sizeof(char*), sizeof(short));
}
