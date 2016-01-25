#include "trie.h"
#include <string.h>
#include <stdlib.h> 
# include <assert.h>

trienode * alloc_node(){
    trienode * res;
    int i;
    res = (trienode *) malloc(sizeof(trienode));
    res->wordend = 0;			// a memset should do just fine and probably more optimal here ... 
    for (i = 0 ; i < NUM_CHAR; ++i)
        res->children[i] = NULL;
    return res;
}

/*
  load words specified in filename on to the trie
*/
trienode * load_dict(char * filename){
    char line[MAX_WORD_LEN];
    trienode * res = alloc_node();

    FILE *file = fopen(filename, "r");
    if (file){
       while(fgets(line, MAX_WORD_LEN, file)){
           insert_word(line, res);
       }
       fclose(file);
    }
    return res;
}
/*
  helper for load_dict that inserts single word on to trie 
*/

void insert_word(char *word, trienode * trie){
    int i;
    assert(trie);
    trienode *cur = trie;
    while(*word && (*word != '\n')){
        i = *word - 'a';
        assert((i < NUM_CHAR) && (i >= 0));
        if (!cur->children[i]){
            cur->children[i] = alloc_node();
        }
        word++;
        cur = cur->children[i];
        if (!*word)
            cur->wordend = 1;
        else if (*word == '\n')
            cur->wordend = 1;
    }   
}

/*
   prints out words in the dictionary that have the string in word as a prefix
*/

int autocomplete(char *word, trienode *trie){
    int i;
    char * cur = word;
    while(*cur){
        i = *cur - 'a';
	if((i >= NUM_CHAR) || (i < 0) || (!trie->children[i]))
	    return 0;

       trie = trie->children[i];
       cur++;
    }
    printwords(word, trie);
    return 1;
}

void printwords(char *word, trienode *trie){
    char res[MAX_WORD_LEN];
    printwordsHelper(res, 0, word, trie);
}

void printwordsHelper(char *res, int i, char *word, trienode *trie){
    int j;
    if (!trie)
        return;
    if (trie->wordend)
        printword(res, i, word);
    for (j = 0 ; j < NUM_CHAR; ++j){
        res[i] = (char)((int)'a' + j);
        printwordsHelper(res, i+1, word, trie->children[j]);
    }
}

void printword(char *res, int i, char * pref){
    int j;
    printf("%s",pref);
    for (j = 0; j < i; ++j)
        printf("%c",res[j]);
     printf("\n");
}

/*
  answers if the string in word is present in the trie 
*/
int find(char * word, trienode * trie){
    int i;
    trienode *cur = trie;
     while(*word){
        i = *word - 'a';
	if((i >= NUM_CHAR) || (i < 0) || (!trie->children[i]))
            return 0;
        cur = cur->children[i];
        word++;
     }
     return 1;
}

/*
  print words in the trie
*/
void print(trienode *trie){
    char word[MAX_WORD_LEN];
    printf("printing trie\n");
    printwords("", trie);
}

/*
  delete trie
*/
void deletetrie(trienode * trie){
    int i;
    if (trie){
        for (i = 0; i < NUM_CHAR; ++i){
            deletetrie(trie->children[i]);
        }
        free(trie);
    }
}
