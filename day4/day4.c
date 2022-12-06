#include "../utils/utils.h"

int main(int argc, char** argv)
{
	if(parse_command_line(argc, argv) != 0) 
		return 1;

	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
  
    long sum = 0;
	while((read = getline(&line, &len, f)) != -1)
	{	
        // read contains the number of read characters + \n
		long s1, e1, s2, e2;

		char * endp;
		s1 = strtol(line, &endp, 10);
		e1 = strtol(endp+1, &endp, 10);
		s2 = strtol(endp+1, &endp, 10);
		e2 = strtol(endp+1, NULL, 10);

		switch (part)
		{
			case 1:
				if((s1 >= s2 && e1 <= e2) ||(s2 >= s1 && e2 <= e1)) sum++;
				break;
			case 2:
				if((s1 >= s2 && s1 <= e2) ||
					(e1 >= s2 && e1 <= e2) ||
					(s2 >= s1 && s2 <= e1) ||
					(e2 >= s1 && e2 <= e1)) sum++;
				break;
			default:
				break;
		}
	}

	printf("Result: %ld \n", sum);
	
	if(f != NULL) fclose(f);
	return 0;
}
