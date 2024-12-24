// Sidharth S
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_CUSTOMERS 100
#define MAX_BORROWED_BOOKS 50

int main();

struct Book {
    int BI;
    char Book_name[50];
    char Author_name[50];
    float price;
};

struct Customer {
    int uniqueID;
    char username[50];
    char password[50];
};

struct Book library[MAX_BOOKS];
struct Customer customers[MAX_CUSTOMERS];
struct Book mylibrary[MAX_BORROWED_BOOKS];

int book_count = 0;
int borrowed_count = 0;
int customerCount = 0;

#define BOOK_FILE "books.txt"
#define CUSTOMER_FILE "customers.txt"

void read_books_from_file() {
    FILE *file = fopen(BOOK_FILE, "r");
    if (file) {
        fscanf(file, "%d\n", &book_count);
        for(int i = 0; i < book_count; i++) {
            fscanf(file, "%d,%[^,],%[^,],%f\n", 
                &library[i].BI,
                library[i].Book_name,
                library[i].Author_name,
                &library[i].price);
        }
        fclose(file);
    }
}

void write_books_to_file() {
    FILE *file = fopen(BOOK_FILE, "w");
    if (file) {
        fprintf(file, "%d\n", book_count);
        for(int i = 0; i < book_count; i++) {
            fprintf(file, "%d,%s,%s,%.2f\n", 
                library[i].BI,
                library[i].Book_name,
                library[i].Author_name,
                library[i].price);
        }
        fclose(file);
    }
}

void read_customers_from_file() {
    FILE *file = fopen(CUSTOMER_FILE, "r");
    if (file) {
        fscanf(file, "%d\n", &customerCount);
        for(int i = 0; i < customerCount; i++) {
            fscanf(file, "%d,%[^,],%[^\n]\n", 
                &customers[i].uniqueID,
                customers[i].username,
                customers[i].password);
        }
        fclose(file);
    }
}

void write_customers_to_file() {
    FILE *file = fopen(CUSTOMER_FILE, "w");
    if (file) {
        fprintf(file, "%d\n", customerCount);
        for(int i = 0; i < customerCount; i++) {
            fprintf(file, "%d,%s,%s\n", 
                customers[i].uniqueID,
                customers[i].username,
                customers[i].password);
        }
        fclose(file);
    }
}

// Sidharth S

// Niranjan

int is_duplicate_book_id(int Book_id){
    for(int i=0;i<book_count;i++){
        if(library[i].BI==Book_id){
            return 1;
        }
    }
    return 0;
}

void Add_Book() {
    if (book_count >= MAX_BOOKS) {
        printf("\033[1;31mLibrary is full. Cannot add more books.\033[0m\n");
        return;
    }

    struct Book *new_book = &library[book_count];

    printf("\033[1;34mEnter Author name: \033[0m");
    getchar();  
    scanf("%[^\n]%*c", new_book->Author_name);  

    printf("\033[1;34mEnter Book name: \033[0m");
    scanf("%[^\n]%*c", new_book->Book_name);  

    printf("\033[1;34mEnter Book ID: \033[0m");
    while (1) {
        if (scanf("%d", &new_book->BI) != 1 || new_book->BI<=0) {
            printf("\033[1;31mInvalid input for Book ID. Please enter a valid number: \033[0m");
        } 
        else if(is_duplicate_book_id(new_book->BI)){
            printf("\033[1;31mError: Book ID %d already exists. Please enter a unique Book ID: \033[0m", new_book->BI);
        }
        else {
            break;
        }
    }

    printf("\033[1;34mEnter price: \033[0m");
    while (1) {
        if (scanf("%f", &new_book->price) != 1 || new_book->price <= 0) {
            printf("\033[1;31mInvalid price input. Please enter a positive number: \033[0m");
        } else {
            break;
        }
    }

    book_count++;
    printf("\033[1;32mBook added successfully!\033[0m\n");
}


void List_Book() {
    if (book_count == 0) {
        printf("\033[1;31mNo books available in the library.\033[0m\n");
        return;
    }

    printf("\033[1;36mAvailable Books:\033[0m\n");
    for (int i = 0; i < book_count; i++) {
        printf("\033[1;33m%d)\n",i+1);
        printf("\033[1;33mAuthor name:\033[0m %s\n", library[i].Author_name);
        printf("\033[1;33mBook name:\033[0m %s\n", library[i].Book_name);
        printf("\033[1;33mBook ID:\033[0m %d\n", library[i].BI);
        printf("\033[1;33mBook Price:\033[0m %.2f\n\n", library[i].price);
    }
}

