#include <stdio.h>
#include <stdlib.h>
#include <plotter.h>
#include <string.h>

#define VERSION "1.0"

static void
do_usage();

void truncate_file_name(char* fileName);

int main(int argc, char * const argv[], char * const envp[]) {

	if(strcmp(argv[1],"-h")==0 || strcmp(argv[1],"--help")==0){
		do_usage();
		exit(0);
	}

	if (strcmp(argv[1], "-V") == 0 || strcmp(argv[1], "--version") == 0) {
		fprintf(stdout, "Version %s\n", VERSION);
		exit(0);
	}

	if(argc < 3 || argc > 6){
		fprintf(stderr, "Cantidad de parametros incorrectos.\n");
		exit(1);
	}

	char * rule = argv[1];
	int int_rule = atoi(rule);

	if(int_rule <= 0 || int_rule > 255){
		fprintf(stderr, "No se encontro una regla valida.\n");
		exit(1);
	}

	char * dim = argv[2];
	int int_dim = atoi(dim);

	if (int_dim <= 0 || int_dim > 1080) {
		fprintf(stderr, "No se encontro una cantidad de celdas validas.\n");
		exit(1);
	}

	char* input_file_name = argv[3];
	char* output_file_name = (char*) malloc(200);
	char buf[200];
	strcpy(output_file_name, input_file_name);
	if(argc==6 && strcmp(argv[4],"-o")==0){
		output_file_name = argv[5];
	}else{
		truncate_file_name(output_file_name);
	}
	snprintf(buf, sizeof buf, "%s%s", output_file_name, ".pbm");
	strcpy(output_file_name,buf);

	FILE *output;
	FILE *input;

	if (!(input = fopen(input_file_name, "r"))) {
		fprintf(stderr, "No se pudo abrir el archivo de entrada.\n");
		exit(1);
	}

	if (!(output = fopen(output_file_name, "w"))) {
		fclose(input);
		fprintf(stderr, "No se pudo abrir el archivo de salida.\n");
		exit(1);
	}
	plotter_params_t params;
	params.output_file_pointer = output;
	params.input_file_pointer = input;
	params.width = int_dim;
	params.height = int_dim;
	params.rule = int_rule;
	plot(&params);
	return 0;
}

static void
do_usage()
{

	fprintf(stdout, "Uso:\n");
	fprintf(stdout, "autcel -h\n");
	fprintf(stdout, "autcel -V\n");
	fprintf(stdout, "autcel R N inputfile [-o outputprefix]\n");
	fprintf(stdout, "Opciones:\n");
	fprintf(stdout, "-h, --help\n");
	fprintf(stdout, "Imprime este mensaje.\n");
	fprintf(stdout, "-V, --version Da la version del programa\n");
	fprintf(stdout, "-o Prefijo de los archivos de salida.\n");
	fprintf(stdout, "Ejemplos:\n");
	fprintf(stdout, "autcel 30 80 inicial -o evolucion");
	fprintf(stdout, "Calcula la evolucion del automate Regla 30 ́\n");
	fprintf(stdout,
			"en un mundo unidimensional de 80 celdas, por 80 iteraciones.\n");
	fprintf(stdout, "El archivo de salida se llamara evolución.pbm\n");
	fprintf(stdout, "Si no se da un prefijo para los archivos de salida,\n");
	fprintf(stdout, "el prefijo sera ́el nombre del archivo de entrada.\n");
}

void truncate_file_name(char* fileName){
	int i = 0;
	while(fileName[i]!='\0' && i<100){
		if(fileName[i]=='.'){
			fileName[i]='\0';
			return;
		}
		i++;
	}
}

