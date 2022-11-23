#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "linkedlist.h"
#include <ctype.h>
#include <stdbool.h>



//retrieve answer from the intent and entity input
char* getAnswer(Node* head, const char* intent, const char* entity) {
	Node* current = head;
	if (current != NULL){
		while (current != NULL) {
			if (compare_token(intent, current->intent) == 0) {
				if (compare_token(entity, current->entity) == 0) {
					return current->answer;
				}
			}
			current = current->next;
		}
	}
	return NULL;
}

/*Use this to check the total structure of the list*/
void printLinkedList(Node *head) {
    Node *cursor = head;
    int count = 1;
    while (cursor != NULL) {
        printf("Data at node%d is: %s\n", count, cursor->answer);
        cursor = cursor->next;
        count++;
    }

}

/*Always inserts in front. Remember to put head to catch the node pointer from this method.*/
Node *insertNode(Node *head, const char *intent, const char *entity, const char *answer) 
{
    Node *newnode = (Node *) malloc(sizeof(Node));
    if(head != NULL)
    {
        //Check if a node of the same question and type already exist in the buffer
        Node *exist = getNode(head, intent, entity);
        if(exist != NULL)
        {
            //Change the existing node's answer (load intent)
            strcpy(exist->answer, answer);
            return head;
        }
        else
        {
            //To end the route and create a new node instead
            newnode->next = head;
            strcpy(newnode->intent, intent);
            strcpy(newnode->entity, entity);
            strcpy(newnode->answer, answer);
            return (newnode);
        }
    }
    else
    {
        //Create a new node and insert into the front
        newnode->next = head;
        strcpy(newnode->intent, intent);
        strcpy(newnode->entity, entity);
        strcpy(newnode->answer, answer);
        return (newnode);
    }
}

//Get existing Node (for insertion and load purposes)
Node *getNode(Node *head, const char *intent, const char *entity) {
    Node *cursor = head;
    if (cursor != NULL) {
        /*To check multiple cursors*/
        while (cursor != NULL) {
            if (compare_token(intent, cursor->intent) == 0) {
                if (compare_token(entity, cursor->entity) == 0) {
                    return cursor;
                }
            }
            cursor = cursor->next;
        }
    }
    return NULL;
}