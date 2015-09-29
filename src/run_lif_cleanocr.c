/*  Clean an OCR output according to a vast lexicon  */
/*  FRED 0615  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <lia_liblex.h>
#include <charset.h>

/*................................................................*/

#define TailleLigne     4000

#define True    1
#define False   0

void ERREUR(char *ch1,char *ch2){
	fprintf(stderr,"ERREUR : %s %s \n",ch1,ch2);
	fprintf(stderr,"Use --h for help \n");
	
	exit(0);
}

void ERREURd(char *ch1, int i){
	fprintf(stderr,"ERREUR : %s %d\n",ch1,i);
	exit(0);
}

/*................................................................*/

#define MAX_CONFUSION   1000

char *T_confusion[MAX_CONFUSION][2];
int NbConf=0;

/*................................................................*/

int find_word(int lexidorig, int lexidlite, char *ch, char *buffer){
	
	int ret,nb,i,j,found;
	char *ptword,chconfu[TailleLigne];
	wchar dest[TailleLigne];
	buffer[0]='\0';
	
	if (word2code(lexidorig,ch,&i)) { sprint_code_list_word(buffer,lexidorig,i); return True; }
	ret=utf8ToUnicode(ch,strlen(ch),dest,TailleLigne); dest[ret]='\0';
	ret=unicodeToIso8859(dest,ret,ch,TailleLigne); ch[ret]='\0';
	copy_lite(dest,ch);
	if (word2code(lexidlite,(char*)dest,&i)) /* we found it lite !! */{
		if (!code2word(lexidorig,i,&ptword)) ERREUR("ZORG:",(char*)dest);
		sprint_code_list_word(buffer,lexidorig,i);
		return True;
	}

	strcpy(ch,(char*)dest);
	for(i=found=0;(!found)&&(ch[i]);i++){
		for (j=0;(j<NbConf)&&(!found);j++)
		if (!strncmp(ch+i,T_confusion[j][0],strlen(T_confusion[j][0]))){
			strcpy(chconfu,ch);
			strcpy(chconfu+i,T_confusion[j][1]);
			strcpy(chconfu+i+strlen(T_confusion[j][1]),ch+i+strlen(T_confusion[j][0]));
			//printf("confusion: %s => %s\n",ch,chconfu);
			if (word2code(lexidlite,chconfu,&i)){
				if (!code2word(lexidorig,i,&ptword)) ERREUR("ZORG:",(char*)dest);
				sprint_code_list_word(buffer,lexidorig,i);
				found=1;
			}
		}
	}
	return found;
}

/*................................................................*/

#define ISO8	0
#define UTF8	1

