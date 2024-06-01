#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONGUEUR_MAX 50


typedef struct Produit {
    int id;
    char nom[LONGUEUR_MAX];
    float prix;
    int stock;
    struct Produit* suivant;
} Produit;

typedef struct Client {
    int id;
    char nom[LONGUEUR_MAX];
    char email[LONGUEUR_MAX];
    char telephone[LONGUEUR_MAX];
    float totalDepense;
    struct Client* suivant;
} Client;

typedef struct Vente {
    int idVente;
    int idProduit;
    int idClient;
    int quantite;
    float prixTotal;
    struct Vente* suivant;
} Vente;

// Liste des Produits
typedef struct {
    Produit* tete;
    int nombre;
} ListeProduits;

// Pile des Clients
typedef struct {
    Client* sommet;
    int nombre;
} PileClients;

// File des Ventes
typedef struct {
    Vente* avant;
    Vente* arriere;
    int nombre;
} FileVentes;

ListeProduits listeProduits = {NULL, 0};
PileClients pileClients = {NULL, 0};
FileVentes fileVentes = {NULL, NULL, 0};

// Fonctions de Gestion des Produits

void ajouterProduit() {
    Produit* nouveauProduit = (Produit*)malloc(sizeof(Produit));
    nouveauProduit->id = listeProduits.nombre + 1;
    printf("Entrez le nom du produit: ");
    scanf("%s", nouveauProduit->nom);
    printf("Entrez le prix du produit: ");
    scanf("%f", &nouveauProduit->prix);
    printf("Entrez le stock du produit: ");
    scanf("%d", &nouveauProduit->stock);
    nouveauProduit->suivant = listeProduits.tete;
    listeProduits.tete = nouveauProduit;
    listeProduits.nombre++;
    printf("Produit ajouté avec succès!\n");
}

void afficherProduits() {
    Produit* actuel = listeProduits.tete;
    while (actuel != NULL) {
        printf("ID: %d, Nom: %s, Prix: %.2f, Stock: %d\n", actuel->id, actuel->nom, actuel->prix, actuel->stock);
        actuel = actuel->suivant;
    }
}

void sauvegarderProduitsDansFichier() {
    FILE *file = fopen("Produits.dat", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir produits.dat pour écriture!\n");
        return;
    }
    fwrite(&listeProduits.nombre, sizeof(int), 1, file);
    Produit* actuel = listeProduits.tete;
    while (actuel != NULL) {
        fwrite(actuel, sizeof(Produit) - sizeof(Produit*), 1, file);
        actuel = actuel->suivant;
    }
    fclose(file);
    printf("Produits sauvegardés avec succès!\n");
}

void chargerProduitsDepuisFichier() {
    FILE *file = fopen("Produits.dat", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir produits.dat pour lecture!\n");
        return;
    }
    fread(&listeProduits.nombre, sizeof(int), 1, file);
    Produit* actuel = NULL;
    for (int i = 0; i < listeProduits.nombre; i++) {
        Produit* nouveauProduit = (Produit*)malloc(sizeof(Produit));
        fread(nouveauProduit, sizeof(Produit) - sizeof(Produit*), 1, file);
        nouveauProduit->suivant = actuel;
        actuel = nouveauProduit;
    }
    listeProduits.tete = actuel;
    fclose(file);
    printf("Produits chargés avec succès!\n");
}

// Fonctions de Gestion des Clients

void ajouterClient() {
    Client* nouveauClient = (Client*)malloc(sizeof(Client));
    nouveauClient->id = pileClients.nombre + 1;
    printf("Entrez le nom du client: ");
    scanf("%s", nouveauClient->nom);
    printf("Entrez l'email du client: ");
    scanf("%s", nouveauClient->email);
    printf("Entrez le telephone du client: ");
    scanf("%s", nouveauClient->telephone);
    nouveauClient->totalDepense = 0;
    nouveauClient->suivant = pileClients.sommet;
    pileClients.sommet = nouveauClient;
    pileClients.nombre++;
    printf("Client ajouté avec succès!\n");
}

void afficherClients() {
    Client* actuel = pileClients.sommet;
    while (actuel != NULL) {
        printf("ID: %d, Nom: %s, Email: %s, telephone: %s, Total Dépensé: %.2f\n", actuel->id, actuel->nom, actuel->email, actuel->telephone, actuel->totalDepense);
        actuel = actuel->suivant;
    }
}

void sauvegarderClientsDansFichier() {
    FILE *file = fopen("Clients.dat", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir clients.dat pour écriture!\n");
        return;
    }
    fwrite(&pileClients.nombre, sizeof(int), 1, file);
    Client* actuel = pileClients.sommet;
    while (actuel != NULL) {
        fwrite(actuel, sizeof(Client) - sizeof(Client*), 1, file);
        actuel = actuel->suivant;
    }
    fclose(file);
    printf("Clients sauvegardés avec succès!\n");
}

void chargerClientsDepuisFichier() {
    FILE *file = fopen("Clients.dat", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir clients.dat pour lecture!\n");
        return;
    }
    fread(&pileClients.nombre, sizeof(int), 1, file);
    Client* actuel = NULL;
    for (int i = 0; i < pileClients.nombre; i++) {
        Client* nouveauClient = (Client*)malloc(sizeof(Client));
        fread(nouveauClient, sizeof(Client) - sizeof(Client*), 1, file);
        nouveauClient->suivant = actuel;
        actuel = nouveauClient;
    }
    pileClients.sommet = actuel;
    fclose(file);
    printf("Clients chargés avec succès!\n");
}

