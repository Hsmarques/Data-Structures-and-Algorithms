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

using namespace std;

struct palavra
{
	int count;
	string palavra;	
};

void swapLoc(std::vector<palavra> & vector_palavras, int i, int j)
{
    palavra tmp = vector_palavras[i];
    vector_palavras[i] = vector_palavras[j];
    vector_palavras[j] = tmp;
}

int partition(vector<palavra>& vector_palavras,int first, int last){

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

void quickSort(vector<palavra>& vector_palavras,int first,int last){
    if ( last > first) {
        int pivot = partition ( vector_palavras, first, last );
        quickSort ( vector_palavras, first, pivot - 1 );
        quickSort ( vector_palavras, pivot + 1, last );
    }
}

int main(){

	register int nr_palavras_ligacao;
	register int nr_linhas;
	register int i;
	register int j;
	register int k;
	register int verifica;
	char linha[400];
	char *token;

	map<string,char> palavras_ligacao;
    map<string,char>::const_iterator it;

    vector<palavra> vector_palavras;
    vector<string> palavrasHashList;

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
		verifica=0;
		struct palavra temp;
		cin.getline(linha,400);
		//fgets(linha, sizeof(linha), stdin);
		
		k=0;
		while (linha[k]!='\0'){
			linha[k]=tolower(linha[k]);
			k++;
		}
		token=strtok(linha," .,;:?!-_@#$%&*+()");
		while (token != NULL)
		{	
			verifica=0;
			it=palavras_ligacao.find(token);
			if(it==palavras_ligacao.end()){
				for(j=0;j<(int)palavrasHashList.size();j++){
					if (palavrasHashList[j].compare(token) == 0) {
	                	verifica = 1;
	                	break;
	            	}
				}
				if(verifica == 1){
					for(j=0;j<(int)vector_palavras.size();j++){
						if(vector_palavras[j].palavra.compare(token) == 0){
							vector_palavras[j].count++;
						}
					}
				}else{
					palavrasHashList.push_back(token);
					string copy= string(token);
					temp.palavra=copy;
					temp.count=1;
					vector_palavras.push_back(temp);
				}
			}
			token = strtok (NULL, " .,;:?!-_@#$%&*+()");
			
		}
	}
	quickSort(vector_palavras,0,(int)vector_palavras.size()-1);

	for (i=0;i<(int)vector_palavras.size();i++){
		cout << vector_palavras[i].palavra << " " << vector_palavras[i].count << endl;
	}

    return 0;

}
