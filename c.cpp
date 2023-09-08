#include <iostream>
#include <algorithm>

using namespace std;

int main(){
    // Seu código vai aqui
	int n,i,nrecolhidas=0,*recolhidas,*bonecas;
	
	cin >> n;
	bonecas = (int *) malloc(n*sizeof(int));
	recolhidas = (int *) malloc(sizeof(int));
	for(i=0;i<n;i++)
		cin >> bonecas[i];
	for(i = n-1;i >0;i--){
		if(bonecas[i] < bonecas[i-1]){
			recolhidas = (int *) realloc(recolhidas,(nrecolhidas+1)*sizeof(int));
			n = i== n-1? 1:0;
			*(recolhidas + nrecolhidas) = *(bonecas + i-1+n);
			nrecolhidas++;
		}
	}
	cout<< nrecolhidas << endl;
	sort(recolhidas,recolhidas+nrecolhidas);
	for(i=0;i<nrecolhidas;i++)
		cout << recolhidas[i]<<' ';
    return 0;
}
