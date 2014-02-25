// compilation : gcc -g freq.c -o freq
// usage : ./makeData training < <fichier_source> > <fichier_dest>
//         ./makeData test < <fichier_source> > <fichier_dest> 

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {

  int c,i,nbr=0,tab[256] = {0};

  //printf("argv2 = %s argv3 = %s\n", argv[2], argv[3]);

  if(argv[1] == NULL) {
	printf("Usage : ./makeData training/test < <fichier_source> > <fichier_dest>\n");
	return 0;
  }

  FILE* input = fopen(argv[2], "r");
  FILE* output = fopen(argv[3], "w");

  if(!strcmp(argv[1], "training"))
  while((c=fgetc(input))!=EOF) {     
      //printf("%c",c); // test char
      //printf("%d\n",c); //test nbr
      nbr++;
      tab[c]++;          
      if (c == '\n') { // fin d'un tweet => affichage
        // affichage et re-initialisation               
	//
	// on ne prend que les symboles suceptible d'être 
	// non-nuls car si on donne trop d'entrée toujours à 0
	// (donc sans information) cela gêne l'apprentissage	
        for(i=97;i<123;i++) // 'a'=97 --> 'z'=122
             fprintf(output, "%f ",(float)tab[i]/(float)nbr);
	     
	     if(!strcmp(argv[2], "./tweets/trainData.de.txt"))
		fprintf(output, "1 -1 -1 -1 -1 -1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.es.txt"))
		fprintf(output, "-1 1 -1 -1 -1 -1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.it.txt"))
		fprintf(output, "-1 -1 1 -1 -1 -1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.tr.txt"))
		fprintf(output, "-1 -1 -1 1 -1 -1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.en.txt"))
		fprintf(output, "-1 -1 -1 -1 1 -1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.fr.txt"))
		fprintf(output, "-1 -1 -1 -1 -1 1 -1");

	     else if(!strcmp(argv[2], "./tweets/trainData.pt.txt"))
		fprintf(output, "-1 -1 -1 -1 -1 -1 1");

        fprintf(output,"\n");         
        // re-initialisation
        nbr = 0;
        for(i=0;i<256;i++)
          tab[i] = 0;
      }
  }
  else if(!strcmp(argv[1], "test"))
      while((c=fgetc(input))!=EOF) {     
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
             fprintf(output, "%f ",(float)tab[i]/(float)nbr);
	fprintf(output, "-1 -1 -1 -1 -1 -1 -1");
        fprintf(output,"\n");         
        // re-initialisation
        nbr = 0;
        for(i=0;i<256;i++)
          tab[i] = 0;
      }
      }

  else
	printf("Usage : ./makeData training/test < <fichier_source> > <fichier_dest>\n");

  fclose(input);
  fclose(output);
  return 0;
}
