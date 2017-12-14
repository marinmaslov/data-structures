/*3. Zadatak - Strukture podataka 2017*/
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct person *pos;
typedef struct person{
	char name[20];
	char surname[20];
	int year;
	pos next;
}person;

pos new_node();
pos menu(pos);
pos input_data(pos);
void add_to_begining(pos);
void print_list(pos);
void add_to_end(pos);
void search_by_surname(pos);
void delete_by_surname(pos);
void after_surname(pos);
void before_surname(pos);
void write_list_to_file(pos);
void read_from_file(pos);

int main()
{
	pos p;
	p = new_node();
	if (p == NULL)
		printf("ERROR!");
	menu(p);
}

pos new_node()
{
	pos q;
	q = (pos)malloc(sizeof(person));
	q->next = NULL;
	return q;
}

pos menu(pos p)
{
	int i;
	printf("0.\tIzlaz\n1.\tDodaj na pocetak\n2.\tIspisi listu\n3.\tDodaj na kraj\n4.\tPronadi po prezimenu\n5.\tBrisi po prezimenu\n6.\tDodaj iza prezimena\n7.\tDodaj ispred prezimena\n8.\tUpisi listu u datoteku\n9.\tUcitaj listu iz datoteke\n");
	scanf("%d", &i);
	if (i == 0)
		return 0;
	else if (i == 1)
		add_to_begining(p);
	else if (i == 2)
		print_list(p);
	else if (i == 3)
		add_to_end(p);
	else if (i == 4)
		search_by_surname(p);
	else if (i == 5)
		delete_by_surname(p);
	else if (i == 6)
		after_surname(p);
	else if (i == 7)
		before_surname(p);
	else if (i == 8)
		write_list_to_file(p);
	else if (i == 9)
		read_from_file(p);
	menu(p);
}

pos input_data(pos p)
{
	printf("Unesite ime:\n");
	scanf("%s", &p->name);
	printf("Unesite prezime:\n");
	scanf("%s", &p->surname);
	printf("Unesite godinu rodenja:\n");
	scanf("%d", &p->year);
	return p;
}

void add_to_begining(pos p)
{
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	pos temp;
	temp = new_node();
	if (temp == NULL)
		printf("ERROR!\n");
	q = p;
	input_data(temp);
	temp->next = q->next;
	q->next = temp;
}

void print_list(pos p)
{
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	q = p;
	if (q->next == NULL){
		printf("Lista je prazna!\n");
	}
	else{
		while (q->next != NULL){
			printf("%s\t%s\t%d\n", q->next->name, q->next->surname, q->next->year);
			q = q->next;
		}
	}
}

void add_to_end(pos p)
{
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	pos temp;
	temp = new_node();
	if (temp == NULL)
		printf("ERROR!\n");
	q = p;
	while (q->next != NULL)
		q = q->next;
	input_data(temp);
	temp->next = q->next;
	q->next = temp;
}

void search_by_surname(pos p)
{
	char s[20];
	printf("Prezime:\n");
	scanf("%s", &s);
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	q = p;
	while (strcmp(q->surname, s)){
		q = q->next;
	}
	printf("%s\t%s\t%d\n", q->name, q->surname, q->year);
}

void delete_by_surname(pos p)
{
	char s[20];
	printf("Prezime:\n");
	scanf("%s", &s);
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	pos temp;
	temp = new_node();
	if (temp == NULL)
		printf("ERROR!\n");
	temp = p;
	q = p;
	while (strcmp(q->surname, s)){
		temp = q;
		q = q->next;
	}
	temp->next = q->next;
}

void after_surname(pos p)
{
	char s[20];
	printf("Prezime:\n");
	scanf("%s", &s);
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	pos temp;
	temp = new_node();
	if (temp == NULL)
		printf("ERROR!\n");
	q = p;
	input_data(temp);
	while (strcmp(q->surname, s)){
		q = q->next;
	}
	temp->next = q->next;
	q->next = temp;
}

void before_surname(pos p)
{
	char s[20];
	printf("Prezime:\n");
	scanf("%s", &s);
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	pos temp1;
	temp1 = new_node();
	if (temp1 == NULL)
		printf("ERROR!\n");
	pos temp2;
	temp2 = new_node();
	if (temp2 == NULL)
		printf("ERROR!\n");
	temp1 = p;
	q = p;
	input_data(temp2);
	while (strcmp(q->surname, s)){
		temp1 = q;
		q = q->next;
	}
	temp1->next = temp2;
	temp2->next = q;
}

void write_list_to_file(pos p)
{
	pos q;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");
	q = p;
	FILE *fp;
	fp = fopen("list.txt", "w");
	while (q->next!=NULL){
		fprintf(fp, "%s\t%s\t%d\n", q->next->name, q->next->surname, q->next->year);
		q = q->next;
	}
	fclose(fp);
}

void read_from_file(pos p)
{
	pos q, temp;
	q = new_node();
	if (q == NULL)
		printf("ERROR!\n");

	q = p;

	char buffer[100];

	FILE *fp;
	fp = fopen("list.txt", "r");
	if (fp == NULL)
		printf("Datoteka je prazna!");
	
	while (!feof(fp)){
			temp = new_node();
			fscanf(fp, "%s %s %d", &temp->name, &temp->surname, &temp->year);
			temp->next = q->next;
			q->next = temp;
			q = q->next;
	}
	fclose(fp);
}