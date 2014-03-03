#include <stdio.h>
#include <stdlib.h>
#include "floatfann.h"
#include "fann.h"

// gcc script.c -o script.exe -Wall -lfann -lm -L/usr/local/lib


/****prototype****/

int compteLigne(FILE *fichier);
int nextCharInFile(FILE *fichier);
void apprentissage(char* filename);
char* parametrisation();
void rempliOut(FILE *src,FILE * out,int input,int lang);


/****main****/

int main (int argc, char **argv){


	char choix;
	int res=0;
	char* filename = NULL;
	filename = parametrisation();
	while(res==0){
		printf("Voulez vous construire le network.net? [Y][N] :");
		scanf("%c",&choix);
		if(choix>=65&&choix<=90)
			choix=choix+32;
		if(choix==121){// y
			apprentissage(filename);
			res=1;
		}else if(choix==110){// n
			printf("Fin\n");
			res=1;
		}else{
			printf("Choix incorrect\n");
			printf("Suggestions :\n\tY\tN\n\ty\tn\n");
		}
	}

	return EXIT_SUCCESS;

}


/****fonctions****/

//--int

int compteLigne(FILE *fichier){
	int res=0;
	int compteur=0;
	int c;
	while(res==0){
		c=fgetc(fichier);
		if(c==EOF)
			res=1;
		if(c=='\n')
			compteur++;
	}
	return compteur;
}

int nextCharInFile(FILE *fichier){

	int tmp;
	int tmpp;
	int tmppp;
	int res=0;
	int c;

	while(res==0){
		c=fgetc(fichier);
		if(c==EOF){
			c=-1;
			res=1;
		}else{
			if(c==35||c==64){//c'est un # ou un @
				int resTag=0;
				while(resTag==0){
				c=fgetc(fichier);
					if(c==32||c=='\n')
						resTag=1;
				}
			}
			if(c>=65&&c<=90)
				c=c+32;
			if(c>=97&&c<=122){
				if(c==104){//c'est un 'h'
					tmp=fgetc(fichier);
					if(tmp==116){//la lettre d'après, le't'
						tmpp=fgetc(fichier);
						if(tmpp==116){//encore un t
							tmppp=fgetc(fichier);
							if(tmppp==112){//si c'est un p on a une url
								int resUrl=0;
								//printf("=>%c%c%c%c",c,tmp,tmpp,tmppp);
								while(resUrl==0){
									c=fgetc(fichier);
									if(c==32||c=='\n')
										resUrl=1;
									//printf("%c",c);
								}
								//printf("<=\n");
							}else{//c=h tmp=t tmpp=t tmppp!=p
								fseek(fichier,-3,SEEK_CUR);
								res=1;
							}
						}else{//c=h tmp=t tmpp!=t
							fseek(fichier,-2,SEEK_CUR);
							res=1;
						}
					} else{//c=h tmp!=t
						fseek(fichier,-1,SEEK_CUR);
						res=1;
					}
				}else{
					res=1;
				}
			}
			if(c=='\n')
				res=1;
		}
	}
	return c;
}

//--void

void apprentissage(char* filename){
	printf("--Apprentissage--\n");

    const unsigned int num_input = 26;
    const unsigned int num_output = 7;
    const unsigned int num_layers = 3;
    const unsigned int num_neurons_hidden = 50;
    const float desired_error = (const float) 0.001;
    const unsigned int max_epochs = 5000;
    const unsigned int epochs_between_reports = 100;


    struct fann *ann = fann_create_standard(num_layers, num_input,
        num_neurons_hidden, num_output);

    fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
    fann_set_activation_function_output(ann, FANN_SIGMOID_SYMMETRIC);

    fann_train_on_file(ann, filename, max_epochs,
    epochs_between_reports, desired_error);

    fann_save(ann, "network.net");

    fann_destroy(ann);

}

