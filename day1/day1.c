#include "../utils/utils.h"

long running_sum = 0;
long max_sum[3];

void updateSums()
{
	if(max_sum[2] < running_sum)
	{
		max_sum[0] = max_sum[1];
		max_sum[1] = max_sum[2];
		max_sum[2] = running_sum;
	}
	else if (max_sum[1] < running_sum)
	{
		max_sum[0] = max_sum[1];
		max_sum[1] = running_sum;
	}
	else if(max_sum[0] < running_sum)
	{
		max_sum[0] = running_sum;
	}
}

int main(int argc, char** argv)
{
	if(parse_command_line(argc, argv) != 0) 
		return 1;

	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
	
	memset(max_sum, 0, 3*sizeof(long));
	long largest_sum = 0;
	while((read = getline(&line, &len, f)) != -1)
	{	
		if(strcmp(line, " ") == 0 || atol(line) == 0){
			updateSums();
			if (largest_sum < running_sum) largest_sum = running_sum;
			running_sum = 0;
			continue;
		}
		running_sum += atol(line);
	}

	updateSums();
	if(part ==1)
		printf("Max number of calories: %ld \n", largest_sum);
	else
		printf("Max number of calories: %ld \n",max_sum[0] + max_sum[1]+ max_sum[2]);
	
	if(f != NULL) fclose(f);
	return 0;
}
