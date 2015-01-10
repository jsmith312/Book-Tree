#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
 

 #define TRUE    1
 #define FALSE   0

 #define MAXLINESIZE 161

typedef struct CatalogNode *BSTNode;

// Catalog node used as a BST node which contains a 
// character pointer to the title in the file and 
// references to the left and right children
struct CatalogNode{
    char *title;
    BSTNode left;
    BSTNode right;
} CatalogNode;

// process the command line options
void 
processOpts(int argc, char *argv[], char *progName, int *rFlag, 
          int *iFlag);
// usage statment 
void 
usage(char *progName, FILE *file);
// process the input file 
BSTNode 
processInputFile(FILE *inputFile, FILE *outputFIle,
        int rFlag, int iFlag);
// process the commands file
BSTNode 
processCommands(FILE *cmdFile, FILE *outputFile,
        int rFlag, int iFlag, BSTNode root);
// add node to the binary search tree
BSTNode 
add(BSTNode root, char *title, int iFlag);
// print the BST recursively
void 
printTree(FILE *outputFile, BSTNode root, int rFlag);
// find and return a reference to the BST node title
char* 
findNode(BSTNode root, char *find, int iFlag);
// delete node from the BST
BSTNode 
del(BSTNode root, char *title, int iFlag);
// delete the tree once we are done with it
void 
deleteTree(BSTNode root);
