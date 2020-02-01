#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000


//declaration des enum_____________________________________________________________
typedef enum{
	ID_TOKEN, PROGRAM_TOKEN ,NUM_TOKEN ,VAR_TOKEN, BEGIN_TOKEN, END_TOKEN, CONST_TOKEN,IF_TOKEN, THEN_TOKEN, WHILE_TOKEN, DO_TOKEN,
	PV_TOKEN, PT_TOKEN, PLUS_TOKEN, MOINS_TOKEN, MULTIPLE_TOKEN, DIV_TOKEN, EG_TOKEN, VIR_TOKEN, AFF_TOKEN, INF_TOKEN,
	INFEG_TOKEN, SUP_TOKEN, SUPEG_TOKEN, DIFF_TOKEN, PO_TOKEN, PF_TOKEN, ERR_TOKEN,  EOF_TOKEN, WRITE_TOKEN, READ_TOKEN 
}CODE_LEX;


typedef enum{
	ERR_CAR_INC,ERR_FICH_VIDE,ERR_ID_LONG, ERR_COMMENT, ERR_NOM_PROGRAMME, ERR_DOUBLE_DECLARATION, ERR_ID_NON_DECLAR, ERR_CONST_CHANGE_VAL
}Erreurs;

typedef enum {
	TPROG, TCONST, TVAR
}TSYM;



//declaration de tableau de string_____________________________________________________________
const char* tab_ERREURS[] = {"caractere inconnue","fichier vide ou nom du fichier incorrect","identifiant trop long","commentaire non fermer",
							"nom de programme non autorisé","double declaration d un identifiant", "identifiant non declare", "constante ne peut changer de valeur "};

const char* tab_CODE_LEX[] = {
	"ID_TOKEN", "PROGRAM_TOKEN" ,"NUM_TOKEN" ,"VAR_TOKEN", "BEGIN_TOKEN", "END_TOKEN", "CONST_TOKEN","IF_TOKEN", "THEN_TOKEN", "WHILE_TOKEN", "DO_TOKEN",
	"PV_TOKEN", "PT_TOKEN", "PLUS_TOKEN", "MOINS_TOKEN", "MULTIPLE_TOKEN", "DIV_TOKEN", "EG_TOKEN", "VIR_TOKEN","AFF_TOKEN", "INF_TOKEN",
	"INFEG_TOKEN", "SUP_TOKEN", "SUPEG_TOKEN", "DIFF_TOKEN", "PO_TOKEN", "PF_TOKEN", "ERR_TOKEN","EOF_TOKEN", "WRITE_TOKEN", "READ_TOKEN"
};

const char* tab_TSYM[] = {"TPROG", "TCONST", "TVAR"};


//declaration des structures_____________________________________________________________
typedef struct 
{
	CODE_LEX CODE;
	char NOM[20];	
}TSym_Cour;

typedef struct 
{
	Erreurs ERROR_;
	char textErreur[N];
}TErreurs_Cour;

typedef struct {
	char NOM[20];
	TSYM TIDF;
}T_TAB_IDF;



//Declaration des variables globales_____________________________________________________________
TSym_Cour Sym_Cour[N];
TErreurs_Cour Erreurs_Cour[N];
T_TAB_IDF TAB_IDFS[N];
int compteur_nom = 0,compteur_code=0,compteur_erreur=0, compteur_semantique = 0;


//fct lire_mot____________________________________________________________________________________
char* lire_mot(char* mot, char current_caractere,FILE * fichier)
{
	int compteur = 0;
	mot[0] = '\0';
	while( ('a' <= current_caractere && current_caractere <= 'z') || ('A' <= current_caractere && current_caractere <= 'Z') || ('1' <= current_caractere && current_caractere <= '9') )
	{
		mot[compteur++] = current_caractere;
		current_caractere = fgetc(fichier);
		if (compteur > 20)
		{
			return "erreur404";
		}
	}
	mot[compteur] = current_caractere;
	if (compteur <= 20)			{mot[compteur+1] = '\0';}
	return mot;	
}


//fct lire_chiffre____________________________________________________________________________________
char* lire_chiffre(char* mot, char current_caractere,FILE * fichier)
{
	int compteur = 0;
	mot[0] = '\0';
	while( ('0' <= current_caractere && current_caractere <= '9')  )
	{
		mot[compteur++] = current_caractere;
		current_caractere = fgetc(fichier);
		if ('A' <= current_caractere && current_caractere<= 'Z' || 'a' <= current_caractere && current_caractere <= 'z')
		{
			return "erreur404";
		}
	}
	mot[compteur] = current_caractere;
	if (compteur <= 20)			{mot[compteur+1] = '\0';}
	return mot;
}





