/*
 * util.c - commonly used utility functions.
 */

void *checked_malloc(int len)
{
	void *p = malloc(len);
	if (p)
		return p;
	fprintf(stderr,"\nRan out of memory!\n");
	exit(1);
}

string String(char *s)
{
	string p = checked_malloc(strlen(s)+1);
	strcpy(p,s);
	return p;
}

U_boolList U_BoolList(bool head, U_boolList tail)
{
	U_boolList list = checked_malloc(sizeof(*list));
	list->head = head;
	list->tail = tail;
	return list;
}
