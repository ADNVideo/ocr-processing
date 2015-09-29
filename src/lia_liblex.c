/*  Managing a lexicon with IDs  */
/*  last modif: FRED 0109 add 'new_lexicon' and 'add_word'  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

/*................................................................*/

#define False	0
#define True	1

#define TailleLigne	4000

#define LIA_MAX_TAILLE_MESSAGE	4000
#define VERBOSE	0

int LIA_AVL_NB_NODE;

void XXERREUR(char *ch1,char *ch2)
{
	fprintf(stderr,"XXERREUR : %s %s\n",ch1,ch2);
	exit(0);
}

/*................................................................*/


typedef struct
    {
    char *key_string;
	int code;
    } type_info;

type_info *new_type_info(char *key, int code)
{
type_info *pt;
pt=(type_info *)malloc(sizeof(type_info));
if (key) pt->key_string=strdup(key); else pt->key_string=NULL;
pt->code=code;
return pt;
}

void free_type_info(type_info *pt)
{
if (pt)
 {
 if (pt->key_string) free(pt->key_string);
 free(pt);
 }
}

void print_type_info(type_info* info, FILE *file)
{
fprintf(file,"%s\t%d\n",info->key_string,info->code);
}
 
/*................................................................*/

/* declaration du type noeud des arbres AVL */

typedef struct lia_avl_type
	{
	signed char dq;
	type_info *info;
	struct lia_avl_type *fg,*fd;
	} *lia_avl_t;

/*................................................................*/

/* les rotations */

/* parametres :
	1- lia_avl_t = racine de l'arbre */
/* retour : True=rotation effectuee / False=rotation impossible */
int lia_rotation_avl_droite(lia_avl_t);
int lia_rotation_avl_gauche(lia_avl_t);
int lia_rotation_avl_gauche_droite(lia_avl_t);
int lia_rotation_avl_droite_gauche(lia_avl_t);

/*................................................................*/

/* l'insertion d'un element */

/* parametres :
	1- lia_avl_t = racine de l'arbre
	2- char * = info a ajouter a l'arbre
	3- int = booleen (True ou False) avec True=ajout avec reequilibrage
	4- char * = chaine de caractere recevant la trace de l'ajout */
/* retour : lia_avl_t = racine de l'arbre modifie */
lia_avl_t lia_ajoute_element_avl(lia_avl_t, type_info *, int, char *);

/*................................................................*/

/* la liberation de la place memoire de l'arbre */

/* parametres :
	1- lia_avl_t = racine de l'arbre */
void lia_libere_avl(lia_avl_t);

/*................................................................*/

/* la recherche d'un element */

/* parametres :
	1- lia_avl_t = racine de l'arbre
	2- char * = info a rechercher dans l'arbre
	3- int * = nb d'occurence de la chaine */
/* retour : the node containing the info or NULL */
lia_avl_t lia_recherche_avl(lia_avl_t, type_info *);

/*................................................................*/

/* l'affichage de l'arbre */

/* parametres :
	1- lia_avl_t = racine de l'arbre a afficher */
void lia_affiche_avl(lia_avl_t);

void lia_affiche_avl_simple(lia_avl_t ,FILE *);
 
/*................................................................*/

/* copy all the nodes of a tree into an array and sort them
 * according to their frequency */

/* parameters:
 *  1- lia_avl_t = root of the tree to copy
 *  2- int * = return value containing the size of the array */
/* return : the adress of the table containing all the nodes sorted */

lia_avl_t *lia_avl_tree2table_freq(lia_avl_t , int *);

/*................................................................*/

/* binary search, according to the code (or freq) on the table of nodes:
 *  1- lia_avl_t = adress of the node table (obtained with lia_avl_tree2table_freq)
 *  2- int = size of the table (# of elements)
 *  3- int = code or freq looked for  */
lia_avl_t lia_avl_code2word(lia_avl_t *, int, int);

/*................................................................*/

/*  Info  */
/*
typedef struct
	{
    char *key_string,*field;
	} type_info;
*/

int compare_info(type_info *pt1, type_info *pt2)
{
return strcmp(pt1->key_string,pt2->key_string);
}

/*................................................................*/

/* les rotations */

