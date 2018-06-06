#ifndef _LIST_H_
#define _LIST_H_

typedef struct ListNode ListNode;

struct ListNode{		
	int lineOfText;	
	int wordOffset;			
	ListNode* next;				
};

typedef struct List{		
	int listSize;				
	ListNode* firstNode;				
}List;


List* createList();
void insertIntoList(List* l,  int lineOfWord, int wordOffset);

void printList(List* l);
void destroyList(List* l);

#endif
