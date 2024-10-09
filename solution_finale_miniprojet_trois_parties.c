#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h> //Cette librairie propose un ensemble de fonction de traitement de caractères
// *******************Les definitions utilisees dans le programme************************
#define MAX_Text_Size 500 //toute utilisation de MAX_Text_Size sera remplacée par 500 dans toute la suite du source
#define Empty_char ' '
// *******************Les structures utilisees dans le programme*****************************
typedef struct List *PList;
struct List
{
    char *mot;
    PList next;
};

typedef struct VecteurDePointeurs VP;
struct VecteurDePointeurs
{
    char car;
    PList head;
};
// *******************Les prototypes de fonctions utilisees dans le programme************************
int Menu(void);
int Sous_Menu(int);
float **Allocation_Matrice(int, int);
char **Allocation_MatriceC(int N, int M);
void Liberer_Matrice(float **, int);
void Affiche_Vecteur(float *, int);
void Affiche_Mat(float **, int, int);
void Affiche_MatC(char **, int, int);
void Saisi_Mat(float **, int, int);
void Add_Soust_Mat(char, float **, float **, int, int);
void Multi_Mat_Nbr(float **, float, float, float);
float **Produit_Matriciel(float **, float **, int, int, int);
float **Sous_Mat_Det(float **, int, int, int);
float Determinant(float **, int);
void Comatrice(float **, float **, int); 
float **Inverse_Matrice(float **, int);
void Transpose_Mat(float **, float **, int, int);
void Trie_Mat_Croissant(float **, int, int);
void Trie_Mat_Decroissant(float **, int, int);
void Max_Ligne(float **, int, int);
void Max_Colonne(float **, int, int);
void Extraction_Sous_Mat(float **, int, int, int, int);
int PlusGrandMot(const char *);
int NbrDesMots(const char *);
void TextToMat(const char *, char **, int, int);
void InitStruct(VP *);
PList CreerUnElm(const char *, PList);
void AjoutMot(VP *, const char *);
void afficherStructure(VP *);
void SupprimerMot(VP *, const char *);

