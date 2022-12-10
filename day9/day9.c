#include "../utils/utils.h"

#define SIZE 2000
#define STARTX 1000
#define STARTY 1000

void print_visited();

typedef struct point{
    int x;
    int y;
}Point;

Point Head = {STARTX, STARTY};
Point Tail[9] = {
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY},
    {STARTX, STARTY}
};

bool visited[SIZE][SIZE] = {0};

int count = 0;

Point advance(Point P, char dir)
{
    if(dir == 'U') P.y--;
    if(dir == 'D') P.y++;
    if(dir == 'R') P.x++;
    if(dir == 'L') P.x--;
    return P;
}

int distance(Point P1, Point P2)
{
    int dx = P1.x - P2.x; 
    int dy = P1.y - P2.y;
    return dx * dx + dy * dy;
}

char direction(Point P1, Point P2)
{
    if(P1.x == P2.x) return P1.y > P2.y ? 'D' : 'U';
    if(P1.y == P2.y) return P1.x > P2.x ? 'R' : 'L';
    return 0;
}

void update_visited(Point p)
{
    if(visited[p.x][p.y] != 1)
    {
        count++;
        visited[p.x][p.y] = 1;
    }
}

Point diag_move(Point ahead, Point behind)
{
    int dx = ahead.x - behind.x; 
    int dy = ahead.y - behind.y;

    /* special case for 2x2 distance 
      . . y  ->  . . y
      . . .  ->  . x .
      x . .  ->  . . .
    */
    if(dx*dx + dy*dy == 8){
        behind.x += dx/2;
        behind.y += dy/2;
        return behind;
    }

    /* L 2x1 distance
      . y .  ->  . y .    . . x  ->  . . .
      . . .  ->  . x .    y . .  ->  y x .
      x . .  ->  . . .    . . .  ->  . . .
    */
    if(dx*dx + dy*dy == 5)
    {
        if(dx*dx == 1) {
            behind.x += dx;
            behind.y += dy/2;
            return behind;
        }

        if(dy*dy == 1){
            behind.y += dy;
            behind.x += dx/2;
            return behind;
        }
    }

    return behind;
}

void move(Point* head, char dir, int steps, Point* tail, int n)
{
    for (int i = 0; i < steps; ++i)
    {
        *head = advance(*head,dir);

        Point* ahead = head;
        Point* behind = tail;
        int j = 0;
        do
        {
            switch (distance(*ahead, *behind))
            {
                case 0: // overlap
                case 1: // next      
                case 2: // diagonal
                    break;
                case 4: // colinear
                    *behind = advance(*behind,  direction(*ahead, *behind));
                    break;
                case 5: // L 2 x 1  distance or 2x2 distance
                case 8:
                    *behind = diag_move(*ahead, *behind);
                    break;
            }

            ahead = behind;
            behind = behind + 1;
            j++;
            
        }while(j < n);
        update_visited(*(ahead));
    }
}

void print_visited()
{
    for(int i = 0; i < SIZE;++i){
        for(int j = 0; j < SIZE; ++j){
            char c = visited[j][i] ?  '#' : '.';
            printf("%c",c);
        }

        printf("\n");    
    }
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t len;

    int tail_size = part == 1 ? 1 : 9;
    memset(visited, 0, sizeof(visited));
    while ((read = getline(&line, &len, f)) != -1)
    {
        char dir;
        int steps = 0;
        int ret = sscanf(line,"%c%d",&dir, &steps);
        if(ret != 2) continue;
        move(&Head, dir, steps, Tail, tail_size);
    }

    print_visited();
    printf("Result %d\n", count);

    if(f != NULL) fclose(f);
    return 0;
}