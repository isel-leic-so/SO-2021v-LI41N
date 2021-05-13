#include <stdio.h>

#include "list.h"

typedef struct my_node {
	int ord;
	list_entry_t entry;
	int value;
} my_node_t;

my_node_t nodes[6] = {
	{ .ord = 0 },
	{ .ord = 1 },
	{ .ord = 2 },
	{ .ord = 3 },
	{ .ord = 4 },
	{ .ord = 5 },
};

int main() {
	
	list_entry_t list;
	init_list_head(&list);
	
	printf("empty: %s\n", is_list_empty(&list) ? "true" : "false");
	
	insert_head_list(&list, &(nodes[1].entry));
	nodes[1].value = 107;
	
	insert_head_list(&list, &(nodes[5].entry));
	nodes[5].value = 81;
	
	insert_head_list(&list, &(nodes[2].entry));
	nodes[2].value = 43;

	for (list_entry_t * pentry = list.flink; pentry != &list; pentry = pentry->flink) {
		//size_t offset_of_entry_in_my_node = (size_t)&(((my_node_t *)0)->entry);
		//my_node_t * pnode = (my_node_t *)(((void *)pentry) - offset_of_entry_in_my_node);
		
		my_node_t * pnode = container_of(pentry, my_node_t, entry);
		
		printf("nodes[%d] : %d\n", pnode->ord, pnode->value);
	}

	return 0;
}
