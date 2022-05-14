#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STR_LEN 64
#define MAX_PERSONS 1024

typedef struct Person {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;

// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int cmp_person(const void *p1, const void *p2) {
	Person* per1 = (Person*) p1;
	Person* per2 = (Person*) p2;

	int diff = per2->age - per1->age;
	if(diff) return diff;

	int first_diff = strcmp(per1->first_name, per2->first_name);

	if(first_diff) return first_diff;

	return strcmp(per1->last_name, per2->last_name);
}

// Read data to Person array (till EOF)
int read_person_array(Person *persons) {
    char c = '\n';
	int p = 0;


	while(c != EOF) {
		char age_str[MAX_STR_LEN];
		int i = 0;

        while ((c = getchar()) != ' ' && c != '\n' && c != EOF)
			age_str[i++] = c;

		if(i == 0)
			return p;

		age_str[i] = '\0';
		persons[p].age = atoi(age_str);

		i = 0;
		while ((c = getchar()) != ' ')
			persons[p].first_name[i++] = c;
		persons[p].first_name[i] = '\0';

		i = 0;
		while ((c = getchar()) != ' ' && c != '\n' && c != EOF)
			persons[p].last_name[i++] = c;
		persons[p].last_name[i] = '\0';

		p++;
	}
    return p;
}

// Print Person array
void print_person_array(Person *persons, int n) {
	for(int i = 0; i < n; i++) 
		printf("%i %s %s\n", persons[i].age, persons[i].first_name, persons[i].last_name);
}

char* start_of_next_word(char* str) {
	while(str[0] != ' ')
		str += sizeof(char);
	str += sizeof(char);
	return str;
}

int is_woman(char* str) {
	char* last = start_of_next_word(start_of_next_word(str));
	last -= 2 * sizeof(char);
	return *last == 'a';
}

// Sort women first (woman's first name ends with 'a');
// Then sort women by age and men by last name
// Line consists of: age, first_name, last_name
// (int that order)
int cmp_lines(const void *l1, const void *l2) {
	char* s1 = (char*) l1;
	char* s2 = (char*) l2;

	int is_woman1 = is_woman(s1);
	int is_woman2 = is_woman(s2);

	if(is_woman1 && !is_woman2)
		return -1;

	if(!is_woman1 && is_woman2)
		return 1;

	if(is_woman1 && is_woman2)
		return atoi(s1) - atoi(s2);

	char* last1 = start_of_next_word(start_of_next_word(s1));
	char* last2 = start_of_next_word(start_of_next_word(s2));

	return strcmp(last1, last2);
}

// Read lines with students' data (as text)
int read_lines(char lines[][MAX_STR_LEN]) {
	int n = 0;
	char c = '\n';

	while (c != EOF) {
		int i = 0;
		while ((c = getchar()) != '\n' && c != EOF)
			lines[n][i++] = c;

		lines[n][i] = '\0';

		if(i == 0)
			return n;

		n++;
	}
	return n;
}

// Print sorted lines
void print_lines(char lines[][MAX_STR_LEN], int n) {
	for(int i = 0; i < n; i++)
		printf("%s\n", lines[i]);
}

// -------------------------------------------------

int read_int() {
	char buf[MAX_STR_LEN];
	int n;
	fgets(buf, MAX_STR_LEN, stdin);
	sscanf(buf, "%d", &n);
	return n;
}

int main(void) {
	int to_do = read_int();
	int n;
	Person persons[MAX_PERSONS];
	char lines[MAX_PERSONS][MAX_STR_LEN];
	switch (to_do) {
		case 1:
			n = read_person_array(persons);
			qsort(persons, (size_t)n, sizeof(Person), cmp_person);
			print_person_array(persons, n);
			break;
		case 2:
			n = read_lines(lines);
			qsort(lines, (size_t) n, MAX_STR_LEN, cmp_lines);
			print_lines(lines, n);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}
}

