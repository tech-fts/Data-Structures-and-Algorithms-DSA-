#include <stdio.h>
#include <stdlib.h>

void project_display(){
    printf("This is vault project!");
    printf("\n");
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
    printf("6. view all accounts in the vault");
    printf("\n");
}

int* check_vault(int *vault, int vault_size){
    printf("Enter the size of the vault: ");
    scanf("%d", &vault_size);
    vault = (int*)malloc(vault_size * sizeof(int));
    printf("Vault created with size %d", vault_size);
    return vault;
}

int main(){
    int option, vault_size; 
    int *vault = NULL; //add pointer to vault array

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
            vault = check_vault(vault, vault_size);
        }else if(option == 2){
            // open an existing vault
            printf("Opening an existing vault...");
            printf("\n");
            if(vault == NULL){
                printf("No vault found. Please create a new vault first.");
                printf("\n");
            }

            printf("Vault opened successfully.");
            printf("\n");
            printf("Vault size: %d", vault_size);
            printf("\n");

        }
    }
    return 0;
}