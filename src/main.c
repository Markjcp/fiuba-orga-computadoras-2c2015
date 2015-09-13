#include <stdio.h>
#include <stdlib.h>
#include <plotter.h>

int main(int argc, char * const argv[], char * const envp[]) {
	FILE *output;
	if (!(output = fopen("salida.pbm", "w"))) {
		fprintf(stderr, "cannot open output file.\n");
		exit(1);
	}
	plotter_params_t params;
	params.file_pointer = output;
	params.width = 24;
	params.height = 7;
	plot(&params);
	return 0;
}
