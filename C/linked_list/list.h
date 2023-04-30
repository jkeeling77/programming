#ifndef LIST_H
#define LIST_H

//#include <stdlib.h>

typedef struct ListElmt_ {
	void* data;
	struct ListElmt_* next;
} ListElmt, ListNode;

typedef struct List_ {
	int size;
	int (*match)(const void* key1, const void* key2);
	void (*destroy)(void* data);
	void (*print)(void* data);
	ListElmt* head;
	ListElmt* tail;
} List;

void      list_init(List* pList, void (*destroy)(void* data), void (*print)(void* data), int(*match)(const void* dataA, const void* dataB));
void      list_destroy(List* pList);
void      list_print(List* pList);
int       list_ins_next(List* pList, ListElmt* element, const void* data);
int       list_insert(List* pList, const void* data);
int       list_remove(List* pList, const void* data);

int       list_rem_next(List* pList, ListElmt* element, void** data);

int       list_size(List* pList);
ListElmt* list_head(List* pList);
ListElmt* list_tail(List* pList);
int       list_is_head(List* pList, ListElmt* pListElmt);
int       list_is_tail(ListElmt* pListElmt);
void*     list_data(ListElmt* pListElmt);
ListElmt* list_next(ListElmt* pListElmt);
void      list_sort(List* pList);

#endif