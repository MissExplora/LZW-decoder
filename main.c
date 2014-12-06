//
//  lzwdekoder.c
//  TINF labos
//
//  Created by Dora Budić on 05/12/14.
//  Copyright (c) 2014 Dora Budić. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPH_SIZE 256
#define DICT_SIZE 65536


unsigned short int counter = 0;

struct node{
    unsigned short int index;
    struct node *next;
};

struct trie_node{
    unsigned short int index;
	char value;
	struct trie_node *link[ALPH_SIZE];
};

struct leave{
    char letters[ALPH_SIZE];
    struct trie_node *pointer;
};

struct dict{
    struct leave *words[DICT_SIZE];
};

struct node *root;
struct dict *start;
struct trie_node *trie_root = NULL;


struct leave *create_leave()
{
    struct leave *q;
    q = (struct leave*) malloc( sizeof(struct leave) );
    memset(q->letters, 0, sizeof(q->letters));
    return q;
}

struct trie_node *create_trie_node() {
    struct trie_node *q = (struct trie_node*) malloc( sizeof(struct trie_node) );
    for(int x=0 ; x < ALPH_SIZE ; x++)
        q->link[x] = NULL;
    q->value = '\0';
    return q;
}


void get_input()
{
    struct node *walker, *new;
    walker = root;
    
    char character;
    char creater[DICT_SIZE] = {};
    
    FILE *f;
	f = fopen("/Users/Dora/Desktop/TINF labos/ulazna2", "r");
	
	if( f == NULL ) {
    	perror("Error while opening the file.\n");
     	exit(EXIT_FAILURE);
   	}
   	else {
        int i = 0;
   		while ((character = fgetc(f)) != EOF && i < DICT_SIZE) {
            if (character == ' ') {
                new = (struct node *) malloc( sizeof(struct node) );
                new->next = NULL;
                walker->index = (unsigned short) atoi(creater);
                //printf("%hu ", walker->index);
                walker->next = new;
                walker = walker->next;
                memset(creater, 0, sizeof(creater));
                i = 0;
            }
            else {
                creater[i] = character;
                i++;
            }
        }
        walker->index = (unsigned short) atoi(creater);
        walker->next = NULL;
        printf("%hu ", walker->index);
   	}
    
    fclose(f);
    
}


void create_dict()
{
    start = (struct dict*) malloc( sizeof(struct dict) );
    for (int x=0; x < DICT_SIZE ; x++) {
        memset(start->words[x]->letters, 0, sizeof(start->words[x]->letters));
    }
}


void start_dictionary()
{
    create_dict();
    trie_root = create_trie_node();
    for (int i=32; i<127; i++) {
        struct leave *l = create_leave();
        struct trie_node *t = create_trie_node();
		t->value = (char) i;
        trie_root->link[counter] = t;
        counter++;
        l->letters[0] = (char) i;
        l->pointer = t;
        start->words[i] = l;
        
    }
}


void decode()
{
    start_dictionary();
    get_input();
    
    struct node *walker;
    struct trie_node *monkey;
    walker = root;
    
    while(walker->next != NULL) {
        char first[ALPH_SIZE] = {};
        char second[2] = {};
        monkey = trie_root;
        
        if (start->words[walker->index]->letters[0] != '\0') {
            printf("%s", start->words[walker->index]->letters);
            strcat(first, start->words[walker->index]->letters);
            monkey = start->words[walker->index]->pointer;
            walker = walker->next;
            if (start->words[walker->index]->letters[0] != '\0') {
                second[0] = start->words[walker->index]->letters[0];
                strcat(first, second);
                strcat(start->words[counter]->letters, first);
                for (int i=0; i<ALPH_SIZE;i++){
                    if (monkey->link[i] == NULL) {
                        monkey->link[i] = create_trie_node();
                        monkey->link[i]->value = second[0];
                        start->words[counter]->pointer = monkey->link[i];
                        break;
                    }
                }
                counter++;
                
                
                
            }
            
        }
    }
}



int main(int argc, const char * argv[])
{
    root = (struct node *) malloc( sizeof(struct node) );
    root->next = NULL;
    
    //get_input();
    
    
    return 0;
}

