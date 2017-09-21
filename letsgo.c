#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

typedef struct {char n[32]; int e; int p;}array;
int meretez ( char *fn, int *m);
int beolvas ( array **v, int *m);
void display (array *v, int m);
int verseny ( array *v, int m);
int maximum (array *v, int m);
int kereso (array *v, int m);
int otven ( array *v, int m);
int megjelenit (char *fn);
int zhkiir (array *v, int m);

int main(){
	array *valami=NULL; int meret=0;
	if(beolvas(&valami, &meret)){printf("Sikertelen memoriafoglalas vagy filenyitas, a program leall ! \n");return(0);}
	display (valami, meret);
	if(verseny(valami, meret)){printf("Sikertelen filenyitas!!!\n");return(0);}
	if(maximum(valami, meret)){printf("Sikertelen filenyitas!!!\n");return(0);}
	if(otven(valami, meret)){printf("Sikertelen filenyitas!!!\n");return(0);}
	if(kereso(valami, meret)){printf("Sikertelen filenyitas!!!\n");return(0);}
	if(zhkiir(valami, meret)){printf("Sikertelen filenyitas!!!\n");return(0);}


}


int meretez ( char *fn, int *m){
	FILE *f=NULL; char c;
	printf("Melyik filet nyissuk meg ? \n"); scanf("%s", fn);
	if(!(f=fopen(fn, "r"))){return(1);}
	while((c=fgetc(f))!=EOF){if(c=='\n'){(*m)++;}}
	fclose(f);
	return(0);
}

int beolvas ( array **v, int *m){
	FILE *f=NULL; char fn[32]; int i=0;
	if(meretez(fn, m)){return(1);}
	if(!(f=fopen(fn, "r"))){return(1);}
	if(!(*v=(array *)malloc(*m*sizeof(array)))){return(1);}
	while(!feof(f)){fscanf(f, "%s%d", (*v)[i].n, &(*v)[i].e);i++;}
	fclose(f);
	return(0);
}

void display (array *v, int m){
	int i;
	for(i=0;i<m;i++){
	printf("Nev: %s \t evfolyam: %d. \n", v[i].n, v[i].e);
	}

}

int verseny ( array *v, int m){
	FILE *f=NULL; int i; srand(time(NULL));
	if(!(f=fopen("verseny.txt", "w"))){return(1);}
	printf("\n\nA verseny eredmenye: \n");
	fprintf(f, "A verseny eredmenye: \n");
	
	for(i=0;i<m;i++){
	v[i].p=rand()%(76+1-25)+25;
	printf("Nev: %s \t evfolyam: %d. \t pontszam: %d\n", v[i].n, v[i].e, v[i].p);
	fprintf(f, "Nev: %s \t evfolyam: %d. \t pontszam: %d\n", v[i].n, v[i].e, v[i].p);
	}
	fflush(f);
	fclose(f);
	return(0);
}

int maximum (array *v, int m){
	FILE *f=NULL; char max=v[0].p; int i=0;
	if(!(f=fopen("verseny.txt", "a"))){return(1);}
	for(i=1;i<m;i++){if(v[i].p>max){max=v[i].p;}}

	for(i=0;i<m;i++){
	if(max==v[i].p){
			printf("\nA legtobb pontot %s erte el %d ponttal a %d. evfolyambol!\n", v[i].n, v[i].p, v[i].e);
			fprintf(f, "\nA legtobb pontot %s erte el %d ponttal a %d. evfolyambol!\n", v[i].n, v[i].p, v[i].e);
		}
	}
	fflush(f);
	fclose(f);
	return(0);	
}

int kereso (array *v, int m){
	FILE *f=NULL; int i=0, j=0, kithossz; char kit[32];
	if(!(f=fopen("verseny.txt", "a"))){return(1);}
	printf("Kit keresunk, Peti mester ? \n"); scanf("%s", kit); kithossz=strlen(kit);
	for(i=0;i<m;i++){
	while(kit[j]!=0){if(v[i].n[j]!=kit[j]){break;}else{j++;}}
	if(kithossz==j && kithossz == strlen(v[i].n)){break;}
	}

	if(i==m){printf("\nNincs ilyen nev a nyilvantartasban!!!\n");return(0);}
	else{
	printf("\nA keresett nev: %s a %d. evfolyambol %d ponttal!\n", v[i].n, v[i].e, v[i].p);
	fprintf(f, "\nA keresett nev: %s a %d. evfolyambol %d ponttal!\n", v[i].n, v[i].e, v[i].p);
	}
	fflush(f);
	fclose(f);
	return(0);	
}

int otven ( array *v, int m){
	FILE *f=NULL; int i, error=1;
	if(!(f=fopen("verseny.txt", "a"))){return(1);}
	
	for(i=0;i<m;i++){
	if(v[i].p>50){
		error=0;
		printf("\nOtvennel tobb pontot ert el %s a %d. evfolyambol %d ponttal\n", v[i].n, v[i].e, v[i].p);
		fprintf(f, "\nOtvennel tobb pontot ert el %s a %d. evfolyambol %d ponttal\n", v[i].n, v[i].e, v[i].p);
		}
	}
	
	if(error==1){printf("Senki sem ert el 50-nel tobb pontot!\n");return(0);}
	fflush(f);
	fclose(f);
	return(megjelenit("verseny.txt"));
}

int megjelenit (char *fn){
	FILE *f=NULL; char c;
	printf("\nA file tartalma: \n\n");
	if(!(f=fopen(fn, "r"))){return(1);}
	printf("\n####################\n");
	while((c=fgetc(f))!=EOF){putchar(c);}
	printf("\n####################\n");

	fclose(f);
	return(0);
}


int zhkiir (array *v, int m){
	FILE *ide=NULL, *innen=NULL; char c;
	if(!(innen=fopen("letsgo.c", "r"))){return(1);}
	if(!(ide=fopen("zh.txt", "w"))){return(1);}
	while((c=fgetc(innen))!=EOF){fputc(c, ide);}
	fflush(ide);
	fclose(ide);
	fclose(innen);
	return(0);
}
