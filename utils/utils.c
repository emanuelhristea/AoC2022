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

static void VectorResize(Vector* self)
{
	// resize if needed
	if (self->count < self->limit) return;
	
	// first element
	if(self->limit == 0) self->limit++;
	else self->limit = ceil(self->limit * GROWTH_FACTOR);

	self->data = realloc(self->data, sizeof(void*) * self->limit);  
}

void VectorPushBack(Vector* self, void* data)
{
	VectorResize(self);
    self->data[self->count++] = data;
}

void VectorPopBack(Vector * self, void * data)
{
	self->data[--self->count] = NULL;
}

void VectorRemoveAt(Vector* self, int index)
{
    if (index < 0 || index >= self->count) return;
    
	// swap items until last
	for(int i = index; i < self->count-1; ++i)
		self->data[i] = self->data[i+1];

	// then remove the last item
	self->data[self->count - 1] = NULL;
	self->count --; 
}

void VectorFree(Vector* self)
{
    if (self->data)
    {
        free(self->data);
        self->data = NULL;
    }
}

void VectorInit(Vector* vector)
{
    vector->limit = INITIAL_CAPACITY;
    vector->count = 0;
    vector->push_back = VectorPushBack;
	vector->pop_back = VectorPopBack;
    vector->remove_at = VectorRemoveAt;
    vector->free = VectorFree;
    vector->data = malloc(sizeof(void*) * vector->limit);
}