//****************************** Fonction Praincipale *********************************
int main(void)
{
    int choixMenu, continuer = 1;
    float **matrice1, **matrice2;
    char s[MAX_Text_Size], mot[100];
    char **matrice3 = NULL;
    VP listVP[26];
    int N, M;
    s[0] = '\0';

    do
    {
        choixMenu = Menu();

        switch (choixMenu)
        {
        case 0:
            continuer = 0; // On quitte la boucle  do while
            break;

        case 11: // **************************La somme de deux matrices (Addition)***********************
        {
            printf("\n Donnez les dimensions des matrices:\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);
            matrice1 = Allocation_Matrice(N, M);
            matrice2 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La 1ere matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);
            printf("La 1ere Matrice est:\n\n");
            Affiche_Mat(matrice1, N, M);

            printf("\n Saisissez les valeurs de La 2eme matrice s'il vous plait':\n");
            Saisi_Mat(matrice2, N, M);
            printf("La 2eme Matrice est:\n\n");
            Affiche_Mat(matrice2, N, M);

            Add_Soust_Mat('+', matrice1, matrice2, N, M); // l'additon
            Affiche_Mat(matrice1, N, M);
            Liberer_Matrice(matrice1, N); // Liberer la memoire
            Liberer_Matrice(matrice2, N);
        }
        break;

        case 12: // ********************La difference de matrices (Soustraction)***********************
        {
            printf("\n Donnez les dimensions des matrices:\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);
            matrice2 = Allocation_Matrice(N, M);
            printf("\n Saisissez les valeurs de La 1ere matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);
            printf("La 1ere Matrice est:\n\n");
            Affiche_Mat(matrice1, N, M);
            printf("\n Saisissez les valeurs de La 2eme matrice s'il vous plait':\n");
            Saisi_Mat(matrice2, N, M);
            printf("La 2eme Matrice est:\n\n");
            Affiche_Mat(matrice2, N, M);

            Add_Soust_Mat('-', matrice1, matrice2, N, M); // soustraction
            Affiche_Mat(matrice1, N, M); //affichage de la matrice

            Liberer_Matrice(matrice1, N); //libérer
            Liberer_Matrice(matrice2, N);
        }
        break;

        case 13: // ***************************Multiplier une matrice par un nombre*************************
        {
            float nombre;

            printf("\n Donnez les dimensions de la matrice:\n");
            printf("Nombre de lignes:  ");
            scanf("%f", &N);
            printf("Nombre de colonnes:  ");
            scanf("%f", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);
            printf("Voici votre Matrice initiale:\n\n");
            Affiche_Mat(matrice1, N, M);

            printf("\n Donnez un nombre:   ");
            scanf("%f", &nombre);

            printf("\nLa Matrice multipliï¿½e par %f est:\n\n", nombre);
            Multi_Mat_Nbr(matrice1, nombre, N, M); //Appel fonction multiplication de matrice par nombre
            Affiche_Mat(matrice1, N, M);

            Liberer_Matrice(matrice1, N);
        }
        break;

        case 14: // **************************Produit matriciel****************************
        {
            int P; // => nombre de colonnes de la 2eme matrice
            float **matProduit;

            printf("\n Les dimensions de la 1ere matrice:\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La 1ere matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);
            printf("La 1ere Matrice est:\n\n");
            Affiche_Mat(matrice1, N, M);

            printf("\n Les dimensions de la 2eme matrice s'il vous plait, nbr de colonnes a saisir seulement':\n");
            printf("Nbr de lignes = %d (obligatoirement saisi)\n", M); //condition de calcul
            printf("Nombre de colonnes:  ");
            scanf("%d", &P);

            matrice2 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La 2eme matrice s'il vous plait':\n");
            Saisi_Mat(matrice2, M, P);
            printf("La 2eme Matrice est:\n\n");
            Affiche_Mat(matrice2, M, P);

            matProduit = Produit_Matriciel(matrice1, matrice2, N, M, P);

            printf("\nLe Produit matriciel est donc:\n\n");
            Affiche_Mat(matProduit, N, P);

            Liberer_Matrice(matrice1, N);
            Liberer_Matrice(matrice2, M);
            Liberer_Matrice(matProduit, N);
        }
        break;

        case 15: // ******************************Inverse d'une matrice******************************
        {
            printf("\n Donnez les dimensions de la matrice s'il vous plait' (carrï¿½e):\n");
            printf("Nombre de lignes == Nombre de colonnes : "); //elle doit obligatoirement etre carrée
            scanf("%d", &N);

            matrice1 = Allocation_Matrice(N, N);

            printf("\n Saisissez les valeurs de La matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, N);
            printf("voici votre Matrice initiale:\n\n");
            Affiche_Mat(matrice1, N, N);

            matrice1 = Inverse_Matrice(matrice1, N);
            //si la fonction n'a pas retourné NULL, alors notre matrice1 a été inversé, on affiche donc//
                   
            if (matrice1 != NULL)
            {
            	printf("la matrice inverse est donc:\n"); // affichage
                Affiche_Mat(matrice1, N, N);
                Liberer_Matrice(matrice1, N);
            }
        }
        break;

        case 21: // *********************Transposï¿½e d'une matrice****************************
        {
            printf("\n Donnez les dimensions de la matrice s'il vous plait':\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            //le nombre de colonnes devient le nombre de ligne
            matrice2 = Allocation_Matrice(M, N);
            matrice1 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);
            printf("Voici votre Matrice initiale:\n\n");
            Affiche_Mat(matrice1, N, M);

            Transpose_Mat(matrice1, matrice2, N, M);
            printf("\nLa matrice transposee est donc:\n\n");
            Affiche_Mat(matrice2, M, N);

            Liberer_Matrice(matrice1, N);
            Liberer_Matrice(matrice2, M);
        }
        break;

        case 22: //**************************Tri d'une matrice**********************************
        //le tri peut etre croissant comme il peut etre decroissant, on a traité les 2 cas, on a choisi la méthode de tri par selection
        {
            char choixOrdre;

            do
            {
                printf("Entrez s'il vous plait:\n D pour le trie Decroissant, Ou\n"
                       " C pour le tri Croissant (en majuscule s'il vous plait'):\n");
                scanf("%s", &choixOrdre);
                /*getchar() pour prendre le \n que laisse scanf() dans le stdin*/
                //getchar();
            } while (choixOrdre != 'D' && choixOrdre != 'C');

            printf("\n Donnez la dimension de votre matrice s'il vous plait':\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n veuillez saisir les valeurs de votre matrice:\n");
            Saisi_Mat(matrice1, N, M);
            printf("Voici votre Matrice non triée:\n\n");
            Affiche_Mat(matrice1, N, M);

            if (choixOrdre == 'D')
                Trie_Mat_Decroissant(matrice1, N, M);
            if (choixOrdre == 'C')
                Trie_Mat_Croissant(matrice1, N, M);
            printf("\nla matrice aprï¿½s le tri :\n");
            Affiche_Mat(matrice1, N, M);
            Liberer_Matrice(matrice1, N);
        }
        break;

        case 23: // ***********************Les ï¿½lements maximum des lignes "vecteur maxligne"**************************
        {
            printf("\n Donnez la dimension de votre matrice s'il vous plait':\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La matrice:\n");
            Saisi_Mat(matrice1, N, M);
            printf("Voici votre Matrice:\n\n");
            Affiche_Mat(matrice1, N, M);

            Max_Ligne(matrice1, N, M);

            Liberer_Matrice(matrice1, N);
        }
        break;

        case 24: // **********************Les ï¿½lements maximum des colonnes "vecteur maxcolonnes"********************************
        {
            printf("\n Donnez la dimension de votre matrice s'il vous plait':\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n veuillez saisir les valeurs de La matrice:\n");
            Saisi_Mat(matrice1, N, M);
            printf("Voici donc votre Matrice:\n\n");
            Affiche_Mat(matrice1, N, M);

            Max_Colonne(matrice1, N, M);

            Liberer_Matrice(matrice1, N);
        }
        break;

        case 25: //************************ Extraction de sous matrices*********************
        {
            int sMat_N, sMat_M;

            printf("\n Donnez la dimension de votre matrice s'il vous plait':\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &M);

            matrice1 = Allocation_Matrice(N, M);

            printf("\n Saisissez les valeurs de La matrice s'il vous plait':\n");
            Saisi_Mat(matrice1, N, M);

            printf("\n Donnez la dimension des sous matrices a extraire:\n");
            printf("Nombre de lignes:  ");
            scanf("%d", &sMat_N);
            printf("Nombre de colonnes:  ");
            scanf("%d", &sMat_M);

            printf("Voici donc votre Matrice initial:\n\n");
            Affiche_Mat(matrice1, N, M);

            printf("toutes les sous matrices possibles sont:\n\n");
            Extraction_Sous_Mat(matrice1, N, M, sMat_N, sMat_M);

            Liberer_Matrice(matrice1, N);
        }
        break;
        case 30: // *********************saisie du texte****************************
        {
            printf("Entrez le texte : ");
            // pour enlever la saut de la ligne
            getchar();
            scanf("%[^\n]s", s);
        }
        break;
        case 31: // *********************crï¿½ation de la matrice de mots****************************
        {
            printf("la crÃ©ation de la matrice pour ces mots : %s", s);
            N = NbrDesMots(s);
            M = PlusGrandMot(s) + 1;
            matrice3 = Allocation_MatriceC(N, M);
            TextToMat(s, matrice3, N, M);
        }
        break;
        case 32: // *********************Affichage de la matrice****************************
        {
            if (matrice3 != NULL)
                Affiche_MatC(matrice3, N, M);
            else
                printf("matrice pas encore creee\n");
        }
        break;
        case 33: // *********************crï¿½ation de la structure de listes****************************
        {
            if (matrice3 != NULL)
            {
                InitStruct(listVP);
                int i;
                for ( i = 0; i < N; i++)
                {
                    AjoutMot(listVP, matrice3[i]);
                }
            }
            else
                printf("matrice pas encore creee\n");
        }
        break;
        case 34: // *********************Affichage de la structure****************************
        {
            afficherStructure(listVP);
        }
        break;
        case 35: // *********************Ajout d'un mot****************************
        {
            printf("insÃ©rer le mot que vous voulez ajouter : ");
            getchar();
            scanf("%s", mot);
            AjoutMot(listVP, mot);
        }
        break;
        case 36: // *********************supression d'un mot****************************
        {
            printf("insÃ©rer le mot que vous voulez  supprimer : ");
            getchar();
            scanf("%s", mot);
            SupprimerMot(listVP, mot);
        }
        break;
        }
    } while (continuer);

    return 0;
}
int Menu(void)
{
    int choix;

    printf("\n*** MENU: ***\n 1.  Operations arithmetiques sur les matrices\n"
           " 2.  Autres operations sur les matrices \n 3.  autres operations \n 4.Quitter\n");

    do
    {
        printf("Choisissez 1 ou 2 ou 3 ou 4 :  ");
        scanf("%d", &choix);
    } while ((choix != 1) && (choix != 2) && (choix != 3) && (choix != 4));

    /* si le choix est 3 on quitte la fonction en retournant 0 */
    if (choix == 4)
        return 0;
    else
        return (Sous_Menu(choix));
}

// on crï¿½e un sous menu correspendant au choix du menu principale
int Sous_Menu(int choix)
{
    int sousChoix;

    /* si le choix est ï¿½gal a 1, on affiche le 1er sous menu */
    if (choix == 1)
    {
        printf("\n 1. Somme de deux matrices\n 2. Difference de deux matrices\n"
               " 3. Multiplication d'une matrice par un nombre\n"
               " 4. Produit de deux matrices\n 5. Inverse d'une matrice\n");

        // on fait un  controle de saisie
        do
        {
            printf("Choisissez un numero compris entre 1 et 5 du menu :  ");
            scanf("%d", &sousChoix);
        } while ((sousChoix != 1) && (sousChoix != 2) && (sousChoix != 3) && (sousChoix != 4) && (sousChoix != 5));

        switch (sousChoix)
        {
        case 1:
            return 11;
            break; /* Menu 1.1 */
        case 2:
            return 12;
            break; /* Menu 1.2 */
        case 3:
            return 13;
            break; /* Menu 1.3 */
        case 4:
            return 14;
            break; /* Menu 1.4 */
        case 5:
            return 15;
            break; /* Menu 1.5 */
        }
    }

    if (choix == 2)
    {
        printf("\n 1. Transposee d'une matrice\n "
               " 2. Tri d'une matrice\n 3. Calcul du vecteur Maxligne\n"
               " 4. Calcule du vecteur Maxcolonne\n"
               " 5. Extraction de Sous-Matrice\n");

        do
        {
            printf("Choisissez un numero entre 1 et 5 du menu :  ");
            scanf("%d", &sousChoix);
        } while ((sousChoix != 1) && (sousChoix != 2) && (sousChoix != 3) && (sousChoix != 4) && (sousChoix != 5) && (sousChoix != 6));

        switch (sousChoix)
        {
        case 1:
            return 21;
            break; /* Menu 2.1 */
        case 2:
            return 22;
            break; /* Menu 2.2 */
        case 3:
            return 23;
            break; /* Menu 2.3 */
        case 4:
            return 24;
            break; /* Menu 2.4 */
        case 5:
            return 25;
            break; /* Menu 2.5 */
        }
    }
    if (choix == 3)
    {
        printf("\n 1. Saisie du texte\n 2. CrÃ©ation de la matrice de mots\n"
               " 3. Affichage de la matrice\n"
               " 4. CrÃ©ation de la structure de listes\n 5. Affichage de la structure\n 6.Ajout d'un mot\n 7.Suppression d'un mot\n");

        // on fait un  controle de saisie
        do
        {
            printf("Choisissez un numero compris entre 1 et 7 du menu :  ");
            scanf("%d", &sousChoix);
        } while ((sousChoix != 1) && (sousChoix != 2) && (sousChoix != 3) && (sousChoix != 4) && (sousChoix != 5) && (sousChoix != 6) && (sousChoix != 7));

        switch (sousChoix)
        {
        case 1:
            return 30;
            break; /* Menu 1.1 */
        case 2:
            return 31;
            break; /* Menu 1.2 */
        case 3:
            return 32;
            break; /* Menu 1.3 */
        case 4:
            return 33;
            break; /* Menu 1.4 */
        case 5:
            return 34;
            break; /* Menu 1.5 */
        case 6:
            return 35;
            break; /* Menu 1.6*/
        case 7:
            return 36;
            break; /* Menu 1.7 */
        }
    }
    return 0; //  pas obligatoire de retourne ici
}
float **Allocation_Matrice(int N, int M)
{
    int i;
    float **A = NULL;

    /* On fait l'allocation de memoire pour un vecteur de N cases,
      C'est un vecteur de pointeurs */
    A = (float **)malloc(sizeof(float *) * N);

    // Si l'allocation est rï¿½ussite, On fait une allocation de M cases pr chaque ligne
    if (A != NULL)
        for (i = 0; i < N; i++)
            A[i] = (float *)malloc(sizeof(float) * M);

    return A;
}
char **Allocation_MatriceC(int N, int M)
{
    int i;
    char **A = NULL;

    /* On fait l'allocation de memoire pour un vecteur de N cases,
      C'est un vecteur de pointeurs */
    A = (char **)malloc(sizeof(char *) * N);

    // Si l'allocation est rï¿½ussite, On fait une allocation de M cases pr chaque ligne
    if (A != NULL)
        for (i = 0; i < N; i++)
            A[i] = (char *)malloc(sizeof(char) * M);

    return A;
}

// cette fonction fait la dÃ©sallocation d'une matrice (elle libere la memoire)
void Liberer_Matrice(float **A, int N)
{
    int i;
    // liberer chaque ligne
    for (i = 0; i < N; i++)
        free(A[i]);

    free(A);
}

//Affichage des ï¿½lements d'un simple vecteur d'entiers
void Affiche_Vecteur(float *vector, int taille)
{
    int i;

    for (i = 0; i < taille; i++)
        printf("%f\t", vector[i]);
}

// Affichage des ï¿½lements de la matrice
void Affiche_Mat(float **A, int N, int M)
{
    int i, j;

    for (i = 0; i < N; i++)
    {
        printf("\n|");
        for (j = 0; j < M; j++)
            printf("%f\t|", A[i][j]);
    }
    printf("\n");
}

// Affichage des ï¿½lements de la matrice
void Affiche_MatC(char **A, int N, int M)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        printf("\n|");
        for (j = 0; j < M - 1; j++)
        {
            printf(" %c |", A[i][j] == '\0' ? Empty_char : A[i][j]);
        }
    }
    printf("\n");
}

// Saisir les ï¿½lï¿½ment de la matrice
void Saisi_Mat(float **A, int N, int M)
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            printf("matrice(%d,%d) :  ", i, j);
            scanf("%f", &A[i][j]);
        }
}

// Fonction Addition ou Soustraction de 2 matrices
void Add_Soust_Mat(char operateur, float **mat1, float **mat2, int N, int M)
{
    int i, j;

    /* Pour ne pas perdre du temps, je ne vais pas crï¿½er une troisiï¿½me matrice
       mat3 pour le rï¿½sultat de l'addition ou celui de la soustraction.
       Je vais dirrectement affecter le resultat ï¿½ mat1 */

    if (operateur == '+')
    {
        printf("\nLa Somme des deux Matrices est:\n\n");

        for (i = 0; i < N; i++)
            for (j = 0; j < M; j++)
                mat1[i][j] += mat2[i][j];
    }

    /* meme principe   */
    else if (operateur == '-')
    {
        printf("\nLa Difference entre les deux Matrices est:\n\n");

        for (i = 0; i < N; i++)
            for (j = 0; j < M; j++)
                mat1[i][j] -= mat2[i][j];
    }
}

//**********************Multiplication d'une matrice par un nombre***********************************
void Multi_Mat_Nbr(float **mat, float nbr, float N, float M)
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            mat[i][j] *= nbr;
}
//**************************** Multiplication de deux matrices*****************************
float **Produit_Matriciel(float **mat1, float **mat2, int N, int M, int P)
{
    int i, k, j;
    float **mat3 = NULL;

    mat3 = Allocation_Matrice(N, P);

    /* produit matriciel : */
    for (i = 0; i < N; i++)
        for (j = 0; j < P; j++)
        {
            mat3[i][j] = 0; /* initialisation ï¿½ 0 */
            for (k = 0; k < M; k++)
                mat3[i][j] += mat1[i][k] * mat2[k][j];
        }

    return mat3;
}

