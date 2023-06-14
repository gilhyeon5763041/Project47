#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
} DListNode;

void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<-| %s |-> ", p->data);
	}
	printf("\n");
}

void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = (element)malloc(strlen(data) + 1);
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed->data);
	free(removed);
}

int main()
{
	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	init(head);

	char choice;
	char fruit[100];

	do {
		printf("\nMenu\n");
		printf("n) Next fruit\n");
		printf("p) Previous fruit\n");
		printf("d) Delete the current fruit\n");
		printf("i) Insert fruit after current fruit\n");
		printf("o) Output the fruit list\n");
		printf("e) Exit the program\n");
		printf("Enter your choice: ");
		scanf(" %c", &choice);

		switch (choice) {
		case 'n': {
			if (head->rlink != head)
				head = head->rlink;
			else
				printf("No next fruit.\n");
			break;
		}
		case 'p': {
			if (head->llink != head)
				head = head->llink;
			else
				printf("No previous fruit.\n");
			break;
		}
		case 'd': {
			// Delete the current fruit
			if (head != NULL) {
				DListNode* temp = head;
				head = head->rlink;
				ddelete(temp, temp);
				printf("Fruit deleted.\n");
			}
			else {
				printf("No fruit to delete.\n");
			}
			break;
		}
		case 'i': {
			printf("Enter the fruit to insert: ");
			scanf(" %s", fruit);
			dinsert(head, fruit);
			printf("Fruit inserted.\n");
			break;
		}
		case 'o': {
			printf("Fruit List: ");
			print_dlist(head);
			break;
		}
		case 'e': {
			printf("Exiting program.\n");
			break;
		}
		default:
			printf("Invalid choice. Try again.\n");
			break;
		}
	} while (choice != 'e');
	DListNode* p = head->rlink;
	while (p != head) {
		DListNode* temp = p;
		p = p->rlink;
		free(temp->data);
		free(temp);
	}
	free(head);

	return 0;
}