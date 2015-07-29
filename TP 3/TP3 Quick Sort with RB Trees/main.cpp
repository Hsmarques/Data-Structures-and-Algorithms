/* 
 * Author: Hugo
 */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <map>
#include <algorithm>
#include <time.h>

#define BILLION 1000000000L

#define BLACK 0
#define RED 1

using namespace std;

struct word
{
	int count;
	string palavra;	
};

struct node {

	string palavra;
	int count;

    int colour;

    struct node* right;
    struct node* left;
};

int id_palavra=0;
bool added= false;

void swapLoc(std::vector<word> & vector_palavras, int i, int j)
{
    word tmp = vector_palavras[i];
    vector_palavras[i] = vector_palavras[j];
    vector_palavras[j] = tmp;
}

int partition(vector<word>& vector_palavras,int first, int last){

    int pivot = first + rand() % ( last - first + 1 );
    int j;
    swapLoc ( vector_palavras, pivot, first );

    pivot = first;

    for (j = first + 1; j <= last; ++j) {

        if(vector_palavras[first].count < vector_palavras[j].count){
            pivot++;
            swapLoc ( vector_palavras, pivot, j );
        }else if(vector_palavras[first].count == vector_palavras[j].count && vector_palavras[first].palavra > vector_palavras[j].palavra){
            pivot++;
            swapLoc ( vector_palavras, pivot, j );
        }

    }

    swapLoc ( vector_palavras, pivot, first );
    return pivot;
}

void quickSort(vector<word>& vector_palavras,int first,int last){
    if ( last > first) {
        int pivot = partition ( vector_palavras, first, last );
        quickSort ( vector_palavras, first, pivot - 1 );
        quickSort ( vector_palavras, pivot + 1, last );
    }
}

struct node* singleleft (struct node* anode) {

    struct node* temp = anode->left;

    anode->left = temp->right;
    temp->right = anode;

    anode->colour = RED;
    temp->colour = BLACK;

    return temp;
}

struct node* singleright (struct node* anode) {

    struct node* temp = anode->right;
	anode->right = temp->left;
    temp->left = anode;
	
	anode->colour = RED;
    temp->colour = BLACK;

    return temp;
}

struct node* leftright (struct node* anode) {
    anode->left = singleright(anode->left);
    return singleleft(anode);
}

struct node* rightleft (struct node* anode) {
    anode->right = singleleft(anode->right);
    return singleright(anode);
}

struct node* addnode (struct node* anode, string copy) {

    if (anode == NULL) {
        struct node* temp = new struct node;
        
       	temp->palavra = copy;
        temp->count = 1;
        temp->colour = RED;
        temp->right = NULL;
        temp->left = NULL;
        added=true;
        return temp;
    }

    if (anode->palavra == copy && added==false) {
    	anode->count++;
    } else {
    					
        if (anode->palavra>copy) {
            anode->left = addnode((anode->left), copy);

            if (anode->left != NULL && anode->right != NULL && anode->left->colour == RED && anode->right->colour == RED) {
                anode->left->colour = BLACK;
                anode->right->colour = BLACK;
                anode->colour = RED;
            }

            if (anode->left != NULL && anode->left->left != NULL && anode->left->colour == RED && anode->left->left->colour == RED) {
                anode = singleleft(anode);
            }

            if (anode->left != NULL && anode->left->right != NULL && anode->left->colour == RED && anode->left->right->colour == RED) {
                anode = leftright(anode);
            }
        }

        if (anode->palavra<copy) {
            anode->right = addnode((anode->right), copy);

            if (anode->left != NULL && anode->right != NULL && anode->left->colour == RED && anode->right->colour == RED) {
                anode->left->colour = BLACK;
                anode->right->colour = BLACK;
                anode->colour = RED;
            }

            if (anode->right != NULL && anode->right->right != NULL && anode->right->colour == RED && anode->right->right->colour == RED) {
                anode = singleright(anode);
            }

            if (anode->right != NULL && anode->right->left != NULL && anode->right->colour == RED && anode->right->left->colour == RED) {
                anode = rightleft(anode);
            }
        }
    }

    return anode;
}

void fill_vector (struct node* anode, vector<word>& vector_palavras) {

    if (anode == NULL) {
        return;
    } else {

        fill_vector(anode->left, vector_palavras);
        delete anode->left;

        struct word temp;
        temp.palavra=anode->palavra;
        temp.count=anode->count;

        vector_palavras.push_back(temp);

        fill_vector(anode->right, vector_palavras);
        delete anode->right;
    }
}

int main(){

	register int nr_palavras_ligacao;
	register int nr_linhas;
	register int i;
	register int k;
	char linha[400];
	char *token;

	uint64_t diff;
	struct timespec start, end;
	
	map<string,char> palavras_ligacao;
    map<string,char>::const_iterator it;

	vector<word> vector_palavras;

    struct node* head = NULL;

    /* measure monotonic time */
	clock_gettime(CLOCK_MONOTONIC, &start);

	cin >> nr_palavras_ligacao;
	for (i = 0; i < nr_palavras_ligacao; ++i){
		cin >> linha;
		k=0;
		while (linha[k]!='\0'){
			linha[k]=tolower(linha[k]);
			k++;
		}
		it=palavras_ligacao.find(linha);
        if(it==palavras_ligacao.end()){
            palavras_ligacao[linha]='m';
        }

	}

	cin >> nr_linhas;
	cin.ignore();
	
	for(i=0; i < nr_linhas; i++){
		cin.getline(linha,400);
		
		k=0;
		while (linha[k]!='\0'){
			linha[k]=tolower(linha[k]);
			k++;
		}
		token=strtok(linha," .,;:?!-_@#$%&*+()");
		while (token != NULL)
		{	
			it=palavras_ligacao.find(token);
			if(it==palavras_ligacao.end()){
				string copy= string(token);
				added=false;
				head = addnode(head, copy);
			}
			token = strtok (NULL, " .,;:?!-_@#$%&*+()");
			
		}
	}
	
	fill_vector(head, vector_palavras);
	quickSort(vector_palavras,0,(int)vector_palavras.size()-1);

	clock_gettime(CLOCK_MONOTONIC, &end);
	/* mark the end time */
	 diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);

/*
	for (i=0;i<(int)vector_palavras.size();i++){
		cout << vector_palavras[i].palavra << " " << vector_palavras[i].count << endl;
	}
*/	
	
    return 0;

}
