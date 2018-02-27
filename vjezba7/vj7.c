#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

typedef struct stog *pos;
typedef struct stog{
	int el;
	pos next;
};



pos CreateNode();
void Print(pos);
void Push(pos, char*);
void Pop(pos, char*);
void ReadFromFile(pos);


int main()
{
	pos S=CreateNode();
	ReadFromFile(S);
	Print(S->next);
	return 0;
}

pos CreateNode()
{
	pos q;
	q = (pos)malloc(sizeof(stog));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

void Print(pos S)
{
	printf("Stog:\n");
	while (S != NULL){
		printf("%d\n", S->el);
		S = S->next;
	}
}

void Push(pos S, char *x)
{
	while (S->next != NULL){
		S = S->next;
	}
	int a;
	a = atoi(x);
	pos temp = CreateNode();
	temp->el = a;
	temp->next = S->next;
	S->next = temp;
}

void Pop(pos S, char *x)
{
	pos P = CreateNode();
	if (S->next == NULL)
		printf("Stog je prazan!\n");
	else{
		pos temp1 = CreateNode();
		pos temp2 = CreateNode();
		while (S->next->next != NULL){
			temp1 = S->next;
			temp2 = S->next->next;
			S = S->next;
		}

		pos q = CreateNode();

		if (*x=='+')
			q->el = temp1->el + temp2->el;
		else if (*x == '-')
			q->el = temp1->el - temp2->el;
		else if(*x == '*')
			q->el = temp1->el * temp2->el;
		else if (*x == '/')
			q->el = temp1->el / temp2->el;
		else
			printf("Greska!");

		S->next = temp2->next;
		S->el = q->el;
	}
}

void ReadFromFile(pos S)
{
	pos temp, q=NULL;
	char *buffer;
	buffer = (char*)malloc(30 * sizeof(char));

	FILE *fp;
	fp = fopen("zadatak.txt", "r");
	if (fp == NULL)
		printf("Greska!");
	else
	{
		while (!feof(fp))
		{
			q = S;
			temp = CreateNode();
			fscanf(fp, "%s", buffer);
			if (*buffer == '+' || *buffer == '-' || *buffer == '*' || *buffer == '/'){
				Pop(q, buffer);
			}
			else{
				Push(q, buffer);
			}
		}
	}
	fclose(fp);
}