char* parametrisation(){

	printf("--Paramétrage--\n");

	char *de="tweets/trainData.de.txt";
	char *fr="tweets/trainData.fr.txt";
	char *en="tweets/trainData.en.txt";
	char *es="tweets/trainData.es.txt";
	char *it="tweets/trainData.it.txt";
	char *pt="tweets/trainData.pt.txt";
	char *tr="tweets/trainData.tr.txt";
	FILE *src;

	printf("-Compte du nombre de ligne totale\n");
	//compte du nombre de ligne total
	int nbTotalTweet=0;

	src=fopen(de,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("de ");

	src=fopen(fr,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("fr ");

	src=fopen(en,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("en ");

	src=fopen(es,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("es ");

	src=fopen(it,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("it ");

	src=fopen(pt,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("pt ");

	src=fopen(tr,"r");
	nbTotalTweet=nbTotalTweet+compteLigne(src);
	fclose(src);
	printf("tr\n %d lignes\n",nbTotalTweet);


	//Inititalisation du fichier de sortie
	printf("-Initialisation du fichier (Nom à spécifier).txt\n");
	int input=26;
	int output=7;
	printf("%d\tnombres d'element\n",nbTotalTweet);
	printf("%d\tentrees (lettres de l'alphabet)\n",input);
	printf("%d\tsorties (langues)\n",output);

	FILE *out;
	char* outFilename = malloc(sizeof (char)*100);
	printf("Entrez le nom du fichier de sortie svp\n");
	scanf("%s", outFilename);
	out=fopen(outFilename,"w");
	fprintf(out,"%d %d %d\n",nbTotalTweet,input,output);

	//remplissage du fichier de sortie
	printf("-Remplissage\n");

	src=fopen(de,"r");
	rempliOut(src,out,input,0);//0 de
	fclose(src);
	printf("de ");

	src=fopen(es,"r");
	rempliOut(src,out,input,1);//1 es
	fclose(src);
	printf("es ");

	src=fopen(it,"r");
	rempliOut(src,out,input,2);//2 it
	fclose(src);
	printf("it ");

	src=fopen(tr,"r");
	rempliOut(src,out,input,3);//3 tr
	fclose(src);
	printf("tr ");

	src=fopen(en,"r");
	rempliOut(src,out,input,4);//4 en
	fclose(src);
	printf("en ");

	src=fopen(fr,"r");
	rempliOut(src,out,input,5);//5 fr
	fclose(src);
	printf("fr ");

	src=fopen(pt,"r");
	rempliOut(src,out,input,6);//6 pt
	fclose(src);
	printf("pt\n");

	fprintf(out,"\n");
	fclose(out);

	printf("\n%s pret pour l'emploi\n", outFilename);

	return outFilename;

}

void rempliOut(FILE *src,FILE * out,int input,int lang){

	int nbr, c=1, i;
	int tab[256];

	c = nextCharInFile(src);
	while(c != EOF) {     
      //printf("c=%c",c); // test char
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
             fprintf(out, "%f ",(float)tab[i]/(float)nbr);
	     
	     if(lang==0)
		fprintf(out, "1 -1 -1 -1 -1 -1 -1");

	     else if(lang==1)
		fprintf(out, "-1 1 -1 -1 -1 -1 -1");

	     else if(lang==2)
		fprintf(out, "-1 -1 1 -1 -1 -1 -1");

	     else if(lang==3)
		fprintf(out, "-1 -1 -1 1 -1 -1 -1");

	     else if(lang==4)
		fprintf(out, "-1 -1 -1 -1 1 -1 -1");

	     else if(lang==5)
		fprintf(out, "-1 -1 -1 -1 -1 1 -1");

	     else if(lang==6)
		fprintf(out, "-1 -1 -1 -1 -1 -1 1");

        fprintf(out,"\n");         
        // re-initialisation
        nbr = 0;
        for(i=0;i<256;i++)
          tab[i] = 0;

      }

      c=nextCharInFile(src);

      }
}
