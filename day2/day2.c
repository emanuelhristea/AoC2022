#include "../utils/utils.h"

int main(int argc, char** argv)
{
	if(parse_command_line(argc, argv) != 0) 
		return 1;

	char * line = NULL;
	size_t len = 0;
	ssize_t read = 0;
    /*1 Rock, 2 Paper, 3 Scissors
          1 2 3
        1 3 0 6
        2 6 3 0
        3 0 6 3
    
    */
    int rock_paper_scissors[3][3] = { 
        {3, 0 ,6}, 
        {6, 3, 0}, 
        {0, 6 ,3} 
    };

    /* choose option based on outcome and opponent input
          1 2 3
        l 3 1 2
        d 1 2 3
        w 2 3 1
    */
    int outcomes[3][3] = { 
        {2, 0, 1}, 
        {0, 1 ,2}, 
        {1, 2 ,0}
    };
	
    long sum = 0;
	while((read = getline(&line, &len, f)) != -1)
	{	
        int opponent = line[0] - 'A';
        int my_move = 0;
        if(part == 1)
        {
            my_move = line[2] -'X';
        }
        else
        {
            int desired_outcome = line[2] -'X';
            my_move = outcomes[desired_outcome][opponent];      
        }
    
        int outcome = rock_paper_scissors[my_move][opponent];
        sum += my_move + 1 +  outcome;
	}

	printf("Total score: %ld \n", sum);
	
	if(f != NULL) fclose(f);
	return 0;
}
