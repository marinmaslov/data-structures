#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack *st;
typedef struct tree *tr;
typedef struct stack {
	tr x;
	st next;
};

typedef struct tree {
	char y[10];
	tr left;
	tr right;
};

st CreateNode();
tr CreateRoot(tr);
void ReadFromFile(char[], st, tr);
void Push(char[], st, tr);
tr Insert(char[], tr);
void Pop(char[], st, tr);
void Print(tr);
void SaveToFile(tr);
void fPrint(tr, FILE *);

int main()
{
	tr t = NULL;
	t = CreateRoot(t);
	st s = CreateNode();
	char dat[30];
	printf("Unesite ime datoteke:\n");
	scanf("%s", &dat);
	ReadFromFile(dat, s, t);
	Print(s->next->x);
	SaveToFile(s->next->x);
	printf("\n");
	return 0;
}

st CreateNode()
{
	st q;
	q = (st)malloc(sizeof(stack));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

tr CreateRoot(tr t)
{
	if (t != NULL){
		CreateRoot(t->left);
		CreateRoot(t->right);
		free(t);
	}
	return NULL;
}

void ReadFromFile(char dat[], st s, tr t)
{
	char el[10];
	FILE *fp;
	fp = fopen(dat, "r");
	if (fp == NULL)
		printf("Greska prilikom otvaranja datoteke!\n");
	else{
		while (!feof(fp)){
			fscanf(fp, "%s", &el);
			if (strcmp(el, "+") == 0 || strcmp(el, "-") == 0 || strcmp(el, "*") == 0 || strcmp(el, "/") == 0 ){
				Pop(el, s, t);
			}
			else{
				Push(el, s, t);
			}
		}
	}
	fclose(fp);
}

void Push(char el[], st s, tr t)
{
	tr tTemp = NULL;
	tTemp = CreateRoot(tTemp);
	tTemp=Insert(el, tTemp);

	st q = NULL;
	q = s;
	st sTemp = CreateNode();
	sTemp->x = tTemp;
	t = tTemp;
	while (q->next != NULL)
		q = q->next;
	sTemp->next = q->next;
	q->next = sTemp;
}

tr Insert(char el[], tr t)
{
	if (NULL == t){
		t = (tr)malloc(sizeof(tree));
		strcpy(t->y, el);
		t->left = NULL;
		t->right = NULL;
	}
	else{
		printf("Greska prilikom dodavanja elementa!");
	}
	return t;
}

void Pop(char el[], st s, tr t)
{
	tr temp = NULL;
	temp = CreateRoot(temp);
	tr temp1 = NULL, temp2 = NULL;
	temp1 = CreateRoot(temp1);
	temp2 = CreateRoot(temp2);

	st q = NULL;
	st prev = NULL;
	q = s;

	while (q->next->next != NULL){
		temp1 = q->next->x;
		temp2 = q->next->next->x;
		prev = q;
		q = q->next;
	}
	
	temp = Insert(el, temp);
	temp->left = temp1;
	temp->right = temp2;

	st sTemp = CreateNode();
	sTemp->next = NULL;
	sTemp->x = temp;

	while (q->next != NULL)
		q = q->next;

	sTemp->next = q->next;
	prev->next = sTemp;
	t = temp;
}

void Print(tr t)
{
	if (t != NULL){
		if (strcmp(t->y, "+") == 0 || strcmp(t->y, "-") == 0) {
			printf("(");
			Print(t->left);
			printf("%s", t->y);
			Print(t->right);
			printf(")");
		}
		else{
			Print(t->left);
			printf("%s", t->y);
			Print(t->right);
		}
	}
}

void SaveToFile(tr t)
{
	FILE *fp;
	fp = fopen("rjesenje.txt", "w");
	if (fp == NULL)
		printf("Greska pri kreiranju datoteke!\n");
	else{
		fPrint(t, fp);
	}
	fclose(fp);
}

void fPrint(tr t, FILE *fp)
{
	if (t != NULL){
		if (strcmp(t->y, "+") == 0 || strcmp(t->y, "-") == 0) {
			fprintf(fp, "(");
			fPrint(t->left, fp);
			fprintf(fp, "%s", t->y);
			fPrint(t->right, fp);
			fprintf(fp, ")");
		}
		else{
			fPrint(t->left, fp);
			fprintf(fp, "%s", t->y);
			fPrint(t->right, fp);
		}
	}
}
