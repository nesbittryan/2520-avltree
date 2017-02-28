#include "avltree.h"

int main () {
    printf("\n--------------------------------\n");
    printf("| Welcome,                     |\n");
    printf("| Made by Ryan Nesbitt, 0915819|\n");
    printf("--------------------------------\n");
    int input;
    int searchCount;
    char * filename;
    if((filename = malloc(sizeof(char) * 20)) == NULL) {
		printf("Memory Allocation Failed\n");
		return(-1);
	}
    char * searchKey;
    if((searchKey = malloc(sizeof(char) * 20)) == NULL) {
		printf("Memory Allocation Failed\n");
		return(-1);
	}
    Head * head;
    do {
        printf("\n1.Initialization\n");
        printf("2.Find\n");
        printf("3.Insert\n");
        printf("4.Remove\n");
        printf("5.Check Height and Size\n");
        printf("6.Find All (above a given frequency)\n");
        printf("7.Exit\n");
        printf("Please Enter an Option: \navl/> ");
        scanf("%d", &input);
        switch(input) {
            case 1:
                printf("Filename : ");
                scanf("%s", filename);
                head = initializeTree(filename);
                break;
            case 2:
                if(head == NULL) {
                    printf("Tree Uninitialized\n");
                    break;
                }
                printf("Find Key: ");
                scanf("%s", searchKey);
                if(displayKey(head->node, searchKey) == 0) {
                    printf("No Such Key\n");
                }
                break;
            case 3:
                if(head == NULL) {
                    printf("Tree Uninitialized\n");
                    break;
                }
                printf("Insert Key: ");
                scanf("%s", searchKey);
                head->node = addNode(head->node, searchKey);
                if(displayKey(head->node, searchKey) == 0) {
                    printf("No Such Key\n");
                }
                break;
            case 4:
                if(head == NULL) {
                    printf("Tree Uninitialized\n");
                    break;
                }
                printf("Remove Key: ");
                scanf("%s", searchKey);
                head->node = removeNode(head->node, searchKey);
                if(displayKey(head->node, searchKey) == 0) {
                    printf("No Such Key\n");
                }
                break;
            case 5:
                if(head == NULL) {
                    printf("Tree Uninitialized\n");
                    break;
                }
                printf("Height of Tree is: %d\n",height(head->node));
                printf("Size of Tree is: %d\n", size(head->node));
                break;
            case 6:
                if(head == NULL) {
                    printf("Tree Uninitialized\n");
                    break;
                }
                printf("Please Enter a Positive Integer: ");
                scanf("%d", &searchCount);
                printKeyAboveCount(head->node, searchCount);
                break;
            case 7:
                printf("Closing Program...\n");
                free(searchKey);
                free(filename);
                freeTree(head->node);
                free(head);
                break;
        }
    } while(input != 7);
    return(0);
}

void freeTree(Node * node) {
    if(node == NULL) {  //if node is NULL, bottom is reached
        return;
    }
    free(node->key);    //frees the key inside
    freeTree(node->left);   //frees left child
    freeTree(node->right);  //frees right child
    free(node);             //frees self
}

Node * findLowest(Node * node) {
    if(node->left == NULL) {
        return node;                    //if it is lowest left return
    } else {
        return findLowest(node->left);  //else go lower
    }
}

Node* removeLowest(Node * node) {
    if(node->left == NULL) {
        return node->right;         //if the left node is null return right
    }
    node->left = removeLowest(node->left);  //return the lowest left
    return balance(node);
}

Node * removeNode(Node * node, char * key) {
    if(node == NULL) {
        return NULL;
    } else {
         if(strcmp(node->key,key) > 0) {
            node->left = removeNode(node->left, key);
        } else if(strcmp(node->key,key) < 0) {
            node->right = removeNode(node->right, key);
        } else {
            if(node->count > 1) {       //if count greater 1 decrement count
                --node->count;
                return node;
            }

            Node * left = node->left;
            Node * right = node->right;

            if(right == NULL) {
                return left;
            }
            Node * lowestNode = findLowest(right);
            lowestNode->left = left;
            lowestNode->right = removeLowest(right);
            return balance(lowestNode);
        }
    }
    return balance(node);
}