//fct pricipale____________________________________________________________________________________
int Sym_Suiv(char* file_path){
	int compteur_declaration_variable = 0, flag_program = 0, flag_const = 0, flag_var = 0, flag_begin = 0, flag_doublon =0;
	char mot[20];
	char current_caractere;
	FILE * fichier = NULL;
	fichier = fopen(file_path,"r");
	current_caractere = fgetc(fichier) ;

	//*****************************************************************
	//Erreur fichier vide
	if (current_caractere == EOF){
		Erreurs_Cour[compteur_erreur].ERROR_ = ERR_FICH_VIDE;
		strcpy(Erreurs_Cour[compteur_erreur].textErreur,tab_ERREURS[ERR_FICH_VIDE]);
		return 1;
	}
	//*****************************************************************

	while (current_caractere != EOF){

		//lire_mot()//*****************************************************************
		if ( 'A' <= current_caractere && current_caractere<= 'Z' || 'a' <= current_caractere && current_caractere <= 'z' )
		{
			strcpy(mot,lire_mot(mot,current_caractere,fichier));

			//Erreur ID long
			if (strcmp("erreur404",mot) == 0)
			{
				Sym_Cour[compteur_code++].CODE = ERR_TOKEN;
				Erreurs_Cour[compteur_erreur].ERROR_ = ERR_ID_LONG;
				strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_ID_LONG]);
				do{
					current_caractere = fgetc(fichier) ;
				}while('A' <= current_caractere && current_caractere<= 'Z' || 'a' <= current_caractere && current_caractere <= 'z');
			}

			else
			{
				
				current_caractere = mot[strlen(mot)-1];
				mot[strlen(mot)-1] = '\0';
				
			
				//Test sur les identifiants_____________________________________________________________
				if (strcmp(mot,"program") == 0)     {Sym_Cour[compteur_code++].CODE = PROGRAM_TOKEN; flag_program = 1;}
				
				else if (strcmp(mot,"const") == 0)  {Sym_Cour[compteur_code++].CODE = CONST_TOKEN; flag_const = 1;}
				
				else if (strcmp(mot,"var") == 0)    {Sym_Cour[compteur_code++].CODE = VAR_TOKEN; flag_var = 1;}
				
				else if (strcmp(mot,"while") == 0)  {Sym_Cour[compteur_code++].CODE = WHILE_TOKEN;}
				
				else if (strcmp(mot,"begin") == 0)  {Sym_Cour[compteur_code++].CODE = BEGIN_TOKEN; flag_begin = 1;}
				
				else if (strcmp(mot,"end") == 0)	{Sym_Cour[compteur_code++].CODE = END_TOKEN;}
				
				else if (strcmp(mot,"if") == 0)		{Sym_Cour[compteur_code++].CODE = IF_TOKEN;}
				
				else if (strcmp(mot,"do") == 0)		{Sym_Cour[compteur_code++].CODE = DO_TOKEN;}
				
				else if (strcmp(mot,"then") == 0)	{Sym_Cour[compteur_code++].CODE = THEN_TOKEN;}

				else if (strcmp(mot,"write") == 0)	{Sym_Cour[compteur_code++].CODE = WRITE_TOKEN;}

				else if (strcmp(mot,"read") == 0)	{Sym_Cour[compteur_code++].CODE = READ_TOKEN;}
				
				//Ajout des contraintes sémantiques !!!
				else{

					Sym_Cour[compteur_code++].CODE = ID_TOKEN ;
					//Ne pas utiliser le nom du programme dans le code
					if (flag_program == 2)
					{
						if (strcmp(mot,TAB_IDFS[0].NOM) == 0)
						{
							Erreurs_Cour[compteur_erreur].ERROR_ = ERR_NOM_PROGRAMME;
							strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_NOM_PROGRAMME]);
						}
					}
					//Remplir la table des symboles avec PROGRAM ID
					if (flag_program == 1)
					{
						strcpy(TAB_IDFS[compteur_semantique].NOM,mot);
						TAB_IDFS[compteur_semantique++].TIDF = TPROG;
						flag_program = 2;
					}
					//Remplir la table des symboles avec CONST ID
					if ( flag_const == 1 && flag_var == 0 && flag_begin == 0 )
					{
						//Tester si il y a double declaration dans const
						for (int i = 0; i < compteur_semantique; ++i)
						{
							if (strcmp(TAB_IDFS[i].NOM,mot) == 0)
							{
								Erreurs_Cour[compteur_erreur].ERROR_ = ERR_DOUBLE_DECLARATION;
								strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_DOUBLE_DECLARATION]);
								flag_doublon = 1;
								break;
							}
						}
						if (flag_doublon == 0)
						{
							strcpy(TAB_IDFS[compteur_semantique].NOM,mot);
							TAB_IDFS[compteur_semantique++].TIDF = TCONST;
						}
						flag_doublon = 0;
					}
					//Remplir la table des symboles avec VAR ID
					if (flag_const == 1 && flag_var == 1 && flag_begin == 0)
					{
						//Tester si il y a double declaration par rapport a var ou const
						for (int i = 0; i < compteur_semantique; ++i)
						{
							if (strcmp(TAB_IDFS[i].NOM,mot) == 0)
							{
								Erreurs_Cour[compteur_erreur].ERROR_ = ERR_DOUBLE_DECLARATION;
								strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_DOUBLE_DECLARATION]);
								flag_doublon = 1;
								break;
							}
						}
						if (flag_doublon == 0)
						{
							strcpy(TAB_IDFS[compteur_semantique].NOM,mot);
							TAB_IDFS[compteur_semantique++].TIDF = TVAR;
						}
						flag_doublon = 0;
					}
					//Tester si les id sont declaré et les const ne doivent pas changer de valeur
					if (flag_const == 1 && flag_var == 1 && flag_begin == 1)
					{
						//Contrainte pour l identifiant non declaré
						for (compteur_declaration_variable = 0; compteur_declaration_variable < compteur_semantique; compteur_declaration_variable++)
						{
							if (strcmp(TAB_IDFS[compteur_declaration_variable].NOM,mot) == 0)
							{
								break;
							}
						}
						if (compteur_declaration_variable == compteur_semantique)
						{
							Erreurs_Cour[compteur_erreur].ERROR_ = ERR_ID_NON_DECLAR;
							strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_ID_NON_DECLAR]);
						}

						//Contraine pour le changement de valeur d une constante
						for (int i = 0; i < compteur_semantique; ++i)
						{
							if (strcmp(TAB_IDFS[i].NOM,mot) == 0 && TAB_IDFS[i].TIDF == TCONST)
							{
								if (current_caractere == ' '){ current_caractere = fgetc(fichier) ;}
								if (current_caractere == ':')
								{
									Erreurs_Cour[compteur_erreur].ERROR_ = ERR_CONST_CHANGE_VAL;
									strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_CONST_CHANGE_VAL]);	
								}
							}
						}
					}
				}
				//_____________________________________________________________
				//Ajout de l identifiant quelsoit sa nature
				strcpy(Sym_Cour[compteur_nom++].NOM,mot);
				mot[0] = '\0';
			}
		}
		////*****************************************************************



		//lire_nombre()//*****************************************************************
		if ( '1' <= current_caractere && current_caractere <= '9' )
		{
			strcpy(mot,lire_chiffre(mot,current_caractere,fichier));
			if (strcmp("erreur404",mot) == 0)
			{
				Sym_Cour[compteur_code++].CODE = ERR_TOKEN;
				Erreurs_Cour[compteur_erreur].ERROR_ = ERR_CAR_INC;
				strcpy(Erreurs_Cour[compteur_erreur++].textErreur,tab_ERREURS[ERR_CAR_INC]);
				do{
					current_caractere = fgetc(fichier) ;
				}while('A' <= current_caractere && current_caractere<= 'Z' || 'a' <= current_caractere && current_caractere <= 'z');
			}
			else
			{
				current_caractere = mot[strlen(mot)-1];
				mot[strlen(mot)-1] = '\0';
				strcpy(Sym_Cour[compteur_nom++].NOM,mot);
				Sym_Cour[compteur_code++].CODE = NUM_TOKEN ;
			}
		}
		//*****************************************************************


		//Sauter commentaire//*****************************************************************
		if ( current_caractere == '{')
		{
			do {
				current_caractere = fgetc(fichier) ;
				if (current_caractere == EOF)
				{
					break;
				}
			}while (current_caractere !='}' );
			//Erreur commentaire non fermé
			if ( current_caractere == EOF )
			{
				Erreurs_Cour[compteur_erreur].ERROR_ = ERR_COMMENT;
				strcpy(Erreurs_Cour[compteur_erreur].textErreur,tab_ERREURS[ERR_COMMENT]);
				return 1;
			} 
		}
		//*****************************************************************


		
		//Ne rien faire//*****************************************************************
		if ( current_caractere == ' ' || current_caractere == '\n' || current_caractere == '\t') 
		{ 
			current_caractere = fgetc(fichier) ;
			continue ;
		}
		//*****************************************************************



		//lire_caractere()//*****************************************************************
		switch (current_caractere)
		{
			case ';':		
							current_caractere = fgetc(fichier) ;    
							Sym_Cour[compteur_code++].CODE = PV_TOKEN;
							continue;
			
			case '=':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = EG_TOKEN ;
							continue;
			
			
			case '.':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = PT_TOKEN;
							continue;
			
			case '*':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = MULTIPLE_TOKEN;
							continue;
			
			
			case '+':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = PLUS_TOKEN;
							continue;
			
			
			case '(':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = PO_TOKEN;
							continue;
			

			case ')':
							current_caractere = fgetc(fichier) ;
							Sym_Cour[compteur_code++].CODE = PF_TOKEN;
							continue;
			

			case ':':
							current_caractere = fgetc(fichier) ;
							if (current_caractere =='=')		{current_caractere = fgetc(fichier) ;Sym_Cour[compteur_code++].CODE = AFF_TOKEN;}
							else								{Sym_Cour[compteur_code++].CODE = PV_TOKEN;}
							continue;
			

			case '<':
							current_caractere = fgetc(fichier) ;
							if (current_caractere =='=') 		{current_caractere = fgetc(fichier) ; Sym_Cour[compteur_code++].CODE = INFEG_TOKEN;}
							else if (current_caractere =='>')	{current_caractere = fgetc(fichier) ;  Sym_Cour[compteur_code++].CODE = DIFF_TOKEN;}
							else								{Sym_Cour[compteur_code++].CODE = INF_TOKEN;}
							continue;
			

			case '>':
							current_caractere = fgetc(fichier) ;
							if (current_caractere =='=') 		{current_caractere = fgetc(fichier) ; Sym_Cour[compteur_code++].CODE = SUPEG_TOKEN;}
							else						 		{Sym_Cour[compteur_code++].CODE = SUP_TOKEN;}
							continue;
			
			default :
							current_caractere = fgetc(fichier) ;
							continue; 
		}
		//*****************************************************************
	}

	fclose(fichier);
	Sym_Cour[compteur_code++].CODE = EOF_TOKEN;
	return 0;
}