int lia_rotation_avl_droite(lia_avl_t pt)
{
lia_avl_t tmpfgfd,tmpfd;
type_info *tmpinfo;
char tmpdq;

if ((pt==NULL)||(pt->fg==NULL)) return False; /* la rotation n'est pas definie */

/*  On echange pt et fg  */
tmpinfo=pt->info;
tmpdq=pt->dq;
pt->info=pt->fg->info;
pt->dq=pt->fg->dq;
pt->fg->info=tmpinfo;
pt->fg->dq=tmpdq;

tmpfgfd=pt->fg->fd;
tmpfd=pt->fd;

pt->fd=pt->fg;
pt->fg=pt->fg->fg;
pt->fd->fg=tmpfgfd;
pt->fd->fd=tmpfd;

return True;
}

int lia_rotation_avl_gauche(lia_avl_t pt)
{
lia_avl_t tmpfdfg,tmpfg;
type_info *tmpinfo;
char tmpdq;

if ((pt==NULL)||(pt->fd==NULL)) return False; /* la rotation n'est pas definie */

/*  On echange pt et fd  */
tmpinfo=pt->info;
tmpdq=pt->dq;
pt->info=pt->fd->info;
pt->dq=pt->fd->dq;
pt->fd->info=tmpinfo;
pt->fd->dq=tmpdq;

tmpfdfg=pt->fd->fg;
tmpfg=pt->fg;

pt->fg=pt->fd;
pt->fd=pt->fd->fd;
pt->fg->fd=tmpfdfg;
pt->fg->fg=tmpfg;

return True;
}

int lia_rotation_avl_gauche_droite(lia_avl_t pt)
{
return ((lia_rotation_avl_gauche(pt->fg))&&(lia_rotation_avl_droite(pt)))?True:False;
}

int lia_rotation_avl_droite_gauche(lia_avl_t pt)
{
return ((lia_rotation_avl_droite(pt->fd))&&(lia_rotation_avl_gauche(pt)))?True:False;
}

/*................................................................*/

/* la creation d'un noeud */

lia_avl_t new_tree_mot_node(type_info *info)
{
lia_avl_t pt;
pt=(lia_avl_t)malloc(sizeof(struct lia_avl_type));
pt->dq=0;
pt->info=info;
pt->fg=pt->fd=NULL;
LIA_AVL_NB_NODE++;
return pt;
}

/*................................................................*/

/* reequilibrage */

int lia_reequilibre_droite(lia_avl_t racine,char *mesg,char *si_modif) /* racine->dq=+2 */
{
char *r_noeud;

if (racine==NULL)
 { if (VERBOSE) sprintf(mesg,"XXERREUR : rotation impossible : racine==NULL"); return False; }

if (racine->fg==NULL)
 {  if (VERBOSE) sprintf(mesg,"XXERREUR : rotation droite impossible : [%s]->fg==NULL",racine->info->key_string); return False; }

r_noeud=racine->info->key_string;

*si_modif=racine->fg->dq==0?0:1;

if (racine->fg->dq>=0) /* 0 ou +1 */
 {
 if (lia_rotation_avl_droite(racine))
  {
  if (VERBOSE) sprintf(mesg+strlen(mesg)," rotation droite sur le noeud [%s]",r_noeud);
  if (racine->dq==1) racine->dq=racine->fd->dq=0; else { racine->dq=-1; racine->fd->dq=1; }
  return True;
  }
 else
  if (VERBOSE) sprintf(mesg,"XXERREUR : rotation droite impossible sur le noeud [%s]",racine->info->key_string);
 }
else
 {
 if (lia_rotation_avl_gauche_droite(racine))
  {
  if (VERBOSE) sprintf(mesg+strlen(mesg)," rotation gauche-droite sur le noeud [%s]",r_noeud);
  switch (racine->dq)
   {
   case  1 : racine->fg->dq=0; racine->fd->dq=-1; break;
   case -1 : racine->fg->dq=1; racine->fd->dq= 0; break;
   case  0 : racine->fg->dq=racine->fd->dq=0; break;
   }
  racine->dq=0;
  return True;
  }
 else
  if (VERBOSE) sprintf(mesg,"XXERREUR : gauche-droite impossible sur le noeud [%s]",racine->info->key_string);
 }
return False;
}

