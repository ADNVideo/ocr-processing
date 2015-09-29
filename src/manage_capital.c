/*  Manage decapital functions in ISO889  */
/*  FRED 0615  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*................................................................*/

#define TailleLigne     8000

#define True    1
#define False   0

void ERREUR(char *,char *);
void ERREURd(char *, int );

/*................................................................*/

int if_capital(char c)
{
if ((c>='A')&&(c<='Z')) return True;
if (
        (c=='É') ||
        (c=='À') ||
        (c=='È') ||
        (c=='Ù') ||
        (c=='Â') ||
        (c=='Ê') ||
        (c=='Î') ||
        (c=='Ô') ||
        (c=='Û') ||
        (c=='Ä') ||
        (c=='Ë') ||
        (c=='Ï') ||
        (c=='Ö') ||
        (c=='Ü') ||
        (c=='Ç') ||
	(c=='Á') ||
	(c=='À') ||
	(c=='Â') ||
	(c=='Å') ||
	(c=='Ä') ||
	(c=='Ã') ||
	(c=='Æ') ||
	(c=='Ç') ||
	(c=='É') ||
	(c=='È') ||
	(c=='Ê') ||
	(c=='Í') ||
	(c=='Î') ||
	(c=='Ï') ||
	(c=='Ñ') ||
	(c=='Ó') ||
	(c=='Ò') ||
	(c=='Ô') ||
	(c=='Ö') ||
	(c=='Õ') ||
	(c=='Ø') ||
	(c=='Ú') ||
	(c=='Û') ||
	(c=='Ü')
   ) return True;
return False;
}

int if_lettre(char c)
{
if ((c>='A')&&(c<='Z')) return True;
if ((c>='a')&&(c<='z')) return True;
if (
        (c=='É') ||
        (c=='À') ||
        (c=='È') ||
        (c=='Ù') ||
        (c=='Â') ||
        (c=='Ê') ||
        (c=='Î') ||
        (c=='Ô') ||
        (c=='Û') ||
        (c=='Ä') ||
        (c=='Ë') ||
        (c=='Ï') ||
        (c=='Ö') ||
        (c=='Ü') ||
        (c=='Ç') ||
	(c=='Á') ||
	(c=='À') ||
	(c=='Â') ||
	(c=='Å') ||
	(c=='Ä') ||
	(c=='Ã') ||
	(c=='Æ') ||
	(c=='Ç') ||
	(c=='É') ||
	(c=='È') ||
	(c=='Ê') ||
	(c=='Í') ||
	(c=='Î') ||
	(c=='Ï') ||
	(c=='Ñ') ||
	(c=='Ó') ||
	(c=='Ò') ||
	(c=='Ô') ||
	(c=='Ö') ||
	(c=='Õ') ||
	(c=='Ø') ||
	(c=='Ú') ||
	(c=='Û') ||
	(c=='Ü') ||
	(c=='é') ||
	(c=='à') ||
	(c=='è') ||
	(c=='ù') ||
	(c=='â') ||
	(c=='ê') ||
	(c=='î') ||
	(c=='ô') ||
	(c=='û') ||
	(c=='ä') ||
	(c=='ë') ||
	(c=='ï') ||
	(c=='ö') ||
	(c=='ü') ||
	(c=='ç')
   ) return True;
return False;
}

char decapital(char c)
{
if ((c>='A')&&(c<='Z')) return (c+('a'-'A'));
if (c=='É') return 'é';
if (c=='À') return 'à';
if (c=='È') return 'è';
if (c=='Ù') return 'ù';
if (c=='Â') return 'â';
if (c=='Ê') return 'ê';
if (c=='Î') return 'î';
if (c=='Ô') return 'ô';
if (c=='Û') return 'û';
if (c=='Ä') return 'ä';
if (c=='Ë') return 'ë';
if (c=='Ï') return 'ï';
if (c=='Ö') return 'ö';
if (c=='Ü') return 'ü';
if (c=='Ç') return 'ç';
if (c=='Á') return 'a';
if (c=='Â') return 'â';
if (c=='Å') return 'a';
if (c=='Ä') return 'ä';
if (c=='Ã') return 'a';
if (c=='Æ') return 'a';
if (c=='Í') return 'i';
if (c=='Î') return 'î';
if (c=='Ï') return 'ï';
if (c=='Ñ') return 'n';
if (c=='Ó') return 'o';
if (c=='Ò') return 'ò';
if (c=='Ô') return 'ô';
if (c=='Ö') return 'ö';
if (c=='Õ') return 'o';
if (c=='Ø') return 'o';
if (c=='Ú') return 'u';
if (c=='Û') return 'û';
if (c=='Ü') return 'ü';
return c;
}

char recapital(char c)
{
if ((c>='a')&&(c<='z')) return (c+('A'-'a'));
if (c=='é') return 'É';
if (c=='à') return 'À';
if (c=='è') return 'È';
if (c=='ù') return 'Ù';
if (c=='â') return 'Â';
if (c=='ê') return 'Ê';
if (c=='î') return 'Î';
if (c=='ô') return 'Ô';
if (c=='û') return 'Û';
if (c=='ä') return 'Ä';
if (c=='ë') return 'Ë';
if (c=='ï') return 'Ï';
if (c=='ö') return 'Ö';
if (c=='ü') return 'Ü';
if (c=='ç') return 'Ç';
return c;
}

