#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define BUFFER_SIZE 1024
#define MAX_RATE 4
#define MEMORY_ALLOCATION_ERROR -1
#define LIST_ERROR -2
#define PROGRAM_ERROR -3

typedef union data_union
{
	int int_data;
	char char_data;
	void *ptr_data;
} data_union;

typedef void (*DataFp)(data_union);
typedef void (*DataPFp)(data_union *);
typedef int (*CompareDataFp)(data_union, data_union);
typedef int (*HashFp)(data_union, int);

typedef struct ht_element
{
	struct ht_element *next;
	data_union data;
} ht_element;

typedef struct hash_table
{
	int size;
	int no_elements;
	ht_element **ht;
	DataFp dump_data;
	DataFp free_data;
	CompareDataFp compare_data;
	HashFp hash_function;
	DataPFp modify_data;
} hash_table;

void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (ptr)
		return ptr;
	exit(MEMORY_ALLOCATION_ERROR);
}

// ---------------------- functions to implement

// initialize table fields
void init_ht(hash_table *p_table, int size, DataFp dump_data, DataFp free_data,
			 CompareDataFp compare_data, HashFp hash_function, DataPFp modify_data)
{
	p_table = malloc(sizeof(hash_table));
	p_table->ht = malloc(size * sizeof(void *));
	for (int i = 0; i < size; i++)
		p_table->ht[i] = NULL;

	p_table->size = size;
	p_table->no_elements = 0;

	p_table->dump_data = dump_data;
	p_table->free_data = free_data;
	p_table->compare_data = compare_data;
	p_table->hash_function = hash_function;
	p_table->modify_data = modify_data;
}

// print elements of the list with hash n
void dump_list(const hash_table *p_table, int n)
{
	ht_element *el = p_table->ht[n];

	while (el)
	{
		p_table->dump_data(el->data);
		el = el->next;
	}
}

// Free element pointed by data_union using free_data() function
void free_element(DataFp free_data, ht_element *to_delete)
{
	free_data(to_delete->data);
	free(to_delete);
}

// free all elements from the table (and the table itself)
void free_table(hash_table *p_table)
{
	for (int i = 0; i < p_table->size; i++)
	{
		ht_element *el = p_table->ht[i];

		while (el)
		{
			ht_element *next = el->next;
			free_element(p_table->free_data, el);
			el = next;
		}
	}
	free(p_table->ht);
}

// calculate hash function for integer k
int hash_base(int k, int size)
{
	static const double c = 0.618033988; // (sqrt(5.) – 1) / 2.;
	double tmp = k * c;
	return (int)floor(size * (tmp - floor(tmp)));
}

void rehash(hash_table *p_table)
{
	p_table->size *= 2;
	ht_element *head = NULL;
	ht_element *tail = NULL;

	for (int i = 0; i < p_table->size; i++)
	{
		ht_element *el = p_table->ht[i];
		if (!el)
			continue;

		if (!head)
		{
			head = el;
			continue;
		}
		else
			tail->next = el;

		while (el->next)
			el = el->next;

		tail = el;
	}

	p_table->size *= 2;
	p_table->ht = realloc(p_table->ht, p_table->size);
	for (int i = 0; i < p_table->size; i++)
		p_table->ht[i] = NULL;

	while (head)
	{
		const int hash = p_table->hash_function(head->data, p_table->size);
		ht_element *neck = p_table->ht[hash];
		p_table->ht[hash] = head;
		head->next = neck;
	}
}

// find element; return pointer to previous
ht_element *find_previous(hash_table *p_table, data_union data, int *first)
{
	ht_element *prev = NULL;
	ht_element *el = p_table->ht[*first];

	while (el && p_table->compare_data(el->data, data))
	{
		prev = el;
		el = el->next;
	}
	if (!el)
		exit(5);

	return prev;
}

// return pointer to element with given value
ht_element *get_element(hash_table *p_table, data_union *data)
{
	int hash = p_table->hash_function(*data, p_table->size);
	// ht_element *prev = find_previous(p_table, *data, hash);

	ht_element *prev = NULL;
	ht_element *el = p_table->ht[hash];

	while (el && p_table->compare_data(el->data, *data))
	{
		prev = el;
		el = el->next;
	}
	if (!el)
		exit(5);

	return prev ? prev->next : p_table->ht[hash];
}

