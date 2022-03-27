#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// consider chars from [FIRST_CHAR, LAST_CHAR)
#define FIRST_CHAR 33
#define LAST_CHAR 127
#define MAX_CHARS (LAST_CHAR - FIRST_CHAR)
#define MAX_DIGRAMS (LAST_CHAR - FIRST_CHAR) * (LAST_CHAR - FIRST_CHAR)

#define NEWLINE '\n'
#define IN_WORD 1

#define IN_LINE_COMMENT 1
#define IN_BLOCK_COMMENT 2

#define TEST 0   // 1 dla testowania, 0 dla automatycznej oceny

int count[MAX_DIGRAMS] = { 0 };

// function to be used as comparator to qsort (compares counters and thes sorts
// alphabetically when equal)
int cmp (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	if (count[va] == count[vb]) return va - vb; // sort alphabetically if counts equal
	return count[vb] - count[va];
}

// function to be used as comparator to qsort for digrams (compares counters and
// thes sorts alphabetically when equal)
int cmp_di (const void *a, const void *b) {
	int va = *(int*)a;
	int vb = *(int*)b;
	// sort according to second char if counts and the first char equal
	if (count[va] == count[vb] && va / MAX_CHARS == vb / MAX_CHARS) return va % MAX_CHARS - vb % MAX_CHARS;
	// sort according to first char if counts equal
	if (count[va] == count[vb]) return va / MAX_CHARS - vb / MAX_CHARS;
	return count[vb] - count[va];
}

// count number of lines (nl), number of words (nw) and number of characters
// (nc) in the text read from stream
void wc(int *nl, int *nw, int *nc, FILE *stream)
{
    *nl = 0;
    *nw = 0;
    *nc = 0;
    char ch;
    int in = 0;
    
    while ((ch = fgetc(stream)) != EOF) {
        *nc += 1;
    
        if(ch == ' ' || ch == '\t' || ch == '\0' || ch == '\n') {
            if (in == 1) {
                in = 0;
                *nw += 1;
            }
    
            if(ch = '\0' || ch == '\n') {
              *nl += 1;
            }
        }
        else {
          in = 1;
        }
    }
}

// count how many times each character from [FIRST_CHAR, LAST_CHAR) occurs
// in the text read from stream. Sort chars according to their respective
// cardinalities (decreasing order). Set n_char and cnt to the char_no - th char
// in the sorted list and its cardinality respectively
void char_count(int char_no, int *n_char, int *cnt, FILE *stream)
{
    *n_char = 0;
    *cnt = 0;

    int count[MAX_CHARS];
    int count_copy[MAX_CHARS];
    int indexes[MAX_CHARS];
    
    for(int i = 0; i < MAX_CHARS; i++) {
        count[i] = 0;
        indexes[i] = i;
    }
    
    while(1) {
        char ch = getc(stream);
        
        if(ch == EOF) {
            break;
        }
        
        count[ch - FIRST_CHAR] += 1;
    }
    
    for(int i = 0; i < MAX_CHARS; i++) {
        count_copy[i] = count[i];
    }
    
    for(int i = 0; i < MAX_CHARS; i++) {
        int sorted = 1;
        for(int j = 0; j < MAX_CHARS - i - 1; j++) {
            if(count_copy[j] < count_copy[j + 1]) {
                int tmp = count_copy[j];
                int temp = indexes[j];
                count_copy[j] = count_copy[j + 1];
                indexes[j] = indexes[j + 1];
                count_copy[j + 1] = tmp;
                indexes[j + 1] = temp;
                sorted = 0;
            }
        }
        if(sorted == 1) {
            break;
        }
    }
    
    *n_char = '!' + indexes[char_no - 1];
    *cnt = count[indexes[char_no - 1]];
}

