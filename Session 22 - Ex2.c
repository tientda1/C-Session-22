#include <stdio.h>
typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[100];
int numAccounts = 0;

void loadAccountsFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        fread(&numAccounts, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), numAccounts, file);
        fclose(file);
    }
}

void saveAccountsToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(&numAccounts, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), numAccounts, file);
        fclose(file);
    }
}

int isUsernameTaken(const char *username) {
    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1;
        }
    }
    return 0;
}

void registerAccount() {
    if (numAccounts >= 100) {
        printf("Khong the dang ky them tai khoan. Danh sach tai khoan da day.\n");
        return;
    }

    Account newAccount;
    char confirmPassword[50];

    printf("Nhap tai khoan: ");
    scanf("%s", newAccount.username);

    if (isUsernameTaken(newAccount.username)) {
        printf("Tai khoan da ton tai. Vui long chon ten tai khoan khac.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", newAccount.password);

    printf("Xac nhan lai mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(newAccount.password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Vui long thu lai.\n");
        return;
    }

    accounts[numAccounts++] = newAccount;
    saveAccountsToFile();
    printf("Ðang ky thanh cong.\n");
}

void login() {
    char username[50];
    char password[50];

    printf("Nhap tai khoan: ");
    scanf("%s", username);

    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong.\n");
            return;
        }
    }
    printf("Dang nhap that bai. Tai khoan hoac mat khau không dung.\n");
}

int main() {
    loadAccountsFromFile();

    int choice;

    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 3);

    return 0;
}