int main(int argc, char const *argv[])
{
	system("clear");
	if ( Sym_Suiv("exemple1.p") == 0 ) //Entrer le nom du fichier dans la fct Sys_suiv
	{
		// CODE NUMERIQUES
		/*printf("\n_____________________LES CODES_____________________\n\n");
		for (int i = 0; i < compteur_code; ++i)
		{
			printf("%d \n",Sym_Cour[i].CODE);
		}*/

		// CODES ..._TOKEN
		printf("\n_____________________LES CODES_____________________\n\n");
		for (int i = 0; i < compteur_code; ++i)
		{
			printf("%s \n",tab_CODE_LEX[Sym_Cour[i].CODE] );
		}

		printf("\n_____________________LES MOTS_____________________\n\n");
		for (int i = 0; i < compteur_nom; ++i)
		{
			printf("NOM: %s \n",Sym_Cour[i].NOM );
		}
		printf("\n_____________________LA TABLE DES SYMBOLES_____________________\n\n");
		for (int i = 0; i < compteur_semantique; ++i)
		{
			printf("mot : %s , identifiant : %s\n",TAB_IDFS[i].NOM,tab_TSYM[TAB_IDFS[i].TIDF] );
		}
		if (compteur_erreur >=1)
		{
			printf("\n_____________________LES ERREURS_____________________\n\n");
			for (int i = 0; i <compteur_erreur; ++i)
			{
				printf("CODE: %d \n", Erreurs_Cour[i].ERROR_);
				printf("---> %s \n", Erreurs_Cour[i].textErreur);
			}
		}
	//Program break
	}
	else{
		printf("Fatal Error\n");
		printf("CODE: %d \n", Erreurs_Cour[0].ERROR_);
		printf("---> %s \n", Erreurs_Cour[0].textErreur);
	}
	

	
	return 0;
}