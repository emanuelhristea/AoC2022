#include "../utils/utils.h"

inline int get_priority(char c)
{
	return 1 + (c >= 'a' ? c - 'a' : 26 + c - 'A');
}

int main(int argc, char** argv)
{
	if(parse_command_line(argc, argv) != 0) return 1;

	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
  
	bool map[MAX_CHAR] = {0};
	bool maps[3][MAX_CHAR] = {0};

	long sum = 0;
	int count = 0;
	
	while((read = getline(&line, &len, f)) != -1)
	{	
		if(part == 1)
		{
			memset(map, false , MAX_CHAR*sizeof(bool));	
			// the number of read characters is read -1 since we also have \n in there
			ssize_t half = (read - 1)/2;
			for(int i =0; i < half; i++) map[(int)line[i]] = true;
			
			for(int i = half; i < read -1; i++){
				if(map[(int)line[i]] == true) continue;
				sum += get_priority(line[i]);
				break;
			} 
		} 
		else if(part ==2)
		{
			memset(maps[count%3], false , MAX_CHAR*sizeof(bool));	 
			
			for(int i =0; i < read - 1; i++)
				maps[count%3][(int)line[i]] = true;
			// compute prio at 3rd line
			if(count % 3 == 2) {
				for(int c = 0; c < MAX_CHAR; ++c ){
					if(maps[0][c] == false || maps[1][c] == false || maps[2][c] == false ) continue;
					sum += get_priority((char)c);
				}	
			}

			++count; 
		}
	}

	printf("Result: %ld \n", sum);

	if(f != NULL) fclose(f);
	return 0;
}
