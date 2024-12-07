#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_USERS 100
struct Book {
    int BI;
    char Book_name[50];
    char Author_name[50];
    float price;
};

struct Book library[MAX_BOOKS];
struct Book mylibrary[50];
int book_count = 0;
int borrowed_count = 0; 

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
            while (getchar() != '\n'); 
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
            while (getchar() != '\n');
        } else {
            break;
        }
    }

    book_count++;
    printf("\033[1;32mBook added successfully!\033[0m\n");
}

void Books(){
    strcpy(library[0].Author_name,"JK Rowling");
    strcpy(library[0].Book_name,"Fantastic Beasts and where to Find Them");
    library[0].BI = 1011;
    library[0].price = 1200;

    strcpy(library[1].Author_name,"Matthew Reinhart ");
    strcpy(library[1].Book_name,"Harry Potter: A Pop-Up Guide to Hogwarts");
    library[1].BI = 6987;
    library[1].price = 6900;

    strcpy(library[2].Author_name,"Daniel H. Nexon, Iver B. Neumann ");
    strcpy(library[2].Book_name,"Prince Prigio");
    library[2].BI = 12345;
    library[2].price = 5000;
    
    strcpy(library[3].Author_name, "George Orwell");
    strcpy(library[3].Book_name, "1984");
    library[3].BI = 2345;
    library[3].price = 799.00;
    
    strcpy(library[4].Author_name, "J.R.R. Tolkien");
    strcpy(library[4].Book_name, "The Hobbit");
    library[4].BI = 6789;
    library[4].price = 999.00;
    
    strcpy(library[5].Author_name, "F. Scott Fitzgerald");
    strcpy(library[5].Book_name, "The Great Gatsby");
    library[5].BI = 4567;
    library[5].price = 499.00;
    
    strcpy(library[6].Author_name, "Harper Lee");
    strcpy(library[6].Book_name, "To Kill a Mockingbird");
    library[6].BI = 9876;
    library[6].price = 599.00;
    
    strcpy(library[7].Author_name, "Jane Austen");
    strcpy(library[7].Book_name, "Pride and Prejudice");
    library[7].BI = 1234;
    library[7].price = 699.00;
    
    strcpy(library[8].Author_name, "Mary Shelley");
    strcpy(library[8].Book_name, "Frankenstein");
    library[8].BI = 3456;
    library[8].price = 450.00;
    
    strcpy(library[9].Author_name, "Mark Twain");
    strcpy(library[9].Book_name, "Adventures of Huckleberry Finn");
    library[9].BI = 7890;
    library[9].price = 550.00;
    
    strcpy(library[10].Author_name, "Lewis Carroll");
    strcpy(library[10].Book_name, "Alice's Adventures in Wonderland");
    library[10].BI = 1357;
    library[10].price = 620.00;
    
    strcpy(library[11].Author_name, "Ernest Hemingway");
    strcpy(library[11].Book_name, "The Old Man and the Sea");
    library[11].BI = 2468;
    library[11].price = 770.00;
    
    strcpy(library[12].Author_name, "Victor Hugo");
    strcpy(library[12].Book_name, "Les Misérables");
    library[12].BI = 1593;
    library[12].price = 1250.00;
    
    strcpy(library[13].Author_name, "Leo Tolstoy");
    strcpy(library[13].Book_name, "War and Peace");
    library[13].BI = 3690;
    library[13].price = 999.00;
    
    book_count = 14; 
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
        if (strcmp(library[i].Book_name, Book_T) == 0){

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

void Search_Book(char Book_T[]) {
    int found = 0;

    for (int i = 0; i < book_count; i++) {
        if (strcmp(library[i].Book_name, Book_T) == 0) {
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
        if (strcmp(library[i].Book_name, Book) == 0) {
            is_there = 1;
            for (int j = 0; j < borrowed_count; j++) {
                if (strcmp(mylibrary[j].Book_name, Book) == 0) {
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
        if(strcmp(mylibrary[i].Book_name, Book) == 0){
            is_there = 1;
            
            for(int j = 0; j < book_count; j++){
                if(strcmp(library[j].Book_name, Book) == 0){
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

void admin_login(){
    char user[10],password[10];

    int login_attempts=3;

    char olduser_name[20] = "Admin123";
    char old_password[20] = "985123";

    printf("\033[1;36m\n ADMIN LOGIN PAGE \033[0m\n");

    while(login_attempts!=0){
        printf("\033[1;32m\nEnter username:\033[0m");
        scanf("%s",user);
        printf("\033[1;32mEnter password:\033[0m");
        scanf("%s",password);
       if((strcmp(olduser_name,user)==0 && strcmp(old_password,password)==0)){
        printf("\nLogged In SuccessFully!\n");
        break;
       } 
       else{
        login_attempts--;
        printf("\033[1;31mInvalid Username or password. %d attempts remaining.\033[0m\n",login_attempts);
       }
    }

    if(login_attempts==0){
        printf("\033[1;33mToo many failed attempts.Please Try next time!\033[0m\n");
        exit(0);
    }
    
}

void customer_login(){
    char user[10],password[10];

    int login_attempts=3;

    char olduser_name[20] = "Sidhu-985";
    char old_password[20] = "SST2005";

    printf("\033[1;36m\n CUSTOMER LOGIN PAGE \033[0m\n");

    while(login_attempts!=0){
        printf("\033[1;32m\nEnter username:\033[0m");
        scanf("%s",user);
        printf("\033[1;32m\nEnter password:\033[0m");
        scanf("%s",password);
       if((strcmp(olduser_name,user)==0 && strcmp(old_password,password)==0)){
        printf("\nLogged In SuccessFully!\n");
        break;
       } 
       else{
        login_attempts--;
        printf("\033[1;31mInvalid Username or password. %d attempts remaining.\033[0m\n",login_attempts);
       }
    }

    if(login_attempts==0){
        printf("\033[1;33mToo many failed attempts.Please Try next time!\033[0m\n");
        exit(0);
    }
    
}

int menu_admin() {
    int choice;
    printf("\033[1;32m\nADMIN\033[0m\n");
    printf("\033[1;36m\n1: Add Book\033[0m");
    printf("\033[1;36m\n2: Delete Book\033[0m");
    printf("\033[1;36m\n3: List Books\033[0m");
    printf("\033[1;36m\n4: Logout\033[0m");
    printf("\033[1;36m\n5: Exit Program\033[0m");
    printf("\n\n\033[1;34mEnter your choice: \033[0m");
    scanf("%d", &choice);
    printf("\033[1;36m===========================================================\033[0m\n");
    return choice;
}

int menu_customer(){
    int choice;
    printf("\033[1;32m\nCUSTOMER\033[0m\n");
    printf("\033[1;36m\n1: List the Books\033[0m");
    printf("\033[1;36m\n2: Search Books by Name\033[0m");
    printf("\033[1;36m\n3: Borrow a Book\033[0m");
    printf("\033[1;36m\n4: Return a Book\033[0m");
    printf("\033[1;36m\n5: My Library\033[0m");
    printf("\033[1;36m\n6: Logout\033[0m");
    printf("\033[1;36m\n7: Exit Program\033[0m");
    printf("\n\n\033[1;34mEnter your choice: \033[0m");
    scanf("%d", &choice);
    printf("\033[1;36m===========================================================\033[0m\n");
    return choice;
}

int choose_role() {
    int choic1;
    printf("\033[1;36m===========================================================\033[0m\n");
    printf("\033[1;32mWELCOME TO MY LIBRARY MANAGEMENT SYSTEM\033[0m\n");
    printf("\033[1;36m===========================================================\033[0m\n");
    printf("\033[1;34mWhich one are you?\033[0m\n");
    printf("\033[1;38m\n1: Admin\033[0m");
    printf("\033[1;38m\n2: Customer\033[0m\n");
    printf("\n\n\033[1;34mEnter your choice: \033[0m");
    scanf("%d", &choic1);
    printf("\033[1;36m===========================================================\033[0m\n");
    return choic1;
}

int main() {
    char Book_title[50];

    Books();

    int choic1 = choose_role();

    (choic1==1)?admin_login():customer_login();

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
                    (choic1==1)?admin_login():customer_login();
                    break;
                case 5:
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
                    (choic1==1)?admin_login():customer_login();
                    break;
                case 7:
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