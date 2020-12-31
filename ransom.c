#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
char *readline();
char **split_string(char*);
struct node *arr_to_linked_list(char *arr, int max_words);
void free_linked_list(struct node *head);
bool check_if_poss(struct node *head_magazine,struct node *head_note);



struct node{
	struct node *next;
	char word[6];
};

/**
  *function that checks if all the words in the note are also in the magazine
  *receives the parameters:
  *magazine_count - number of total words in magazine
  *magazine - pointer to the char array of the magazine's words
  *note_count - number of total words in magazine
  *note - pointer to the char array of the magazine's words
  ***/
void checkMagazine(int magazine_count, char **magazine, int note_count, char **note) {
    if (magazine_count < note_count){
    	printf("No");
    	return;
    }
    struct node *head_magazine=arr_to_linked_list(*magazine, magazine_count);
	struct node *head_note=arr_to_linked_list(*note, note_count);
	if (head_note==NULL|| head_magazine==NULL){
		free_linked_list(head_magazine);
		free_linked_list(head_note);
		return;
	}
	bool succeed=check_if_poss(head_magazine, head_note);
	if (succeed){
		printf("Yes");
	}
	else {
		printf("No");
	}
	free_linked_list (head_magazine);
	free_linked_list (head_note);
	free(*magazine);
	free(*note);

}

/*
  *this function returns TRUE if all the words in the note can be found in the
  *magazine, and otherwise returns FALSE.
  *receives the parameters:
  *head_magazine - a pointer to the struct of the head of the magazine linked
  *list.
  *head_note - a pointer to the struct of the head of the note linked list.
 */
bool check_if_poss(struct node *head_magazine,struct node *head_note){
	struct node *note = head_note;
	struct node *magazine = head_magazine;
	while(note != NULL){
		if (magazine==NULL){
			return FALSE;
		}
		while(strcmp(note->word, magazine->word)){
			magazine=magazine->next;
			if (magazine==NULL){
				return FALSE;
			}
		}
		magazine->word[0]='\0';
		note=note->next;
		magazine=head_magazine;
	}
	return TRUE;


}

/*
  *this function receives the arrays entered by the user(each array at a time)
  *and turn the array into a linked list with max_words nodes, which is the
  *array length.
  *receives the parameters:
  *arr - array of all the words
  *max_words - number of words in the array
 */
struct node *arr_to_linked_list(char *arr, int max_words){
	int num_counted_words = 0;
	struct node *head = NULL;
	head = (struct node*)malloc(sizeof(struct node));
	if (head==NULL){
		return NULL;
	}
	head->next= NULL;
	struct node *curr = head;
	int arr_index=0;
	while(num_counted_words<max_words){
		int i;
		for(i=0;arr[arr_index]!='\0';i++, arr_index++){
			curr->word[i]=arr[arr_index];
		}
		arr_index++;
		curr->word[i]='\0';
		num_counted_words++;
		if (num_counted_words != max_words){
			curr->next=(struct node*)malloc(sizeof(struct node));
			if (curr->next==NULL){
				return NULL;
			}
			curr=curr->next;
			curr->next=NULL;
		}
	}
	return head;
}

/*
 * this function receives a pointer to the head of the linked-list and free all
 * the memory allocated by the lists' nodes.
 */
void free_linked_list(struct node *head){
	struct node *temp= head;
	while(head != NULL){
		head= temp->next;
		free(temp);
		temp=head;
	}
}


int main()
{
    char **mn = split_string(readline());

    char *m_endptr;
    char *m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char *n_endptr;
    char *n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char **magazine_temp = split_string(readline());

    char **magazine = malloc(m  *sizeof(char*));

    for (int i = 0; i < m; i++) {
        char *magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char **note_temp = split_string(readline());

    char **note = malloc(n  *sizeof(char*));

    for (int i = 0; i < n; i++) {
        char *note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char *readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char *data = malloc(alloc_length);

    while (true) {
        char *cursor = data + data_length;
        char *line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char **split_string(char *str) {
    char **splits = NULL;
    char *token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*)  *++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
