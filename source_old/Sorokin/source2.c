#include <stdio.h>
#include <string.h>
#define MAX_FILE_SIZE 1000
/*Pozvolyaet opredelyat imya novogo tipa dannyh BYTE*/
typedef unsigned char BYTE;
/*perechislenie chvetov*/
enum colors {blue, green, red};

/*Pozvolyaet opredelyat imya novogo tipa dannyh PIXEL*/
typedef struct{BYTE blue ; BYTE green; BYTE red;} PIXEL;
main()
{
/*Obyavlenie peremennih dlya izobrah*/
    char type[2];  
    int size;
    int res;
    int off;
    int ssz;
    int w;
    int h;
    int end[7];
/*Otkrivaet 1 fail and schitivaet*/
    FILE * fin = fopen("1.bmp", "r");
    perror("Open file");
/*Otkrivaet 2 fail and zapisivaet*/
    FILE * fout = fopen("2.bmp", "w");
    perror("Open file");

/*schitivaet*/
    fread(&type, 2, 1, fin);
    fread(&size, 4, 1, fin);
    fread(&res, 4, 1, fin);
    fread(&off, 4, 1, fin);
    fread(&ssz, 4, 1, fin);
    fread(&w, 4, 1, fin);
    fread(&h, 4, 1, fin);
    fread(end, 4, 7, fin);
    PIXEL rastr[MAX_FILE_SIZE][MAX_FILE_SIZE];

/*schitivaet pixeli*/
int padding=(size-off-h*w*3)/h;
BYTE pad[20];   
int i,j;
for(i=0; i<h ; i++)
{
	for(j=0; j<w ; j++)
		fread(&rastr[i][j], 3, 1, fin);
        fread(pad, padding, 1, fin);        
} 
/*new visota and zapis faila*/
    int new_w = w*3;
    fwrite(&type, 2, 1, fout);
    fwrite(&size, 4, 1, fout);
    fwrite(&res, 4, 1, fout);
    fwrite(&off, 4, 1, fout);
    fwrite(&ssz, 4, 1, fout);
    fwrite(&new_w, 4, 1, fout);
    fwrite(&h, 4, 1, fout);
    fwrite(end, 4, 7, fout);
/*rabochii kod (rastagivaet izobrah v 3 raza po gorizontali)*/
for(i=0; i<h ; i++)
{
	for(j=0; j<w ; j++)
	{
		fwrite(&rastr[i][j], 3, 1, fout);
		fwrite(&rastr[i][j], 3, 1, fout);
		fwrite(&rastr[i][j], 3, 1, fout);
	}
        fwrite(pad, padding, 1, fout);        
}	
return 0; 
}
