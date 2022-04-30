#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000
typedef struct
{
	int first;
	int second;
} pair;

int comapare(const void *a, const void *b) {
	return (*(int *)a - *(int *)b);
}

// Add pair to existing relation if not already there
int add_relation(pair *p, int n, pair insert) {
	for (int i = 0; i < n; ++i)
		if (p[i].first == insert.first && p[i].second == insert.second)
			return n;
	p[n].first = insert.first;
	p[n].second = insert.second;
	return n + 1;
}
// Case 1:
// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* pairs, int n) {
	int unique[MAX_RANGE] = {0};
	int unique_reflexive[MAX_RANGE];
	for(int i = 0; i < n; i++){
		unique[pairs[i].first] = 1;
		unique[pairs[i].second] = 1;
		if(pairs[i].first == pairs[i].second)
			unique_reflexive[pairs[i].first] = 1;
	}

	for(int i = 0; i < MAX_RANGE; i++)
		if(unique[i] == 1 && unique_reflexive[i] == 0)
			return 0;

	return 1;
}
// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* pairs, int n) {
	for(int i = 0; i < n; i++)
		if(pairs[i].first == pairs[i].second)
			return 0;

	return 1;
}
// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* pairs, int n) {
	for(int i = 0; i < n; i++) {
		int ok = 0;
		for (int j = 0; j < n; j++)
			if(pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first) {
				ok = 1;
				break;
			}
		if(!ok)
			return 0;
	}
	return 1;
}
// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* pairs, int n) {
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if(pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first) 
				if(pairs[i].first != pairs[i].second)
					return 0;
		
	}
	return 1;
}
// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair* pairs, int n) {
	return !is_symmetric(pairs, n);
}
// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair *p, int n)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (p[i].second == p[j].first)
			{
				int bool = 0;
				for (int k = 0; k < n; ++k)
				{
					if (p[i].first == p[k].first && p[j].second == p[k].second)
					{
						bool = 1;
						break;
					}
				}
				if (bool == 0)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}
// // Case 2:// // A partial order relation is a homogeneous relation that is
// // reflexive, transitive, and antisymmetric
int get_domain(pair *p, int n, int *domain)
{
	int d_size = 0;
	for (int i = 0; i < n; ++i) {
		int found = 0;
		for (int j = 0; j < d_size; ++j)
			if (p[i].first == domain[j]) {
				found = 1;
				break;
			}

		if (!found) {
			domain[d_size] = p[i].first;
			d_size++;
		}
	}

	for (int i = 0; i < n; ++i) {
		int found = 0;
		for (int j = 0; j < d_size; ++j)
			if (p[i].second == domain[j])
			{
				found = 1;
				break;
			}

		if (!found) {
			domain[d_size] = p[i].second;
			d_size++;
		}
	}

	qsort(domain, d_size, sizeof(int), comapare);
	return d_size;
}

int is_connected(pair *p, int n) {
	int domain[2 * n], d_size;
	d_size = get_domain(p, n, domain);

	for (int i = 0; i < d_size; ++i) {
		int bool = 0;
		for (int j = i + 1; j < d_size; ++j) 
			for (int k = 0; k < n; ++k) 
				if ((p[k].first == domain[i] && p[k].second == domain[j])
				 || (p[k].second == domain[i] && p[k].first == domain[j]))
				{
					bool = 1;
					break;
				}

		if (!bool)
			return 0;
	}
	return 1;
}
int is_partial_order(pair *p, int n) {
	return is_reflexive(p, n) && is_transitive(p, n) && is_antisymmetric(p, n);
}
// // A total order relation is a partial order relation that is connected
int is_total_order(pair *p, int n) {
	return is_partial_order(p, n) && is_connected(p, n);
}
// // Relation R is connected if for each x, y in X:
// // xRy or yRx (or both)
int find_max_elements(pair *p, int n, int *max_el) {
	int result = 0;
	for (int i = 0; i < n; ++i) {
		int bool = 0;
		int found = 0;
		int snd = p[i].second;

		for (int j = 0; j < result; ++j)
			if (snd == max_el[j]) {
				found = 1;
				break;
			}

		if (!found) {
			bool = 1;
			for (int k = 0; k < n; ++k)
			{
				if (p[k].first == snd && p[k].second != snd)
				{
					bool = 0;
					break;
				}
			}
		}

		if (bool) {
			max_el[result] = snd;
			result++;
		}
	}

	qsort(max_el, result, sizeof(int), comapare);
	return result;
}
int find_min_elements(pair *p, int n, int *min_el) {
	int result = 0;
	for (int i = 0; i < n; ++i) {
		int bool = 0;
		int found = 0;
		int snd = p[i].first;

		for (int j = 0; j < result; ++j)
			if (snd == min_el[j]) {
				found = 1;
				break;
			}
		if (!found) {
			bool = 1;
			for (int k = 0; k < n; ++k) {
				if (p[k].second == snd && p[k].first != snd) {
					bool = 0;
					break;
				}
			}
		}

		if (bool)
		{
			min_el[result] = snd;
			result += 1;
		}
	}

	qsort(min_el, result, sizeof(int), comapare);

	return result;
}
// // Case 3:
int composition(pair *p2, int n2, pair *p1, int n1, pair *res)
{
	int size = 0;
	for (int i = 0; i < n2; i++) 
		for (int j = 0; j < n1; j++) 
			if (p2[i].second == p1[j].first) {
				pair tmp;
				tmp.first = p2[i].first;
				tmp.second = p1[j].second;
				size = add_relation(res, size, tmp);
			}

	return size;
}
int cmp(pair p1, pair p2)
{
	if (p1.first == p2.first)
		return p1.second - p2.second;
	return p1.first - p2.first;
}
// // Read number of pairs, n, and then n pairs of ints
int read_relation(pair *p)
{
	int n, f, s;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d"
			  "%d",
			  &f, &s);
		p[i].first = f;
		p[i].second = s;
	}
	return n;
}

void print_int_array(int *array, int n)
{
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void)
{
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	scanf("%d", &to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;
	switch (to_do)
	{
	case 1:
		printf("%d ", is_reflexive(relation, size));
		printf("%d ", is_irreflexive(relation, size));
		printf("%d ", is_symmetric(relation, size));
		printf("%d ", is_antisymmetric(relation, size));
		printf("%d ", is_asymmetric(relation, size));
		printf("%d\n", is_transitive(relation, size));
		break;
	case 2:
		ordered = is_partial_order(relation, size);
		n_domain = get_domain(relation, size, domain);
		printf("%d %d\n", ordered, is_total_order(relation, size));
		print_int_array(domain, n_domain);
		if (!ordered)
			break;
		int max_elements[MAX_REL_SIZE];
		int min_elements[MAX_REL_SIZE];
		int no_max_elements = find_max_elements(relation,
												size, max_elements);
		int no_min_elements = find_min_elements(relation,
												size, min_elements);
		print_int_array(max_elements, no_max_elements);
		print_int_array(min_elements, no_min_elements);
		break;
	case 3:
		size_2 = read_relation(relation_2);
		printf("%d\n", composition(relation, size,
								   relation_2, size_2, comp_relation));
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}