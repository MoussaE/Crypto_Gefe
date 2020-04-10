#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//quelques fonctions de conversions 16 -> 2 et 2 -> 16 
char* HexaEnBinaire(char entier);
char* BinairEnHexa(char * entier);
char* conversion16en2(char * hexa);
char* conversion2en16(char* binair);


//<<7
char * Fonction_de_rotation(char * data)
{
	char * tmp = malloc (sizeof(char) * 32 +1); 
	
	for (int i = 7 ; i < 32 ; ++i )
		 tmp [i-7] = data[i]; 
	for (int  i = 0 ; i< 7; ++i )
		 tmp [i+25]= data[i];
		free(data);
		return tmp;  

}

// retourne le xor de deux entier sous forme de chaine 
char * XOR_TABLEAU (char * a , char * b )
{
    char * retour = malloc (sizeof (char) *32 + 1); 

    for (int i = 0 ; i< 32 ; ++i )
    {
    	retour [i] = ( ((int)(a[i]-48)) ^ ((int)(b[i]-48)) )+ '0'; 
    }

   return retour; 
}



char ** retouver_cle(char * a , char* b , char *c , char *d,char * e , char* f , char *g , char *h)
{
	char * xl0 = conversion16en2(a);      
	char * xr0 = conversion16en2(b); 
	char * xl12 = conversion16en2(c);
	char * xr12 = conversion16en2(d);
	char * bl0 = conversion16en2(e); 
	char * br0 = conversion16en2(f); 
	char * bl12 = conversion16en2(g);
	char * br12 = conversion16en2(h);
	
    char *b1  = malloc(sizeof (char) * 32 +1 ); 
     char *b1r  = malloc(sizeof (char) * 32 +1 ); 

    
	char ** clee = malloc (sizeof(char *) *2 +1); 
	for (int i = 0 ; i< 2 ; ++i ) clee[i] = malloc(sizeof(char) *32+1);

       strcpy (clee[0] ,XOR_TABLEAU(xl12, Fonction_de_rotation(XOR_TABLEAU(bl12,br12))));
       strcpy (clee[1] ,XOR_TABLEAU(xr12 , Fonction_de_rotation(XOR_TABLEAU(xr12,xl12))));

 		 strcpy (b1,XOR_TABLEAU(bl0, Fonction_de_rotation(XOR_TABLEAU(bl0,br0))));
   	     strcpy (b1r ,XOR_TABLEAU(clee[1], Fonction_de_rotation(XOR_TABLEAU(br0,b1))));

   	     if ( !strcmp(b1 , xl0) && !strcmp(br0,b1r))
   	     	printf ("\nk0 et k1 sont les bonnes clées \n"); 
   	     else 
   	     	printf("réessayez a nouveau avec de nouveau parametre dans le makefile\n");

      return clee ;  
	 

}


int main (int argc , char ** argv)
{


	 if(argc < 9) printf("erreur du nombre d'arguments \n" );
      
    // exmple du DM  45019824 51023321 00D7818E 72AF039A
    // on retrouve bien   k0  : 01020304 k1  : 00D7818E
    // pour tester dautre exemples il faut modifier les valeur d'enntree dans la makefile

   char ** clee = retouver_cle (argv[1],argv[2],argv[3],argv[4],argv[5],argv[6],argv[7],argv[8]);
   printf (" k0  : %s\n",conversion2en16(clee[0]));
   printf (" k1  : %s\n",conversion2en16(clee[1]));

   for (int i = 0 ; i < 2 ; ++ i)  free(clee[i]); 
   free (clee);


	return 0; 
}









char * HexaEnBinaire(char entier)
{
   char * retour = malloc (sizeof (char) * 4+1); 

   switch (entier)
   {
      case '0' : strcpy(retour , "0000"); break;
      case '1' : strcpy(retour , "0001"); break; 
	  case '2' : strcpy(retour , "0010"); break; 
	  case '3' : strcpy(retour , "0011"); break; 
	  case '4' : strcpy(retour , "0100"); break; 
	  case '5' : strcpy(retour , "0101"); break; 
	  case '6' : strcpy(retour , "0110"); break; 	 
	  case '7' : strcpy(retour , "0111"); break; 
	  case '8' : strcpy(retour , "1000"); break; 
	  case '9' : strcpy(retour , "1001"); break; 
	  case 'A' : strcpy(retour , "1010"); break; 
	  case 'B' : strcpy(retour , "1011"); break; 
	  case 'C' : strcpy(retour , "1100"); break; 
	  case 'D' : strcpy(retour , "1101"); break; 
	  case 'E' : strcpy(retour , "1110"); break; 
	  case 'F' : strcpy(retour , "1111"); break; 
	default :  printf ("erreur de conversion \n "); exit(1);   
   }
   return retour ; 
}

char*  BinairEnHexa(char *  entier)
{
	char * tmp = malloc (sizeof (char)*1+1);
      		if(!strcmp(entier, "0000"))    strcpy(tmp ,"0");
      else if (!strcmp(entier , "0001"))   strcpy(tmp ,"1");
	  else if (!strcmp(entier , "0010"))   strcpy(tmp ,"2");
	  else if (!strcmp(entier , "0011"))   strcpy(tmp ,"3");
	  else if (!strcmp(entier , "0100"))   strcpy (tmp ,"4");
	  else if (!strcmp(entier , "0101"))   strcpy(tmp ,"5");
	  else if (!strcmp(entier , "0110"))   strcpy(tmp,"6");
	  else if (!strcmp(entier , "0111"))   strcpy(tmp ,"7");
	  else if (!strcmp(entier , "1000"))   strcpy(tmp,"8");
	  else if (!strcmp(entier , "1001"))   strcpy(tmp,"9");
	  else if (!strcmp(entier , "1010"))   strcpy(tmp,"A");
	  else if (!strcmp(entier, "1011"))    strcpy(tmp,"B");
	  else if (!strcmp(entier, "1100"))    strcpy(tmp,"C");
	  else if (!strcmp(entier , "1101"))   strcpy(tmp,"D");
	  else if (!strcmp(entier , "1101"))   strcpy(tmp,"D");
	  else if (!strcmp(entier , "1110"))   strcpy(tmp,"E");
	  else if (!strcmp(entier, "1111"))    strcpy(tmp ,"F");
	    
	  return tmp ; 
	
}


char *conversion16en2(char * hexa)
{
	   char * retour  = malloc (sizeof (char )* strlen (hexa)*4+1);
	   for (int i = 0 ; i< strlen(hexa) ; ++i )
	      strcat (retour ,HexaEnBinaire(hexa[i]));
	      return retour;  
}

char * conversion2en16(char* binair)
{  
	int cpt = 0 ; 
	 char * tmp = malloc (sizeof(char) *1+1);
     char * retour = malloc (sizeof (char)* (strlen(binair)/4)  + 1 ); 
     char * tmp1 = malloc (sizeof(char) *4+1);
     for (int i = 0 ; i < strlen(binair) ; i++){
     		tmp[0] = binair[i];
     		tmp[1] = '\0'; 
     		cpt++; 
     		strcat (tmp1 , tmp);
     		if (cpt == 4  )
     		{ 
     			strcat(retour,BinairEnHexa(tmp1));  
     			cpt = 0 ; 
     			 free (tmp1);  
     			 tmp1 = malloc (sizeof(char) *4+1) ;
     			}	
     }
   return retour;       
}