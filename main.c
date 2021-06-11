#include "alex_tree.h"
#include <crtdbg.h>
Node * stampa(const ElemType * v, size_t n) 
{
	printf("Dato il vettore di ElemType v[%zu] = { ", n);
	for (size_t i = 0; i < n - 1; i++)
	{
		if (v[i] != NV) { ElemWriteStdout(v + i); }
		else { printf("NULL"); }
		printf(", ");
	}
	ElemWriteStdout(v + n - 1);
	printf(" }\n\n");
	return TreeFromLevelVector(v, n);
}
int main(void) 
{
	const ElemType v1[] = { 22,42,53,13,24,75,NV,5,6,NV,8 };
	Node* n1 = stampa(v1, sizeof(v1) / sizeof(ElemType));

	const ElemType v2[] = {2,4,5,NV,2,7,1};
	Node* n2 = stampa(v2, sizeof(v2) / sizeof(ElemType));

	bool same = TreeIsSame(n1, n2);
	printf("Gli alberi n1 e n2 %ssono uguali\n\n", (same) ? "" : "non ");
	
	TreePrintLevel(n1);
	printf("\n\n");
	TreePrintLevel(n2);
	printf("\n\n");

	printf("Libero la memoria allocata... ");
	TreeDelete(n1);
	TreeDelete(n2);
	if (_CrtDumpMemoryLeaks() == 0) { printf("fatto\n\n"); }
	else { printf("MEMORY LEAK! - Controlla le malloc/calloc/realloc che siano correttamente liberate!\n\n"); }
	return 0;
}