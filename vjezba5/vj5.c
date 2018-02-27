#include<stdio.h>
#include<malloc.h>

typedef struct lista *pos;
typedef struct lista {
	int el;
	pos next;
};

pos CreateNode();
void ReadFromFile(pos, char *);
void Print(pos);
void Unija(pos, pos, pos);
void Presjek(pos, pos, pos);

int main()
{
	pos L1=CreateNode();
	pos L2=CreateNode();
	pos U = CreateNode();
	pos P = CreateNode();
	char *c;
	c = (char*)malloc(100 * sizeof(char));
	printf("Unesite ime prve datoteke:\n");
	scanf("%s", c);
	ReadFromFile(L1, c);
	printf("Unesite ime druge datoteke:\n");
	scanf("%s", c);
	ReadFromFile(L2, c);
	printf("Prva lista:\n");
	Print(L1->next);
	printf("Druga lista:\n");
	Print(L2->next);
	printf("Unija:\n");
	Unija(L1->next, L2->next, U);
	Print(U->next);
	printf("Presjek:\n");
	Presjek(L1->next, L2->next, P);
	Print(P->next);
}

pos CreateNode()
{
	pos q;
	q = (pos)malloc(sizeof(lista));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

void ReadFromFile(pos p, char *dat)
{
	pos temp, q;
	FILE *fp = NULL;
	fp = fopen(dat, "r");
	if (fp == NULL)
		printf("Greska");
	else{
		while (!feof(fp)){
			q = p;
			temp = CreateNode();
			if (temp==NULL)
				printf("Greska");
			else{
				temp->next = NULL;
				fscanf(fp, "%d", &temp->el);
				if (q==NULL)
					printf("Greska");
				else{
					while (q->next != NULL&&q->next->el >= temp->el)
						q = q->next;
					temp->next = q->next;
					q->next = temp;
				}
			}
		}
	}
	fclose(fp);
}

void Print(pos p)
{
	while (p != NULL){
		printf("%d\n", p->el);
		p = p->next;
	}
}

void Unija(pos L1, pos L2, pos U)
{
	pos temp, q;
	
	while (L1 != NULL&&L2!=NULL){
		temp = CreateNode();
		if (L1->el < L2->el){
			temp->el = L2->el;
			L2 = L2->next;
		}
		else if (L1->el > L2->el){
			temp->el = L1->el;
			L1 = L1->next;
		}
		else{
			temp->el = L1->el;
			L1 = L1->next;
			L2 = L2->next;
		}
		U->next = temp;
		U = temp;
	}
	if (L1 == NULL){
		q = L2;
	}
	else{
		q = L1;
	}
	while (q != NULL){
		U->next = q;
		q = q->next;
	}
}

void Presjek(pos L1, pos L2, pos P)
{
	pos temp;
	while (L1 != NULL&&L2 != NULL){
		temp = CreateNode();
		if (L1->el == L2->el){
			temp->el = L1->el;
			L1 = L1->next;
			L2 = L2->next;
			P->next = temp;
			P = temp;
		}
		else if(L1->el < L2->el){
			L2 = L2->next;
		}
		else {
			L1 = L1->next;
		}
	}
}
