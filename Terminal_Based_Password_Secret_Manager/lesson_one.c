#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char account[50];
    char username[50];
    char password[50];
} Account;

void project_display() {
    printf("\n___________This is vault project!___________\n");
    printf("This project is a terminal based password secret manager.\n");
    printf("This project is written in C language.\n");
    printf("1. create a new vault\n");
    printf("2. open an existing vault\n");
    printf("3. add an account to the vault\n");
    printf("4. delete an account from the vault\n");
    printf("5. update an account in the vault\n");
    printf("6. view all accounts in the vault\n");
    printf("Enter your option: ");
}

// Fixed: XOR encryption operating on fixed-size byte buffers instead of strlen()
void encrypt_decrypt_bytes(char *data, size_t size, const char *key) {
    size_t key_len = strlen(key);
    for (size_t i = 0; i < size; i++) {
        data[i] ^= key[i % key_len];
    }
}

// Fixed: Writes binary structures directly using fwrite
void save_to_database(const Account *account) {
    FILE *vault_file = fopen("vault.bin", "ab"); // Append binary mode
    if (vault_file == NULL) {
        printf("Error opening vault file for writing.\n");
        return;
    }

    Account encrypted_acc = *account;

    // Encrypt each fixed buffer
    encrypt_decrypt_bytes(encrypted_acc.account, sizeof(encrypted_acc.account), "K");
    encrypt_decrypt_bytes(encrypted_acc.username, sizeof(encrypted_acc.username), "K");
    encrypt_decrypt_bytes(encrypted_acc.password, sizeof(encrypted_acc.password), "K");

    fwrite(&encrypted_acc, sizeof(Account), 1, vault_file);
    fclose(vault_file);
}

Account* check_vault(Account *vault, int *vault_size, int *account_count) {
    printf("Enter the size of the vault: ");
    if (scanf("%d", vault_size) != 1 || *vault_size <= 0) {
        printf("Invalid vault size.\n");
        while (getchar() != '\n'); // Clear input buffer
        return NULL;
    }

    vault = (Account*)calloc(*vault_size, sizeof(Account));
    *account_count = 0;

    printf("Vault created with size %d\n", *vault_size);
    return vault;
}

void encrypt_decrypt(Account *account, int slot) {
    printf("Encrypting and saving password for account: %s (slot: %d)\n", account->account, slot);
    save_to_database(account);
    printf("Encrypted and saved successfully.\n");
}

void add_account(Account *vault, int vault_size, int *account_count) {
    if (vault == NULL) {
        printf("No vault found. Please create a new vault first.\n");
        return;
    }

    if (*account_count >= vault_size) {
        printf("Vault is full. Cannot add more accounts.\n");
        return;
    }

    Account new_account;

    printf("Enter account name: ");
    scanf("%49s", new_account.account);
    printf("Enter username: ");
    scanf("%49s", new_account.username);
    printf("Enter password: ");
    scanf("%49s", new_account.password);

    for (int i = 0; i < vault_size; i++) {
        if (vault[i].account[0] == '\0') {
            vault[i] = new_account;
            encrypt_decrypt(&new_account, i);
            (*account_count)++;
            printf("Account added successfully.\n");
            return;
        }
    }
}

// Fixed: Reads binary structures using fread and decrypts them line-by-line
void view_accounts() {
    FILE *vault_file = fopen("vault.bin", "rb"); // Read binary mode
    if (vault_file == NULL) {
        printf("No vault file found on disk. Add an account first.\n");
        return;
    }

    Account acc;
    int count = 0;
    printf("\n--- Vault Contents ---\n");

    while (fread(&acc, sizeof(Account), 1, vault_file) == 1) {
        // Decrypt in-place
        encrypt_decrypt_bytes(acc.account, sizeof(acc.account), "K");
        encrypt_decrypt_bytes(acc.username, sizeof(acc.username), "K");
        encrypt_decrypt_bytes(acc.password, sizeof(acc.password), "K");

        printf("[%d] Account: %s | Username: %s | Password: %s\n", 
               ++count, acc.account, acc.username, acc.password);
    }

    if (count == 0) {
        printf("Vault file is empty.\n");
    }

    fclose(vault_file);
}

int main() {
    int option;
    int vault_size = 0;
    int account_count = 0;
    Account *vault = NULL;

    while (1) {
        project_display();
        if (scanf("%d", &option) != 1) {
            printf("Invalid input. Please enter a number between 1 and 6.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }

        if (option == 1) {
            printf("Creating a new vault...\n");
            if (vault != NULL) {
                free(vault);
                vault = NULL;
            }
            vault = check_vault(vault, &vault_size, &account_count);
        } else if (option == 2) {
            printf("Opening an existing vault...\n");
            if (vault == NULL) {
                printf("No vault found in memory. Please create a new vault first.\n");
            } else {
                printf("Vault opened successfully. Size: %d\n", vault_size);
            }
        } else if (option == 3) {
            printf("Adding a new account to the vault...\n");
            add_account(vault, vault_size, &account_count);
        } else if (option == 6) {
            printf("Viewing accounts in the vault...\n");
            view_accounts();
        } else {
            printf("Exiting the program...\n");
            if (vault != NULL) {
                free(vault);
            }
            break;
        }
    }
    return 0;
}