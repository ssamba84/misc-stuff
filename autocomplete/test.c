#include "trie.h"
int print_and_read(const char * prompt, char * out){
    printf("%s ", prompt);
    if(scanf("%s", out) != 1)
        return 0;
    return 1;
}
void driver(trienode *node){
    char input[MAX_WORD_LEN];
    while(print_and_read("Enter word to autocomplete", input)){
	autocomplete(input,node);
    }
}

int main(int argc, char *argv[]){
    trienode * node; 
    char input[MAX_WORD_LEN];
    if (argc < 2){
        printf("Enter filename containing dictionary as argument\n");
        return 0;
    }

    node = load_dict(argv[1]);
    driver(node);
    deletetrie(node);
    return 1;
}
