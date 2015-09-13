#include <stdio.h>
#include <stdlib.h>

typedef struct {
	size_t width;
	size_t height;
	
	FILE *file_pointer;
} plotter_params_t;
