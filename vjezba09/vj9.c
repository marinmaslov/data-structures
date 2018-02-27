#include<stdio.h>
#include<malloc.h>


typedef struct node *stablo;
typedef struct node{
	int el;
	stablo left;
	stablo right;
};

int Menu(stablo);
stablo CreateTree(stablo);
stablo AddElement(int, stablo);
void PrintTree(stablo);
stablo DeleteElement(int, stablo);
stablo FindMin(stablo);
stablo FindMax(stablo);
stablo FindElement(int, stablo);

int main()
{
	stablo s = NULL;
	CreateTree(s);
	Menu(s);
	return 0;
}

int Menu(stablo s)
{
	int a,x;
	printf("\nIzbornik:\n\t0. Izlaz\n\t1. Dodaj element u stablo\n\t2. Ispisi stablo\n\t3. Izbrisi element\n\t4. Pronadi element\n\t5. Izbrisi stablo\n");
	scanf("%d", &a);
	if (a == 0)
		return 0;
	else if (a == 1){
		printf("Element:\n");
		scanf("%d", &x);
		s=AddElement(x, s);
	}
	else if (a == 2)
		PrintTree(s);
	else if (a == 3){
		printf("Element kojeg zelite izbrisati:\n");
		scanf("%d", &x);
		s = DeleteElement(x, s);
	}
	else if (a == 4){
		printf("Element kojeg trazite:\n");
		scanf("%d", &x);
		s = FindElement(x, s);
		printf("Element kojeg trazite nalazi se na adresi: %d\n", &s->el);
	}
	else if (a == 5)
		s = CreateTree(s);
	else
		printf("Greska pri unosu!\n");
	Menu(s);
}

stablo CreateTree(stablo s)
{
	if (NULL!=s){
		CreateTree(s->left);
		CreateTree(s->right);
		free(s);
	}
	return NULL;
}

stablo AddElement(int x, stablo s)
{
	if (NULL==s){
		s = (stablo)malloc(sizeof(node));
		s->el = x;
		s->left = NULL;
		s->right = NULL;
	}
	else if (x > s->el){
		s->right = AddElement(x, s->right);
	}
	else if (x < s->el){
		s->left = AddElement(x, s->left);
	}
	return s;
}

void PrintTree(stablo s)
{
	if (NULL != s){
		PrintTree(s->left);
		printf("%d ", s->el);
		PrintTree(s->right);
	}
}

stablo DeleteElement(int x, stablo s)
{
	if (NULL == s)
		return s;
	else {
		if (x > s->el){
			s->right = DeleteElement(x, s->right);
		}
		else if (x < s->el){
			s->left = DeleteElement(x, s->left);
		}
		else if (s->left&&s->right!=NULL){
			stablo temp;
			temp = FindMin(s->right);
			s->el = temp->el;
			s->right = DeleteElement(s->el, s->right);
		}
		else {
			stablo temp;
			temp = s;
			if (s->left == NULL)
				s = s->right;
			else
				s = s->left;
			free(temp);
		}
	}
	return s;
}

stablo FindMin(stablo s)
{
	if (s == NULL)
		return NULL;
	else if (s->left = NULL)
		return s;
	else
		return FindMin(s->left);
}

stablo FindElement(int x, stablo s)
{
	if (NULL == s)
		return NULL;
	else if (x > s->el)
		s->right = FindElement(x, s->right);
	else if (x < s->el)
		s->left = FindElement(x, s->left);
	return s;
}
