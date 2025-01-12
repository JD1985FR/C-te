#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * Exemple : Méthode de Gauss pour résoudre A*x = b
 * où A est une matrice n x n, et b un vecteur n.
 *
 * On lit les coefficients de A et b, puis on résout le système.
 * Implémente l'élimination de Gauss classique (sans pivotage).
 *
 * Pour plus de robustesse, on pourrait ajouter:
 *   - du pivotage partiel (échanger la ligne pivot avec
 *     la ligne qui a le plus grand élément dans la colonne pivot).
 *   - de la vérification d'absence de pivot nul.
 */

int main() {
    int n, i, j, k;

    // 1) Lecture de la taille du système
    printf("Entrez la taille n du système (nb d'équations) : ");
    scanf("%d", &n);

    // Création d'une matrice (n x n+1) pour la matrice augmentée : A et b
    // -> indices : [0..n-1][0..n]
    double **mat = (double**) malloc(n * sizeof(double*));
    for(i = 0; i < n; i++) {
        mat[i] = (double*) malloc((n + 1) * sizeof(double));
    }

    // 2) Lecture des coefficients
    // L'utilisateur donne A[i][j] (j=0..n-1) et b[i] (la colonne n)
    printf("Entrez les coefficients de la matrice augmentée (A|b):\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n + 1; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    // 3) Élimination de Gauss (sans pivot)
    for(k = 0; k < n - 1; k++) {
        // mat[k][k] est le pivot

        // Vérifier si le pivot est nul (dans un code robuste, on pivoterait)
        if(fabs(mat[k][k]) < 1e-12) {
            printf("Attention: pivot nul détecté à la ligne %d.\n", k);
            // On pourrait échanger la ligne k avec une autre ligne ici (pivotage)
            // Pour cet exemple, on continue juste, mais le résultat peut être faux
        }

        // Élimination dans les lignes en dessous de k
        for(i = k + 1; i < n; i++) {
            double facteur = mat[i][k] / mat[k][k];
            for(j = k; j < n + 1; j++) {
                mat[i][j] = mat[i][j] - facteur * mat[k][j];
            }
        }
    }

    // 4) Résolution par substitution arrière
    double *x = (double*) malloc(n * sizeof(double));

    // On part de la dernière ligne jusqu'à la première
    for(i = n - 1; i >= 0; i--) {
        double somme = 0.0;
        // Calcul de la somme des A[i][j]*x[j] déjà connus
        for(j = i + 1; j < n; j++) {
            somme += mat[i][j] * x[j];
        }
        // x[i] = (b[i] - somme) / A[i][i]
        x[i] = (mat[i][n] - somme) / mat[i][i];
    }

    // 5) Affichage des solutions
    printf("\nLes solutions du système sont:\n");
    for(i = 0; i < n; i++) {
        printf("x[%d] = %.6f\n", i, x[i]);
    }

    // Libération de la mémoire
    for(i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);
    free(x);

    return 0;
}