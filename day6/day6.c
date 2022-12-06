#include "../utils/utils.h"

bool is_unique(char* window, int size)
{
    bool chars[MAX_CHAR] = {0};
    for(int i = 0; i < size; ++i)
    {
        if(chars[(int)window[i]] == true) return false;
        chars[(int)window[i]] = true;
    }
    return true;
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) 
		return 1;

    char * line = NULL;
    ssize_t read;
    size_t size;

    int len = part == 1 ? 4 : 14;
    char window[len];
    memset(window, 0, len);

    int pos = 0;
    while ((read = getline(&line, &size, f)) != -1)
    {
        for (int i = 0; i< read-1; i++)
        {   
            window[i%len] = line[i];    
            if(i < len) continue;

            if(is_unique(window, len)) {
                pos = i+1;
                break;
            }
        }
    }

    printf("Result %d\n", pos);

    if(f != NULL) fclose(f);
    return 0;
}