void Delete_Book(char Book_T[]) {
    int found = 0;

    for (int i = 0; i < book_count; i++) {
        if (strcasecmp(library[i].Book_name, Book_T) == 0){

            found = 1;
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j + 1];
            }
            book_count--;
            printf("\033[1;32mBook with name %s deleted successfully!\033[0m\n", Book_T);
            break;
        }
    }

    if (!found) {
        printf("\033[1;31mBook with name %s not found.\033[0m\n", Book_T);
    }
}

// Niranjan

// Shivanand

void Search_Book(char Book_T[]) {
    int found = 0;

    for (int i = 0; i < book_count; i++) {
        if (strcasecmp(library[i].Book_name, Book_T) == 0) {
            found = 1;
            printf("\033[1;36mBook found:\033[0m\n");
            printf("\033[1;33mAuthor name:\033[0m %s\n", library[i].Author_name);
            printf("\033[1;33mBook name:\033[0m %s\n", library[i].Book_name);
            printf("\033[1;33mBook ID:\033[0m %d\n", library[i].BI);
            printf("\033[1;33mBook Price:\033[0m %.2f\n", library[i].price);
            break;
        }
    }

    if (!found) {
        printf("\033[1;31mBook with name %s not found.\033[0m\n", Book_T);
    }
}

void Borrow_Book(char Book[]) {
    int is_there = 0;

    for (int i = 0; i < book_count; i++) {
        if (strcasecmp(library[i].Book_name, Book) == 0) {
            is_there = 1;
            for (int j = 0; j < borrowed_count; j++) {
                if (strcasecmp(mylibrary[j].Book_name, Book) == 0) {
                    printf("\033[1;31mThe book \"%s\" is already borrowed.\033[0m\n", Book);
                    return;
                }
            }

            mylibrary[borrowed_count] = library[i];
            for (int j = i; j < book_count - 1; j++) {
                library[j] = library[j+1];
            }
            book_count--;

            borrowed_count++;
            printf("\033[1;32mBook \"%s\" borrowed successfully.\033[0m\n", Book);
            break;
        }
    }

    if (!is_there) {
        printf("\033[1;31mBook with name \"%s\" not found.\033[0m\n", Book);
    }
}

void Return_Book(char Book[]){
    int is_there = 0;

    for(int i = 0; i < borrowed_count; i++){
        if(strcasecmp(mylibrary[i].Book_name, Book) == 0){
            is_there = 1;
            
            for(int j = 0; j < book_count; j++){
                if(strcasecmp(library[j].Book_name, Book) == 0){
                    printf("\033[1;31mThe book \"%s\" is already in the library.\033[0m\n", Book);
                    return;
                }
            }
            
            library[book_count] = mylibrary[i];

            for (int j = i; j < borrowed_count - 1; j++) {
                mylibrary[j] = mylibrary[j+1];
            }
            borrowed_count--;
            book_count++;
            
            printf("\033[1;32mBook \"%s\" returned successfully.\033[0m\n", Book);
            return;
        }
    }

    if (!is_there) {
        printf("\033[1;31mBook with name \"%s\" is not borrowed yet.\033[0m\n", Book);
    }
}

void myLibrary() {
    if (borrowed_count == 0) {
        printf("\033[1;31mNo books have been borrowed yet.\033[0m\n");
        return;
    }

    printf("\033[1;36mList of Books Borrowed:\033[0m\n");
    for (int i = 0; i < borrowed_count; i++) {
        printf("\033[1;33m%d) \033[0m%s\n", i + 1, mylibrary[i].Book_name);
    }
}

// Shivanand

// Sidharth P

int choose_role() {
    int choic1;
    printf("\033[1;36m===========================================================\033[0m\n");
    printf("\033[1;32mWELCOME TO MY LIBRARY MANAGEMENT SYSTEM\033[0m\n");
    printf("\033[1;36m===========================================================\033[0m\n");
    printf("\033[1;34mWhich one are you?\033[0m\n");
    printf("\033[1;33m1) Admin\033[0m\n");
    printf("\033[1;33m2) Customer\033[0m\n");
    printf("\033[1;33m3) Exit\033[0m\n");
    printf("\033[1;34mEnter your choice: \033[0m");
    while (1) {
        if (scanf("%d", &choic1) != 1 || choic1 < 1 || choic1 > 3) {
            printf("\033[1;31mInvalid choice. Please enter a number between 1 and 3: \033[0m");
            while (getchar() != '\n');  
        } else {
            break;
        }
    }
    return choic1;
}

