#include "alex_tree.h"
#include <stdlib.h>
#include <string.h>
static void TreeGetHeightRec(Node* n, size_t curr_lvl, size_t* level)
{
	if (n == NULL) { return; }
	if (curr_lvl > *level) { *level = curr_lvl; }
	TreeGetHeightRec(n->left, curr_lvl + 1, level);
	TreeGetHeightRec(n->right, curr_lvl + 1, level);
}
size_t TreeGetHeight(Node* n)
{
	size_t level = 1;
	TreeGetHeightRec(n, level, &level);
	return level;
}

static void TreeIsSameRec(Node* n1, Node* n2, bool* same)
{
	if (*same == false) { return; }
	if ((n1 == NULL) && (n2 == NULL)) { return; }
	if ((n1 == NULL) || (n2 == NULL)) { *same = false; return; }
	*same = ElemCompare(TreeGetRootValue(n1), TreeGetRootValue(n2)) == 0;
	TreeIsSameRec(n1->left, n2->left, same);
	TreeIsSameRec(n1->right, n2->right, same);
}
bool TreeIsSame(Node* n1, Node* n2)
{
	bool ris = true;
	TreeIsSameRec(n1, n2, &ris);
	return ris;
}

Node* TreeFromLevelVector(const ElemType* v, size_t v_size)
{
	if (v == NULL || v_size == 0) { return NULL; }
	Node** vcurr = calloc(v_size, sizeof(Node*));
	for (size_t i = 0; i < v_size; i++) { if (v[i] != NV) { vcurr[i] = TreeCreateRoot(v + i, NULL, NULL); } }
	size_t l = 0;
	size_t r = 0;
	for (size_t i = 0; i < v_size; i++)
	{
		if (vcurr[i] != NULL)
		{
			vcurr[i]->left = ((size_t)((l << 1) + 1) < v_size) ? vcurr[(l++ << 1) + 1] : NULL;
			vcurr[i]->right = ((size_t)((r + 1) << 1) < v_size) ? vcurr[(r++ + 1) << 1] : NULL;
		}
	}
	Node* ris = vcurr[0];
	free(vcurr);
	return ris;
}

static void TreeGetLevelValuesRec(const Node* n, const ElemType** ris, size_t level, size_t curr_lvl, size_t* index)
{
	if (n == NULL)
	{
		*index += (size_t)(1 << (level - curr_lvl));
		return;
	}
	if (curr_lvl == level)
	{
		ris[*index] = &(n->value);
		*index += (size_t)(1 << (level - curr_lvl));
		return;
	}
	TreeGetLevelValuesRec(n->left, ris, level, curr_lvl + 1, index);
	TreeGetLevelValuesRec(n->right, ris, level, curr_lvl + 1, index);
}
const ElemType** TreeGetLevelValues(const Node* n, size_t level)
{
	if (n == NULL) { return NULL; }
	const ElemType** ris = calloc(1 << level, sizeof(ElemType*));
	size_t index = 0;
	TreeGetLevelValuesRec(n, ris, level, 0, &index);
	return ris;
}

static void PrintfNTabOnString(char* str, size_t n) { for (size_t i = 0; i < n * TAB_SIZE; i++) { sprintf(str + strlen(str), " "); } }
static void PrintfInString(char* str, const ElemType* e)
{
	if (e == NULL) { sprintf(str + strlen(str), "% *c ", TAB_SIZE - 1, NV_PRINT); }
	else { sprintf(str + strlen(str), "% *d ", TAB_SIZE - 1, *e); }
}
static const ElemType*** TreeGetLevelVectors(Node* n)
{
	size_t h = TreeGetHeight(n) + 1;
	const ElemType*** ris = calloc(h, sizeof(ElemType**));
	for (size_t i = 0; i < h; i++) { ris[i] = TreeGetLevelValues(n, i); }
	return ris;
}

void TreePrintLevel(Node* n)
{
	const ElemType*** ris = TreeGetLevelVectors(n);
	size_t n_level = TreeGetHeight(n);
	size_t str_vet_dim = (size_t)(n_level << 1) + 1;
	size_t str_len = (size_t)((1 << (n_level + 1)) - 1) * TAB_SIZE;
	char** str = calloc(str_vet_dim, sizeof(char*));
	for (size_t i = 0; i < str_vet_dim; i++) { str[i] = calloc(str_len + 1, 1); }
	for (size_t i = 0; i < n_level + 1; i++)
	{
		char* s = str[i << 1];
		size_t tabs = (size_t)(1 << (n_level - i)) - 1;
		if (i != n_level) { PrintfNTabOnString(s, tabs); }
		for (size_t j = 0; j < (size_t)(1 << i) - 1; j++)
		{
			if ((i == 0) || (ris[i - 1][j >> 1] != NULL)) { PrintfInString(s, ris[i][j]); }
			else { PrintfNTabOnString(s, 1); }
			PrintfNTabOnString(s, (size_t)(tabs << 1) + 1);
		}
		if ((i == 0) || (ris[i - 1][((1 << i) - 1) >> 1] != NULL)) { PrintfInString(s, ris[i][(1 << i) - 1]); }
	}
	for (size_t i = 0; i < n_level; i++)
	{
		memset(str[(i << 1) + 1], ' ', str_len - (size_t)(1 << (n_level - i)) - 1);
		char* succ = str[(i + 1) << 1];
		char* curr = str[(i << 1) + 1];
		char* prec = str[i << 1];
		size_t count = 0;
		for (size_t j = 0; j < str_len; j++)
		{
			if (succ[j] != ' ' && j < strlen(succ))
			{
				curr[j] = (((count++)%2)==0)? FRECCIA_SX : FRECCIA_DX;
				j += TAB_SIZE - 1;
			}
		}
		bool collegamento = false;
		for (size_t j = 0; j < str_len; j++)
		{
			if ((curr[j] == FRECCIA_SX) || (curr[j] == FRECCIA_DX)) { collegamento = !collegamento; j++; }
			if (collegamento)
			{
				if (j > 0 && curr[j - 1] != PLUS && prec[j] != ' ' && j < strlen(prec)) { curr[j] = PLUS; }
				else { curr[j] = LINE; }
			}
		}
	}
	for (size_t i = 0; i < str_vet_dim; i++) { printf("%s\n", str[i]); free(str[i]); }
	for (size_t i = 0; i < n_level + 1; i++) { free((ElemType**)ris[i]); }
	free(str);
	free((ElemType***)ris);
}
