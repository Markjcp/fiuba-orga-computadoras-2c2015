#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t width;
	size_t height;
	
	FILE *output_file_pointer;
	FILE *input_file_pointer;
} plotter_params_t;

void
plot(plotter_params_t* params);

unsigned int
convertRule(unsigned int number, char result[8]);
