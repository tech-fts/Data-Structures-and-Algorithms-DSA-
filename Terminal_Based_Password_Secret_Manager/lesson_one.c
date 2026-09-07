#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char account[50];
    char username[50];
    char password[50];
} Account;

void project_display(){
    printf("\n___________This is vault project!___________\n");
    printf("This project is a terminal based password secret manager.");
    printf("\n");
    printf("This project is written in C language.");
    printf("\n");
    printf("1. create a new vault");
    printf("\n");
    printf("2. open an existing vault");
    printf("\n");
    printf("3. add a account to the vault");
    printf("\n");
    printf("4. delete a account from the vault");
    printf("\n");
    printf("5. update a account in the vault");
    printf("\n");
    printf("6. view all accounts in the vault \n");
    printf("Enter your option: ");
}

Account* check_vault(Account *vault, int *vault_size, int *account_count){
    printf("Enter the size of the vault: ");
    scanf("%d", vault_size);
    vault = (Account*)calloc(*vault_size, sizeof(Account));
    *account_count = 0;

    printf("Vault created with size %d\n", *vault_size);
    return vault;
}

void save_to_database(char *account, char *username, char *password){
    // Placeholder for saving to database
    printf("Saving to database: Account: %s, Username: %s, Password: %s\n", account, username, password);
    FILE *vault_file = fopen("vault.txt", "a");
    if (vault_file == NULL) {
        printf("Error opening vault file for writing.\n");
        return; 
    }
    fprintf(vault_file, "Account: %s, Username: %s, Password: %s\n", account, username, password);
    fclose(vault_file);
}

char encrypt_decrypt_string(char *str, char *key){
    // Simple XOR encryption/decryption for demonstration
    // while(*str){
    //     *str ^= *key; // XOR with key
    //     str++;
    // } //one way 

    int key_length = strlen(str);
    for (int i=0; i < key_length; i++) {
        str[i] ^= key[i % strlen(key)]; // XOR with key
    } //two ways
    return *str;
}

void encrypt_decrypt(Account *account, int count){
    printf("Encrypting/Decrypting password for account: %s %d\n", account->account, count);
    char new_account[50];
    char new_username[50];
    char new_password[50];
    // Implementation for encryption/decryption
    for(int i = 0; i< count; i++){//need to know how to loop for aoount structure
        new_account[i] = encrypt_decrypt_string(account->account, "K");
        new_username[i] = encrypt_decrypt_string(account->username, "K");
        new_password[i] = encrypt_decrypt_string(account->password, "K");

        save_to_database(new_account, new_username, new_password);
        printf("Encrypted/Decrypted Account: %s, Username: %s, Password: %s\n", new_account, new_username, new_password);
    }
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

    // Prompt user ONCE outside the search loop
    printf("Enter account name: ");
    scanf("%49s", new_account.account);
    printf("Enter username: ");
    scanf("%49s", new_account.username);
    printf("Enter password: ");
    scanf("%49s", new_account.password);

    // Loop through the array to find an empty slot
    for (int i = 0; i < vault_size; i++) {
        if (vault[i].account[0] == '\0') { 
            vault[i] = new_account;
            encrypt_decrypt(&new_account, i == 0 ? 1 : i); // Call the encrypt_decrypt function here add new funtion 
            (*account_count)++;
            printf("Account added successfully.\n");
            return;
        }
    }
}

void view_accounts(FILE *vault_file, int *vault_size) {
    if(vault_file == NULL || *vault_size <= 0){
        printf("No accounts to display. Please create a new vault first.");
        printf("\n");
        return;
    }
    printf("Accounts in the vault:\n");
    // for(int i = 0; i < *vault_size; i++){
    //     if(vault[i].account[0] != '\0'){ // Check for non-empty slot
    //         printf("Account: %s, Username: %s, Password: %s\n", vault[i].account, vault[i].username, vault[i].password);
    //     }
    // }
    char line[200];
    while(fgets(line, sizeof(line), vault_file) != NULL){
        printf("%s", line);
    }
    fclose(vault_file);
}

int main(){
    int option; 
    int vault_size = 0;
    int account_count = 0;
    Account *vault = NULL; //add pointer to vault array

    while(1){
        project_display();
        if(scanf("%d", &option) != 1){
            printf("Invalid input. Please enter a number between 1 and 6.");
            printf("\n");
            // clear the input buffer
            while(getchar() != '\n');
            continue;
        }

        if(option == 1){
            // create a new vault
            printf("Creating a new vault...");
            printf("\n");
            if(vault != NULL){
                free(vault);
                vault = NULL;
            }
            vault = check_vault(vault, &vault_size, &account_count);
        }else if(option == 2){
            // open an existing vault
            printf("Opening an existing vault...");
            printf("\n");
            if(vault == NULL){
                printf("No vault found. Please create a new vault first.");
                printf("\n");
            } else {
                printf("Vault opened successfully.");
                printf("\n");
                printf("Vault size: %d", vault_size); //no need to display the vault size here, but it can be useful for debugging and no need to add * for pointer
                printf("\n");
            }

        }else if(option == 3){
            // add a account to the vault
            printf("Adding a new account to the vault...");
            printf("\n");
            add_account(vault, vault_size, &account_count);
        }else if(option == 6){
            // view accounts in the vault
            printf("Viewing accounts in the vault...");
            printf("\n");
            FILE *vault_file = fopen("vault.txt", "r");
            if(vault_file != NULL) {
                printf("Vault contents:\n");
                view_accounts(vault_file, &vault_size);
                // fclose(vault_file);
            } else {
                printf("No vault file found. Please create a new vault first.");
                printf("\n");
                continue;
            }
        }else{
            printf("Exiting the program...");
            break;
        }
    }
    return 0;
}