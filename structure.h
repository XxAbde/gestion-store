#define MAX_NAME_LENGTH 50
#define MAX_PRODUCTS 100
#define MAX_CLIENTS 100
#define MAX_SALES 100

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    float price;
    int stock;
} Product;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char phone[MAX_NAME_LENGTH];
    float totalSpent;
} Client;

typedef struct {
    int saleId;
    int productId;
    int clientId;
    int quantity;
    float totalPrice;
} Sale;
