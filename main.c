#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


typedef enum {
    INACTIVE = 0,
    ACTIVE = 1,
    PENDING = 2,
    SUSPENDED = 3
} ActivationStatus;

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    ActivationStatus status;
} UserData;

typedef union {
    int flag;
    _Bool boolean;
} ActivationFlag;

int registerUser(UserData users[], int *userCount, const char *username, const char *password, ActivationFlag activationFlag);
int loginUser(const UserData users[], int userCount, const char *username, const char *password);

int main() {
    UserData users[MAX_USERS];
    int userCount = 0;
    int choice;

    do {
        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];
                ActivationFlag activationFlag;

                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                printf("Enter activation flag (0 or 1): ");
                scanf("%d", &activationFlag.flag);

                int result = registerUser(users, &userCount, username, password, activationFlag);
                if (result == 0) {
                    printf("Registration successful.\n");
                } else {
                    printf("Registration failed. User already exists or maximum users reached.\n");
                }

                break;
            }

            case 2: {
                char username[MAX_USERNAME_LENGTH];
                char password[MAX_PASSWORD_LENGTH];

                printf("Enter username: ");
                scanf("%s", username);

                printf("Enter password: ");
                scanf("%s", password);

                int result = loginUser(users, userCount, username, password);
                if (result == -1) {
                    printf("Login failed. User not found.\n");
                } else if (result == 0) {
                    printf("Login successful.\n");
                } else {
                    printf("Login failed. Incorrect password.\n");
                }

                break;
            }

            case 3:
                printf("Exiting program.\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 3);

    return 0;
}

int registerUser(UserData users[], int *userCount, const char *username, const char *password, ActivationFlag activationFlag) {
    if (*userCount >= MAX_USERS) {
        return -1;
    }

    for (int i = 0; i < *userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return -2;
        }
    }

    strcpy(users[*userCount].username, username);
    strcpy(users[*userCount].password, password);
    users[*userCount].status = (ActivationStatus)activationFlag.flag;
    (*userCount)++;

    return 0;
}

int loginUser(const UserData users[], int userCount, const char *username, const char *password) {
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) == 0) {
                if (users[i].status == ACTIVE || users[i].status == PENDING) {
                    return 0;
                } else {
                    return -2;
                }
            } else {
                return 1;
            }
        }
    }

    return -1;
}