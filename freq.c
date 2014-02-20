// compilation : gcc -g freq.c -o freq
// usage : ./freq < tweets.txt 

#include <stdio.h>

int main(int argc, char **argv) { 
  int c,i,nbr=0,tab[256] = {0};
 
  while((c=fgetc(stdin))!=EOF) {     
      //printf("%c",c); // test char
      //printf("%d\n",c); //test nbr
      nbr++;
      tab[c]++;          
      if (c == '\n') { // fin d'un tweet => affichage
        // affichage et re-initialisation               
	//
	// one ne prend que les symboles suceptible d'être 
	// non-nuls car si on donne trop d'entrée toujours à 0
	// (donc sans information) cela gêne l'apprentissage	
        for(i=97;i<123;i++) // 'a'=97 --> 'z'=122
	//for(i=0;i<256;i++)
             printf("%f ",(float)tab[i]/(float)nbr);
        printf("\n");         
        // re-initialisation
        nbr = 0;
        for(i=0;i<256;i++)
          tab[i] = 0;
      }
  }
  return 0;
}
