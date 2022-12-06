#include "../utils/utils.h"

typedef struct node {
    char data;
    struct node * next;
    struct node * prev;
} Node;

typedef struct stack{
    Node * head;
    Node * tail;
} Stack;


void printStacks(Stack * stacks, int number)
{
    for (int i = 0; i < number; ++i) 
    {
        printf("%d: ", i+1);
        Node * it = stacks[i].tail;
        while(it != NULL) {printf("%c ", it->data); it = it->prev;};
        printf("\n");
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) 
		return 1;

    char * line = NULL;
    ssize_t read;
    size_t size;

    Stack data[9] = {0};

    int readInput = 0;
    while ((read = getline(&line, &size, f)) != -1){
        if(!readInput && strcmp(line, "\n") == 0) readInput = 1;
        if(!readInput)
        {
            for(int i =0; i<read -1; ++i)
            {
                int index = i/4;
                if(line[i] >= 'A' && line[i] <= 'Z')
                {    
                    if(data[index].head == NULL) 
                    {
                        data[index].head = malloc(sizeof(Node));
                        data[index].head->data = line[i];
                        data[index].head->next = NULL;
                        data[index].head->prev = NULL;
                        data[index].tail = data[index].head;
                    }
                    else
                    {   
                        Node* node = malloc(sizeof(Node));
                        node->data = line[i];
                        node->next = NULL;

                        node->prev = data[index].tail;
                        data[index].tail->next = node;
                        data[index].tail = node;
                    }
                } 
            } 
        }
        else{
            int move, from , to;
            if (3 == sscanf(line,"%*[^0123456789]%d%*[^0123456789]%d%*[^0123456789]%d",&move,&from,&to))
            {
                printf("move %d from %d to %d \n", move, from, to);
                from--; to--;
                if(part == 1)
                {
                    for(int i =0; i< move; ++i){
                        Node* top = data[from].head;
                        //pop the from stack
                        data[from].head = data[from].head->next;
                        if(data[from].head != NULL){
                            data[from].head->prev = NULL;
                        }else{
                            data[from].tail = NULL;
                        } 

                        //push on the to stack
                        if(data[to].head == NULL){
                            data[to].head = top;
                            top->next = NULL;
                            top->prev = NULL;
                            data[to].tail = top;
                        }else{
                            data[to].head->prev = top;
                            top->prev = NULL;
                            top->next = data[to].head;
                            data[to].head = top;
                        }
                    } 
                }
                else{
                    // in this case we only need to find the node move down and swap pointers
                    Node * top = data[from].head;
                    Node * pickup = top;
                    for(int i =0; i < move-1; ++i) pickup = pickup->next;   
        
                    data[from].head = pickup->next;
                    if(data[from].head != NULL){
                        data[from].head->prev = NULL;
                    }else{
                        data[from].tail = NULL;
                    } 

                    //push move on the to stack
                    if(data[to].head == NULL){
                        data[to].head = top;
                        top->prev = NULL;
                        data[to].tail = pickup;
                        data[to].tail->next = NULL;
                    }else{
                        data[to].head->prev = pickup;
                        pickup->next = data[to].head;
                        
                        top->prev = NULL;
                        data[to].head = top;
                    }
                }
              
            }

            printStacks(data, 9);       
        }  
    }

    printf("Result: \n");
    for (int i = 0; i<9; ++i) printf("%c",data[i].head->data);
    printf("\n");

    if(f != NULL) fclose(f);
    return 0;
}