#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Structures ---

struct AgriculturalAccount {
    char name[50];
    int age;
    char cropType[50];
};

struct User {
    char username[50];
    char password[50];
    struct AgriculturalAccount account;
    struct User* next;
};

struct Product {
    int productId;
    char name[50];
    float price;
    int quantity;
    struct Product* next;
};

struct FarmerProduct {
    int productCode;
    char name[50];
    char description[100];
    float price;
    int quantity;
    struct FarmerProduct* next;
};

// --- User Management Functions ---

struct User* createAccount(struct User* userList) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        printf("Memory allocation failed.\n");
        return userList;
    }

    printf("Enter username: ");
    scanf("%s", newUser->username);
    printf("Enter password: ");
    scanf("%s", newUser->password);
    printf("Enter your full name: ");
    scanf("%s", newUser->account.name);
    printf("Enter age: ");
    scanf("%d", &newUser->account.age);
    printf("Enter Occupation: ");
    scanf("%s", newUser->account.cropType);

    newUser->next = userList;
    return newUser;
}

void displayProfile(const struct User* user) {
    printf("\n--- User Profile ---\n");
    printf("Username: %s\n", user->username);
    printf("Name: %s\n", user->account.name);
    printf("Age: %d\n", user->account.age);
    printf("Occupation: %s\n", user->account.cropType);
}

struct User* login(struct User* userList) {
    char username[50], password[50];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    struct User* current = userList;
    while (current != NULL) {
        if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Admin function to view all users
void viewAllUsers(struct User* head) {
    printf("\n--- Registered Users List ---\n");
    if (head == NULL) {
        printf("No users registered yet.\n");
        return;
    }
    struct User* current = head;
    while (current != NULL) {
        printf("Username: %s | Password: %s | Name: %s | Age: %d | Occ: %s\n",
               current->username, current->password, current->account.name,
               current->account.age, current->account.cropType);
        current = current->next;
    }
}

// Admin function to delete a user
struct User* deleteUserByAdmin(struct User* head, char* username) {
    if (head == NULL) return NULL;

    struct User *current = head, *prev = NULL;

    if (strcmp(head->username, username) == 0) {
        struct User* temp = head->next;
        free(head);
        printf("User '%s' deleted successfully.\n", username);
        return temp;
    }

    while (current != NULL && strcmp(current->username, username) != 0) {
        prev = current;
        current = current->next;
    }

    if (current != NULL) {
        prev->next = current->next;
        free(current);
        printf("User '%s' deleted successfully.\n", username);
    } else {
        printf("User '%s' not found.\n", username);
    }
    return head;
}

// --- Product & Farmer Functions ---

struct Product* createProduct(int productId, const char* name, float price, int quantity) {
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));
    newProduct->productId = productId;
    strncpy(newProduct->name, name, 50);
    newProduct->price = price;
    newProduct->quantity = quantity;
    newProduct->next = NULL;
    return newProduct;
}

struct Product* addProduct(struct Product* head, struct Product* newProduct) {
    if (head == NULL) return newProduct;
    struct Product* current = head;
    while (current->next != NULL) current = current->next;
    current->next = newProduct;
    return head;
}

void displayProducts(const struct Product* head) {
    printf("\n--- General Product List ---\n");
    const struct Product* current = head;
    while (current != NULL) {
        printf("Code: %d, Name: %s, Price: %.2f, Quantity: %d\n",
               current->productId, current->name, current->price, current->quantity);
        current = current->next;
    }
}

struct FarmerProduct* createFarmerProduct(int code, const char* name, const char* desc, float price, int qty) {
    struct FarmerProduct* newP = (struct FarmerProduct*)malloc(sizeof(struct FarmerProduct));
    newP->productCode = code;
    strncpy(newP->name, name, 50);
    strncpy(newP->description, desc, 100);
    newP->price = price;
    newP->quantity = qty;
    newP->next = NULL;
    return newP;
}

struct FarmerProduct* addFarmerProduct(struct FarmerProduct* head, struct FarmerProduct* newP) {
    if (head == NULL) return newP;
    struct FarmerProduct* curr = head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newP;
    return head;
}

void displayFarmerProducts(const struct FarmerProduct* head) {
    printf("\n--- Farmer Products List ---\n");
    const struct FarmerProduct* current = head;
    while (current != NULL) {
        printf("Code: %d, Name: %s, Desc: %s, Price: %.2f, Qty: %d\n",
               current->productCode, current->name, current->description, current->price, current->quantity);
        current = current->next;
    }
}

void buyProductLogic(struct Product* head, int code) {
    struct Product* current = head;
    while (current != NULL && current->productId != code) current = current->next;
    if (current != NULL) {
        int qty;
        printf("Enter quantity to buy: ");
        scanf("%d", &qty);
        if (qty > 0 && qty <= current->quantity) {
            current->quantity -= qty;
            printf("Purchase successful! Total: %.2f\n", current->price * qty);
        } else printf("Invalid quantity.\n");
    } else printf("Product not found.\n");
}

