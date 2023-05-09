#include<stdio.h>
#include<string.h>

typedef struct{
	int matr;
	char nimi[50];
	char kood[11];
}TUDENG;

typedef struct{
	char kood[11];
	char linn[15];
}ELANIK;

int failikontroll(FILE*);
int failipikkus(FILE*);
void failistsisse(FILE*, TUDENG[]);
void failistsisse2(FILE*, ELANIK[]);


int main(void){
	FILE *F1;
	F1 = fopen("F1.txt", "r");
	if(failikontroll(F1)){
		return 10;
	}
	int pikkus;
	pikkus=failipikkus(F1);
	TUDENG tudengid[pikkus];
	failistsisse(F1, tudengid);
	FILE *F2;
	F2 = fopen("F2.txt", "r");
	if(failikontroll(F2)){
		return 12;
	}
	int pikkus2;
	pikkus2=failipikkus(F2);
	ELANIK elanikudkood[pikkus2];
	failistsisse2(F2, elanikudkood);
	char koht[15];
	printf("Sisestage elukoht: \n");
	scanf("%s", koht);
	int i;
	for(i=0;i<pikkus;i++){
		int kont;
		kont=strcmp(koht, elanikudkood[i].linn);
		if(kont==0){
			printf("%d %s %s\n", tudengid[i].matr, tudengid[i].nimi, tudengid[i].kood);
		}
	}
	
	
	return 0;
}

int failikontroll(FILE *F){
	if(F==NULL){
		return 1;
	}
	return 0;
}

int failipikkus(FILE *F){
	int i=0;
	char buf[256];
	while(fgets(buf, 256, F) != NULL){
		i++;
	}
	rewind(F);
	return i;
}

void failistsisse(FILE *F1, TUDENG tudengid[]){
	int i=0;
	while(fscanf(F1, "%d %s %s", &tudengid[i].matr, tudengid[i].nimi, tudengid[i].kood) != EOF){
		i++;
	}
}

void failistsisse2(FILE *F2, ELANIK elanikud[]){
	int i=0;
	while(fscanf(F2, "%s %s", elanikud[i].kood, elanikud[i].linn) != EOF){
		i++;
	}
}