void signUp() {
    if (customerCount >= MAX_CUSTOMERS) {
        printf("Customer limit reached. Cannot register more customers.\n");
        return;
    }

    struct Customer newCustomer;
    newCustomer.uniqueID = customerCount + 1000; 

    printf("Enter username: ");
    scanf("%s", newCustomer.username);

    printf("Enter password: ");
    scanf("%s", newCustomer.password);

    customers[customerCount] = newCustomer;
    customerCount++;

    printf("Sign-up successful! Your unique ID is: %d\n", newCustomer.uniqueID);
}

void admin_login(){
    char user[10], password[10];
    int login_attempts=3;
    char olduser_name[20] = "Admin123";
    char old_password[20] = "985123";

    printf("\033[1;36m\n ADMIN LOGIN PAGE \033[0m\n");

    while(login_attempts!=0){
        printf("\033[1;32m\nEnter username:\033[0m");
        scanf("%s", user);
        printf("\033[1;32mEnter password:\033[0m");
        scanf("%s", password);
       if((strcmp(olduser_name, user)==0 && strcmp(old_password, password)==0)){
        printf("\nLogged In Successfully!\n");
        break;
       } 
       else{
        login_attempts--;
        printf("\033[1;31mInvalid Username or password. %d attempts remaining.\033[0m\n", login_attempts);
       }
    }

    if(login_attempts==0){
        printf("\033[1;33mToo many failed attempts. Please try next time!\033[0m\n");
        exit(0);
    }
}

void customer_logIn() {
    int id;
    char username[50], password[50];

    printf("\033[1;32m\nEnter your unique ID:\033[0m");
    scanf("%d", &id);

    printf("\033[1;32m\nEnter username:\033[0m");
    scanf("%s", username);

    printf("\033[1;32mEnter password:\033[0m");
    scanf("%s", password);
    
    if(id-1000 < customerCount && id>=1000){
        if (customers[id-1000].uniqueID == id &&
            strcmp(customers[id-1000].username, username) == 0 &&
            strcmp(customers[id-1000].password, password) == 0) {
            printf("Login successful! Welcome, %s.\n", username);
            return;
        }
    }
    printf("Invalid credentials. Please try again.\n");
    main();
}

int menu_admin() {
    int choice;
    while (1) {
        printf("\033[1;32m\nADMIN\033[0m\n");
        printf("\033[1;36m\n1: Add Book\033[0m");
        printf("\033[1;36m\n2: Delete Book\033[0m");
        printf("\033[1;36m\n3: List Books\033[0m");
        printf("\033[1;36m\n4: Logout\033[0m");
        printf("\033[1;36m\n5: Exit Program\033[0m");
        printf("\n\n\033[1;34mEnter your choice: \033[0m");
        
        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 5) {
            printf("\033[1;36m===========================================================\033[0m\n");
            return choice;
        } else {
            printf("\033[1;31mInvalid choice. Please enter a number between 1 and 5.\033[0m\n");
            while (getchar() != '\n'); 
        }
    }
}

int menu_customer() {
    int choice;
    while (1) {
        printf("\033[1;32m\nCUSTOMER\033[0m\n");
        printf("\033[1;36m\n1: List the Books\033[0m");
        printf("\033[1;36m\n2: Search Books by Name\033[0m");
        printf("\033[1;36m\n3: Borrow a Book\033[0m");
        printf("\033[1;36m\n4: Return a Book\033[0m");
        printf("\033[1;36m\n5: My Library\033[0m");
        printf("\033[1;36m\n6: Logout\033[0m");
        printf("\033[1;36m\n7: Exit Program\033[0m");
        printf("\n\n\033[1;34mEnter your choice: \033[0m");

        if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 7) {
            printf("\033[1;36m===========================================================\033[0m\n");
            return choice;
        } else {
            printf("\033[1;31mInvalid choice. Please enter a number between 1 and 7.\033[0m\n");
            while (getchar() != '\n'); 
        }
    }
}

