#include "catalog.h"

BSTNode 
processInputFile(FILE *inputFile, FILE *outputFile,
            int rFlag, int iFlag)
{
    // initailize array for each line in the file
    char readLine[MAXLINESIZE];
    // pointer to the title
    char *title;
    // initialize the root node
    BSTNode root = NULL;
    // while we dont reach the end of the file
    while (!(feof(inputFile))) {
        // Break out of the loop when we have hit the end of the file
        if (fgets(readLine, MAXLINESIZE, inputFile) == NULL) {
            break;
        }
        // if the first 8 characters in the line are 'Title  '
        if (strncmp("Title:  ", readLine, 8) == 0) {   
            // allocate the size of the string
            title = malloc(strlen(readLine)-7);
            // copy the result to title 
            strcpy(title, readLine + 8);
            // add the title to our BST
            root = add(root, title, iFlag);
        }
    }
    // return the root node
    return root;
}

BSTNode 
processCommands(FILE *cmdFile, FILE *outputFile, 
                int rFlag, int iFlag, BSTNode root)
{
    // initailize array for each line in the file
    char readLine[MAXLINESIZE];
    // pointer to the title in the BST
    char *title;
    // pointer to the result of the findNode when TITLE is present
    char *find_title;
    // pointer to the result of the findNode when ADD is present
    char *find_add;
    // pointer to the result of the findNode when DELETE is present
    char* find_del;
    // while we dont reach the end of the file
    while (!feof(cmdFile)) {
        // if there is nothing from the command file to put in readline
        // then break out of the loop
        if (fgets(readLine, MAXLINESIZE, cmdFile) == NULL) {
            break;
        }
        // If TITLE is in the first 6 characters of the line
        if (strncmp("TITLE ", readLine, 6) == 0) {   
            // allocate memory for the max line size
            title = malloc(MAXLINESIZE);
            // copy the read line to the allocated space
            strcpy(title, readLine + 6);
            // print TITLE
            printf("TITLE\n");
            // find the title in the BST
            find_title = findNode(root, title, iFlag);
            // if the title was not found in the BST 
            // print NOT FOUND to stdout
            if (find_title == NULL)
                printf("NOT FOUND: %s", title);
            else
                printf("FOUND: %s",title);
            // free the title string, we are done with it.
            free(title);
        }
        // If SAVE-TITLE is in the line:
        if (strncmp("SAVE-TITLES", readLine, 11) == 0) {
            // print SAVE-TITLES to stdout
            printf("%s\n","SAVE-TITLES");
            // print the tree
            printTree(outputFile, root, rFlag);
        }
        // If ADD is in the line:
        if (strncmp("ADD ", readLine, 4) == 0) {
            // allocate memory space for the line
            title = malloc(MAXLINESIZE);
            // copy the rest of the string to the title 
            // string 
            strcpy(title, readLine + 4);
            // print ADD the stdout 
            printf("ADD\n");
            // look for the title we wish to add 
            find_add = findNode(root, title, iFlag);
            // if the title is not already there, add it
            // the the BST
            if (find_add == NULL) {
                // print ADDED to stdout
                printf("ADDED: %s",title);   
                // assign the new root returned by the delete function
                root = add(root, title, iFlag);
            }
            // otherwise print FOUND to stdout
            else{
                // print FOUND to stdout
                printf("FOUND: %s", title);
                // free the title strings
                free(title);
            }
        }
        // If DELETE-TITLE is in the first 13 lines
        if (strncmp("DELETE-TITLE ", readLine, 13) == 0) {
            // allocate space for the line
            title = malloc(MAXLINESIZE);
            // copy the title to the line
            strcpy(title, readLine+13);
            //int status = 0;
            printf("DELETE-TITLE\n");
            // find the node that we wish to delete
            find_del = findNode(root, title, iFlag);                
            // if the outcome of the find command is NULL
            // we havent found the title 
            if (find_del == NULL) {
                // print not found
                printf("NOT FOUND: %s",title);
                free(title);
            } 
            // if the title was found, call del() 
            // and print to stdout DELETED
            else {
                root = del(root, title, iFlag);
                // print DELETED to stdout
                printf("DELETED: %s",title);
                // free the title string since del() doesnt hold a 
                // reference to it  
                free(title);
            }
        }
    }
    // print the new line character
    printf("\n");
    // return the root
    return root;
}