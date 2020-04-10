#include <stdio.h>
#include <stdlib.h>
#include <string.h>


float correlation(int *Suite, int *L1,int taille){	//renvoie une probabilité de corrélation
	float compteur = 0.0 ;
	for(int i = 0 ; i < taille ; i++){
		if(L1[i] == Suite[i]) compteur ++ ;
			
	}
	
	return compteur/taille ;
}

int comparer(float p1, float p2){	
	float tmp = 0.01;
	if((p1 < p2 + tmp) && (p1 > p2 - tmp)) return 1;		//definir intervalle
	return 0;
}


void conversion_decimal_a_binaire(int a, int T2[],int n) 
//n taille du tableau T2 à remplir
{

	int* T = malloc(n*sizeof(int));
	T[n-1] = 1;
	//placer les bits de poid faible à droite et bits de poid fort à gauche
	for(int i = n-2; i>=0;i--){
		T[i] = 2*T[i+1];

	}

	for (int j=0;j<n;j++)
	{	
		if(a < T[j])
		{
			T2[j] = 0;
		}
		else 
		{
			T2[j] = 1;
			a = a - T[j];
		}
	}
	free(T);
}


int retroL0(int T[16]) 
{
	return T[15]^T[14]^T[11]^T[8];
}

//a faire pour les 3


void decalage(int*L, int bit_calcule)
{		
	for(int i = 15;i>0; i--)
	{
		L[i] = L[i-1];
	}
	
	L[0] = bit_calcule;
}


int main(int argc, char **argv)	//argv 1 = suite chiffrante 
{	
	if(argc < 2) {
		printf("nombre d'arguments insuffisants\n");
		exit(1);
	}

	int i = 0;//compteur
	int k = 0; //tmp
	int taille = strlen(argv[1]);	//taille de la suite
	if(taille < 16) { 
		 printf("Taille insuffisante\n");
		 exit(1);
	 }
		

	int * suite = malloc(sizeof(int) * taille );
	for(int i = 0 ; i < taille ; i++ ) 		
	{
		if(argv[1][i] == '0') suite[i] = 0;
		else if(argv[1][i] == '1') suite[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(1);
		}
	}
	

	float proba1 = 0.25 ;	//proba correlation du LFSR1
	float proba2 = 0.25 ;	//proba correlation du LFSR2
	float proba3 = 0.75 ;	//proba correlation du LFSR3
	int bit_calcule_L0 =0; 

	int LFSR1[16];
	int * sortieLFSR1 = malloc(sizeof(int) * taille);
	
	for (i = 0 ; i < 65536; i++)
	{	
		conversion_decimal_a_binaire(i , LFSR1 , 16);		
		
		for(int j = 0; j < taille ; j++){
			bit_calcule_L0 = retroL0(LFSR1);
			sortieLFSR1[j] = bit_calcule_L0;
			decalage(LFSR1,bit_calcule_L0);
		}
		float correl = correlation(suite,sortieLFSR1,taille);
		
		int comp = comparer(correl,proba1);
		if(comp)
		{ 
			k = i;
			printf("%d\n",k);
			printf("corrl = %f\n",correl);
		}
	}	
	
	printf("i = %d\n" ,i );
	printf("k = %d\n", k);
	printf("\n");
	while(i < 16){
		printf("%d",LFSR1[i]);
		i++;
	}
		printf("\n");

	free(suite);
	free(sortieLFSR1);
	
	return 0;
}