/* Fonction qui enleve une ligne et une colonne precise ï¿½ une matrice,
   Pour l'utiliser dans le calcul du déterminant :) */
float** Sous_Mat_Det( float** mat, int dim, int lign_a_sup, int col_a_sup )
{
    int i, j, l = 0, c = 0;
    float **sousMat;

    sousMat = Allocation_Matrice( dim-1, dim-1 );

    //parcourir chaque ligne
    for( i=0; i<dim; i++ )
        if( i != lign_a_sup ) /* si cette ligne n'est ps Ã  supprimer: */
        {
            for( j=0; j<dim; j++ )
                if( j != col_a_sup ) /*si ce n'est pas la colonne Ã  supprimer */
                {
                    sousMat[l][c] = mat[i][j];
                    c++;
                    if( c > dim-2 )
                    {
                        c = 0;
                        l++;
                    }
                }
        }

    return sousMat;

}

float Determinant( float **mat, int N )
{
    int c, signe = 1;
    float det = 0.0;

    if( N == 1 )
        return mat[0][0];

    for( c=0; c<N; c++ )
    {
        det += signe * mat[0][c] * Determinant(Sous_Mat_Det(mat,N,0,c), N-1);
        signe *= (-1);
    }
//    printf("det est %f\n",det);
    return det;
}
/* Fonction qui calcule la CoMatrice d'une matrice donnï¿½e,
   pour l'utiliser dans le calcul de l'inverse */
