#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H
#include "chat1002.h"
#include <stdio.h>
/* functions defined in linkedlist.c */
struct Node {
	char intent[32];
	char entity[64];
	char answer[256];
	struct Node* next;
};

typedef struct Node Node;

char* getAnswer(Node* head, const char* intent, const char* entity);
void printLinkedList(Node *head);
Node *insertNode(Node *head, const char *intent, const char *entity, const char *answer);
Node *getNode(Node *head, const char *intent, const char *entity);
#endif