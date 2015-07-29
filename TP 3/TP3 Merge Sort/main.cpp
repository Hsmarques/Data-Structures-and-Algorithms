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

using namespace std;

struct palavra
{
	int count;
	string palavra;	
};

vector<palavra> merge(vector<palavra> vector_palavras,unsigned int first,unsigned int mid,unsigned int last){
    palavra temp[last-first];
    unsigned int i=first,j=mid,k=0;
    while(i<mid && j<last){
        if(vector_palavras[i].count > vector_palavras[j].count){
            temp[k++]=vector_palavras[i++];
        }else if(vector_palavras[i].count==vector_palavras[j].count && vector_palavras[i].palavra < vector_palavras[j].palavra){
            temp[k++]=vector_palavras[i++];
        }else{
        	temp[k++]=vector_palavras[j++];
        }
    }
    while(i<mid){
        temp[k++]=vector_palavras[i++];
    }
    while(j<last){
        temp[k++]=vector_palavras[j++];
    }

    for(i=0;i<(last-first);i++){
        vector_palavras[first+i]=temp[i];
    }
    return vector_palavras;
}

vector<palavra> mergeSort(vector<palavra> vector_palavras,unsigned int first,unsigned int last){
    unsigned int mid;
    if(first<last-1){
        mid =(first+last)/2;
        vector_palavras=mergeSort(vector_palavras,first,mid);
        vector_palavras=mergeSort(vector_palavras,mid,last);
        vector_palavras=merge(vector_palavras,first,mid,last);
    }
    return vector_palavras;
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

	uint64_t diff;
	struct timespec start, end;
	
	map<string,char> palavras_ligacao;
    map<string,char>::const_iterator it;

    vector<palavra> vector_palavras;
    vector<string> palavrasHashList;

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
	vector_palavras=mergeSort(vector_palavras,0,vector_palavras.size());

	clock_gettime(CLOCK_MONOTONIC, &end);
	/* mark the end time */
	 diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff);


	/*for (i=0;i<(int)vector_palavras.size();i++){
		cout << vector_palavras[i].palavra << " " << vector_palavras[i].count << endl;
	}*/

    return 0;

}