// count how many times each digram (a pair of characters, from [FIRST_CHAR,
// LAST_CHAR) each) occurs in the text read from stream. Sort digrams according
// to their respective cardinalities (decreasing order). Set digram[0] and
// digram[1] to the first and the second char in the digram_no - th digram_char
// in the sorted list. Set digram[2] to its cardinality.
void digram_count(int digram_no, int digram[], FILE *stream)
{
    int count[MAX_CHARS*MAX_CHARS];
    int indexes[MAX_CHARS*MAX_CHARS][2];
    
    for(int i = 0; i < MAX_CHARS*MAX_CHARS; i++) {
        count[i] = 0;
        indexes[i][0] = i/MAX_CHARS;
        indexes[i][1] = i%MAX_CHARS;
    }
    
    char last_char = getc(stream);
    char ch = getc(stream);
    
    while(1) {
        if(ch == EOF) {
            break;
        }
        
        if(last_char != '\n' && ch != '\n' && last_char != EOF && ch != EOF && last_char != ' ' && ch != ' ') {
            count[(last_char - FIRST_CHAR) * MAX_CHARS + (ch - FIRST_CHAR)] += 1;
        }
        
        last_char = ch;
        ch = getc(stream);
    }
    
    for(int i = 0; i < MAX_CHARS*MAX_CHARS; i++) {
        for(int j = 0; j < MAX_CHARS*MAX_CHARS - i - 1; j++) {
            if(count[indexes[j][0] * MAX_CHARS + indexes[j][1]] < count[indexes[j+1][0] * MAX_CHARS + indexes[j+1][1]]) {
                int l_ind = indexes[j][0];
                int r_ind = indexes[j][1];
                indexes[j][0] = indexes[j+1][0];
                indexes[j][1] = indexes[j+1][1];
                indexes[j+1][0] = l_ind;
                indexes[j+1][1] = r_ind;
            }
        }
    }    
    
    digram[0] = '!' + indexes[digram_no - 1][0];
    digram[1] = '!' + indexes[digram_no - 1][1];
    digram[2] = count[indexes[digram_no - 1][0] * MAX_CHARS + indexes[digram_no - 1][1]];
}

// Count block and line comments in the text read from stream. Set
// line_comment_counter and block_comment_counter accordingly
void find_comments(int *line_comment_counter, int *block_comment_counter, FILE *stream)
{
    *line_comment_counter = 0;
    *block_comment_counter = 0;
    int state = 0;
    
    int last_char;
    int ch;
    int flag = 0;
    int cudz = 0;
    
    last_char = getc(stream);
    ch = getc(stream);
    
    while(1) {
        if(ch == EOF) {
            break;
        }
        else if(flag > 0) {
            flag -= 1;
        }
        else if(cudz > 0) {
            cudz -= 1;
        }
        else if(cudz == 0 && state == 0 && (ch == '"' || ch == '\'')) {
            state = 3;
            cudz = 2;
        }
        else if(cudz == 0 && state == 3 && last_char != '/' && (ch == '"' || ch == '\'')) {
            state = 0;
        }
        else if(state == 0 && last_char == '/' && ch == '/') {
            state = 1;
            *line_comment_counter += 1;
            last_char = ch;
            ch = getc(stream);
            continue;
        }
        else if(state == 1 && last_char == '\n' || ch == '\n') {
            state = 0;
        }
        else if(state == 0 && last_char == '/' && ch == '*' && flag == 0) {
            state = 2;
            *block_comment_counter += 1;
            flag = 2;
        }
        else if(state == 2 && flag == 0 && last_char == '*' && ch == '/') {
            state = 0;
        }
        
        last_char = ch;
        ch = getc(stream);
    }
}

int main(void) {
	int to_do;
	int nl, nw, nc, char_no, n_char, cnt;
	int line_comment_counter, block_comment_counter;
	int digram[3];

	char file_name[40];
	FILE *stream;

	if(TEST) printf("Wpisz nr zadania ");
	scanf ("%d", &to_do);
    if(TEST)  stream = stdin;
    else {
        scanf("%s",file_name);
        stream = fopen(file_name,"r");
        if(stream == NULL) {
            printf("fopen failed\n");
            return -1;
        }
    }

//	to_do = read_line();
	switch (to_do) {
		case 1: // wc()
			wc (&nl, &nw, &nc, stream);
			printf("%d %d %d\n", nl, nw, nc);
			break;
		case 2: // char_count()
//			char_no = read_line();
            if(TEST) printf("Wpisz numer znaku ");
            scanf("%d",&char_no);
			char_count(char_no, &n_char, &cnt, stream);
			printf("%c %d\n", n_char, cnt);
			break;
		case 3: // digram_count()
//			char_no = read_line();
            if(TEST) printf("Wpisz numer digramu ");
            scanf("%d",&char_no);
			digram_count(char_no, digram, stream);
			printf("%c%c %d\n", digram[0], digram[1], digram[2]);
			break;
		case 4:
			find_comments(&line_comment_counter, &block_comment_counter, stream);
			printf("%d %d\n", block_comment_counter, line_comment_counter);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}