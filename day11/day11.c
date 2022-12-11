#include "../utils/utils.h"

typedef enum {add, mul, divide, modulo} Operation;
typedef enum {unary, self} Cardinality;

typedef struct 
{
    Vector items;
    Operation op;
    Cardinality card;
    int default_operand;
    int div_by;
    int pass_to_if_true;
    int pass_to_if_false;
    int inspected;
}monkey;

size_t* get_item_at(monkey* m, int index)
{
    if(index < 0 || index >= m->items.count) return NULL;
    return (size_t*)m->items.data[index];
}

size_t get_worry(monkey* m, size_t old)
{
    size_t op1 = old;
    size_t op2 = m->card == unary ? m->default_operand : op1;
    return m->op == add ? op1 + op2 : op1 * op2;
}

int pass_to(monkey* m, size_t worry)
{
    return worry % m->div_by == 0 ? m->pass_to_if_true : m->pass_to_if_false;
}

monkey * new_monkey()
{
    monkey* m = malloc(sizeof(monkey));
    m->inspected = 0;
    VectorInit(&m->items);
    return m;
}

size_t * new_item(size_t item)
{
    size_t* ret = malloc(sizeof(size_t));
    *ret = item;
    return ret;
}

void print_monkeys(Vector * monkeys, bool all)
{
    printf("\n");
    for (int i = 0; i < monkeys->count; i ++)
    {
        monkey * it = monkeys->data[i];
        printf("Monkey %d: [ ", i);
        for (int j = 0; j < it->items.count; ++j)
            printf("%lu ", *get_item_at(it, j));
        
        printf("]\n");
        printf("inspected: %d \n", it->inspected);
        if(!all) continue;
        printf("op: %s \n", it->op == add ? "add" : "mul");
        printf("card: %s \n", it->card == self ? "self" : "other");
        printf("default: %d \n", it->default_operand);
        printf("div by: %d \n", it->div_by);
        printf("if true: %d \n", it->pass_to_if_true);
        printf("if false: %d \n", it->pass_to_if_false);
        printf("\n");
    }
    printf("\n");
}

void play_round(Vector * monkeys, Operation op, size_t relaxation)
{
    for (int i = 0; i < monkeys->count; i ++)
    {    
        monkey * it = monkeys->data[i];
        while(it->items.count > 0)
        {
            // worry
            size_t * cur_worry = get_item_at(it, 0);
            *cur_worry = get_worry(it, *cur_worry);
            // relax
            if(op == divide) *cur_worry /= relaxation;
            if(op == modulo) *cur_worry %= relaxation;

            //test
            int dest = pass_to(it, *cur_worry);
            monkey * to = monkeys->data[dest];
            to->items.push_back(&to->items, cur_worry);
            it->items.remove_at(&it->items, 0);
            it->inspected++;
        }
    }
}

size_t compute_monkey_business(Vector * monkeys)
{
    size_t largest = 0;
    size_t second_largest = 0;

    for (int i = 0; i < monkeys->count; i ++)
    {
        monkey * it = monkeys->data[i];
        if(it->inspected > largest) {
            second_largest = largest;
            largest = it->inspected;
        }else if(it->inspected > second_largest){
            second_largest = it->inspected;
        }         
    }

    return largest * second_largest;
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t len;

    Vector monkeys;
    VectorInit(&monkeys);
    monkey* it = NULL;
    while ((read = getline(&line, &len, f)) != -1)
    {
        int index;
        int ret = sscanf(line,"Monkey %d", &index);
        if(ret == 1) {    
            monkeys.push_back(&monkeys, new_monkey());
            it = monkeys.data[index];
            continue;
        }

        if(it == NULL) continue;
        
        char discard[read]; memset(discard, 0, sizeof(discard));
        char data[read]; memset(data, 0, sizeof(data));
        ret = sscanf(line, "%[ \t]Starting items: %[^\n]",discard, data);
        // starting items list
        size_t item;
        if(ret == 2) {
            do{
                ret = sscanf(data, "%lu,%[^\n]", &item, data);
                it->items.push_back(&it->items, new_item(item));
            }while(ret > 1);
            continue;
        }

        //parse operation
        ret = sscanf(line, "%[ \t]Operation: %[^\n]",discard, data);
        if(ret == 2) 
        {
            char op_tk[3][read]; memset(op_tk, 0, sizeof(op_tk));
            // new = op1 op op2
            ret = sscanf(data, "new = %s%s%s", op_tk[0], op_tk[1], op_tk[2]);
            if(ret < 3) continue;

            if(strcmp(op_tk[1], "*") == 0) it->op = mul;
            if(strcmp(op_tk[1], "+") == 0) it->op = add;
            if(strcmp(op_tk[0], op_tk[2]) == 0) it->card = self;
            it->default_operand = atoi(op_tk[2]);
            continue;
        }

        // parse test
        ret = sscanf(line, "%[ \t]Test: %[^\n]",discard, data);
        if(ret == 2)
        {
            sscanf(data, "divisible by %d", &it->div_by);
            continue;
        }

        // parse if true
        ret = sscanf(line, "%[ \t]If true: %[^\n]",discard, data);
        if(ret == 2)
        {
            sscanf(data, "throw to monkey %d", &it->pass_to_if_true);
            continue;
        }

        // parse if false
        ret = sscanf(line, "%[ \t]If false: %[^\n]",discard, data);
        if(ret == 2)
        {
            sscanf(data, "throw to monkey %d", &it->pass_to_if_false);
            continue;
        }

    }

    if(part == 1) {
        
        // play 20 rounds
        for(int i =0; i<20; ++i)
        {
            play_round(&monkeys, divide, 3);
            print_monkeys(&monkeys, false);
        }

        printf("Result %lu\n", compute_monkey_business(&monkeys));
    }
    
    if(part == 2)
    {
        // find the product of all the modulo factors
        size_t factors = 1;
        for (int i = 0; i < monkeys.count; i ++)
        {
            monkey * it = monkeys.data[i];
            factors *= it->div_by;
        }
        //play 10000 rounds
        for(int i =1; i<=10000; ++i)
        {
            play_round(&monkeys, modulo, factors);
            if(i%1000 == 0 || i == 1 || i == 20)
                print_monkeys(&monkeys, false);
        }
        printf("Result %lu\n", compute_monkey_business(&monkeys));
    } 

    monkeys.free(&monkeys);
    if(f != NULL) fclose(f);
    return 0;
}