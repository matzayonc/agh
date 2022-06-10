#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define MEMORY_ALLOCATION_ERROR -1
#define LIST_ERROR -2
#define PROGRAM_ERROR -3

struct tagList;
typedef void (*ConstDataFp)(const void *);
typedef void (*DataFp)(void *);
typedef int (*CompareDataFp)(const void *, const void *);
typedef void (*InsertInOrder)(struct tagList *, void *);

typedef struct tagListElement
{
	struct tagListElement *next;
	void *data;
} ListElement;

typedef struct tagList
{
	ListElement *head;
	ListElement *tail;
	ConstDataFp dump_data;
	DataFp free_data;
	CompareDataFp compare_data;
	InsertInOrder insert_sorted;
} List;

// -----------------------------------------------------------------
// generic functions - they are common for all instances of the list
// (independent of the data type)
// -----------------------------------------------------------------

void init_list(
	List *p_list,
	ConstDataFp dump_data,
	DataFp free_data,
	CompareDataFp compare_data,
	InsertInOrder insert_sorted)
{

	p_list->head = NULL;
	p_list->tail = NULL;

	p_list->dump_data = dump_data;
	p_list->free_data = free_data;
	p_list->insert_sorted = insert_sorted;
	p_list->compare_data = compare_data;
}

// Print all elements of the list
void dump_list(const List *p_list)
{
	ListElement *curr = p_list->head;

	while (curr)
	{
		if (p_list->dump_data)
		{
			p_list->dump_data(curr->data);
		}
		curr = curr->next;
	}
}

// Print elements of the list if comparable to data
void dump_list_if(List *p_list, void *data)
{
	ListElement *curr = p_list->head;

	while (curr)
	{
		if (p_list->dump_data && p_list->compare_data(data, curr->data) == 0)
		{
			p_list->dump_data(curr->data);
		}
		curr = curr->next;
	}
}

// Free all elements of the list
void free_list(List *p_list)
{

	ListElement *curr = NULL;
	curr = p_list->head;

	while (curr != NULL)
	{
		ListElement *to_remove = curr;
		curr = curr->next;
		if (p_list->free_data)
			p_list->free_data(
				to_remove->data);

		free(to_remove);
	}

	p_list->head = NULL;
	p_list->tail = NULL;
}

// Push element at the beginning of the list
void push_front(
	List *p_list,
	void *data)
{
	ListElement *element = malloc(sizeof(ListElement));
	if (element == NULL)
		exit(MEMORY_ALLOCATION_ERROR);
	element->data = data;
	element->next = p_list->head;

	if (p_list->head)
		p_list->head = element;
	else
		p_list->head = p_list->tail = element;
}

// Push element at the end of the list
void push_back(
	List *p_list,
	void *data)
{
	ListElement *element = malloc(sizeof(ListElement));
	if (element == NULL)
		exit(MEMORY_ALLOCATION_ERROR);
	element->data = data;
	element->next = NULL;

	if (p_list->tail)
		p_list->tail->next = element;
	p_list->tail = element;

	if (!p_list->head)
		p_list->head = p_list->tail;
}

// Remove the first element
void pop_front(List *p_list)
{
	if (p_list->head == NULL)
		return;

	ListElement *to_remove = p_list->head;

	p_list->head = p_list->head->next;
	free(to_remove);

	if (p_list->head == NULL)
		p_list->tail = NULL;
}

// Reverse the list
void reverse(List *p_list)
{

	if (p_list->head == NULL)
		return;

	if (p_list->head->next == NULL)
		return;

	ListElement *prev = p_list->head;
	ListElement *next = p_list->head->next;

	prev->next = NULL;

	while (next)
	{
		ListElement *p = next->next;
		next->next = prev;
		prev = next;
		next = p;
	}

	ListElement *pp = p_list->head;
	p_list->head = p_list->tail;
	p_list->tail = pp;
}

// insert element preserving the ordering (defined by insert_sorted function)
void insert_in_order(
	List *p_list,
	void *data)
{
	p_list->insert_sorted(p_list, data);
}

// find element in sorted list after which to insert given element
ListElement *find_insertion_point(
	const List *p_list,
	ListElement *p_element)
{
}

// Insert element after 'previous'
void push_after(List *p_list, void *data, ListElement *previous)
{
}

// Insert element preserving order (no counter)
void insert_elem(List *p_list, void *p_data)
{

	if (p_list->head == NULL)
	{
		push_back(p_list, p_data);
		return;
	}

	ListElement *prev = p_list->head;
	ListElement *next = p_list->head->next;
	ListElement *p = malloc(sizeof(ListElement));

	p->data = p_data;

	if (p_list->compare_data(prev->data, p_data) == 0)
		return;
	if (p_list->compare_data(prev->data, p_data) > 0)
	{
		push_front(p_list, p_data);
		return;
	}

	while (next != NULL)
	{
		if (p_list->compare_data(p_data, next->data) == 0)
			return;

		if (p_list->compare_data(p_data, next->data) < 0)
		{
			prev->next = p;
			p->next = next;
			return;
		}

		prev = prev->next;
		next = next->next;
	}

	push_back(p_list, p_data);
}

// ---------------------------------------------------------------
// type-specific definitions
// ---------------------------------------------------------------