char desaccentue(char c)
{
if (c=='É') return 'E';
if (c=='À') return 'A';
if (c=='È') return 'E';
if (c=='Ù') return 'U';
if (c=='Â') return 'A';
if (c=='Ê') return 'E';
if (c=='Î') return 'I';
if (c=='Ô') return 'O';
if (c=='Û') return 'U';
if (c=='Ä') return 'A';
if (c=='Ë') return 'E';
if (c=='Ï') return 'I';
if (c=='Ö') return 'O';
if (c=='Ü') return 'U';
if (c=='Ç') return 'C';
if (c=='é') return 'e';
if (c=='à') return 'a';
if (c=='è') return 'e';
if (c=='ù') return 'u';
if (c=='â') return 'a';
if (c=='ê') return 'e';
if (c=='î') return 'i';
if (c=='ô') return 'o';
if (c=='û') return 'u';
if (c=='ä') return 'a';
if (c=='ë') return 'e';
if (c=='ï') return 'i';
if (c=='ö') return 'o';
if (c=='ü') return 'u';
if (c=='ç') return 'c';
if (c=='á') return 'a';
if (c=='Á') return 'A';
if (c=='à') return 'a';
if (c=='À') return 'A';
if (c=='â') return 'a';
if (c=='Â') return 'A';
if (c=='å') return 'a';
if (c=='Å') return 'A';
if (c=='ä') return 'a';
if (c=='Ä') return 'A';
if (c=='ã') return 'a';
if (c=='Ã') return 'A';
if (c=='æ') return 'a';
if (c=='Æ') return 'A';
if (c=='ç') return 'c';
if (c=='Ç') return 'C';
if (c=='ð') return 'd';
if (c=='é') return 'e';
if (c=='É') return 'E';
if (c=='è') return 'e';
if (c=='È') return 'E';
if (c=='ê') return 'e';
if (c=='Ê') return 'E';
if (c=='ë') return 'e';
if (c=='í') return 'i';
if (c=='Í') return 'I';
if (c=='ì') return 'i';
if (c=='î') return 'i';
if (c=='Î') return 'I';
if (c=='ï') return 'i';
if (c=='Ï') return 'I';
if (c=='ñ') return 'n';
if (c=='Ñ') return 'N';
if (c=='ó') return 'o';
if (c=='Ó') return 'o';
if (c=='ò') return 'o';
if (c=='Ò') return 'O';
if (c=='ô') return 'o';
if (c=='Ô') return 'O';
if (c=='ö') return 'o';
if (c=='Ö') return 'O';
if (c=='õ') return 'o';
if (c=='Õ') return 'O';
if (c=='ø') return 'o';
if (c=='Ø') return 'O';
if (c=='ú') return 'u';
if (c=='Ú') return 'U';
if (c=='ù') return 'u';
if (c=='û') return 'u';
if (c=='Û') return 'U';
if (c=='ü') return 'u';
if (c=='Ü') return 'U';
if (c=='ý') return 'y';
if (c=='ÿ') return 'y';
return c;
}

char *decapital_string(char *pt)
{
int i;
for(i=0;pt[i];i++) pt[i]=decapital(pt[i]);
return pt;
}

int strange_inside(char *ch)
{
int i;
for (i=0;ch[i];i++)
 {
 if ((!if_lettre(ch[i]))&&(ch[i]!='-')&&(ch[i]!='_')&&(ch[i]!='\'')&&(ch[i]!=' ')&&(ch[i]!='.'))
  {
  if (ch[i+1]) return True;
  }
 }
return False;
}

int just_capital(char *ch)
{
int i;
for (i=0;ch[i];i++)
 {
 if ((if_lettre(ch[i]))&&(!if_capital(ch[i]))) return False;
 }
return True;
}

int no_capital(char *ch)
{
int i;
for (i=0;ch[i];i++)
 {
 if ((if_lettre(ch[i]))&&(if_capital(ch[i]))) return False;
 }
return True;
}

int include_a2(char *ch)
{
int i;
for (i=0;ch[i];i++)
 {
 if ((ch[i]=='à')&&((i==0)||(ch[i-1]==' '))&&((ch[i+1]==' ')||(ch[i+1]=='\0'))) return True;
 }
return False;
}

int include_sequence_capital(char *ch)
{
static char chtmp[TailleLigne],*pt;
int i,ifroman;
strcpy(chtmp,ch);
for(pt=strtok(chtmp," -");pt;pt=strtok(NULL," -"))
 {
 for(ifroman=True,i=0;(pt[i])&&(if_capital(pt[i]));i++)
  {
  if ((pt[i]!='I')&&(pt[i]!='V')&&(pt[i]!='X')) ifroman=False;
  }
 if ((!pt[i])&&(!ifroman)) return True;
 }
return False;
}

void copy_lite(char *dest, char *source)
{
int i,j;

for(i=j=0;source[i];i++) if (if_lettre(source[i])) dest[j++]=desaccentue(decapital(source[i]));
dest[j]='\0';
if (0) printf("[%s] => [%s]\n",source,dest);
}

/*................................................................*/
/*................................................................*/
 
