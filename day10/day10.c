#include "../utils/utils.h"

#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 6

typedef struct
{
    int X;
    int cycle;
}CPU;

/*
Cycle   1 -> ######################################## <- Cycle  40
*/
bool screen[SCREEN_HEIGHT][SCREEN_WIDTH] = {0};
CPU cpu = {1, 0};
int signal = 0;

bool test_cycle(int c)
{
    return c == 20 || c == 60 || c == 100 || c == 140 || c == 180 || c == 220;
}

int get_signal()
{
    if(test_cycle(cpu.cycle)) return cpu.cycle*cpu.X;
    return 0;
}

void draw_pixel()
{
    int row = cpu.cycle/SCREEN_WIDTH;
    int col = cpu.cycle - row*SCREEN_WIDTH;
    // we are still on the prev row on the last column
    if(col == 0) --row, col = 40; 
    --col;
    
    screen[row][col] = col == cpu.X || col == cpu.X +1 || col == cpu.X-1;
}

void draw_screen()
{
    for(int i = 0; i < SCREEN_HEIGHT; ++i )
    {
        for(int j = 0; j < SCREEN_WIDTH; ++j)
            printf("%c", screen[i][j] ? '#' : '.');
        printf("\n");
    }
}

void on_clock_tick()
{
    ++cpu.cycle;
    signal += get_signal();
    draw_pixel();
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t len;
    while ((read = getline(&line, &len, f)) != -1)
    {
        char instr[read];
        int value = 0;
        int ret = sscanf(line,"%s%d",instr, &value);
        if(ret < 1 || ret > 2) continue;

        //noop just increases the cycle counter
        if(strcmp(instr, "noop") == 0) 
        {
            on_clock_tick();
            continue;
        }
        
        //increment the cycle counter by 2 and modify the register
        if(strcmp(instr, "addx") == 0)
        {
            on_clock_tick();
            on_clock_tick();    
            cpu.X += value;
        }
    }

    if(part == 1) printf("Result %d\n", signal);
    
    if(part == 2) draw_screen();

    if(f != NULL) fclose(f);
    return 0;
}