#include "../utils/utils.h"

#define SMALL_DIR_SIZE 100000
#define TOTAL_DISK_SIZE 70000000
#define TARGET_UNUSED 30000000

typedef enum {dir, file} Type;

typedef struct inode {
    char* name;
    Type type;
    long size;
    struct inode* parent;
    struct inode* first_sibling;
    struct inode* first_child;
}iNode;

iNode* create_inode(const char* name, Type type, long size)
{
    iNode* node = malloc(sizeof(iNode));
    node->name = strdup(name);
    node->type = type;
    if(type == file) node->size = size;
    else node->size = 0;
    node->first_child = NULL;
    node->first_sibling = NULL;
    node->parent = NULL;

    return node;
}

void add_child(iNode* parent, iNode* child)
{ 
    if(child == NULL) return;

    child->parent = parent;
    if(parent->first_child == NULL) 
    {
        parent->first_child = child;
        return;
    }

    iNode * it = parent->first_child;
    while(it->first_sibling != NULL) it = it->first_sibling;
    it->first_sibling = child;             
}

iNode* find_child_dir(iNode* parent, const char* name)
{
    iNode *it = parent->first_child;
    while(it != NULL)
    {
        if(it->type == dir && strcmp(it->name, name) == 0) return it;
        it = it->first_sibling;
    }

    return NULL;
}

long total_size(iNode* node)
{
    if(node == NULL) return 0;
    long size = node->size;
    iNode* it = node->first_child;
    
    while(it != NULL){
        size += total_size(it);
        it = it->first_sibling;
    }

    return size;
}

bool is_cd(const char* w1, const char* w2)
{
    return strcmp(w1, "$") == 0 && strcmp(w2, "cd") == 0;
}

bool is_ls(const char* w1, const char* w2)
{
    return strcmp(w1, "$") == 0 && strcmp(w2, "ls") == 0;
}

void print_tree(iNode* node, int level)
{
    if(node == NULL) return;
   
    printf("%*c", level, ' ');   
    if(node->type == file)
        printf("- %s (file, %ld)\n", node->name, node->size);
    else 
        printf("- %s (dir)\n", node->name);

    print_tree(node->first_child,  level + 1);
    print_tree(node->first_sibling, level); 
}

long sum_tree(iNode * node)
{
    long sum = 0;
    if(node == NULL) return sum;

    if(node->type == dir){
        long size = total_size(node);
        if(size < SMALL_DIR_SIZE) sum += size;
    }

    sum += sum_tree(node->first_child);
    sum += sum_tree(node->first_sibling); 
    return sum;
}

long to_delete(iNode* node, long target)
{
    long min = TOTAL_DISK_SIZE;
    if(node == NULL) return min;

    if(node->type == dir){
        long size = total_size(node);
        if(size > target && min > size) min = size;
    }

    long child_min = to_delete(node->first_child, target);
    if(min > child_min) min = child_min;
    long sibling_min = to_delete(node->first_sibling, target); 
    if(min > sibling_min) min = sibling_min;
    
    return min;
}

int main(int argc, char **argv)
{
    if(parse_command_line(argc, argv) != 0) return 1;

    char * line = NULL;
    ssize_t read;
    size_t size;

    iNode *root = NULL;
    iNode * current = NULL;
    bool inListing = false;
    while ((read = getline(&line, &size, f)) != -1)
    {    
        char w1[read]; memset(w1, 0, sizeof(w1));
        char w2[read]; memset(w2, 0, sizeof(w2));
        char w3[read]; memset(w3, 0, sizeof(w3));

        int ret = sscanf(line,"%s%s%s",w1, w2, w3);
        if(ret < 2) continue;

        //build the root first
        if(root == NULL && is_cd(w1, w2))
        {
            current = root = create_inode("/", dir, 0);
            continue;
        }

        //we are listing the current directory -> add children
        if(is_ls(w1, w2) && current)
        {
            inListing = true;
            continue;
        }

        //we are changing directories
        if(is_cd(w1, w2) && current)
        {
            iNode * navigateTo = NULL;  
            if(strcmp(w3, "..") == 0) 
                navigateTo = current->parent; 
            else 
                navigateTo = find_child_dir(current, w3);

            if(navigateTo) current = navigateTo;

            inListing = false; 
            continue;
        }

        // add children and siblings
        if(inListing && current)
        {
            if(strcmp(w1, "dir") == 0) 
                add_child(current, create_inode(w2, dir, 0));
            else 
                add_child(current, create_inode(w2, file, atol(w1)));   
        }
             
    }

    print_tree(root ,1);
    printf("\n");

    if(part == 1)
    {
        long ret = sum_tree(root);
        printf("Result %ld\n", ret);
    }

    if(part == 2)
    {
        long used = total_size(root);
        long needed =  TARGET_UNUSED - (TOTAL_DISK_SIZE - used);
        printf("Total %d, Used %ld, Needed %ld \n", TOTAL_DISK_SIZE, used, needed);
        
        long ret = to_delete(root, needed);
        printf ("Result %ld\n", ret);
    }

    if(f != NULL) fclose(f);
    return 0;
}