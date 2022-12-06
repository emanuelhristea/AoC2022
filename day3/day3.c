#include "../utils/utils.h"

int get_priority(char c)
{
	return 1 + (c >= 'a' ? c - 'a' : 26 + c - 'A');
}

int main(int argc, char** argv)
{
	if(parse_command_line(argc, argv) != 0) 
		return 1;

	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
  
    long sum = 0;
	char maps[3][256] = {0};
	int count = 0;
	while((read = getline(&line, &len, f)) != -1)
	{	
		if(part == 1)
		{
			char map[256] = {0};
			// the number of read characters is read -1 since we also have \n in there
			ssize_t half = (read-1)/2;
			for(int i =0; i < half; i++) map[(int)line[i]] = 1;
			
			for(int i = half; i < read -1; i++){
				if(map[(int)line[i]] == 0) continue;
				sum += get_priority(line[i]);
				break;
			} 
		} 
		else if(part ==2)
		{
			memset(maps[count%3], 0 , 256);	 
			for(int i =0; i < read-1; i++) maps[count%3][(int)line[i]] = 1;
			// compute prio at 3rd line
			if(count % 3 == 2) {
				for(int c = 0; c < 256; ++c ){
					if(maps[0][c] == 0 || maps[1][c] == 0 || maps[2][c] == 0 ) continue;
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
