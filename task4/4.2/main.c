#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct Item {
    char value[MAX_LENGTH];
    int priority;
    struct Item* prev;
    struct Item* next;
    struct Item* head;
    struct Item* end;  
} Item;

Item* enqueue(char* value, int priority, Item* item) {
	Item* tmp;
	tmp = (Item*)malloc(sizeof(Item));
	if (tmp == NULL) 
	{
		exit(1);
	} 
    strncpy(tmp->value, value, MAX_LENGTH);
    tmp->priority = priority;
	tmp->next = item->head;
	tmp->prev = NULL;
	if (item->head) { item->head->prev = tmp; }
	item->head = tmp;
	if (item->end == NULL)
	{
		item->end = tmp;
	}
	return item;
}

Item* dequeue_min_priority(int priority, Item* item) {
	struct Item* tmp = item->end;
	if (item == NULL)
	{
		return NULL;
	}
    do {
        if (tmp->priority >= priority) {
            strncpy(item->value, tmp->value, MAX_LENGTH);
        }
        tmp = tmp->prev;
    } while (tmp != item);
	printf("%s\n", tmp->value);
	return tmp;
}

Item* dequeue(Item* item) {
	struct Item* next;
	if (item == NULL)
	{
		exit(1);
	}
	next = item->end;
	item->end = item->end->prev;
	if (item->end)
	{
		item->end->next = NULL;
	}
	if (next == item->head)
	{
		item->head = NULL;
	}
    strncpy(item->value, next->value, MAX_LENGTH);
	printf("Deleted: \n");
	printf("%s\n", next->value);
	free(next);
	return item;
}

Item* dequeue_by_priority(int priority, Item* item) {
	Item* tmp = item->head;
    Item* next = item->end;
	if (item == NULL)
	{
		return NULL;
	}
    do {
        if (next->priority == priority) {
            tmp->next->prev = tmp->prev;
            tmp->prev->next=item->next;
        }
        tmp->end = tmp->end->prev;
        tmp->end->next = tmp->head;
    } while (item != tmp);
	printf("%d\n", next->value);
	return next;
}


int main(void) {
    Item* item = (Item*)malloc(sizeof(Item));
    item->head = NULL;
	item->end = NULL;
    item = enqueue("100 prior", 100, item);
    item = enqueue("200 prior", 200, item);
    item = enqueue("50 prior", 50, item);
    item = enqueue("250 prior", 250, item);
    item = dequeue(item);
    printf("%s\n", dequeue_by_priority(100, item));
    printf("%s\n", dequeue_min_priority(150, item));
}