void Comatrice( float** mat, float** comat, int dim )
{
    int i, j;

    for( i=0; i<dim; i++ )
        for( j=0; j<dim; j++ )
            comat[i][j] = Determinant( Sous_Mat_Det( mat, dim, i, j ), dim-1 );
}

/* Fonction qui calcule l'inverse d'une matrice donnée, et retourne NULL si la
   matrice est non inversible ( det == 0 ) */
float** Inverse_Matrice( float **matrice, int dim )
{
    float det = Determinant( matrice, dim );
    printf("det est %f\n",det);
    float **comatrice, **comatTransposed;
    if( det == 0 )
    {
        printf("\nLe determinant est null, cet matrice est non inversible\n\n");
        return NULL;
    }
    comatrice = Allocation_Matrice( dim, dim );
    comatTransposed = Allocation_Matrice( dim, dim );
    /* calculer la comatrice de la matrice */
    Comatrice( matrice, comatrice, dim );
    printf("\n\nLa comatrice:\n");
    Affiche_Mat(comatrice, dim, dim);
    /* calculer la comatrice transpose */
    Transpose_Mat( comatrice, comatTransposed,dim, dim );
    printf("\n\nLa comatrice transposÃ©:\n");
    Affiche_Mat(comatTransposed, dim, dim);
    /* calculer la matrice inverse selon la relation suivante:
       l'inverse d'un matrice = (1 / det) * comatriceTranspoed */
    Multi_Mat_Nbr( comatTransposed, (1.0/det), dim, dim );
    return comatTransposed;
}
/* La transposï¿½ d'une matrice */
void Transpose_Mat( float **mat1, float **mat2,int N, int M )
{
    int i,j;

    for( i=0; i<N; i++ )
        for( j=0; j<M; j++ )
            mat2[j][i] = mat1[i][j];
}


