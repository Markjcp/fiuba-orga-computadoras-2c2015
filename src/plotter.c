/*
 * plotter.c
 *
 *  Created on: 13 de set. de 2015
 *      Author: marcos
 */
#include <stdio.h>
#include <stdlib.h>
#include <plotter.h>

void
plot(plotter_params_t* params)
{
	fprintf(params->output_file_pointer, "P2\n");
	fprintf(params->output_file_pointer, "%u ", (unsigned) params->width);
	fprintf(params->output_file_pointer, "%u\n", (unsigned) params->height);

	size_t width = params->width;
	size_t height = params->height;
	int i, j = 0;

	char first_line[width*2];
	if (fgets(first_line,width*2,params->input_file_pointer) == NULL){
		fprintf(stderr, "Incorrect input file\n");
		exit(1);
	}

	for (j = 0; j < width*2; j += 2) {
		fprintf(params->output_file_pointer, "%c", first_line[j]);
		if (j < width*2 - 2) {
			fprintf(params->output_file_pointer, " ");
		}
	}
	fprintf(params->output_file_pointer, "\n");

	for(i = 0; i< height -1; i++)
	{
		for (j = 0; j < width; j++)
		{
			int black_or_white = 0;
			if( j % 2 == 0){
				black_or_white = 1;
			}
			fprintf(params->output_file_pointer, "%i", black_or_white);
			if(j < width -1){
				fprintf(params->output_file_pointer, " ");
			}
		}
		if(i< height -1){
			fprintf(params->output_file_pointer, "\n");
		}
	}
	if(fclose(params->output_file_pointer)){
		fprintf(stderr, "cannot close output file.\n");
		exit(1);
	}
	if (fclose(params->input_file_pointer)) {
		fprintf(stderr, "cannot close input file.\n");
		exit(1);
	}
}

unsigned int convertRule(unsigned int number, char result[8]) {
	if(number > 255){
		return -1;
	}
	unsigned int i= 0;
	for(i=0; i<8;i++){
		result[i]='0';
	}

	int rem;
	unsigned int size = 7;
	while (number!=0)
	{
		rem=number%2;
		number/=2;
		result[size]=rem+'0';
		size--;
	}
	result[8] = '\0';
	return 1;
}

