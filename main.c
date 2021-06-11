#include "alex_tree.h"
static int id = 1;
int main(void)
{
	{
		printf("TREE %d:\t", id++);
		const Elem_List v[] = { E(2), E(4), E(5), E(0), E(6), E(7), N(1), E(5), E(6), N(3), E(8) };
		stampa(v, sizeof(v) / sizeof(Elem_List));
	}
	{
		printf("TREE %d:\t", id++);
		const Elem_List v[] = { E(2), E(4), E(5), E(0), E(6), E(7) };
		stampa(v, sizeof(v) / sizeof(Elem_List));
	}
	{
		printf("TREE %d:\t", id++);
		const Elem_List v[] = { E(6), E(7), N(2), E(5), E(6), E(8) };
		stampa(v, sizeof(v) / sizeof(Elem_List));
	}
	{
		printf("TREE %d:\t", id++);
		const Elem_List v[] = { E(6), E(7), N(2), E(5), E(6), E(8), N(3), E(4) };
		stampa(v, sizeof(v) / sizeof(Elem_List));
	}
	return 0;
}