int lia_reequilibre_gauche(lia_avl_t racine,char *mesg,char *si_modif) /* racine->dq=-2 */
{
char *r_noeud;

if (racine==NULL)
 { if (VERBOSE) sprintf(mesg,"XXERREUR : rotation impossible : racine==NULL"); return False; }

if (racine->fd==NULL)
 {  if (VERBOSE) sprintf(mesg,"XXERREUR : rotation gauche impossible : [%s]->fd==NULL",racine->info->key_string); return False; }

r_noeud=racine->info->key_string;

*si_modif=racine->fd->dq==0?0:1;

if (racine->fd->dq<1) /* -1 ou 0 */
 {
 if (lia_rotation_avl_gauche(racine))
  {
  if (VERBOSE) sprintf(mesg+strlen(mesg)," rotation gauche sur le noeud [%s]",r_noeud);
  if (racine->dq==-1) racine->dq=racine->fg->dq=0; else { racine->dq=1; racine->fg->dq=-1; }
  return True;
  }
 else
  if (VERBOSE) sprintf(mesg,"XXERREUR : rotation gauche impossible sur le noeud [%s]",racine->info->key_string);
 }
else
 {
 if (lia_rotation_avl_droite_gauche(racine))
  {
  if (VERBOSE) sprintf(mesg+strlen(mesg)," rotation droite-gauche sur le noeud [%s]",r_noeud);
  switch (racine->dq)
   {
   case  1 : racine->fd->dq=-1; racine->fg->dq= 0; break;
   case -1 : racine->fd->dq= 0; racine->fg->dq= 1; break;
   case  0 : racine->fg->dq=racine->fd->dq=0; break;
   }
  racine->dq=0;
  return True;
  }
 else
  if (VERBOSE) sprintf(mesg,"XXERREUR : droite-gauche impossible sur le noeud [%s]",racine->info->key_string);
 }
return False;
}

/*................................................................*/

/* l'insertion d'un element */

lia_avl_t lia_insere_avl(lia_avl_t racine, type_info *info, char *si_augm,int avec_reequilibrage,char *mesg)
{
int comp;

if (racine==NULL) { *si_augm=1; return new_tree_mot_node(info); }

comp=compare_info(racine->info,info);

if (comp==0)
 {
 /* message -> le noeud est deja dans l'arbre */
 if (VERBOSE) sprintf(mesg,"noeud [%s] deja present",info->key_string);
 *si_augm=0;
 }
else
 if (comp>0)
  { /* sur le fils gauche */
  racine->fg=lia_insere_avl(racine->fg,info,si_augm,avec_reequilibrage,mesg);
  if (*si_augm)
   {
   if (racine->dq<0) *si_augm=0;
   racine->dq++;
   }
  /* eventuelle rotation */
  if ((avec_reequilibrage)&&(racine->dq==2))
   { lia_reequilibre_droite(racine,mesg,si_augm); *si_augm=0; }
  }
 else
  { /* sur le fils droit */
  racine->fd=lia_insere_avl(racine->fd,info,si_augm,avec_reequilibrage,mesg);
  if (*si_augm)
   {
   if (racine->dq>0) *si_augm=0;
   racine->dq--;
   }
  /* eventuelle rotation */
  if ((avec_reequilibrage)&&(racine->dq==-2))
   { lia_reequilibre_gauche(racine,mesg,si_augm); *si_augm=0; }
  }
return racine;
}

lia_avl_t lia_ajoute_element_avl(lia_avl_t racine, type_info *info, int avec_reequilibrage, char *mesg)
{
char si_augm;
if (VERBOSE) mesg[0]='\0';
return lia_insere_avl(racine,info,&si_augm,avec_reequilibrage,mesg);
}

/*................................................................*/

/* la liberation de la place memoire de l'arbre */

void lia_libere_avl(lia_avl_t racine)
{
if (racine)
 {
 lia_libere_avl(racine->fg);
 lia_libere_avl(racine->fd);
 free_type_info(racine->info);
 free(racine);
 }
}

/*................................................................*/

/* la recherche d'un element */

lia_avl_t lia_recherche_avl(lia_avl_t racine, type_info *info)
{
int comp;
if (racine==NULL) return NULL;
if ((comp=compare_info(racine->info,info))==0) return racine;
if (comp>0)  return lia_recherche_avl(racine->fg,info);
else         return lia_recherche_avl(racine->fd,info);
}

/*................................................................*/

