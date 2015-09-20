#include <stdio.h>
#include <stdlib.h>
#include <plotter.h>

int main(int argc, char * const argv[], char * const envp[]) {
	FILE *output;
	FILE *input;

	if (!(input = fopen("entrada.txt", "r"))) {
		fprintf(stderr, "cannot open input file.\n");
		exit(1);
	}

	if (!(output = fopen("salida.pbm", "w"))) {
		fprintf(stderr, "cannot open output file.\n");
		exit(1);
	}
	plotter_params_t params;
	params.output_file_pointer = output;
	params.input_file_pointer = input;
	params.width = 800;
	params.height = 600;
	params.rule = 126;
	plot(&params);
	return 0;
}