// Fonctions de Gestion des Ventes

void enregistrerVente() {
    Vente* nouvelleVente = (Vente*)malloc(sizeof(Vente));
    nouvelleVente->idVente = fileVentes.nombre + 1;
    printf("Entrez l'ID du produit: ");
    scanf("%d", &nouvelleVente->idProduit);
    printf("Entrez l'ID du client: ");
    scanf("%d", &nouvelleVente->idClient);
    printf("Entrez la quantite: ");
    scanf("%d", &nouvelleVente->quantite);

    Produit* produit = listeProduits.tete;
    while (produit != NULL && produit->id != nouvelleVente->idProduit) {
        produit = produit->suivant;
    }

    Client* client = pileClients.sommet;
    while (client != NULL && client->id != nouvelleVente->idClient) {
        client = client->suivant;
    }

    if (produit == NULL || client == NULL) {
        printf("ID de produit ou de client invalide!\n");
        free(nouvelleVente);
        return;
    }

    if (produit->stock < nouvelleVente->quantite) {
        printf("Stock insuffisant!\n");
        free(nouvelleVente);
        return;
    }

    produit->stock -= nouvelleVente->quantite;
    nouvelleVente->prixTotal = produit->prix * nouvelleVente->quantite;
    client->totalDepense += nouvelleVente->prixTotal;

    nouvelleVente->suivant = NULL;
    if (fileVentes.arriere == NULL) {
        fileVentes.avant = nouvelleVente;
    } else {
        fileVentes.arriere->suivant = nouvelleVente;
    }
    fileVentes.arriere = nouvelleVente;
    fileVentes.nombre++;
    printf("Vente enregistrée avec succès!\n");
}

void afficherVentes() {
    Vente* actuel = fileVentes.avant;
    while (actuel != NULL) {
        printf("ID Vente: %d, ID Produit: %d, ID Client: %d, quantite: %d, Prix Total: %.2f\n", actuel->idVente, actuel->idProduit, actuel->idClient, actuel->quantite, actuel->prixTotal);
        actuel = actuel->suivant;
    }
}

void sauvegarderVentesDansFichier() {
    FILE *file = fopen("Ventes.dat", "wb");
    if (file == NULL) {
        printf("Impossible d'ouvrir ventes.dat pour écriture!\n");
        return;
    }
    fwrite(&fileVentes.nombre, sizeof(int), 1, file);
    Vente* actuel = fileVentes.avant;
    while (actuel != NULL) {
        fwrite(actuel, sizeof(Vente) - sizeof(Vente*), 1, file);
        actuel = actuel->suivant;
    }
    fclose(file);
    printf("Ventes sauvegardées avec succès!\n");
}

void chargerVentesDepuisFichier() {
    FILE *file = fopen("Ventes.dat", "rb");
    if (file == NULL) {
        printf("Impossible d'ouvrir ventes.dat pour lecture!\n");
    return;
    }
    fread(&fileVentes.nombre, sizeof(int), 1, file);
    Vente* actuel = NULL;
    Vente* precedent = NULL;
    for (int i = 0; i < fileVentes.nombre; i++) {
        Vente* nouvelleVente = (Vente*)malloc(sizeof(Vente));
        fread(nouvelleVente, sizeof(Vente) - sizeof(Vente*), 1, file);
        nouvelleVente->suivant = NULL;
        if (precedent == NULL) {
            actuel = nouvelleVente;
        } else {
            precedent->suivant = nouvelleVente;
        }
        precedent = nouvelleVente;
    }
    fileVentes.avant = actuel;
    fileVentes.arriere = precedent;
    fclose(file);
    printf("Ventes chargées avec succès!\n");
}
// Menu Principal

void afficherMenu() {
    printf("1. Ajouter un Produit\n");
    printf("2. Afficher les Produits\n");
    printf("3. Ajouter un Client\n");
    printf("4. Afficher les Clients\n");
    printf("5. Enregistrer une Vente\n");
    printf("6. Afficher les Ventes\n");
    printf("7. Sauvegarder les Données\n");
    printf("8. Charger les Données\n");
    printf("9. Quitter\n");
}

int main() {
    int choix;

    chargerProduitsDepuisFichier();
    chargerClientsDepuisFichier();
    chargerVentesDepuisFichier();

    do {
        afficherMenu();
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterProduit();
                break;
            case 2:
                afficherProduits();
                break;
            case 3:
                ajouterClient();
                break;
            case 4:
                afficherClients();
                break;
            case 5:
                enregistrerVente();
                break;
            case 6:
                afficherVentes();
                break;
            case 7:
                sauvegarderProduitsDansFichier();
                sauvegarderClientsDansFichier();
                sauvegarderVentesDansFichier();
                break;
            case 8:
                chargerProduitsDepuisFichier();
                chargerClientsDepuisFichier();
                chargerVentesDepuisFichier();
                break;
            case 9:
                printf("Sortie...\n");
                break;
            default:
                printf("Choix invalide ! Veuillez réessayer.\n");
        }
    } while (choix != 9);

    return 0;
}
