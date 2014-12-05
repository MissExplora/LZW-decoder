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


struct node{
    unsigned short int index;
    struct node *next;
};


struct dict{
    char *link[DICT_SIZE];
};

struct node *root;
struct dict *start;


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
                printf("%hu ", walker->index);
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



int main(int argc, const char * argv[])
{
    root = (struct node *) malloc( sizeof(struct node) );
    root->next = NULL;
    
    get_input();
    
    
    return 0;
}

