#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#define ARR_SIZE 20000
struct list_item{
	list_item*	next;
	int			value;
};
struct list{
	list_item*	first;
	size_t		size;
};
void swap(int &a, int&b){
	int tmp = a; a = b; b = tmp;
}
void print(list* list){
	for (list_item* i = list->first; i; i = i->next)
		printf("%3d", i->value);
	printf("\n");
}
list_item* new_item(list* list, int value){
	list_item *item = (list_item*) calloc(sizeof(list_item), 1);
	item->value = value;
	list_item *lasti = list->first;
	if (!lasti) return list->first = item;
	while(lasti->next) lasti = lasti->next;
	return lasti->next = item;
}
void delete_item(list_item *item){
	DebugBreak();
}
size_t get_size(list_item *list){
	size_t size = 0;
	while(list){
		size++;
		list = list->next;
	};
	return size;
}
void sort(list* my, int size);
int main(){
	srand(time(NULL));
	list my_list;
	my_list.first = NULL;
	for (int i=0 ;i < ARR_SIZE; i++)
		new_item(&my_list, rand() % 99);
	//print(&my_list);
	printf("%d\n", get_size(my_list.first));
	long time_start = clock();
	sort(&my_list, get_size(my_list.first));
	long time_end = clock();
	printf("Elapsed time %d", time_end - time_start);
	//print(&my_list);
	getch();
	return 0;
}
list_item* get_by_index(list* my, int num){
	list_item *res = my->first;
	for (int i = 0; i < num && res->next; i++)
		res = res->next;
	return res;
}
void sort(list* my, int size){
	if (size == 1){
		return;
	}
	list list_l, list_r;
	list_l = *my;
	list_l.size = size/2;
	list_r.first = get_by_index(my, size/2);
	list_r.size = get_size(list_r.first);
	get_by_index(&list_l, list_l.size - 1)->next = 0;
	sort(&list_l, size/2);
	sort(&list_r, get_size(list_r.first));

	list new_list;
	new_list.first = NULL;
	for (list_item *l = list_l.first, *r = list_r.first; l || r;){
		if (!l) {
			new_item(&new_list, r->value);
			r = r->next;
		}
		else if (!r) {
			new_item(&new_list, l->value);
			l = l->next;
		}
		else {
			if (l->value < r->value){
				new_item(&new_list, l->value);
				l = l->next;
			}
			else{
				new_item(&new_list, r->value);
				r = r->next;
			}
		}
	}
	*my = new_list;
	return;
}