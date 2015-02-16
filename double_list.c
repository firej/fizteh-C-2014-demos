#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct __listnode{
	int data;
	struct __listnode *prev;
	struct __listnode *next;
};

#define listnode struct __listnode

typedef struct __list{
	listnode* head;
	listnode* tail;
	size_t size;
} list;


list*	new_list();
bool	remove_list(list* ls);
bool	add_to_list(list* ls, int data);
bool	insert_to_list(list* ls, size_t index, int data);
bool	remove_from_list(list* ls, int data);
bool	remove_from_list_by_index(list* ls, size_t index);
bool	remove_from_list_by_ptr(list* ls, listnode* node);
listnode*	find_in_list(list* ls, int data);

int main(){
	list *ls = new_list();
	printf("%d\n", ls->size);
	add_to_list(ls, 574874);
	add_to_list(ls, 245);
	add_to_list(ls, 864);
	add_to_list(ls, 97);
	remove_from_list(ls, 245);
	bool res = insert_to_list(ls, 2, 77);
	printf("%d %d\n", ls->size, res);
	return 0;
}

list*	new_list() {
	return (list*)calloc(1, sizeof(list));
}

bool	remove_list(list* ls){
	while (ls->tail){
		remove_from_list_by_ptr(ls, ls->tail);
	}
	free(ls);
	return true;
}

bool	add_to_list(list* ls, int data){
	listnode *node = (listnode*)calloc(1, sizeof(listnode));
	node->data = data;
	if (!ls->head) {
		ls->head = node;
	}
	if (ls->tail)
		ls->tail->next = node;
	node->prev = ls->tail;
	ls->tail = node;
	ls->size++;
	return true;
}

bool	insert_to_list(list* ls, size_t index, int data){
	if (index > ls->size)
		return false;

	if (index == ls->size){
		return add_to_list(ls, data);
	}

	listnode *node = (listnode*)calloc(1, sizeof(listnode));
	node->data = data;
	listnode *place = ls->head;
	for (size_t i = 0; i < index; i++) {
		place = place->next;
	}

	if (ls->head == place) {
		ls->head = node;
	}
	else {
		place->prev->next = node;
	}

	place->prev = node;
	node->next = place;

	ls->size++;
	return true;
}

bool	remove_from_list(list* ls, int data){
	return remove_from_list_by_ptr(ls, find_in_list(ls, data));
}

bool	remove_from_list_by_index(list* ls, size_t index){
	if (!ls->head || !ls->tail || index > ls->size)
		return false;
	listnode *node = ls->head;
	for (size_t i = 1; i < index; i++) {
		node = node->next;
	}
	return remove_from_list_by_ptr(ls, node);
}

bool	remove_from_list_by_ptr(list* ls, listnode* node) {
	if (!ls->head || !ls->tail || !node)
		return false;

	if (ls->head == node){
		ls->head = node->next;
		if (node->next)
			node->next->prev = NULL;
	}
	else {
		node->prev->next = node->next;
	}

	if (ls->tail == node) {
		ls->tail = node->prev;
		if (node->prev)
			node->prev->next = NULL;
	}
	else{
		node->next->prev = node->prev;
	}
	free(node);
	ls->size--;
	return true;
}
listnode*	find_in_list(list* ls, int data) {
	if (!ls->head || !ls->tail)
		return NULL;
	listnode* node = ls->head;
	do {
		if (node->data == data){
			return node;
		}
		node = node->next;
	} while (node);
	return NULL;
}