/* Trier la matrice selon l'ordre Decroissant (Trie par selection) */
void Trie_Mat_Decroissant(float **mat, int N, int M)
{
    int i, j, L, C, posColonMin, posLignMin;
    float tmp;

    printf("\nLa matrice Trie selon l'ordre decroissant est donc:\n\n");

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            /* Recherche du maximum aprï¿½s A[i][j] */
            posLignMin = i;
            posColonMin = j;

            C = j;

            for (L = i; L < N; L++)
            {
                if (L != i)
                    C = 0;
                for (; C < M; C++)
                    if (mat[L][C] > mat[posLignMin][posColonMin])
                    {
                        posLignMin = L;
                        posColonMin = C;
                    }
            }

            /* Echange de A[I] avec le maximum */
            tmp = mat[i][j];
            mat[i][j] = mat[posLignMin][posColonMin];
            mat[posLignMin][posColonMin] = tmp;
        }
}

/* Trier la matrice selon l'ordre Croissant (Tri par selection) */
void Trie_Mat_Croissant(float **mat, int N, int M)
{
    int i, j, L, C, posColonMin, posLignMin;
    float tmp;

    printf("\nLa matrice Trie selon l'ordre croissant est donc:\n\n");

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
        {
            /* Recherche du maximum aprï¿½s A[i][j] */
            posLignMin = i;
            posColonMin = j;
            C = j;

            for (L = i; L < N; L++)
            {
                if (L != i)
                    C = 0;
                for (; C < M; C++)
                    if (mat[L][C] < mat[posLignMin][posColonMin])
                    {
                        posLignMin = L;
                        posColonMin = C;
                    }
            }

            /* Echange de A[I] avec le max */
            tmp = mat[i][j];
            mat[i][j] = mat[posLignMin][posColonMin];
            mat[posLignMin][posColonMin] = tmp;
        }
}