// insert element
void insert_element(hash_table *p_table, data_union *data)
{
	const int hash = p_table->hash_function(*data, p_table->size);

	ht_element *el = malloc(sizeof(ht_element));
	el->next = p_table->ht[hash];
	p_table->ht[hash] = el;
}

// remove element
void remove_element(hash_table *p_table, data_union data)
{
	int hash = p_table->hash_function(data, p_table->size);
	ht_element *prev = NULL;
	ht_element *el = p_table->ht[hash];

	while (el && p_table->compare_data(el->data, data))
	{
		prev = el;
		el = el->next;
	}

	if (!prev)
		p_table->ht[hash] = el->next;
	else
		prev->next = el->next;

	free_element(p_table->free_data, el);
}

// type-specific definitions

// int element

int hash_int(data_union data, int size)
{
	return hash_base(data.int_data, size);
}

void dump_int(data_union data)
{
	printf("%d\n", data.int_data);
}

int cmp_int(data_union a, data_union b)
{
	return b.int_data - a.int_data;
}

// read int value and insert to the union
data_union create_data_int()
{
	data_union created;
	scanf("%d", &(created.int_data));
	return created;
}

// char element

int hash_char(data_union data, int size)
{
	return hash_base((int)data.char_data, size);
}

void dump_char(data_union data)
{
	printf("%c\n", data.char_data);
}

int cmp_char(data_union a, data_union b)
{
	return a.char_data - b.char_data;
}

// read char value and insert to the union
data_union create_data_char()
{
	data_union created;
	scanf("%c", &(created.char_data));
	return created;
}

// Word element

typedef struct DataWord
{
	char *word;
	int counter;
} DataWord;

void dump_word(data_union data)
{
}

void free_word(data_union data)
{
}

int cmp_word(data_union a, data_union b)
{
	return a.char_data - b.char_data;
}

int hash_word(data_union data, int size)
{
	int s = 0;
	DataWord *dw = (DataWord *)data.ptr_data;
	char *p = dw->word;
	while (*p)
	{
		s += *p++;
	}
	return hash_base(s, size);
}

// increase the counter
void modify_word(data_union *data)
{
	DataWord *dw = (DataWord *)data->ptr_data;
	dw->counter++;
}

// allocate DataWord structure and insert to the union
data_union create_data_word(char *value)
{
	DataWord *word = malloc(sizeof(DataWord));
	word->word = value;
	data_union created;
	created.ptr_data = word;
	return created;
}

// read text, parse it to words, and insert those words to the hashtable
void stream_to_ht(hash_table *p_table, FILE *stream)
{
}

// test primitive type list
void table_test(hash_table *p_table, int n, data_union (*create_data)())
{
	char op;
	data_union data;
	for (int i = 0; i < n; ++i)
	{
		scanf(" %c", &op);
		data = create_data();
		switch (op)
		{
		case 'r':
			remove_element(p_table, data);
			break;
		case 'i':
			insert_element(p_table, &data);
			break;
		default:
			printf("No such operation: %c\n", op);
			break;
		}
	}
}

int main(void)
{
	int to_do, n, index;
	hash_table table;
	char buffer[BUFFER_SIZE];
	data_union data;

	scanf("%d", &to_do);
	switch (to_do)
	{
	case 1: // test integer table
		scanf("%d %d", &n, &index);
		init_ht(&table, 4, dump_int, NULL,
				cmp_int, hash_int, NULL);
		table_test(&table, n, create_data_int);
		printf("%d\n", table.size);
		dump_list(&table, index);
		// free_table(&table);
		break;
	case 2: // test char table
			// scanf("%d %d",&n, &index);
			// init_ht(&table, 4, dump_char,NULL,
			//         cmp_char, hash_char, NULL);
			// table_test(&table, n, create_data_char);
			// printf ("%d\n", table.size);
			// dump_list(&table, index);
			// free_table(&table);
			// break;
	case 3: // read words from text, insert into table, and print
			// scanf("%s", buffer);
			// init_ht(&table, 8, dump_word, free_word,
			//         cmp_word, hash_word, modify_word);
			// stream_to_ht(&table, stdin);
			// printf ("%d\n", table.size);
			// data = create_data_word(buffer);
			// ht_element *e = get_element(&table, &data);
			// if (e) table.dump_data(e->data);
			// if (table.free_data) table.free_data(data);
			// free_table(&table);
			// break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}