void buyFarmerProductLogic(struct FarmerProduct* head, int code) {
    struct FarmerProduct* current = head;
    while (current != NULL && current->productCode != code) current = current->next;
    if (current != NULL) {
        int qty;
        printf("Enter quantity to buy: ");
        scanf("%d", &qty);
        if (qty > 0 && qty <= current->quantity) {
            current->quantity -= qty;
            printf("Purchase successful! Total: %.2f\n", current->price * qty);
        } else printf("Invalid quantity.\n");
    } else printf("Product not found.\n");
}

// --- Utilities & Admin Menu ---

const char* getChatBotResponse(const char* query) {
    if (strstr(query, "hello") || strstr(query, "hi")) return "Hello! How can I help you?";
    if (strstr(query, "products")) return "We offer Fruits, Vegetables, Seeds, and more!";
    if (strstr(query, "buy")) return "Visit our marketplace to buy fresh products.";
    return "Our expert will be with you shortly. Check our tutorials meanwhile.";
}

void adminFunctions(struct Product** productList, struct User** userList) {
    int choice;
    char targetUser[50];
    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Product\n2. Display General Products\n3. Delete Product\n");
        printf("4. Refresh\n5. View Registered Users\n6. Delete User\n7. Exit Admin Panel\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int id, q; float p; char n[50];
                printf("ID, Name, Price, Qty: ");
                scanf("%d %s %f %d", &id, n, &p, &q);
                *productList = addProduct(*productList, createProduct(id, n, p, q));
                break;
            }
            case 2: displayProducts(*productList); break;
            case 5: viewAllUsers(*userList); break;
            case 6:
                printf("Enter username to delete: ");
                scanf("%s", targetUser);
                *userList = deleteUserByAdmin(*userList, targetUser);
                break;
            case 7: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 7);
}

// --- Main Program ---

int main() {
    struct User* userList = NULL;
    struct User* loggedInUser = NULL;
    struct Product* productList = NULL;
    struct FarmerProduct* farmerProductList = NULL;
    int choice, running = 1;

    while (running) {
        printf("\n======= AGRISOLUTIONS =======\n");
        if (loggedInUser == NULL) {
            // Guest Menu
            printf("1. Sign Up\n2. Log In\n3. Chat with ChatBot\n4. Help & Support\n5. Admin Login\n6. Exit\n");
        } else {
            // User Menu
            printf("1. Profile\n2. Expert Appointment\n3. Chat with ChatBot\n4. Help & Support\n");
            printf("5. Farmer Sell Post\n6. Display Farmer Products\n7. Display General Products\n");
            printf("8. Buy Farmer Product\n9. Buy General Product\n10. Log Out\n");
        }
        printf("Enter Choice: ");
        scanf("%d", &choice);

        if (loggedInUser == NULL) {
            switch (choice) {
                case 1: userList = createAccount(userList); printf("Signed up!\n"); break;
                case 2: loggedInUser = login(userList); if(loggedInUser) printf("Logged in!\n"); else printf("Failed.\n"); break;
                case 3: {
                    char q[50]; printf("Bot (type 'exit'): ");
                    while(scanf("%s", q) && strcmp(q, "exit") != 0) printf("%s\nBot: ", getChatBotResponse(q));
                    break;
                }
                case 4: printf("Email: naham@agrisolutions.com | Phone: +880123456789\n"); break;
                case 5: {
                    char au[20], ap[20];
                    printf("Admin User/Pass: "); scanf("%s %s", au, ap);
                    if(strcmp(au, "admin") == 0 && strcmp(ap, "admin123") == 0) adminFunctions(&productList, &userList);
                    else printf("Access Denied.\n");
                    break;
                }
                case 6: running = 0; break;
                default: printf("Invalid choice.\n");
            }
        } else {
            switch (choice) {
                case 1: displayProfile(loggedInUser); break;
                case 2: printf("Call +880123456789 for appointment.\n"); break;
                case 3: {
                    char q[50]; printf("Bot (type 'exit' when done): ");
                    while(scanf("%s", q) && strcmp(q, "exit") != 0) printf("%s\nBot: ", getChatBotResponse(q));
                    break;
                }
                case 4: printf("Email: naham@agrisolutions.com | Phone: +880123456789\n"); break;
                case 5: {
                    int id, q; float p; char n[50], d[100];
                    printf("Code, Name, Desc, Price, Qty: ");
                    scanf("%d %s %s %f %d", &id, n, d, &p, &q);
                    farmerProductList = addFarmerProduct(farmerProductList, createFarmerProduct(id, n, d, p, q));
                    printf("Post added!\n");
                    break;
                }
                case 6: displayFarmerProducts(farmerProductList); break;
                case 7: displayProducts(productList); break;
                case 8: {
                    int code; displayFarmerProducts(farmerProductList);
                    printf("Enter Code: "); scanf("%d", &code);
                    buyFarmerProductLogic(farmerProductList, code);
                    break;
                }
                case 9: {
                    int code; displayProducts(productList);
                    printf("Enter Code: "); scanf("%d", &code);
                    buyProductLogic(productList, code);
                    break;
                }
                case 10: loggedInUser = NULL; printf("Logged out.\n"); break;
                default: printf("Invalid choice.\n");
            }
        }
    }


    return 0;
}
