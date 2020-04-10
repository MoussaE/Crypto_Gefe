#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int* StringtoInt(char *chaine)
{
	int taille = strlen(chaine) -1 ; 
	int  *tab = malloc ( taille *sizeof(int)); 
	for( int i = 0 ; i < taille ; ++i )
		tab[i] = (int) (chaine [i]-48);
	return tab; 
}

int * CalculduBitFort0(int * tab)
{
    int val  = tab[0] ^ tab[1] ^ tab[4] ^tab [7] ; 
    for (int i = 0 ; i< 15 ; ++i)
          tab[i] = tab[i+1]; 
    tab [15] = val ; 
    return tab;    
}

int * CalculduBitFort1(int * tab)
{
    int val  = tab[0] ^ tab[1] ^ tab[7] ^tab [11] ; 
    for (int i = 0 ; i< 15 ; ++i)
          tab[i] = tab[i+1]; 
    tab [15] = val ;
    return tab; 
    
}
int * CalculduBitFort2(int * tab)
{
    int val  = tab[0] ^ tab[2] ^ tab[3] ^tab [5] ;  
    for (int i = 0 ; i< 15 ; ++i)
          tab[i] = tab[i+1]; 
    tab [15] = val ; 
    return tab; 

}

int FonctiondeFiltrage(int x0 , int x1 , int x2 , int * F)
{
  if (x0 == 0 && x1 == 0 && x2 == 0)  	   return F[0];
  else if  (x0 == 1 && x1 == 0 && x2 == 0) return F[1];
  else if  (x0 == 0 && x1 == 1 && x2 == 0) return F[2];
  else if  (x0 == 1 && x1 == 1 && x2 == 0) return F[3];
  else if  (x0 == 0 && x1 == 0 && x2 == 1) return F[4];
  else if  (x0 == 1 && x1 == 0 && x2 == 1) return F[5];
  else if  (x0 == 0 && x1 == 1 && x2 == 1) return F[6];
  else  return F[7];

}

char * Generer_Suite_Chiffrante(char *F , char *L0 , char  *L1, char *L2 , int nb_tours)
{
   char * suite = malloc (nb_tours*sizeof(char) + 1);
   int * lfsr0 = StringtoInt(L0);
   int * lfsr1 = StringtoInt(L1);
   int * lfsr2 = StringtoInt(L2);
   int * f = StringtoInt (F);
    

   for (int i = 0 ; i <nb_tours ; ++i)
   {
   			suite [i] =(FonctiondeFiltrage(lfsr0[0],lfsr1[0],lfsr2[0],f))+'0';
   			lfsr0 = CalculduBitFort0(lfsr0);
   			lfsr1 = CalculduBitFort1(lfsr1);
   			lfsr2 = CalculduBitFort2(lfsr2);
   }
   
   	free (lfsr0); free(lfsr1); free(lfsr2); free (f); 
  	return suite; 
}







int main(int argc , char ** argv)
{
   if ( argc < 4)
   				 printf ("Erreur veuillez vérfifier le nombre d'argumant dans le Makefile !\n"); 
   
   //taille souhaité de la suite 
   int taille = 100;

   printf("\nLFSR0 : %s\n",argv[2]);
   printf("\nLFSR1 : %s\n",argv[3]);
   printf("\nLFSR2 : %s\n",argv[4]);
   printf("\nFonction de filtrage F: %s\n",argv[1]);
   printf("\nLa taille de la suite chifffrante  est  : %d \n",taille);
   printf("\nSuite chifffrante:%s\n",Generer_Suite_Chiffrante(argv[1],argv[2],argv[3],argv[4],taille));



	return 0; 
}