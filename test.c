#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

void disableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~ECHO; // Disable echoing characters
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void enableEcho() {
    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag |= ECHO; // Enable echoing characters
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

char getHiddenInput() {
    char ch;
    disableEcho(); // Disable echoing
    ch = getchar(); // Read character
    enableEcho(); // Restore echoing
    return ch;
}

void getPasswordInput(char *password, int maxLength) {
    int i = 0;
    char ch;
    printf("Enter password: ");
    
    while (i < maxLength - 1) {
        ch = getHiddenInput(); // Read character without echo
        
        if (ch == '\n') { // Enter key is pressed
            if (i == 0) { // If no character was entered
                continue; // Prompt again
            }
            break; // Exit loop if at least one character was entered
        }
        
        if (ch == 127) { // Handle backspace (ASCII 127)
            if (i > 0) {
                i--;
                printf("\b \b"); // Move cursor back and overwrite with space
            }
        } else {
            password[i++] = ch; // Store character
            printf("*"); // Print asterisk for each character entered
        }
    }
    
    password[i] = '\0'; // Null-terminate the password string
    printf("\n");
}

// Example usage in an admin login function
void admin_login() {
    char user[20], password[20];
    int login_attempts = 3;
    const char *olduser_name = "Admin123";
    const char *old_password = "985123";

    printf("\033[1;36m\n ADMIN LOGIN PAGE \033[0m\n");
    
    while (login_attempts != 0) {
        printf("Enter username: ");
        scanf("%s", user);
        getPasswordInput(password, sizeof(password));
        
        if ((strcmp(olduser_name, user) == 0 && strcmp(old_password, password) == 0)) {
            printf("\nLogged In Successfully!\n");
            break;
        } else {
            login_attempts--;
            printf("\033[1;31mInvalid Username or password. %d attempts remaining.\033[0m\n", login_attempts);
        }
    }
    
    if (login_attempts == 0) {
        printf("\033[1;33mToo many failed attempts. Please Try next time!\033[0m\n");
        exit(0);
    }
}

// Main function for testing purposes
int main() {
    admin_login(); // Call admin login for testing

    return 0;
}