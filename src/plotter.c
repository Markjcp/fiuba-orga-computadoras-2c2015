/*
 * plotter.c
 *
 *  Created on: 13 de set. de 2015
 *      Author: marcos
 */
#include <stdio.h>
#include <stdlib.h>
#include "plotter.h"

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
		fprintf(stderr, "Incorrect input file\n");
		exit(1);
	}

	i=0;
	for (j = 0; j < width * 2; j += 2) {
		fprintf(params->output_file_pointer, "%c", first_line[j]);
		matrix[0][i] = first_line[j];
		if (j < width * 2 - 2) {
			fprintf(params->output_file_pointer, " ");
		}
		i++;
	}
	fprintf(params->output_file_pointer, "\n");

	for (i = 1; i < height; i++) {
		for (j = 0; j < width; j++) {
			char to_print = '0';

			if(params->mips_impl){
				to_print = proximo(&matrix[0][0], i, j,params->rule, (unsigned int)width);
			}else{
				to_print = next_portable(&matrix[0][0], i, j,params->rule, (unsigned int)width);

			}

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
		fprintf(stderr, "cannot close output file.\n");
		exit(1);
	}
	if (fclose(params->input_file_pointer)) {
		fprintf(stderr, "cannot close input file.\n");
		exit(1);
	}
}

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

unsigned char next_portable(unsigned char *a, unsigned int i, unsigned int j,
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
	if (j == N) {
		nextIndex = 0;
	} else {
		nextIndex = j + 1;
	}
	return decideNextChar(a[(i - 1) * N + previousIndex] == '1',
			a[(i - 1)* N + currentIndex] == '1', a[ (i - 1)*N + nextIndex] == '1', rule);
}

