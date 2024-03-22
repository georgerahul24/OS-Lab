#include<stdio.h>
#include<stdlib.h>

typedef struct binarytree {
    int key;
    struct binarytree *left;
    struct binarytree *right;
    struct binarytree *parent;
} tree;

tree *BuildBT(int key, tree *parent, tree *left, tree *right) {
    tree *temp = NULL;
    temp = (tree *) calloc(1, sizeof(tree));
    temp->key = key;
    temp->left = left;
    temp->right = right;
    temp->parent = parent;
    return temp;
}

tree *InsertIntoBT(int key, tree *root, tree *parent) {
    if (!root)
        return BuildBT(key, parent, NULL, NULL);
    if (key < root->key)
        root->left = InsertIntoBT(key, root->left, root); // Pass root as parent
    else if (key > root->key)
        root->right = InsertIntoBT(key, root->right, root); // Pass root as parent
    return root;
}


tree *findnode(tree *root, int data) {
    if (!root)
        return NULL;
    if (root->key == data)
        return root;
    tree *left = findnode(root->left, data);
    if (left) {
        return left;
    }
    tree *right = findnode(root->right, data);
    if (right) {
        return right;
    }
    return NULL;
}

int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}

int depth(tree *root, int data) {
    int count = 0;
    tree *temp = findnode(root, data);
    //temp=temp->parent;
    while (temp && temp != root) {
        temp = temp->parent;
        count++;
    }
    return count;
}

int main() {
    tree *root = NULL;
    int key = 0, n = 0;
    while (1) {
        printf("\n1.to enter data into the binary tree");
        printf("\n2.Find a node with a given key value");
        printf("\n4.to find the depth of node with given key value");
        printf("\n.Enter choice:");
        scanf("%d", &n);
        switch (n) {
            case 1: {
                printf("\nenter the data:");
                scanf("%d", &key);
                root = InsertIntoBT(key, root,NULL);
                break;
            }
            case 2: {
                printf("\nenter the key value that you want to search:");
                scanf("%d", &key);
                tree *temp = findnode(root, key);
                printf("\naddress of the required node is %p", temp);
                printf("\nthe value at the given node is %d", temp->key);
                break;
            }

            case 4: {
                printf("\nenter the key value of the node whose depth you want:");
                scanf("%d", &key);
                int d = depth(root, key);
                printf("\ndepth of the node is %d", d);
                break;
            }
        }


    }
    return 0;
}