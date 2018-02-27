#include<stdio.h>
#include<malloc.h>

#define filename1 "polinom1.txt"
#define filename2 "polinom2.txt"

typedef struct polinom *pos;
typedef struct polinom {
	int br;
	int ex;
	pos next;
};

pos CreateNode();
void ReadFromFile(pos, char*);
void Print(pos);
void Zbroj(pos, pos, pos);
void Umnozak(pos, pos, pos);

int main()
{
	pos P1 = CreateNode();
	pos P2 = CreateNode();
	pos Z = CreateNode();
	pos U = CreateNode();

	ReadFromFile(P1, filename1);
	ReadFromFile(P2, filename2);
	Print(P1->next);
	printf("\n");
	Print(P2->next);
	printf("\nZbroj:\n");
	Zbroj(P1->next, P2->next, Z);
	Print(Z->next);
	printf("Umnozak:\n");
	Umnozak(P1->next, P2->next, U);
	Print(U->next);

	return 0;
}

pos CreateNode()
{
	pos q = NULL;
	q = (pos)malloc(sizeof(polinom));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

void ReadFromFile(pos p, char *dat)
{
	pos q = NULL;
	pos temp = NULL;

	FILE *fp = NULL;
	fp = fopen(dat, "r");
	if (fp == NULL)
		printf("Greska!");
	else{
		while (!feof(fp)){
			q = p;
			temp = CreateNode();
			if (temp == NULL)
				printf("Greska!");
			else{
				temp->next = NULL;
				fscanf(fp, "%d %d", &temp->br, &temp->ex);
				if (q == NULL)
					printf("Greska!");
				else{
					while (q->next != NULL&&q->next->ex >= temp->ex)
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
		printf("%d\t%d\n", p->br, p->ex);
		p = p->next;
	}
}

void Zbroj(pos P1, pos P2, pos Z)
{
	pos q = NULL;
	pos temp = NULL;

	while (P1 != NULL&&P2 != NULL){
		temp = CreateNode();
		if (P1->ex > P2->ex){
			temp->ex = P1->ex;
			temp->br = P1->br;
			P1 = P1->next;
		}
		else if (P1->ex < P2->ex){
			temp->ex = P2->ex;
			temp->br = P2->br;
			P2 = P2->next;
		}
		else {
			temp->ex = P1->ex;
			temp->br = P1->br + P2->br;
			P1 = P1->next;
			P2 = P2->next;
		}
		temp->next = Z->next;
		Z->next = temp;
		Z = Z->next;
	}
	if (P1 != NULL)
		q = P1;
	else{
		q = P2;
	}
	while (q != NULL){
		temp = CreateNode();
		temp->br = q->br;
		temp->ex = q->ex;
		temp->next = Z->next;
		Z->next = temp;
		Z = Z->next;
		q = q->next;
	}
}

void Umnozak(pos P1, pos P2, pos U)
{
	pos temp, prev, novi;
	pos q = NULL;
	int n;


	while (P1 != NULL){
		q = P2;
		while (P2 != NULL){

			temp = U->next;
			prev = U;

			n = P1->ex + P2->ex;


			while (temp != NULL && temp->ex > n){
				prev = temp;
				temp = temp->next;
			}

			if (temp != NULL && temp->ex == n) {
				temp->br = (P1->br * P2->br)+temp->br;
			}

			else {
				novi = CreateNode();
				novi->ex = n;
				novi->br = P1->br * P2->br;
				prev->next = novi;
				novi->next = temp;
			}
			P2 = P2->next;
		}
		P2 = q;
		P1 = P1->next;
	}
}
