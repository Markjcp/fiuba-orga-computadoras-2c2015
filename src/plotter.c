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
	fprintf(params->file_pointer, "P2\n");
	fprintf(params->file_pointer, "%u ", (unsigned) params->width);
	fprintf(params->file_pointer, "%u\n", (unsigned) params->height);

	size_t width = params->width;
	size_t height = params->height;
	int i, j = 0;

	for(i = 0; i< height; i++)
	{
		for (j = 0; j < width; j++)
		{
			int black_or_white = 0;
			if( j % 2 == 0){
				black_or_white = 1;
			}
			fprintf(params->file_pointer, "%i", black_or_white);
			if(j < width -1){
				fprintf(params->file_pointer, " ");
			}
		}
		if(i< height -1){
			fprintf(params->file_pointer, "\n");
		}
	}
	if(fclose(params->file_pointer)){
		fprintf(stderr, "cannot close output file.\n");
		exit(1);
	}
}