int main(int argc, char **argv) {
	
	if(argc <2){
		fprintf(stderr,"USAGE : %s --input ocr.flitred.xml --lex lexique [--confusion <file>][--threshold <float>] \n", argv[0]);
		fprintf(stderr," --input                      Specify input XML file\n");
		fprintf(stderr," --lex                        Specify vocabulary\n");
		fprintf(stderr," --confusion                  Specify confusions file (eg. o p)\n");
		fprintf(stderr," --threshold                  Specify the filtering threshold (percentage of sentence to be found in the lexicon, 0-1, default 0.5)\n");		
		
	return 1;
	}



    
	int ret,nb,i,j,k,lexidorig,lexidlite,ilite,found,nbin;
	double coeff;
	char ch[TailleLigne],*chname,chorig[TailleLigne],*ptword,chconfu[TailleLigne],buffer[TailleLigne],chfilt[TailleLigne],wpart1[TailleLigne],wpart2[TailleLigne],input[TailleLigne];
	wchar dest[TailleLigne];
	FILE *file;
	chconfu[0]='\0';
	chname=NULL;
	coeff=0.5;

	if (argc>1)
		for(nb=1;nb<argc;nb++)
		if (!strcmp(argv[nb],"--lex")){
			if (nb+1==argc) ERREUR("must have a value after argument;",argv[nb]);
			chname=argv[++nb];
		}	
		else
			if (!strcmp(argv[nb],"--confusion")){
				if (nb+1==argc) ERREUR("must have a value after argument;",argv[nb]);
				strcpy(chconfu,argv[++nb]);
		}
		else
			if (!strcmp(argv[nb],"--input")){
				if (nb+1==argc) ERREUR("must have a value after argument;",argv[nb]);
				strcpy(input,argv[++nb]);
		}
		else
			if (!strcmp(argv[nb],"--threshold")){
				if (nb+1==argc) ERREUR("must have a value after argument;",argv[nb]);
				if (sscanf(argv[++nb],"%lf",&coeff)!=1) ERREUR("bad argument:",argv[nb]);
			}
		else
			if (!strcmp(argv[nb],"--h")){
				fprintf(stderr,"USAGE : %s --input ocr.flitred.xml --lex lexique [--confusion <file>][--threshold <float>] \n", argv[0]);
				exit(0);
			}
		else ERREUR("Unknown option ",argv[nb]);

			if (chname==NULL) {
				fprintf(stderr,"**** BAD SYNTAX ****\n");
				fprintf(stderr,"USAGE : %s --input ocr.flitred.xml --lex lexique [--confusion <file>][--threshold <float>] \n", argv[0]);
				exit(0);
			}


			if (chconfu[0]){
				NbConf=0;
				if (!(file=fopen(chconfu,"rt"))) ERREUR("can't open:",chconfu);
				for (nb=0;fgets(ch,TailleLigne,file);nb++){
					if (NbConf==MAX_CONFUSION) ERREUR("cste MAX_CONFUSION too small","");
					ptword=strtok(ch," \t\n\r"); if (!ptword) ERREUR("bad format:",ch);
					T_confusion[NbConf][0]=strdup(ptword);
					ptword=strtok(NULL," \t\n\r"); if (!ptword) ERREUR("bad format:",ch);
					T_confusion[NbConf][1]=strdup(ptword);
					NbConf++;
				}
				fclose(file);
			}

			lexidorig=new_lexicon();
			lexidlite=new_lexicon();
			if (!(file=fopen(chname,"rt"))) ERREUR("can't open:",chname);
			for(nb=ilite=0;fgets(ch,TailleLigne,file);nb++){
				strtok(ch," \t\n\r");
				strcpy(chorig,ch);
				ret=utf8ToUnicode(ch,strlen(ch),dest,TailleLigne);
				dest[ret]='\0';
				ret=unicodeToIso8859(dest,ret,ch,TailleLigne);
				ch[ret]='\0';
				copy_lite(dest,ch);
				if (!word2code(lexidlite,(char*)dest,&j)) j=ilite++;
				add_word_lexicon(lexidlite,(char*)dest,j);
				add_word_lexicon(lexidorig,chorig,j);
			}
			fclose(file);
			lexicon_sort_code(lexidlite);
			lexicon_sort_code(lexidorig);
			
			FILE *f;
			
			if (!(f=fopen(input,"rt"))) ERREUR("can't open:",input);
			while(fgets(ch,TailleLigne,f)){
				int ok=0;
				printf("%s",ch);
				if (strstr(ch,"<ocr>")){
					for(i=0;(ch[i])&&(strncmp(ch+i,"<ocr>",4));i++) printf("%c",ch[i]); if (!ch[i]) ERREUR("DOODi::",ch);
					for (j=i+5;(ch[j])&&(strncmp(ch+j,"</ocr>",5));j++); if (!ch[j]) ERREUR("bad format:",ch);
					ch[j]='\0';
					strcpy(chorig,ch+i+5);
					for(chfilt[0]='\0',nb=nbin=0,ptword=strtok(chorig," \t\n\r");ptword;ptword=strtok(NULL," \t\n\r"),nb++){
						strcpy(wpart1,ptword);
						if (find_word(lexidorig,lexidlite,ptword,buffer)){ 
							nbin++; 
							sprintf(chfilt+strlen(chfilt),"[%s]",buffer); 
							char k;
							for(k=0; ptword[k]!='\0'; ++k);
							if (k >3) ok=1;
						}
						else
							if (strstr(wpart1,"'")){
								for(i=0;(wpart1[i])&&(wpart1[i]!='\'');i++);
									wpart1[i]='\0';
									for(i++,j=0;wpart1[i];i++,j++) wpart2[j]=wpart1[i];
									wpart2[j]='\0';
								if (find_word(lexidorig,lexidlite,wpart1,buffer)) {
									nbin++;
									sprintf(chfilt+strlen(chfilt),"[%s]",buffer); 
									char k;
									for(k=0; wpart1[k]!='\0'; ++k);
									if (k >3) ok=1;
								}
								else sprintf(chfilt+strlen(chfilt),"[!%s!]",wpart1);
								if (find_word(lexidorig,lexidlite,wpart2,buffer)) {
									 sprintf(chfilt+strlen(chfilt),"[%s]",buffer); 
								}
								else sprintf(chfilt+strlen(chfilt),"[!%s!]",wpart2);
							}
						else sprintf(chfilt+strlen(chfilt),"[!%s!]",wpart1);
					}	
					float t=coeff;
					if (nb <=3) {t=0.5;}
					if (ok ==0) {t=1;}
					if (nbin>=((double)nb)*(double)t) // more than coeff% in vocab 
						printf("<ocrFiltered>%s<ocrFiltered>\n",chfilt);
					else
						printf("<ocrFiltered>REJECTED<ocrFiltered>\n");
			}
		}
		fclose(f);
	exit(0);
}
  