Head * initializeTree(char * filename) {
    Head * head;
    if((head = malloc(sizeof(Head))) == NULL) {
        printf("Memory Allocation Failed\n");
		return NULL;
    }
    FILE* inputFile = fopen(filename, "r");
    if(inputFile == NULL) {
        printf("File Pointer Null...\n");
        free(head);
        return NULL;
    }
    char * key;
    if((key = malloc(sizeof(char) * 20)) == NULL) {
        printf("Memory Allocation Failed\n");
		return(NULL);
    }
    while(fscanf(inputFile,"%s", key) == 1) {
        head->node = addNode(head->node, key);  //scanning in file word by word
    }
    fclose(inputFile);
    return head;
}

Node * createNode(char * key) {
    Node * node;
    if((node = malloc(sizeof(Node))) == NULL){
        printf("Memory Allocation Failed\n");
        return NULL;
    }
    if((node->key = malloc(sizeof(char) * 20)) == NULL) {
        printf("Memory Allocation Failed\n");
        return NULL;
    }
    strcpy(node->key, key);             //creating new node

    node->count = 1;
    node->left = NULL;
    node->right = NULL;

    return node;
}

Node * addNode( Node * node, char * key) {
    if(node == NULL) {
        return createNode(key);             //adds node if node isnt an existing node
    } else {
        if(strcmp(node->key,key) == 0) {
            ++node->count;                  //increments count if it does exist
        } else if(strcmp(node->key,key) > 0) {
            node->left = addNode(node->left, key);
        } else {
            node->right = addNode(node->right, key);
        }
    }
    return balance(node);
}

void printKeyAboveCount(Node * node, int count) {
    if(node == NULL) {
        return;
    } else {
        if(node->count >= count) {      //if count of key is greater than count, print
            printf("Key: %s, Frequency: %d\n", node->key, node->count);
        }
        printKeyAboveCount(node->left, count);
        printKeyAboveCount(node->right, count);
    }
}

int displayKey(Node * node, char * key) {
    if(node == NULL) {
        return 0;   //returns 0 if no key found
    } else {
        if(strcmp(node->key,key) == 0) {    //displays key if found and returns 1 for key found
            printf("Key: %s, Count: %d\n", key, node->count);
            return 1;
        } else {
            int l = displayKey(node->left, key);
            int r = displayKey(node->right, key);
            return l + r;
        }
    }
}

int searchTree(Node * node, char * key) {
    if(node == NULL) {
        return 0;
    } else {
        if(strcmp(node->key,key) == 0) {
            return 1;
        } else {
            int l = searchTree(node->left, key);
            int r = searchTree(node->right, key);
            return l + r;
        }
    }
}

int isExternal(Node * n) {
	if(n->left == NULL && n->right == NULL) {
		return 1;     //true EXTERNAL
	} else {
		return 0;     //false INTERNAL
	}
}

int size(Node * node) {
    if(node == NULL) {
        return 0;
    } else {
        return size(node->left) + size(node->right) + 1;
    }
}

int height(Node * node) {
	if (node == NULL) {
        return -1;
    }

    int left = height(node->left);
    int right = height(node->right);

    if (left > right) {				//finds biggest height between left
        return left + 1;			//and right
    } else {
        return right + 1;
    }
}

Node * balance(Node * node) {
    if(height(node->left) - height(node->right) == 2) { //if it is left heavy
        if(height(node->left->right) > height(node->left->left)) {      //if its left right heavy
            return rotateDoubleRight(node);                             //double rotate
        }
        return rotateRight(node);                                       //else single rotate
    } else if(height(node->left) - height(node->right) == -2) {         //if it is right heavy
        if(height(node->right->left) > height(node->right->right)) {    //if its right left heavy
            return rotateDoubleLeft(node);                              //double rotate
        }
        return rotateLeft(node);                                        //else rotate left
    }
    return node;                                                        //tree is balanced
}

Node * rotateRight(Node * node) {
    Node * otherNode = node->left;
    node->left = otherNode->right;
    otherNode->right = node;
    return otherNode;
}

Node * rotateLeft(Node * node) {
    Node * otherNode = node->right;
    node->right = otherNode->left;
    otherNode->left = node;
    return otherNode;
}

Node * rotateDoubleLeft(Node * node) {
    node->right = rotateRight(node->right);
    node = rotateLeft(node);
    return node;
}

Node * rotateDoubleRight(Node * node) {
    node->left = rotateLeft(node->left);
    node = rotateRight(node);
    return node;
}