// int element

typedef struct DataInt
{
	int id;
} DataInt;

void dump_int(const void *d)
{
	DataInt *p = (DataInt *)d;
	printf("%d ", p->id);
}

void free_int(void *d)
{
	free(d);
}

int cmp_int(const void *a, const void *b)
{
	DataInt *pa = a;
	DataInt *pb = b;
	return pa->id - pb->id;
}

DataInt *create_data_int(int v)
{
	DataInt *p = malloc(sizeof(DataInt));
	p->id = v;
	return p;
}

// Word element

typedef struct DataWord
{
	char *word;
	int counter;
} DataWord;

void dump_word(const void *d)
{
	DataWord *p = d;
	printf("%s\n", p->word);
}

void dump_word_lowercase(const void *d)
{
	DataWord *p = d;
	printf("%s\n", p->word);

	// printf( "%s\n", tolower( p->word ));
}

void free_word(void *d)
{
	DataWord *p = d;
	free(p->word);
	free(p);
}

// conpare words case insensitive
int cmp_word_alphabet(const void *a, const void *b)
{
	DataWord *pa = a;
	DataWord *pb = b;

	return strcmp(pa->word, pb->word);
}

int cmp_word_counter(const void *a, const void *b)
{
	DataWord *pa = a;
	DataWord *pb = b;
	// printf("%d %d\n", pa->counter, pb->counter);
	return pa->counter - pb->counter;
}

void increment_counter(void *data)
{
	DataWord *p = data;
	p->counter++;
}

// insert element; if present increase counter
void insert_elem_counter(List *p_list, void *data)
{

	if (p_list->head == NULL)
	{
		push_back(p_list, data);
		return;
	}

	ListElement *prev = p_list->head;
	ListElement *next = p_list->head->next;
	ListElement *p = malloc(sizeof(ListElement));

	p->data = data;

	if (p_list->compare_data(prev->data, data) == 0)
	{
		increment_counter(prev->data);
		return;
	}
	if (p_list->compare_data(prev->data, data) > 0)
	{
		push_front(p_list, data);
		return;
	}

	while (next != NULL)
	{
		if (p_list->compare_data(data, next->data) == 0)
		{
			increment_counter(next->data);
			return;
		}

		if (p_list->compare_data(data, next->data) < 0)
		{
			prev->next = p;
			p->next = next;
			return;
		}

		prev = prev->next;
		next = next->next;
	}

	push_back(p_list, data);
}

void to_lower(char *str)
{
	for (int i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

// read text, parse it to words, and insert those words to the list
// in order given by the last parameter (0 - read order,
// 1 - alphabetical order)
void stream_to_list(
	List *p_list,
	FILE *stream,
	int order)
{
	ListElement *curr = p_list->head;

	char buffer[BUFFER_SIZE];

	char delimiters[] = "\t\r\n .,?!:;-";

	while (fgets(buffer, BUFFER_SIZE, stream) != NULL)
	{
		char *pch;
		pch = strtok(buffer, delimiters);

		while (pch != NULL)
		{
			DataWord *w = malloc(sizeof(DataWord));
			w->word = strdup(pch);
			w->counter = 1;
			// printf("%s\n", w->word);
			if (order)
			{
				to_lower(w->word);
				insert_elem_counter(p_list, w);
			}
			else
				push_back(p_list, w);
			pch = strtok(NULL, delimiters);

			// push_back( p_list, );
		}
		// free( pch );
	}
}

// test integer list
void list_test(List *p_list, int n)
{
	char op[2];
	int v;
	for (int i = 0; i < n; ++i)
	{
		scanf("%s", op);
		switch (op[0])
		{
		case 'f':
			scanf("%d", &v);
			push_front(p_list, create_data_int(v));
			break;
		case 'b':
			scanf("%d", &v);
			push_back(p_list, create_data_int(v));
			break;
		case 'd':
			pop_front(p_list);
			break;
		case 'r':
			reverse(p_list);
			break;
		case 'i':
			scanf("%d", &v);
			insert_in_order(p_list, create_data_int(v));
			break;
		default:
			printf("No such operation: %s\n", op);
			break;
		}
	}
}

int main(void)
{
	int to_do, n;
	List list;

	scanf("%d", &to_do);
	switch (to_do)
	{
	case 1: // test integer list
		scanf("%d", &n);
		init_list(&list, dump_int, free_int,
				  cmp_int, insert_elem);
		list_test(&list, n);
		dump_list(&list);
		free_list(&list);
		break;
	case 2: // read words from text, insert into list, and print
		init_list(&list, dump_word, free_word,
				  cmp_word_alphabet, insert_elem_counter);
		stream_to_list(&list, stdin, 0);
		dump_list(&list);
		free_list(&list);
		break;
	case 3: // read words, insert into list alphabetically, print words encountered n times
		scanf("%d", &n);
		init_list(&list, dump_word_lowercase, free_word,
				  cmp_word_alphabet, insert_elem_counter);
		stream_to_list(&list, stdin, 1);
		list.compare_data = cmp_word_counter;
		DataWord data = {NULL, n};
		//			list.dump_data = dump_word_lowercase;
		dump_list_if(&list, &data);
		printf("\n");
		free_list(&list);
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}