/* l'affichage de l'arbre */

void lia_affiche_avl_simple(lia_avl_t racine,FILE *file)
{
if (racine)
 {
 lia_affiche_avl_simple(racine->fg,file);
 print_type_info(racine->info,file);
 lia_affiche_avl_simple(racine->fd,file);
 }

}
  
/*................................................................*/

/* copy all the nodes of a tree into an array and sort them
 * according to their frequency */

int compare_freq(const void *a, const void *b)
{
lia_avl_t *c,*d;
c=(lia_avl_t *)a;
d=(lia_avl_t *)b;
return ((*d)->info->code-(*c)->info->code);
}

void copy_tree2table(lia_avl_t racine, lia_avl_t *tabl, int *i)
{
if (racine!=NULL)
 {
 tabl[(*i)++]=racine;
 copy_tree2table(racine->fg,tabl,i);
 copy_tree2table(racine->fd,tabl,i);
 }
}

int lia_avl_size(lia_avl_t racine)
{
if (racine==NULL) return 0;
else return 1 + lia_avl_size(racine->fg) + lia_avl_size(racine->fd);
}

lia_avl_t *lia_avl_tree2table_freq(lia_avl_t racine, int *nb)
{
lia_avl_t *tabl;
int i;
*nb=lia_avl_size(racine);
tabl=(lia_avl_t *)malloc(sizeof(lia_avl_t)*(*nb));
i=0;
copy_tree2table(racine,tabl,&i);
qsort(tabl,*nb,sizeof(lia_avl_t),compare_freq);
return tabl;
}

lia_avl_t lia_avl_code2word(lia_avl_t *tabl, int nb, int code)
{
struct lia_avl_type tkey;
lia_avl_t *resu,key;
type_info info;
info.code=code;
tkey.info=&info;
key=(lia_avl_t)(&tkey);
resu=bsearch(&key,tabl,nb,sizeof(lia_avl_t),compare_freq);
return *resu;
}

/*................................................................*/

/* managing lexicon */

#define MAX_LEXICON_AVL	100

lia_avl_t T_avl_lexicon[MAX_LEXICON_AVL];
lia_avl_t *T_tabl_avl_lexicon[MAX_LEXICON_AVL];
int T_tabl_avl_lexicon_size[MAX_LEXICON_AVL];
int Nb_Avl_Lexicon=0;

int load_lexicon(char *filename)
{
FILE *file;
static char ch[TailleLigne],*pt;
int code;

if (Nb_Avl_Lexicon==MAX_LEXICON_AVL) XXERREUR("cste 'MAX_LEXICON_AVL' too small","");
if (!(file=fopen(filename,"rt"))) XXERREUR("can't open:",filename);
for (code=0,T_avl_lexicon[Nb_Avl_Lexicon]=NULL;fgets(ch,TailleLigne,file);)
 {
 pt=strtok(ch," \t\n"); if (pt) pt=strtok(NULL," \t\n");
 if ((pt)&&(sscanf(pt,"%d",&code)!=1)) XXERREUR("bad format in:",pt);
 if (!pt) code++;
 T_avl_lexicon[Nb_Avl_Lexicon]=lia_ajoute_element_avl(T_avl_lexicon[Nb_Avl_Lexicon],new_type_info(ch,code),True,NULL);
 }
T_tabl_avl_lexicon[Nb_Avl_Lexicon]=lia_avl_tree2table_freq(T_avl_lexicon[Nb_Avl_Lexicon],
		&(T_tabl_avl_lexicon_size[Nb_Avl_Lexicon]));
fclose(file);
return Nb_Avl_Lexicon++;
}

int new_lexicon()
{
if (Nb_Avl_Lexicon==MAX_LEXICON_AVL) XXERREUR("cste 'MAX_LEXICON_AVL' too small","");
T_avl_lexicon[Nb_Avl_Lexicon]=NULL;
T_tabl_avl_lexicon[Nb_Avl_Lexicon]=NULL;
return Nb_Avl_Lexicon++;
}

int add_word_lexicon(int lexid, char *word, int code)
{
T_avl_lexicon[lexid]=lia_ajoute_element_avl(T_avl_lexicon[lexid],new_type_info(word,code),True,NULL);
return True;
}

