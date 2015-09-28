/*
 * plotter.c
 *
 *  Created on: 13 de set. de 2015
 *      Author: marcos
 */
#include <stdio.h>
#include <stdlib.h>
#include <plotter.h>
#include <proximo.h>

void plot(plotter_params_t* params) {
	fprintf(params->output_file_pointer, "P1\n");
	fprintf(params->output_file_pointer, "%u ", (unsigned) params->width);
	fprintf(params->output_file_pointer, "%u\n", (unsigned) params->height);

	size_t width = params->width;
	size_t height = params->height;
	int i, j = 0;

	char first_line[width * 2];
	unsigned char matrix[height][width];
	if (fgets(first_line, width * 2, params->input_file_pointer) == NULL) {
		fprintf(stderr, "Archivo de entrada incorrecto");
		fclose(params->output_file_pointer);
		fclose(params->input_file_pointer);
		exit(1);
	}

	i=0;
	fprintf(stdout, "Leyendo estado inicial...\n");
	for (j = 0; j < width * 2; j += 2) {
		fprintf(params->output_file_pointer, "%c", first_line[j]);
		matrix[0][i] = first_line[j];
		if (j < width * 2 - 2) {
			fprintf(params->output_file_pointer, " ");
		}
		i++;
	}
	fprintf(params->output_file_pointer, "\n");

	fprintf(stdout, "Grabando archivo de salida...\n");
	for (i = 1; i < height; i++) {
		for (j = 0; j < width; j++) {
			char to_print = '0';

			to_print = proximo(&matrix[0][0], i, j,params->rule, (unsigned int)width);
			//printf("Fila %i Columna %i Valor %c",i,j,to_print);
			fprintf(params->output_file_pointer, "%c",to_print);
			matrix[i][j] = to_print;
			if (j < width - 1) {
				fprintf(params->output_file_pointer, " ");
			}
		}
		if (i < height) {
			fprintf(params->output_file_pointer, "\n");
		}
	}
	if (fclose(params->output_file_pointer)) {
		fprintf(stderr, "No se pudo cerrar archivo.\n");
		exit(1);
	}
	if (fclose(params->input_file_pointer)) {
		fprintf(stderr, "No se pudo cerrar archivo.\n");
		exit(1);
	}
	fprintf(stdout, "Listo.\n");
}

unsigned int convertRule(unsigned char number, char result[8]) {
	
	unsigned int i = 0;
	for (i = 0; i < 8; i++) {
		result[i] = '0';
	}

	int rem;
	unsigned int size = 7;
	while (number != 0) {
		rem = number % 2;
		number /= 2;
		result[size] = rem + '0';
		size--;
	}
	result[8] = '\0';
	return 1;
}



