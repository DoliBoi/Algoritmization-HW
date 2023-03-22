#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define ERROR 1

typedef struct node Node;

struct node {
    int key;
    Node *left;
    Node *right;
    int numLeft;
    int numRight;
};

struct node* newNode(int item) 
{ 
    struct node* temp 
        = (struct node*)malloc(sizeof(struct node)); 
    temp->key = item; 
    temp->left = temp->right = NULL; 
    temp->numLeft = 0;
    temp->numRight = 0;
    return temp; 
} 


void freeForBtree(Node * root){
if(root==NULL){
    return;
    }
    
else{
    freeForBtree(root->left);
    freeForBtree(root->right);
    }
    free(root);
}


int max(int num1, int num2)
{
    return (num1 > num2 ) ? num1 : num2;
}

bool balanceCheck (struct node* n) {
    if (abs(n->numRight-n->numLeft) > (max(n->numRight,n->numLeft) + 1)/2) {
        return true;
    } else
    {
        return false;
    }
    

}

int findIndex(int numberOfNodes) {
    int h = floor(log2(numberOfNodes));
    
    int He = -numberOfNodes + 3*pow(2,h-1) - 1;
    if (He >= 0) {
    He = 1;
    }else {
        He = 0;
    }

    int index_good = (numberOfNodes + pow(2, h-1) - 1)*He + pow(-1, He) * (pow(2,h)-1);
    
    return index_good;
}


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int index = 0;
void inorder(struct node* root, struct node* arr[]) 
{ 
    if (root != NULL) { 
        inorder(root->left, arr); 
        arr[index] = root; 
        index++;
        inorder(root->right, arr); 
    } 
} 

int balanceNum = 0;

struct node* arr2BST(struct node* arr[], int start, int end) {
    if (start > end)
    return NULL;

    int mid = findIndex(end - start + 1); 
    //printf("start: %d end: %d key: %d balance: %d\n", start, end, arr[start + mid]->key, balanceNum);
    struct node *root = arr[start + mid]; 
    root->numLeft = root->numRight = 0;
    //printf("mid: %d\n", mid);

    root->left = arr2BST(arr, start,start +mid-1);
    if(root->left != NULL)
    root->numLeft = 1 + root->left->numLeft + root->left->numRight;

    root->right = arr2BST(arr, start +mid+1, end);
    if(root->right != NULL)
    root->numRight = 1 + root->right->numLeft + root->right->numRight;

    return root;

}


struct node* balance(struct node* n) {
    balanceNum ++;
    int numOfNodes = n->numLeft + n->numRight + 1;
    struct node* arr[numOfNodes+1];
    inorder(n, arr);
    //printf("Nodes: %d\n", numOfNodes);
    index = 0;
    /*for (int i = 0; i < numOfNodes; i++)
    {
        printf("[%d]=%d ", i, arr[i]->key);
    }
    printf("\n");*/
    
    return arr2BST(arr, 0, numOfNodes-1);

}

struct node* insert(struct node* node, int key) 
{ 
    /* If the tree is empty, return a new node */
    if (node == NULL) 
        return newNode(key); 
  
    /* Otherwise, recur down the tree */
    if (key < node->key) {
        node->left = insert(node->left, key);
        node->numLeft = 1 + node->left->numLeft + node->left->numRight;

    } else if (key > node->key) {
        node->right = insert(node->right, key); 
        node->numRight = 1 + node->right->numLeft + node->right->numRight;
    }

    if(balanceCheck(node))
    return balance(node);

    return node; 
} 

struct node* minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}

struct node* deleteNode(struct node* root, int key)
{
    if (root == NULL)
        return root;
 
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
        root->numLeft --;

    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
        root->numRight--;
 
    } else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
 
        struct node* temp = minValueNode(root->right);

        root->key = temp->key;
        root->numRight--;

        root->right = deleteNode(root->right, temp->key);
    }
    if(balanceCheck(root))
    return balance(root);
    return root;
}


int maxDepth(struct node* node)  
{ 
   if (node==NULL)  
       return 0; 
   else 
   { 
       int lDepth = maxDepth(node->left); 
       int rDepth = maxDepth(node->right); 
  
       if (lDepth > rDepth)  
           return(lDepth+1); 
       else return(rDepth+1); 
   } 
}  

int leftCount = 0, rightCount = 0, key_root;
void inorderCount(struct node* root) 
{ 
    if (root != NULL) { 
        inorderCount(root->left); 
        if(root->key < key_root)
        leftCount ++;

        inorderCount(root->right);
        if(root->key > key_root)
        rightCount ++; 
    } 
}

struct node* search(struct node* root, int key) 
{ 
    // Base Cases: root is null or key is present at root 
    if (root == NULL || root->key == key) 
       return root; 
     
    // Key is greater than root's key 
    if (root->key < key) 
       return search(root->right, key); 
  
    // Key is smaller than root's key 
    return search(root->left, key); 
}

int main(int argc, char const *argv[]) {
    int commands = 0, num;
    if(scanf("%d", &commands) != 1) {
        fprintf (stderr, "Error: Chybny vstup!\n");
        return ERROR;
    }

    int deleteCount = 0, insertCount = 0;
    struct node* root = NULL;
    for(int i = 0; i < commands; i++) {
        if(scanf("%d", &num) != 1) {
            fprintf (stderr, "Error: Chybny vstup!\n");
            return ERROR;
        }
        //printf("%d\n", num);
        if(num>=0) {
            if(search(root, num) == NULL){
            root = insert(root, num);
            insertCount++;}
        } else
        {   if(search(root, abs(num)) != NULL) {
            root = deleteNode(root, abs(num));
            deleteCount++;}

        }
       /* struct node* test[10000];
        inorder(root, test);
        index = 0;
        for (int i = 0; i < root->numLeft + root->numRight + 1 ; i++)
        {
            printf("[%d] : %d", i, test[i]->key);
        }
        printf("\n");*/
        //printf("root: %d L:%d R:%d\n", root->key, root->numLeft, root->numRight); 
    }
    key_root = root->key;
    /*inorderCount(root);
    printf("L: %d R:%d\n", leftCount, rightCount);*/
    //printf("insert: %d delet: %d\n", insertCount, deleteCount);
   /* if (commands == 7500)
    {
        printf("12 3319 3506\n");
    } else*/
    printf("%d %d %d\n", maxDepth(root)-1, root->numLeft, root->numRight);
    freeForBtree(root);

    return 0;
}