void lexicon_sort_code(int lexid)
{
if (T_tabl_avl_lexicon[lexid]) free(T_tabl_avl_lexicon[lexid]);
T_tabl_avl_lexicon[lexid]=lia_avl_tree2table_freq(T_avl_lexicon[lexid],&(T_tabl_avl_lexicon_size[lexid]));
}

void print_lexicon_sort_code(int lexid, FILE *file)
{
int i;
if (T_tabl_avl_lexicon[lexid]) free(T_tabl_avl_lexicon[lexid]);
T_tabl_avl_lexicon[lexid]=lia_avl_tree2table_freq(T_avl_lexicon[lexid],&(T_tabl_avl_lexicon_size[lexid]));
for(i=T_tabl_avl_lexicon_size[lexid]-1;i>=0;i--) print_type_info(T_tabl_avl_lexicon[lexid][i]->info,file);
}

void delete_lexicon(int lexid)
{
if (T_avl_lexicon[lexid]) lia_libere_avl(T_avl_lexicon[lexid]);
if (T_tabl_avl_lexicon[lexid]) free(T_tabl_avl_lexicon[lexid]);
T_avl_lexicon[lexid]=NULL;
T_tabl_avl_lexicon[lexid]=NULL;
}

/*................................................................*/

int code2word(int lexid, int code, char **word)
{
lia_avl_t resu;
if (code<0) return False;
resu=lia_avl_code2word(T_tabl_avl_lexicon[lexid],T_tabl_avl_lexicon_size[lexid],code);
if (resu) *word=resu->info->key_string;
return resu?True:False;
}

void fprint_code_list_word(FILE *file, int lexid, int code)
{
int i,dejaone;
struct lia_avl_type tkey;
lia_avl_t *resu,key;
type_info info;

if (code<0) return;
info.code=code;
tkey.info=&info;
key=(lia_avl_t)(&tkey);
resu=bsearch(&key,T_tabl_avl_lexicon[lexid],T_tabl_avl_lexicon_size[lexid],sizeof(lia_avl_t),compare_freq);
if (!resu) return ;
for(dejaone=False,i=0;(resu-i>=(T_tabl_avl_lexicon[lexid]))&&((*(resu-i))->info->code==code);i++)
 {
 if (dejaone) fprintf(file," "); else dejaone=True;
 fprintf(file,"%s",(*(resu-i))->info->key_string);
 }
for(i=1;(resu+i<((T_tabl_avl_lexicon[lexid])+T_tabl_avl_lexicon_size[lexid]))&&((*(resu+i))->info->code==code);i++)
 {
 if (dejaone) fprintf(file," "); else dejaone=True;
 fprintf(file,"%s",(*(resu+i))->info->key_string);
 }
}

void sprint_code_list_word(char *buffer, int lexid, int code)
{
int i,dejaone;
struct lia_avl_type tkey;
lia_avl_t *resu,key;
type_info info;

buffer[0]='\0';

if (code<0) return;
info.code=code;
tkey.info=&info;
key=(lia_avl_t)(&tkey);
resu=bsearch(&key,T_tabl_avl_lexicon[lexid],T_tabl_avl_lexicon_size[lexid],sizeof(lia_avl_t),compare_freq);
if (!resu) return ;
for(dejaone=False,i=0;(resu-i>=(T_tabl_avl_lexicon[lexid]))&&((*(resu-i))->info->code==code);i++)
 {
 if (dejaone) sprintf(buffer+strlen(buffer)," "); else dejaone=True;
 sprintf(buffer+strlen(buffer),"%s",(*(resu-i))->info->key_string);
 }
for(i=1;(resu+i<((T_tabl_avl_lexicon[lexid])+T_tabl_avl_lexicon_size[lexid]))&&((*(resu+i))->info->code==code);i++)
 {
 if (dejaone) sprintf(buffer+strlen(buffer)," "); else dejaone=True;
 sprintf(buffer+strlen(buffer),"%s",(*(resu+i))->info->key_string);
 }
}

int word2code(int lexid, char *word, int *code)
{
lia_avl_t resu;
type_info info;
info.key_string=word;
resu=lia_recherche_avl(T_avl_lexicon[lexid],&info);
if ((resu)&&(code)) *code=resu->info->code;
return resu?True:False;
}

int size_lexicon(int lexid)
{
return T_tabl_avl_lexicon_size[lexid];
}

