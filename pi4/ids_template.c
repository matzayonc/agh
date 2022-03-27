#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2
#define IN_STRING 4
#define IN_CHAR 5
#define IN_ID 8

#define MAX_ID_LEN 64
#define MAX_IDS 1024

int index_cmp(const void*, const void*);
int cmp(const void*, const void*);

char tab[MAX_IDS][MAX_ID_LEN];

#define AMOUNT_OF_KEYWORDS 32
char *keywords[] = {
	"auto", "break", "case", "char",
	"const", "continue", "default", "do",
	"double", "else", "enum", "extern",
	"float", "for", "goto", "if",
	"int", "long", "register", "return",
	"short", "signed", "sizeof", "static",
	"struct", "switch", "typedef", "union",
	"unsigned", "void", "volatile", "while"
};

#define MAX_LINE 128

int is_valid(char c){
	if(c >= 'A' && c <= 'Z') return 1;
	if(c >= 'a' && c <= 'z') return 1;
	if(c == '_') return 1;
	if(c >= '0' && c <= '9') return 2;

	return 0;
}

int is_keyword(char* c) {
	for(int i = 0; i < AMOUNT_OF_KEYWORDS; i++) {
		int f = strcmp(c, keywords[i]);

		if (f < 0) return 0;
		if (f == 0) return 1;
	}

	return 0;
}


void print_tab(int n) {
	for (int i = 0; i < n; i++)
		printf("tab[%d] = %s\n", i, tab[i]);
}


int set_id(char* word, int index) {
	// qsort(tab, index, MAX_ID_LEN, cmp);

	for(int i = 0; i < index; i++) 
		if (strcmp(word, tab[i]) == 0) 
			return 1;

	tab[index][0] = word[0];
	for(int i = 1; word[i-1] != '\0'; i++) 
		tab[index][i] = word[i];

	printf("set %s\n", tab[index]);
	// print_tab(index+1);
	return 0;
}

int find_idents() {

	char line[MAX_LINE];
	char current[MAX_ID_LEN];
	int head = 0;
	int current_head = 0;

	int status = 0;



	while(1) {
		if(fgets (line, MAX_LINE, stdin) == NULL)
			return head;

		int i = 0;

		while(line[i] != '\n') { 

			if(status == IN_BLOCK_COMMENT) {
				if(line[i] == '*' && line[i+1] == '/') 
					status = 0;
				i++;
				continue;
			} else if(status == IN_STRING) {
				if(line[i] == '"')
					status = 0;
				i++;
				continue;
			} else if(status == IN_CHAR) {
				if(line[i] == '\'')
					status = 0;
				i++;
				continue;
			}


			int valid = is_valid(line[i]);
			
			if (valid == 1 || (current_head != 0 && valid == 2)) {
				current[current_head++] = line[i];
			} 
			
			if ((valid != 1 && (current_head == 0 || valid != 2)) || line[i+1] == '\n') {
				current[current_head++] = '\0';
				if(current_head > 1 && is_keyword(current) == 0) {

					if (set_id(current, head++))
						head--; // if exists don't increment

					// printf("c: %d, w: %s\n", current_head-1, current);
				}

				current_head = 0;

				if(line[i] == '/' && line[i+1] == '*') {
					i ++;
					status = IN_BLOCK_COMMENT;
				}
				else if(line[i] == '/' && line[i+1] == '/') {
					break;
				}
				else if(line[i] == '"') {
					status = IN_STRING;
				}
				else if(line[i] == '\'') {
					status = IN_CHAR;
				}


			}

			i++;
		}
 

		// sscanf (line, "%d", &n);
		// printf("o: %s", line);
	}



	return head;

}

int cmp(const void* first_arg, const void* second_arg) {
	char *a = *(char**)first_arg;
	char *b = *(char**)second_arg;
	return strcmp(a, b);
}

int index_cmp(const void* first_arg, const void* second_arg) {
	int a = *(int*)first_arg;
	int b = *(int*)second_arg;
	return strcmp(tab[a], tab[b]);
}

int main(void) {
	printf("%d\n", find_idents());



	return 0;
}

