#include "utils.h"

FILE *f = NULL;
int part = 0;

inline int parse_command_line(int argc, char ** argv)
{
	//read input parameters
	if(argc < 2){
		printf("you must specify the input file path \n");
		return 1;
	}

	char* input_file = argv[1];
	printf("input selected %s \n", input_file);
	
	if(argc < 3){
		printf("you must specify the part number 1 or 2 \n");
		return 1;
	}

	part = atoi(argv[2]);
	if(part < 1 || part > 2){
		printf("Invalid part option %d. 1 or 2 expected \n", part);
		return 1;
	}

	f = fopen(input_file, "r");
	if(f == NULL){
		printf("Could not open file %s \n", input_file);
		return 1;
	}

	return 0;
}