/* Les elements max des lignes */
void Max_Ligne(float **mat, int N, int M)
{
    int i, j;
    float *maxLigne, Max;
    printf("\nLe vecteur des elements maximum des lignes est:\n\n");

    maxLigne = (float *)malloc(N * sizeof(float));

    for (i = 0; i < N; i++)
    {
        /* initialiser avec le 1er elt de la ligne */
        Max = mat[i][0];

        for (j = 0; j < M; j++)
            if (Max < mat[i][j])
                Max = mat[i][j];

        maxLigne[i] = Max;
    }

    Affiche_Vecteur(maxLigne, N);
}

/* Les ï¿½lements maximum des colonnes */
void Max_Colonne(float **mat, int N, int M)
{
    int i, j;
    float *maxColonne, Max;
    printf("\nLe vecteur des elements maximum des colonne est:\n\n");

    maxColonne = (float *)malloc(M * sizeof(float));

    for (j = 0; j < M; j++)
    {
        /* initialiser avec le 1er element de la colonne */
        Max = mat[0][j];

        for (i = 0; i < N; i++)
            if (Max < mat[i][j])
                Max = mat[i][j];

        maxColonne[j] = Max;
    }

    Affiche_Vecteur(maxColonne, M);
}

/* Extarcation des sous matrices s_mat de taille s_N et s_M ï¿½ partir de la
   matrice mat avec dimentions N et M */