// Sidharth P

int main() {
    char Book_title[50];

    read_books_from_file();
    read_customers_from_file();

    int choic1 = choose_role();
    
    if (choic1 == 1) {
        admin_login();
    } 
    else if (choic1 == 2) {
        int choice;
        while (1) {
            printf("\033[1;32m\n1. Sign Up\n2. Log In\n3. Exit\033[0m\n\n");
            printf("\033[1;32mEnter your choice:\033[0m ");
            
            if (scanf("%d", &choice) == 1) {
                if (choice == 1) {
                    signUp();
                    break;
                } else if (choice == 2) {
                    customer_logIn();
                    break;
                } else if (choice == 3) {
                    main();  
                    break;
                } 
            } else {
                printf("\033[1;31mInvalid input. Please enter a numeric input.\033[0m\n");
                while (getchar() != '\n'); 
            }
        }
    }


    while (1) {
        if (choic1 == 1) {
            switch (menu_admin()) {
                case 1:
                    Add_Book();
                    break;
                case 2:
                    printf("\033[1;34mEnter the Book name to delete: \033[0m");
                    getchar();
                    scanf("%[^\n]%*c", Book_title);
                    Delete_Book(Book_title);
                    break;
                case 3:
                    List_Book();
                    break;
                case 4:
                    choic1 = choose_role();
                     if(choic1==1){
                        admin_login();
                    }else if(choic1==2){
                        int choice;
                        while (1) {
                            printf("\033[1;32m\n1. Sign Up\n2. Log In\n3. Exit\033[0m\n\n");
                            printf("\033[1;32mEnter your choice:\033[0m ");
                            
                            if (scanf("%d", &choice) == 1) {
                                if (choice == 1) {
                                    signUp();
                                    break;
                                } else if (choice == 2) {
                                    customer_logIn();
                                    break;
                                } else if (choice == 3) {
                                    main();
                                    break;
                                } 
                                } else {
                                    printf("\033[1;31mInvalid input. Please enter a numeric input.\033[0m\n");
                                    while (getchar() != '\n'); 
                            }
                        }
                    }
                    break;
                case 5:
                    write_books_to_file();
                    write_customers_to_file();
                    printf("\033[1;32mExiting program. Goodbye!\033[0m\n");
                    return 0;
                default:
                    printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
            }
        } else if (choic1 == 2) {
            switch (menu_customer()) {
                case 1:
                    List_Book();
                    break;
                case 2:
                    printf("\033[1;34mEnter the Book name to search: \033[0m");
                    getchar();
                    scanf("%[^\n]%*c", Book_title);
                    Search_Book(Book_title);
                    break;
                case 3:
                    printf("\033[1;34mEnter the Book name to borrow: \033[0m");
                    getchar();
                    scanf("%[^\n]%*c", Book_title);
                    Borrow_Book(Book_title);
                    break;
                case 4:
                    printf("\033[1;34mEnter the Book name to return: \033[0m");
                    getchar();
                    scanf("%[^\n]%*c", Book_title);
                    Return_Book(Book_title);
                    break;
                case 5:
                    myLibrary();
                    break;
                case 6:
                    choic1 = choose_role();
                     if(choic1==1){
                        admin_login();
                    }else if(choic1==2){
                        int choice;
                        while (1) {
                            printf("\033[1;32m\n1. Sign Up\n2. Log In\n3. Exit\033[0m\n\n");
                            printf("\033[1;32mEnter your choice:\033[0m ");
                            
                            if (scanf("%d", &choice) == 1) {
                                if (choice == 1) {
                                    signUp();
                                    break;
                                } else if (choice == 2) {
                                    customer_logIn();
                                    break;
                                } else if (choice == 3) {
                                    main();
                                    break;
                                } 
                                } else {
                                    printf("\033[1;31mInvalid input. Please enter a numeric input.\033[0m\n");
                                    while (getchar() != '\n'); 
                            }
                        }
                    }
                    break;
                case 7:
                    write_books_to_file();
                    write_customers_to_file();
                    printf("\033[1;32mExiting program. Goodbye!\033[0m\n");
                    return 0;
                default:
                    printf("\033[1;31mInvalid choice. Please try again.\033[0m\n");
            }
        } else {
            printf("\033[1;31mInvalid role selected. Exiting program.\033[0m\n");
            return 0;
        }
    }
}
