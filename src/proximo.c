#include <proximo.h>

char decideNextChar(unsigned int previous, unsigned int current,
		unsigned int next, char rule[8]) {
	char result = '0';
	if (!previous && !current && !next) { //	000
		result = rule[7];
	}
	if (!previous && !current && next) { //	001
		result = rule[6];
	}
	if (!previous && current && !next) { //	010
		result = rule[5];
	}
	if (!previous && current && next) { //	011!previous && current && next
		result = rule[4];
	}
	if (previous && !current && !next) { //	100
		result = rule[3];
	}
	if (previous && !current && next) { //	101
		result = rule[2];
	}
	if (previous && current && !next) { //	110
		result = rule[1];
	}
	if (previous && current && next) { //		111
		result = rule[0];
	}
	return result;
}

unsigned char proximo(unsigned char *a, unsigned int i, unsigned int j,
		unsigned char regla, unsigned int N) {

	char rule[8];
	if(convertRule(regla,rule)==-1){
		fprintf(stderr, "Incorrect rules\n");
		exit(1);
	}

	unsigned int previousIndex = 0;
	unsigned int currentIndex = j;
	unsigned int nextIndex = 0;
	if (j == 0) {
		previousIndex = N - 1;
	} else {
		previousIndex = j - 1;
	}
	if (j == N -1) {
		nextIndex = 0;
	} else {
		nextIndex = j + 1;
	}
	return decideNextChar(a[(i - 1) * N + previousIndex] == '1',
			a[(i - 1)* N + currentIndex] == '1', a[ (i - 1)*N + nextIndex] == '1', rule);
}
