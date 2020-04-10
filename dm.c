#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void affichage_tableau(int * T, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d",T[i]);
	}
	printf("\n");
}

void affichage_entree(int F[8], int k0[16], int k1[16], int k2[16], int n)
{
	printf("n = %d\n",n);
	printf("F = ");
	affichage_tableau(F,8);
	printf("k0 = ");
	affichage_tableau(k0,16);
	printf("k1 = ");
	affichage_tableau(k1,16);
	printf("k2 = ");
	affichage_tableau(k2,16);
}

void affichage_sortie(int *s, int n)
{
	printf("Sortie :");
	for (int i = 0; i < n; i++)
	{
		printf("%d",s[i]);
	}
	
	printf("\n");
}

void decalage(int*L, int bit_calcule)
{		
	for(int i = 15;i>0; i--)
	{
		L[i] = L[i-1];
	}
	
	L[0] = bit_calcule;
}

int filtrage(int T[8] , int x, int y , int z){
	int w = -1; 
	
	if((x==0) && (y==0) && (z==0)) w = T[0];
	if((x==1) && (y==0) && (z==0)) w = T[1];
	if((x==0) && (y==1) && (z==0)) w = T[2];
	if((x==1) && (y==1) && (z==0)) w = T[3];
	if((x==0) && (y==0) && (z==1)) w = T[4];
	if((x==1) && (y==0) && (z==1)) w = T[5];
	if((x==0) && (y==1) && (z==1)) w = T[6];
	if((x==1) && (y==1) && (z==1)) w = T[7];
	
	if((w != 0) && (w!=1)) printf("ERREUR : Table de filtrage invalide\n") ;
	return w ;
}

int retroL0(int T[16]) {
	return T[15]^T[14]^T[11]^T[8];
}

int retroL1(int T[16]) {
	return T[15]^T[14]^T[8]^T[4];
}

int retroL2(int T[16]) {
	return T[15]^T[13]^T[12]^T[10];
}

int * generateur(int F[8], int k0[16], int k1[16], int k2[16], int n)
{
	int * res = malloc(sizeof(int)*n);
	int bit_calcule_L0, bit_calcule_L1, bit_calcule_L2;
	
	for(int i = 0; i<n; i++)
	{
		res[i] = filtrage(F,k0[15],k1[15],k2[15]);
		bit_calcule_L0 = retroL0(k0);
		bit_calcule_L1 = retroL1(k1);
		bit_calcule_L2 = retroL2(k2);
		decalage(k0,bit_calcule_L0);
		decalage(k1,bit_calcule_L1);
		decalage(k2,bit_calcule_L2);
		printf("------------------------------------------------\n");
		printf("Pour %d, s[%d] = %d, x1 = %d, x2 = %d et x3 = %d\n", i,i,res[i],bit_calcule_L0,bit_calcule_L1,bit_calcule_L2);
		printf("k0 =");
		affichage_tableau(k0,16);
		printf("k1 =");
		affichage_tableau(k1,16);
		printf("k2 =");
		affichage_tableau(k2,16);
		printf("------------------------------------------------\n");
	}
	
	return res;
}

int main(int argc, char **argv)
{
	//Table de fonction de filtrage
	int F[8];
	//Sous-clé k0
	int k0[16];
	//Sous-clé k1
	int k1[16];
	//Sous-clé k2
	int k2[16];
	//Nombre de bits de la suite chiffrante
	int n;
	//Sortie du générateur
	int *s;
	
	if(argc<5){
		printf("Erreur: nombre d'arguments insuffisant\n");
		exit(EXIT_FAILURE);
	}





	//Vérification de la taille des données en entrée
	if(strlen(argv[1]) != 8 || strlen(argv[2]) != 16 || strlen(argv[3]) != 16 || strlen(argv[4]) != 16)
	{
		printf("ERREUR : taille non valide\n");
		exit(1);
	}   
	
	
	//Conversion en tableau d'entiers
	
	//Pour F
	for (int i = 0; i < 8; i++)
	{
		if(argv[1][i] == '0') F[i] = 0;
		else if(argv[1][i] == '1') F[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(1);
		}
	}
	
	//Pour k0, k1 et k2
	for (int i = 0; i < 16; i++)
	{
		if(argv[2][i] == '0') k0[i] = 0;
		else if(argv[2][i] == '1') k0[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(1);
		}
		
		if(argv[3][i] == '0') k1[i] = 0;
		else if(argv[3][i] == '1') k1[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(1);
		}
		
		if(argv[4][i] == '0') k2[i] = 0;
		else if(argv[4][i] == '1') k2[i] = 1;
		else
		{
			printf("ERREUR : caractère invalide\n");
			exit(1);
		}
	}
	
	//Pour n
	n = atoi(argv[5]);
	if(n <= 0) 
	{
		printf("ERREUR : Entier non valide\n");
		exit(1);
	}
	
	affichage_entree(F,k0,k1,k2,n);
	s = generateur(F,k0,k1,k2,n);	
	affichage_sortie(s,n);
	free(s);
	return 0;
}
