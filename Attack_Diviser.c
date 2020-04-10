#include <stdio.h>
#include <stdlib.h>
#include<string.h> 


float correlation(int *Suite, int *L1){	
	float compteur = 0.0 ;
	for(int i = 0 ; i < 16 ; i++)
		if(L1[i] == Suite[i]) compteur ++ ;
	return compteur/16 ;
}

int comparer(float p1, float p2){	
	if((p1 )==(p2)) return 1;

	return 0;
}


int * CalculduBitFort0(int * tab)
{
    int val  = tab[0] ^ tab[1] ^ tab[4] ^tab [7] ; 
    for (int i = 0 ; i< 15 ; ++i)
          tab[i] = tab[i+1]; 
    tab [15] = val ; 
    return tab;    
}

int* StringtoInt(char *chaine)
{
	int taille = strlen(chaine) -1 ; 
	int  *tab = malloc ( taille *sizeof(int)); 
	for( int i = 0 ; i < taille ; ++i )
		tab[i] = (int) (chaine [i]-48);
	return tab; 
}




int* New_Init(int *T){
int rest;
if(T[15]+1==2){
T[15]=0;
rest=1;
}else if(T[15]+1==1){
T[15]=1;
}

for(int i=14;i>=0;i--){
if(T[i]+rest==2){
T[i]=0;
rest=1;
}else if(T[i]+rest==1){
T[i]=1;
rest=0;
}
}

return T ; 
}


int *  conversion_decimal_a_binaire(int a, int *T2) 

{
	int n = 16 ;
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
	for ( int i = 0 ; i< 16 ; i++) printf ("%d",T2[i]);printf("\n");
	return T2;
}





int main (int argc , char ** argv)
{
    
    
	if (argc < 2) { printf ("Erreur dans le nombre d'argument verifiez le makefile ! ");  exit(1); }


	float tab_correlations[3]={0.375,0.75,0.25};
	
	//la ou on va stocker le resulat  des 3 lfsr 
	char ** LFSRS = malloc(sizeof(char *) * 3 +1);
	for (int i = 0 ; i < 3; i++)  LFSRS[i] = malloc (sizeof (char) *16 +1) ;
	//taille de la suite chiffrante
	int taille = strlen(argv[1])-1;	
	int * suite = StringtoInt(argv[1]);
	//lfsr qui servira de tester les 2 puissance 16 possiblité
	int *LFSRTEST = malloc(sizeof(int)*16);
	for (int i = 0 ; i< 16 ; ++i ) LFSRTEST[i] = 0 ;
	//la sortie du lfsrtest qui fait la mm taile que la suite car on compare 
	char *generer = malloc(taille* sizeof(char) +1); 
	 
	//65536 2^16
	for (int i = 0 ; i < 65536; i++){		
	  //int * tmp = 	New_Init(LFSRTEST);
		LFSRTEST = New_Init(LFSRTEST);
	  //on produit  une chaine de la mm taille que la suite 
			for (int k = 0 ; k < taille ; ++k){
								generer[k] = '0'+ LFSRTEST[0];
								LFSRTEST = CalculduBitFort0(LFSRTEST);
							} 
		// on compare la correlation de la suite generer et la suite chiffree 
		//avec la correlation quon a 	

		if( comparer( correlation(StringtoInt(generer),suite) , tab_correlations[0]) )
	        // si cest bon on stock 
			for (int j =0 ; j< 16 ; ++j ) LFSRS[0][j]='0'+LFSRTEST[j] ;
		if( comparer( correlation(StringtoInt(generer),suite) , tab_correlations[1]) )
	        // si cest bon on stock 
			for (int j =0 ; j< 16 ; ++j ) LFSRS[1][j]='0'+LFSRTEST[j] ;
		if( comparer( correlation(StringtoInt(generer),suite) , tab_correlations[2]) )
	        // si cest bon on stock 
			for (int j =0 ; j< 16 ; ++j ) LFSRS[2][j]='0'+LFSRTEST[j] ;
				
		
		 
	
		
	    

	    //LFSRTEST= New_Init(tmp);
		
	}	
		
		for (int i = 0 ; i< 3 ; ++i)
		 	 	printf("LFSR%d :%s\n",i , LFSRS[i]);
	

	return 0; 
}