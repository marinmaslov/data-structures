#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define MIN 10
#define MAX 100
#define RANGE MAX-MIN


typedef struct stog *posS;
typedef struct stog{
	int el;
	posS next;
};

typedef struct red *posQ;
typedef struct red{
	int el;
	posQ next;
};

int Menu(posS,posQ);

posS CreateNodeS();
void PrintS(posS);
void PushS(posS);
void PopS(posS);

posQ CreateNodeQ();
void PrintQ(posQ);
void PushQ(posQ);
void PopQ(posQ);

int main()
{
	posS S=CreateNodeS();
	posQ Q = CreateNodeQ();
	Menu(S,Q);
	return 0;
}

int Menu(posS S, posQ Q)
{
	int a;
	printf("Izbornik:\n\t0. Izlaz\n\t1. Push na Stog\n\t2. Pop sa Stoga\n\t3. Print Stog\n\t4. Push na Red\n\t5. Pop sa Reda\n\t6. Print Red\n");
	scanf("%d", &a);
	if (a == 0)
		return 0;
	else if (a == 1)
		PushS(S);
	else if (a == 2)
		PopS(S);
	else if (a == 3)
		PrintS(S->next);
	else if (a == 4)
		PushQ(Q);
	else if (a == 5)
		PopQ(Q);
	else if (a == 6)
		PrintQ(Q->next);

	Menu(S, Q);
}

posS CreateNodeS()
{
	posS q;
	q = (posS)malloc(sizeof(stog));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

void PrintS(posS S)
{
	printf("Stog:\n");
	while (S != NULL){
		printf("%d\n", S->el);
		S = S->next;
	}
}

void PushS(posS S)
{
	int x;
	while (S->next != NULL){
		S = S->next;
	}
	x = rand() % RANGE + MIN;
	posS temp = CreateNodeS();
	temp->el = x;
	temp->next = S->next;
	S->next = temp;
}

void PopS(posS S)
{
	if (S->next == NULL)
		printf("Stog je prazan!\n");
	else{
		posS prev = NULL;
		while (S->next != NULL){
			prev = S;
			S = S->next;
		}

		posS temp = CreateNodeS();
		temp = S;

		prev->next = temp->next;
		free(temp);
	}
}


posQ CreateNodeQ()
{
	posQ q;
	q = (posQ)malloc(sizeof(red));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

void PrintQ(posQ Q)
{
	printf("Red:\n");
	while (Q != NULL){
		printf("%d\n", Q->el);
		Q = Q->next;
	}
}

void PushQ(posQ Q)
{
	int x;
	while (Q->next != NULL){
		Q = Q->next;
	}
	x = rand() % RANGE + MIN;
	posQ temp = CreateNodeQ();
	temp->el = x;
	temp->next = Q->next;
	Q->next = temp;
}

void PopQ(posQ Q)
{
	if (Q->next == NULL)
		printf("Red je prazan!\n");
	else {
		posQ q = NULL;
		q = Q->next->next;
		posQ temp = CreateNodeQ();
		temp = Q->next;
		Q->next = q;
		free(temp);
	}
	
}
