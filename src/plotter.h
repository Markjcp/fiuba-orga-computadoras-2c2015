#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t width;
	size_t height;
	unsigned char rule;
	
	FILE *output_file_pointer;
	FILE *input_file_pointer;
} plotter_params_t;

void
plot(plotter_params_t* params);

unsigned int
convertRule(unsigned char number, char result[8]);

char
decideNextChar(unsigned int previous, unsigned int current,unsigned int next, char result[8]);

unsigned char next_portable
(unsigned char *a, unsigned int i, unsigned int j, unsigned char regla, unsigned int N);



