#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 1000
#define MAX_RANGE 1000

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);

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
int is_transitive(pair* pairs, int n) {
	for(int i = 0; i < n; i++) 
		for(int j = 0; j < n; j++) {
			if(pairs[i].second != pairs[j].first)
				continue;

			int ok = 0;
			for(int k = 0; k < n; k++)
				if(pairs[i].first == pairs[k].first && pairs[j].second == pairs[k].second){
					ok = 1;
					break;
				}

			if(!ok)
				return 0;
		}
	return 1;
}

// Case 2:
// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair*, int);
// A total order relation is a partial order relation that is connected
int is_total_order(pair*, int);
// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair*, int);
int find_max_elements(pair*, int, int*);
int find_min_elements(pair*, int, int*);
int get_domain(pair*, int, int*);

// Case 3:
int composition (pair*, int, pair*, int, pair*);

int cmp (pair p1, pair p2) {
	if (p1.first == p2.first) return p1.second - p2.second;
	return p1.first - p2.first;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair* tab) {
	int n;
	scanf("%d",&n);
	for(int i = 0; i < n; i++) {
		scanf("%d",&tab[i].first);
		scanf("%d",&tab[i].second);
	}
	return n;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		// case 2:
		// 	ordered = is_partial_order(relation, size);
		// 	n_domain = get_domain(relation, size, domain);
		// 	printf("%d %d\n", ordered, is_total_order(relation, size));
		// 	print_int_array(domain, n_domain);
		// 	if (!ordered) break;
		// 	int max_elements[MAX_REL_SIZE];
		// 	int min_elements[MAX_REL_SIZE];
		// 	int no_max_elements = find_max_elements(relation, size, max_elements);
		// 	int no_min_elements = find_min_elements(relation, size, min_elements);
		// 	print_int_array(max_elements, no_max_elements);
		// 	print_int_array(min_elements, no_min_elements);
		// 	break;
		// case 3:
		// 	size_2 = read_relation(relation_2);
		// 	printf("%d\n", composition(relation, size,
		// 	   relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}