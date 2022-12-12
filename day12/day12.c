#include "../utils/utils.h"

void print_map(int x, int y, char map[x][y], char* fmt)
{
    for(int i = 0; i<x; ++i)
    {
        for(int j = 0; j<y; ++j)
            printf(fmt, map[i][j]);
        
        printf("\n");
    }
}

void update(int rows, int cols, char map[rows][cols], char costs[rows][cols], int x,  int y, int Ex, int Ey)
{
    if(x == Ex && y == Ey) return;
    // up
    if(x > 0 && map[x][y] - map[x-1][y] >= -1 && costs[x-1][y] ==-1) {
        costs[x-1][y] = costs[x][y] +1;
        update(rows, cols, map, costs, x-1 ,y, Ex, Ey);
    }

    // down
    if(x < rows-1 && map[x][y] - map[x+1][y] >= -1 && costs[x+1][y] ==-1) {
        costs[x+1][y] = costs[x][y] +1;
        update(rows, cols, map, costs, x+1 ,y, Ex, Ey);
    }

    // left
    if(y > 0 &&  map[x][y] - map[x][y-1] >= -1 && costs[x][y-1] == -1) {
        costs[x][y-1] = costs[x][y] +1;
        update(rows, cols, map, costs, x ,y-1, Ex, Ey);
    }

    // right
    if(y < cols-1 && map[x][y] - map[x][y+1] >= -1 && costs[x][y+1] == -1) {
        costs[x][y+1] = costs[x][y] +1;
        update(rows, cols, map, costs, x ,y+1, Ex, Ey);
    }
    //dead end
    costs[x][y]--;
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t len;

    int ROWS = 0; int COLS = 0;
    while ((read = getline(&line, &len, f)) != -1)
    {
        //find the size for the input
        int size = line[read-1] == '\n' ? read -1 : read;
        if(COLS<size) COLS = size;
        ROWS++;
    }

    rewind(f);
    char map[ROWS][COLS]; memset(map,0, sizeof(map));
     
    int Sx = 0;
    int Sy = 0;
    int Ex = 0;
    int Ey = 0;
    int i =0;
    while ((read = getline(&line, &len, f)) != -1)
    {
        int size = line[read-1] == '\n' ? read -1 : read;
        for(int j =0 ;j < size; ++j)
        {
            map[i][j] = line[j];
            if(line[j] == 'S') {
                Sx = i; 
                Sy = j;
                map[i][j] = 'a';
            }
            if(line[j] == 'E') {
                Ex = i; 
                Ey = j;
                map[i][j] = 'z';
            }
        }
        i++;    
    }

    print_map(ROWS, COLS, map, "%c");
    /* memoize the partial costs to reach the end form x,y. -1 means no solution */
    char costs[ROWS][COLS]; memset(costs,-1, sizeof(costs));
    costs[Sx][Sy] = 0;
    // start from the end and compute the optimal path
    update(ROWS, COLS, map, costs, Sx, Sy, Ex, Ey);
    print_map(ROWS, COLS, costs, "%02d ");

    if(part == 1) 
    {
        printf("Result %d\n", 0);
    }
    
    if(part == 2)
    {
        // find the product of all the modulo factors
        printf("Result %d\n", 0);
    } 

    if(f != NULL) fclose(f);
    return 0;
}