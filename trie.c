// Copyright [2023] <Junhyoung Lee>
/* trie implements a trie, made of trieNodes. This includes
   code to build, search, and delete a trie
   CSE374, HW5, 23wi 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trienode.h"


/* You'll want to prototype any helper functions you need here */
trieNode* node_creater(void);
int change_ch(char ch);
int* change_word(char* word);
trieNode* insert_word(char* word, trieNode* root);

/* You'll need to implement the functions declare in trienode.h */
/* As well as the helpfer functions you prototype above. */

// build_tree is given a word list (dict), build a trie that holds
// each word. Return pointer to the root node.
trieNode* build_tree(FILE *dict) {
  char word[MAXLEN];
  trieNode* root = node_creater();
  while (fgets(word, MAXLEN, dict)) {
    if ( word[strlen(word)-1] == '\n' ) {
      word[strlen(word) - 1] = '\0';
    }
    insert_word(word, root);
  }
  return root;
}

// This function creates a new node for a trie data struture
trieNode* node_creater(void) {
  trieNode* new_node = (trieNode*)malloc(sizeof(trieNode));
  for (int i = 0; i < BRANCHES; i++) {
    new_node -> branches[i] = NULL;
  }
  new_node -> word = NULL;
  return new_node;
}

// change_ch takes a character as input and returns an integer based on the input character.
int change_ch(char ch) {
  if ((ch == 97) || (ch == 98) || (ch == 99)) {
    return 1;
  } else if ((ch == 100) || (ch == 101) || (ch == 102)) {
    return 2;
  } else if ((ch == 103) || (ch == 104) || (ch == 105)) {
    return 3;
  } else if ((ch == 106) || (ch == 107) || (ch == 108)) {
    return 4;
  } else if ((ch == 109) || (ch == 110) || (ch == 111)) {
    return 5;
  } else if ((ch == 112) || (ch == 113) || (ch == 114)|| (ch == 115)) {
    return 6;
  } else if ((ch == 116) || (ch == 117) || (ch == 118)) {
    return 7;
  } else if ((ch == 119) || (ch == 120) || (ch == 121)|| (ch == 122)) {
    return 8;
  } else {
    return 9;
  }
}


// change_word takes a string as input and returns an array of integers based on the characters in the input string.
int* change_word(char* word) {
  int check = strlen(word);
  int *new_word = malloc(sizeof(int)*check);
  int i = 0;
  while (word[i] != '\0') {
      new_word[i] = change_ch(word[i]);
      i++;
  }
  return new_word;
}


// insert_word takes a string word and a pointer to a trieNode root as input
trieNode* insert_word(char* word, trieNode* root) {
  trieNode* new_temp = root;
  int *wre;
  wre = change_word(word);
  for (int i = 0; word[i] != '\0'; i++) {
    int index = wre[i];
    if (new_temp -> branches[index] == NULL) {
      new_temp -> branches[index] = node_creater();
    }
    new_temp = new_temp -> branches[index];
  }
  while (new_temp -> word != NULL) {
    if (new_temp -> branches[0] == NULL) {
      new_temp -> branches[0] = node_creater();
    }
    new_temp = new_temp -> branches[0];
  }
  new_temp -> word = (char*)malloc((strlen(word) + 1) * sizeof(char));
  strcpy(new_temp -> word, word);
  free(wre);
  return root;
}

// free_tree deletes the entire tree branching from root
void free_tree(trieNode* root) {
  for (int i = 0; i < BRANCHES; i++) {
    free_tree(root -> branches[i]);
  }
  if (root->word != NULL) {
    free(root->word);
  } else {
    return;
  }
  free(root);
  root = NULL;
}

// get_word is given a pattern, return the word stored in the appropriate trieNode
// Given a pattern, return the word stored in the appropriate trieNode.
char* get_word(trieNode *root, char *pattern) {
  trieNode* arc = root;
  for (int i = 0; pattern[i] != '\0'; i++) {
    if (pattern[i] == '#') {
      if (arc->branches[0] == NULL) {
        return "There are no more T9onyms\n";
      }
      arc = arc -> branches[0];
    } else {
      if (pattern[i] > '9' || pattern[i] < '1') {
        return "Not found in current dictionary\n";
      }
      int n = pattern[i] - '1';
      if (arc->branches[n] == NULL) {
        return "Not found in current dictionary\n";
      }
      arc = arc -> branches[n];
    }
  }
  if (arc -> word == NULL) {
    return "Not found in current dictionary\n";
  } else {
    return arc -> word;
  }
}