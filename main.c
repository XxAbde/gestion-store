#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_nom_LENGTH 50
#define MAX_ProduitS 100
#define MAX_CLIENTS 100
#define MAX_VenteS 100

typedef struct {
    int id;
    char nom[MAX_nom_LENGTH];
    float prix;
    int stock;
} Produit;

typedef struct {
    int id;
    char nom[MAX_nom_LENGTH];
    char email[MAX_nom_LENGTH];
    char phone[MAX_nom_LENGTH];
    float totalSpent;
} Client;

typedef struct {
    int VenteId;
    int ProduitId;
    int clientId;
    int quantity;
    float totalprix;
} Vente;

Produit Produits[MAX_ProduitS];
int ProduitCount = 0;

Client clients[MAX_CLIENTS];
int clientCount = 0;

Vente Ventes[MAX_VenteS];
int VenteCount = 0;

void addProduit() {
    if (ProduitCount >= MAX_ProduitS) {
        printf("Produit limit reached!\n");
        return;
    }

    Produit p;
    p.id = ProduitCount + 1;
    printf("Enter Produit nom: ");
    scanf("%s", p.nom);
    printf("Enter Produit prix: ");
    scanf("%f", &p.prix);
    printf("Enter Produit stock: ");
    scanf("%d", &p.stock);

    Produits[ProduitCount] = p;
    ProduitCount++;
    printf("Produit added successfully!\n");
}

void displayProduits() {
    for (int i = 0; i < ProduitCount; i++) {
        printf("ID: %d, nom: %s, prix: %.2f, Stock: %d\n", Produits[i].id, Produits[i].nom, Produits[i].prix, Produits[i].stock);
    }
}

void saveProduitsToFile() {
    FILE *file = fopen("Produits.dat", "wb");
    if (file == NULL) {
        printf("Unable to open Produits.dat for writing!\n");
        return;
    }
    fwrite(&ProduitCount, sizeof(int), 1, file);
    fwrite(Produits, sizeof(Produit), ProduitCount, file);
    fclose(file);
    printf("Produits saved successfully!\n");
}

void loadProduitsFromFile() {
    FILE *file = fopen("Produits.dat", "rb");
    if (file == NULL) {
        printf("Unable to open Produits.dat for reading!\n");
        return;
    }
    fread(&ProduitCount, sizeof(int), 1, file);
    fread(Produits, sizeof(Produit), ProduitCount, file);
    fclose(file);
    printf("Produits loaded successfully!\n");
}

void addClient() {
    if (clientCount >= MAX_CLIENTS) {
        printf("Client limit reached!\n");
        return;
    }

    Client c;
    c.id = clientCount + 1;
    printf("Enter client nom: ");
    scanf("%s", c.nom);
    printf("Enter client email: ");
    scanf("%s", c.email);
    printf("Enter client phone: ");
    scanf("%s", c.phone);
    c.totalSpent = 0;

    clients[clientCount] = c;
    clientCount++;
    printf("Client added successfully!\n");
}

void displayClients() {
    for (int i = 0; i < clientCount; i++) {
        printf("ID: %d, nom: %s, Email: %s, Phone: %s, Total Spent: %.2f\n", clients[i].id, clients[i].nom, clients[i].email, clients[i].phone, clients[i].totalSpent);
    }
}

void saveClientsToFile() {
    FILE *file = fopen("clients.dat", "wb");
    if (file == NULL) {
        printf("Unable to open clients.dat for writing!\n");
        return;
    }
    fwrite(&clientCount, sizeof(int), 1, file);
    fwrite(clients, sizeof(Client), clientCount, file);
    fclose(file);
    printf("Clients saved successfully!\n");
}

void loadClientsFromFile() {
    FILE *file = fopen("clients.dat", "rb");
    if (file == NULL) {
        printf("Unable to open clients.dat for reading!\n");
        return;
    }
    fread(&clientCount, sizeof(int), 1, file);
    fread(clients, sizeof(Client), clientCount, file);
    fclose(file);
    printf("Clients loaded successfully!\n");
}

void recordVente() {
    if (VenteCount >= MAX_VenteS) {
        printf("Vente limit reached!\n");
        return;
    }

    Vente s;
    s.VenteId = VenteCount + 1;
    printf("Enter Produit ID: ");
    scanf("%d", &s.ProduitId);
    printf("Enter client ID: ");
    scanf("%d", &s.clientId);
    printf("Enter quantity: ");
    scanf("%d", &s.quantity);

    int ProduitIndex = -1, clientIndex = -1;
    for (int i = 0; i < ProduitCount; i++) {
        if (Produits[i].id == s.ProduitId) {
            ProduitIndex = i;
            break;
        }
    }
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].id == s.clientId) {
            clientIndex = i;
            break;
        }
    }

    if (ProduitIndex == -1 || clientIndex == -1) {
        printf("Invalid Produit or client ID!\n");
        return;
    }

    if (Produits[ProduitIndex].stock < s.quantity) {
        printf("Insufficient stock!\n");
        return;
    }

    Produits[ProduitIndex].stock -= s.quantity;
    s.totalprix = Produits[ProduitIndex].prix * s.quantity;
    clients[clientIndex].totalSpent += s.totalprix;

    Ventes[VenteCount] = s;
    VenteCount++;
    printf("Vente recorded successfully!\n");
}

void displayVentes() {
    for (int i = 0; i < VenteCount; i++) {
        printf("Vente ID: %d, Produit ID: %d, Client ID: %d, Quantity: %d, Total prix: %.2f\n", Ventes[i].VenteId, Ventes[i].ProduitId, Ventes[i].clientId, Ventes[i].quantity, Ventes[i].totalprix);
    }
}

void saveVentesToFile() {
    FILE *file = fopen("Ventes.dat", "wb");
    if (file == NULL) {
        printf("Unable to open Ventes.dat for writing!\n");
        return;
    }
    fwrite(&VenteCount, sizeof(int), 1, file);
    fwrite(Ventes, sizeof(Vente), VenteCount, file);
    fclose(file);
    printf("Ventes saved successfully!\n");
}

void loadVentesFromFile() {
    FILE *file = fopen("Ventes.dat", "rb");
    if (file == NULL) {
        printf("Unable to open Ventes.dat for reading!\n");
        return;
    }
    fread(&VenteCount, sizeof(int), 1, file);
    fread(Ventes, sizeof(Vente), VenteCount, file);
    fclose(file);
    printf("Ventes loaded successfully!\n");
}

void displayMenu() {
    printf("1. Add Produit\n");
    printf("2. Display Produits\n");
    printf("3. Add Client\n");
    printf("4. Display Clients\n");
    printf("5. Record Vente\n");
    printf("6. Display Ventes\n");
    printf("7. Save Data\n");
    printf("8. Load Data\n");
    printf("9. Exit\n");
}

int main() {
    int choice;

    loadProduitsFromFile();
    loadClientsFromFile();
    loadVentesFromFile();

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduit();
                break;
            case 2:
                displayProduits();
                break;
            case 3:
                addClient();
                break;
            case 4:
                displayClients();
                break;
            case 5:
                recordVente();
                break;
            case 6:
                displayVentes();
                break;
            case 7:
                saveProduitsToFile();
                saveClientsToFile();
                saveVentesToFile();
                break;
            case 8:
                loadProduitsFromFile();
                loadClientsFromFile();
                loadVentesFromFile();
                break;
            case 9:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 9);

    return 0;
}
