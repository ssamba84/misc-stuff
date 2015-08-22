# include <stdio.h>
# include <assert.h>

# define NUM_CHAR  26
# define MAX_WORD_LEN  40

typedef struct trienode{
   struct trienode * children[NUM_CHAR];
   int wordend;
}trienode;

trienode * alloc_node();
void insert_word(char *word, trienode *trie);
int find(char *, trienode *);
void print(trienode * );
trienode * load_dict(char *);
void deletetrie(trienode *);
int autocomplete(char *word, trienode *trie);
void printwords(char *word, trienode *trie);
void printwordsHelper(char *res, int i, char *word, trienode *trie);
void printword(char *res, int i, char * pref);
