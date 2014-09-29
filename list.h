#ifndef __LIST_H__
#define __LIST_H__

struct node {
    int val;
    struct node *next; 
};



void validity_create(struct node ** head, char* str);
void LL_create_sort(struct node ** head, int new_val);
void list_print(const struct node *list);
void list_destroy(struct node * head);
#endif // __LIST_H__
