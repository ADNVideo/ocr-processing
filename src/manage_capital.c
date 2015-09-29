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
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�')
   ) return True;
return False;
}

int if_lettre(char c)
{
if ((c>='A')&&(c<='Z')) return True;
if ((c>='a')&&(c<='z')) return True;
if (
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
        (c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�') ||
	(c=='�')
   ) return True;
return False;
}

char decapital(char c)
{
if ((c>='A')&&(c<='Z')) return (c+('a'-'A'));
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return 'a';
if (c=='�') return '�';
if (c=='�') return 'a';
if (c=='�') return '�';
if (c=='�') return 'a';
if (c=='�') return 'a';
if (c=='�') return 'i';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return 'n';
if (c=='�') return 'o';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return 'o';
if (c=='�') return 'o';
if (c=='�') return 'u';
if (c=='�') return '�';
if (c=='�') return '�';
return c;
}

char recapital(char c)
{
if ((c>='a')&&(c<='z')) return (c+('A'-'a'));
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
if (c=='�') return '�';
return c;
}

char desaccentue(char c)
{
if (c=='�') return 'E';
if (c=='�') return 'A';
if (c=='�') return 'E';
if (c=='�') return 'U';
if (c=='�') return 'A';
if (c=='�') return 'E';
if (c=='�') return 'I';
if (c=='�') return 'O';
if (c=='�') return 'U';
if (c=='�') return 'A';
if (c=='�') return 'E';
if (c=='�') return 'I';
if (c=='�') return 'O';
if (c=='�') return 'U';
if (c=='�') return 'C';
if (c=='�') return 'e';
if (c=='�') return 'a';
if (c=='�') return 'e';
if (c=='�') return 'u';
if (c=='�') return 'a';
if (c=='�') return 'e';
if (c=='�') return 'i';
if (c=='�') return 'o';
if (c=='�') return 'u';
if (c=='�') return 'a';
if (c=='�') return 'e';
if (c=='�') return 'i';
if (c=='�') return 'o';
if (c=='�') return 'u';
if (c=='�') return 'c';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'a';
if (c=='�') return 'A';
if (c=='�') return 'c';
if (c=='�') return 'C';
if (c=='�') return 'd';
if (c=='�') return 'e';
if (c=='�') return 'E';
if (c=='�') return 'e';
if (c=='�') return 'E';
if (c=='�') return 'e';
if (c=='�') return 'E';
if (c=='�') return 'e';
if (c=='�') return 'i';
if (c=='�') return 'I';
if (c=='�') return 'i';
if (c=='�') return 'i';
if (c=='�') return 'I';
if (c=='�') return 'i';
if (c=='�') return 'I';
if (c=='�') return 'n';
if (c=='�') return 'N';
if (c=='�') return 'o';
if (c=='�') return 'o';
if (c=='�') return 'o';
if (c=='�') return 'O';
if (c=='�') return 'o';
if (c=='�') return 'O';
if (c=='�') return 'o';
if (c=='�') return 'O';
if (c=='�') return 'o';
if (c=='�') return 'O';
if (c=='�') return 'o';
if (c=='�') return 'O';
if (c=='�') return 'u';
if (c=='�') return 'U';
if (c=='�') return 'u';
if (c=='�') return 'u';
if (c=='�') return 'U';
if (c=='�') return 'u';
if (c=='�') return 'U';
if (c=='�') return 'y';
if (c=='�') return 'y';
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
 if ((ch[i]=='�')&&((i==0)||(ch[i-1]==' '))&&((ch[i+1]==' ')||(ch[i+1]=='\0'))) return True;
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
 