void Extraction_Sous_Mat(float **mat, int N, int M, int s_N, int s_M)
{
    int i, j, L = 0, C = 0;
    float **s_mat;

    /* L c'est l'indice de debut de lignes d'une suite de sous matrice*/
    while (L <= N - s_N)
    {
        /* allocation de la sous matrice */
        s_mat = Allocation_Matrice(s_N, s_M);

        /* remplissage de la sous matrice */
        for (i = 0; i < s_N; i++)
            for (j = 0; j < s_M; j++)
                s_mat[i][j] = mat[i + L][j + C];

        if (C < M - s_M)
            C++;
        else
        {
            C = 0;
            L++;
        }

        /* affichage de la sous matrice */
        Affiche_Mat(s_mat, s_N, s_M);

        Liberer_Matrice(s_mat, s_N);
    }
    return;
}
/* texte */
void TextToMat(const char *msg, char **mat, int N, int M)
{
    int l = strlen(msg), x = 0;
    int i;
    int j;
    for ( i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            if (x < l && !(msg[x] == ' ' || msg[x] == '\t'))
            {
                mat[i][j] = msg[x];
                x++;
            }
            else
                mat[i][j] = '\0';
        }
        while (x < l && (msg[x] == ' ' || msg[x] == '\t'))
        {
            x++;
        }
    }
    return;
}
/*  */
int PlusGrandMot(const char *msg)
{
    int j = 0, N = 0, l = strlen(msg);
    int i;
    for ( i = 0; i < l; i++)
    {
        if (msg[i] == ' ' || msg[i] == '\t')
            j = 0;
        else
        {
            j++;
            if (N < j)
                N = j;
        }
    }
    return N;
}
/*  */
int NbrDesMots(const char *msg)
{
    int N = 0, l = strlen(msg);
    int i;
    if (l > 0 && !(msg[0] == ' ' || msg[0] == '\t'))
        N++;
    for ( i = 0; i < l; i++)
    {
        if (msg[i] == ' ' || msg[i] == '\t')
        {
            if (i + 1 < l && !(msg[i + 1] == ' ' || msg[i + 1] == '\t'))
            {

                N++;
            }
        }
    }
    return N;
}
/*  */
void InitStruct(VP *listVP)
{
	int i;
    for ( i = 0; i < 26; i++)
    {
        listVP[i].head = NULL;
        listVP[i].car = (char)('A' + i);
    }
}
/* création d'un élt */
PList CreerUnElm(const char *mot, PList Next)
{
    PList newList = (PList)malloc(sizeof(struct List));
    newList->mot = strdup(mot);
    newList->next = Next;
    return newList;
}
/* fonction qui supprime un mot */
void SupprimerMot(VP *listVP, const char *mot)
{
    int pos = (int)(toupper(mot[0]) - 'A');
    if (pos > 26)
        printf("il n'y a pas de liste pour cette lettre %c", mot[0]);
    else if (listVP[pos].head == NULL)
        printf("this list '%c' is empty", toupper(mot[0]));
    else if (strcmp(listVP[pos].head->mot, mot) == 0)
    {
        PList p = listVP[pos].head;
        listVP[pos].head = listVP[pos].head->next;
        free(p);
    }
    else
    {
        PList head = listVP[pos].head, next = head->next;
        while (next != NULL && (strcmp(next->mot, mot) != 0))
        {
            head = next;
            next = next->next;
        }
        head->next = next->next;
        free(next);
    }
}
/* fonction qui ajoute un mot */
void AjoutMot(VP *listVP, const char *mot)
{
    int pos = (int)(toupper(mot[0]) - 'A');
    if (pos > 26)
        printf("il n'y a pas de liste pour cette lettre %c", mot[0]);
    else if (listVP[pos].head == NULL || strcmp(listVP[pos].head->mot, mot) > 0)
        listVP[pos].head = CreerUnElm(mot, listVP[pos].head);
    else
    {
        PList head = listVP[pos].head, next = head->next;
        while (next != NULL && (strcmp(next->mot, mot) > 0))
        {
            head = next;
            next = next->next;
        }
        head->next = CreerUnElm(mot, next);
    }
}
/* affichage de la structure */
void afficherStructure(VP *listVP)
{
	int i;
    for ( i = 0; i < 26; i++)
    {
        printf("affichage de list de carracter %c : ", listVP[i].car);
        PList head = listVP[i].head;
        if (head != NULL)
        {
            while (head->next != NULL)
            {
                printf("%s | ", head->mot);
                head = head->next;
            }
            printf("%s\n", head->mot);
        }
        else
            printf("[VIDE]\n", listVP[i].car);
    }
}
