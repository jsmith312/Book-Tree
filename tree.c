#include "catalog.h"
 
BSTNode 
add(BSTNode root, char *title, int iFlag)
{
    // if the node passed in is null, then it must me a 
    // new node
    if(root == NULL) {
        BSTNode temp;
        // allocate memory for the sie of the node
        temp = (BSTNode)malloc(sizeof(CatalogNode));
        // set the title of the node
        temp->title = title;
        // set the left and right of the newly added node's
        // children to NULL
        temp->left = temp->right = NULL;
        // return the node 
        return temp;
    }
    // if the insentitive option is not given, use strcmp 
    // to determine which child to traverse to (left or right)
    // case-sensitively
    if (!(iFlag)) {
        // if title < root->title
        if(strcmp(title, root->title) < 0) {
            // add the title to the right node
            root->right = add(root->right, title, iFlag);
        }
        // if title > root->title
        else if(strcmp(title, root->title) > 0) {
            // add the title to the left node
            root->left = add(root->left, title, iFlag);
        } 
        else {
            free(title);
        }
    // if the insentitive option is given, use strcasecmp 
    // to determine which child to traverse to (left or right)
    // case-insensitively
    } else {
        // if title < root->title
        if(strcasecmp(title, root->title) < 0) {
            root->right = add(root->right, title, iFlag);
        }
        // if title > root->title
        else if(strcasecmp(title, root->title) > 0) {
            root->left = add(root->left, title, iFlag);
        } else {
            free(title);
        }
    }
    // return the root node
    return root;
}

char* 
findNode(BSTNode root, char *find, int iFlag)
{
    // base case for the find node method 
    // returns NULL if the title is not found
    if (root == NULL) {
        return NULL;
    }
    // if the insentitive option is not given, use strcmp 
    // to determine which child to traverse to (left or right)
    // case-sensitively to find the title
    if (!(iFlag)){
        // if find == root->title 
        if (strcmp(find, root->title) == 0)
            return root->title;
        // if find > root->title
        else if (strcmp(find,root->title) > 0)
            return findNode(root->left, find, iFlag);
        // else find < root->title
        else
            return findNode(root->right, find, iFlag);
    // if the insentitive option is not given, use strcasecmp 
    // to determine which child to traverse to (left or right)
    // case-insensitively to find the title
    } else {
        // if find == root->title
        if (strcasecmp(find, root->title) == 0)
            return root->title;
        // if find > root->title
        else if (strcasecmp(find,root->title) > 0)
            return findNode(root->left, find, iFlag);
        // else find < root->title
        else
            return findNode(root->right, find, iFlag);
    }
}

void 
printTree(FILE *outputFile, BSTNode root, int rFlag )
{   

    if ( root == NULL )
    {
        return;
    }
    // travserse down the right substrees until we reach 
    // the fist node in alphabetical order 
    if (rFlag) {
        printTree(outputFile, root->left, rFlag);
        fprintf(outputFile, "Title:  ");
        fprintf(outputFile, "%s", root->title);
        printTree(outputFile, root->right, rFlag);  
    // else, travserse down the left substrees until we reach 
    // the fist node in alphabetical order
    } else {
        printTree(outputFile, root->right, rFlag);
        fprintf(outputFile, "Title:  ");
        fprintf(outputFile, "%s", root->title);
        printTree(outputFile, root->left, rFlag);     
    }
    
}

BSTNode 
del(BSTNode root, char *title, int iFlag)
{
    // varaible used to hold the int result given after 
    // using strcmp or strcasecmp
    int r;
    // add base case
    if(root == NULL)
        return NULL;
    // create a cursor node to serve as the temp node
    BSTNode cursor;
    // if the i flag is specified use the method for ignoring case 
    // sensitivity and traverse through the tree to find the node we want
    // to delete by checking the left and right children at each node.
    if (!(iFlag))
        r = strcmp(title,root->title);
    else
        r = strcasecmp(title,root->title);
    if( r > 0 ) 
        root->left = del(root->left, title, iFlag);
    else if( r < 0 )
        root->right = del(root->right, title, iFlag);
    // Here we have found the node. we check the node in question's left and
    // right children and set the cursor node to the adjacent node and free
    // the node in question 
    else
    {
        // check the left child and see if it is null
        if (root->left == NULL) {
            // if it is set the cursor as the root's right child
            cursor = root->right;
            // free the root node
            free(root->title);
            free(root);
            // and set the root as the cursor
            root = cursor;
        }
        // check the right child and see if it is null
        else if (root->right == NULL)
        {
            // if it is set the cursor as the root's left child
            cursor = root->left;
            // free the root node 
            free(root->title);
            free(root);
            // and set the root as the cursor
            root = cursor;
        }
        // in the case we have 2 children, set the cursor to the right node and 
        // create a reference to the parent node.
        else    
        {
            cursor = root->right;
            BSTNode parent = NULL;
            // while the left subtree is not null 
            while(cursor->left != NULL) {
                // hold a reference to the parent node
                parent = cursor;
                // set cursor node to the left child
                cursor = cursor->left;
            }
            // allocate space for creating a new root title 
            // from the cursor's title. If we need to allocate
            // memory for the loarger string, then free it once we are done 
            // referencing it.
            int root_len = strlen(root->title);
            int cursor_len = strlen(cursor->title);
            if (cursor_len > root_len) {
                char* new_title= malloc(cursor_len+1);
                strcpy(new_title, cursor->title);
                free(root->title);
                root->title = new_title;
            }
            // otherwise we are not concerned with accessing invalid space if 
            // we strcpy the smaller cursor title. 
            else
                strcpy(root->title, cursor->title);
            // if the parent node is not null, traverse to the left node 
            if (parent != NULL)
                parent->left = del(parent->left, parent->left->title, iFlag);
            // otherwise it is not null, so traverse to the right node
            else
                root->right = del(root->right, root->right->title, iFlag);
        }
    }
    // return root node
    return root;
}


void 
deleteTree(BSTNode root)
{
    if (root == NULL) 
        return;
    // traverse left and right of the tree
    deleteTree(root->left);
    deleteTree(root->right);
 
    /* then delete the node and its title string associated*/
    free(root->title);
    free(root);
}
