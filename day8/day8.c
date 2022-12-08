#include "../utils/utils.h"
#define SIZE  100

int data[SIZE][SIZE] = {0};

int size = 99;

void print_grid()
{
    for(int i =0; i< size; ++i){
        for(int j =0 ; j< size; ++j)
            printf("%d", data[i][j]);

        printf("\n");
    }
}

bool is_visible(int i, int j)
{
    if(i == 0 || i == size-1) return true;
    if(j == 0 || j == size-1) return true;

    bool vis_from_left = true;
    for (int x = 0 ; x < i; ++ x)
        if(data[x][j] >= data[i][j]) {
            vis_from_left = false;
            break;
        }

    bool vis_from_right = true;
    for (int x = i+1 ; x < size; ++ x)
        if(data[x][j] >= data[i][j]) {
            vis_from_right = false;
            break;
        }

    bool vis_from_top = true;
    for (int y = 0 ; y < j; ++ y)
        if(data[i][y] >= data[i][j]){
            vis_from_top = false;
            break;
        }

    bool vis_from_bottom = true;
    for (int y = j+1 ; y < size; ++ y)
        if(data[i][y] >= data[i][j])
        {
            vis_from_bottom = false;
            break;
        }

    return vis_from_left || vis_from_right || vis_from_top || vis_from_bottom;
}

long panoramic_score(int i, int j) 
{
    if(i == 0 || i == size-1) return 0;
    if(j == 0 || j == size-1) return 0;

    long to_left = 0;
    long to_right = 0;
    long to_top = 0;
    long to_bottom = 0;

    for (int x = i-1 ; x >= 0; --x){
        to_top++;
        if(data[x][j] >= data[i][j]) break;
    }

    for (int x = i+1; x < size; ++x){
        to_bottom++;
        if(data[x][j] >= data[i][j]) break;
    }

    for (int y = j-1 ; y >= 0; --y){
        to_left++;
        if(data[i][y] >= data[i][j]) break;
    }
    
    for (int y = j+1; y < size; ++y){
        to_right++;
        if(data[i][y] >= data[i][j]) break;
    }

    return to_left * to_right * to_top * to_bottom;
}

int count_visible()
{
    int ret = 0;
    for(int i =0; i< size; ++i)
        for(int j =0; j< size; ++j)
            if(is_visible(i,j)) ret++;
    
    return ret;
}

long max_panorama()
{
    long max = 0;
    for(int i =0; i< size; ++i)
        for(int j =0; j< size; ++j){
            long score = panoramic_score(i,j);
            if(max < score) max = score;
        }

    return max;
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t len;

    int i =0;
    while ((read = getline(&line, &len, f)) != -1)
    {
        // out of memory
        if(read -1 > SIZE || i > SIZE) return 1;
        
        if(i == 0 || read -1 > size) size = read -1;
        for(int j =0; j < read; ++j) 
        {
            if(line[j] < '0' || line[j] > '9') continue;        
            if(i< SIZE && j < SIZE) data[i][j] = line[j] - '0';
        }
            
        i++;
    }

    print_grid(); 
    if(part == 1){
        int count = count_visible();
        printf("Result %d\n", count);
    }

    if(part == 2){
        long max = max_panorama();
        printf("Result %ld\n", max);
    }

    if(f != NULL) fclose(f);
    return 0;
}