#include<stdio.h>
#include<malloc.h>
#include <string.h>

typedef struct osoba *pos;
typedef struct osoba {
	char ime[20];
	char prezime[20];
	int godina;
	pos next;
};

int menu(pos);
pos CreateNode();
pos InsertData(pos);
int AddStart(pos);
int PrintList(pos);
int PrintElement(pos);
int AddEnd(pos);
void Find(pos);
pos FindPrevious(pos);
int Delete(pos);
int AddBehind(pos);
int AddBefore(pos);
int PrintToFile(pos);
int ReafFromFile(pos);


int main(int argv, char argc[])
{
	pos p = CreateNode();
	menu(p);
	return 0;
}

int menu(pos p)
{
	int a;
	printf("Izbornik:\n\t0. Izlaz\n\t1. Dodaj element na pocetak liste\n\t2. Ispisi Listu\n\t3. Dodaj element na kraj liste\n\t4. Trazenje elementa po prezimenu\n\t5. Izbrisi element po prezimenu\n\t6. Dodaj element iza prezimena\n\t7. Dodaj element ispred prezimena\n\t8. Sortiraj listu po prezimenima\n\t9. Unesi listu u datoteku\n\t10. Unesi u listu iz datoteke\n");
	scanf("%d", &a);
	if (a == 0)
		return 0;
	else if (a == 1)
		AddStart(p);
	else if (a == 2)
		PrintList(p);
	else if (a == 3)
		AddEnd(p);
	else if (a == 4)
		Find(p);
	else if (a == 5)
		Delete(p);
	else if (a == 6)
		AddBehind(p);
	else if (a == 7)
		AddBefore(p);
	else if (a == 8){}
	else if (a == 9)
		PrintToFile(p->next);
	else if (a == 10)
		ReafFromFile(p);
	menu(p);
}

pos CreateNode()
{
	pos q = NULL;
	q = (pos)malloc(sizeof(osoba));
	if (q == NULL)
		return q;
	q->next = NULL;
	return q;
}

pos InsertData(pos q)
{
	printf("UNOS PODATAKA\n");
	printf("Unesite ime:\n");
	scanf("%s", &q->ime);
	printf("Unesite prezime:\n");
	scanf("%s", &q->prezime);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &q->godina);
	return q;
}

int AddStart(pos p)
{
	pos temp = NULL;
	temp = CreateNode();
	if (temp == NULL)
		return -1;

	InsertData(temp);

	temp->next = p->next;
	p->next = temp;

}

int PrintList(pos p)
{
	p = p->next;
	if (p == NULL)
		return -2;
	else{
		while (p != NULL){
			printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
			p = p->next;
		}
	}
}

int AddEnd(pos p)
{
	pos temp = CreateNode();
	if (temp == NULL)
		return -3;
	while (p->next != NULL)
		p = p->next;
	InsertData(temp);
	temp->next = p->next;
	p->next = temp;
}

void Find(pos p)
{
	char b[20];
	printf("Koje prezime trazimo?\n");
	scanf("%s", &b);

	while (p != NULL){
		if (strcmp(p->prezime, b) == 0)
			printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}

}

int Delete(pos p)
{
	pos temp = CreateNode();
	if (temp == NULL)
		return -5;
	p = FindPrevious(p);
	if (p == NULL)
		return -6;
	else{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

pos FindPrevious(pos p)
{
	pos q = p;
	char c[20];
	printf("Element ispred kojeg prezimena trazimo?\n");
	scanf("%s", &c);

	while (p != NULL && strcmp(p->prezime, c) != 0){
		q = p;
		p = p->next;
	}

	if (p != NULL)
		return q;
	else
		return NULL;

}

int AddBehind(pos p)
{
	char d[20];
	printf("Iza kojeg prezimena zelite unijeti?\n");
	scanf("%s", &d);

	pos temp = CreateNode();
	if (temp == NULL)
		return -8;
	InsertData(temp);
	while (p != NULL&&strcmp(p->prezime, d) != NULL)
		p = p->next;

	temp->next = p->next;
	p->next = temp;
}


int AddBefore(pos p)
{
	pos temp = CreateNode();
	InsertData(temp);
	p = FindPrevious(p);
	if (p == NULL)
		return -9;
	else{
		temp->next = p->next;
		p->next = temp;
	}
}


int PrintToFile(pos p)
{
	FILE *fp = NULL;
	fp = fopen("osobe.txt", "w");
	if (fp == NULL)
		return -13;

	while (p != NULL){
		fprintf(fp, "%s\t%s\t%d\n", p->ime, p->prezime, p->godina);
		p = p->next;
	}
	fclose(fp);
}

int ReafFromFile(pos p)
{
	FILE *fp = NULL;
	pos q = NULL;
	pos temp = NULL;
	fp = fopen("osobe.txt", "r+");
	if (fp == NULL)
		return -14;
	else{
		while (!feof(fp)){
			q = p;
			temp = CreateNode();
			if (temp == NULL)
				return -15;
			else{
				temp->next = NULL;
				fscanf(fp, "%s %s %d", &temp->ime, &temp->prezime, &temp->godina);
				if (q == NULL)
					return -16;
				else{
					while (q->next != NULL&&strcmp(q->next->prezime, temp->prezime) <= 0){
						q = q->next;
					}
					temp->next = q->next;
					q->next = temp;
				}
			}
		}
	}
	fclose(fp);
}
