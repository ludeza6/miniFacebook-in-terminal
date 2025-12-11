/********* a3_functions.c ********
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "a3_functions.h"
#include "a3_nodes.h"
#include <stdbool.h>
#include <ctype.h>


/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu(){
    printf("*********************************************\n");
    printf("MAIN MENU\n");
    printf("*********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user's posts\n");
    printf("6. Exit\n\n");
    printf("Enter your choice: ");
}


/*
   Function that prints the sub menu with a list of options for the user's posts to choose from
*/
void print_posts_menu()
{
    printf("\n1. Add a new post\n");
    printf("2. Remove a post\n");
    printf("3. Return to main menu\n");
    printf("Enter your choice: ");
}


/*
   Function that prints the sub menu with a list of options for the user's friends to choose from
*/
void print_friends_menu(){
    printf("\n1. Add a new friend\n");
    printf("2. Remove a friend\n");
    printf("3. Return to main menu\n");
    printf("Enter your choice: ");
}


/*
   Helper to remove newline
*/
void remove_newline_char(char *str)
{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

/*
   Helper to get input safely
*/
void get_string_input(char *input, int size) 
{
    fgets(input, size, stdin);
    remove_newline_char(input);
}

/*
   Function that searches if the user is available in the database 
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{    
    for (user_t *curr = users; curr != NULL; curr = curr->next) {
        if (strcmp(curr->username, username) == 0) {
            return curr;
        }
    }
    return NULL;
}


/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
    user_t *node_to_add = malloc(sizeof(user_t));
    assert(node_to_add != NULL);

    unsigned short int k = 0;
    while(username[k] != '\0') { // copy username into struct
        node_to_add->username[k] = tolower(username[k]);
        k++;
    }
    node_to_add->username[k] = '\0';

    strcpy(node_to_add->password, password); // copy password into struct

    node_to_add->friends = NULL;
    node_to_add->posts = NULL;
    node_to_add->next = NULL;

    user_t *walker = users;
    user_t *trailer = NULL;

    // Logic to find insertion point
    while (walker != NULL && strcmp(walker->username, node_to_add->username) < 0){
        trailer = walker;
        walker = walker->next;
    }

    if (trailer == NULL){
        // Insert at head
        node_to_add->next = walker;
        printf("****User Added!****\n");
        return node_to_add; // Return new head
    } else {
        // Insert middle or end
        trailer->next = node_to_add;
        node_to_add->next = walker;
        printf("****User Added!****\n");
        return users; // Head hasn't changed
    }
    
    return users;
}




void change_user_password(user_t *users, const char *username, const char *password)
{
    user_t *target = find_user(users, username);
    
    if (target != NULL){
        strcpy(target->password, password);
        printf("****Password Changed!****\n");
    }
}


/*
   Function that adds a post to a user's timeline following a stack.
*/
void add_post(user_t *user, const char *text)
{
    post_t *p = create_post(text);
    // Stack Push operation
    p->next = user->posts;
    user->posts = p;
    printf("****Post Added!****\n");
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
    post_t *new_node = malloc(sizeof(post_t));
    assert(new_node != NULL);
    strcpy(new_node->content, text);
    new_node->next = NULL;
    return new_node;
}




/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user)
{
    if (user->posts == NULL) {
        return false;
    }

    post_t *temp = user->posts;
    user->posts = user->posts->next; // Move head
    free(temp);
    temp = NULL;
    
    return true;
}





/*
   Function that  displays a specific user's posts (All posts)
*/
void display_all_user_posts(user_t *user)
{
    unsigned short int counter = 1;
    post_t *ptr = user->posts;
    
    printf("-------------------------------------------\n");
    printf("\t%s's posts\n", user->username);
    
    while(ptr != NULL) {
        printf("%d - %s\n", counter, ptr->content);
        counter++;
        ptr = ptr->next;
    }
    printf("-------------------------------------------\n");
}


/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *user, const char *friend){
    friend_t *new_f = create_friend(friend);
    friend_t *walker = user->friends;
    friend_t *trailer = NULL;

    // Standard sorted insert logic
    for (; walker != NULL && strcmp(walker->username, new_f->username) < 0; walker = walker->next) {
        trailer = walker;
    }

    if (trailer == NULL){
        new_f->next = user->friends;
        user->friends = new_f;
    } else {
        trailer->next = new_f;
        new_f->next = walker;
    }
    printf("****Friend Added!****\n");
}




/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username){
    friend_t *f_node = malloc(sizeof(friend_t));
    assert(f_node != NULL);
    
    unsigned short int i = 0;
    for (; i < strlen(username); i++) {
        f_node->username[i] = tolower(username[i]);
    }
    f_node->username[i] = '\0';
    f_node->next = NULL;
    return f_node;
}



/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
    friend_t *walker = user->friends;
    friend_t *trailer = NULL;

    while(walker != NULL){
        if (strcmp(walker->username, friend_name) == 0) {
            // Found match
            if (trailer == NULL) {
                user->friends = walker->next;
            } else {
                trailer->next = walker->next;
            }
            free(walker);
            walker = NULL;
            printf("****Friend Deleted!****\n");
            return true;
        }
        trailer = walker;
        walker = walker->next;
    }
    return false;
}


/*
   Function that displays a specific user's friends (All friends)
*/
void display_user_friends(user_t *user)
{
    int count = 1;
    for (friend_t *curr = user->friends; curr != NULL; curr = curr->next) {
         printf("%d - %s\n", count++, curr->username);
    }
}





/*
   Function that displays "number" of posts for a given user.
*/
void display_posts_by_n(user_t *users, int number)
{
    post_t *walker = users->posts;
    if (walker == NULL){
        return;
    }

    int global_count = 1;
    char response;

    while (walker != NULL) 
    {
        // Inner loop: print 'number' of posts
        for (int i = 0; i < number && walker != NULL; i++) {
            printf("%d - %s\n", global_count++, walker->content);
            walker = walker->next;
        }

        if (walker == NULL) {
            printf("All posts have been displayed.\n");
            break; 
        }

        printf("Enter 'y' if you want to display more, else 'n': ");
        response = fgetc(stdin);

        if (tolower(response) == 'n'){
            break;
        }
    }
}



void clear_user_input() 
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}



/*
   Helper to free a specific friend list
*/
void free_user_friends(friend_t *friend_list) 
{
    friend_t *temp;
    while(friend_list != NULL) {
        temp = friend_list;
        friend_list = friend_list->next;
        free(temp);
        temp =NULL;
    }
}

/*
   Helper to free a specific post list
*/
void free_user_posts(post_t *post_list) 
{
    post_t *temp;
    while(post_list != NULL) {
        temp = post_list;
        post_list = post_list->next;
        free(temp);
        temp =NULL;
    }
}

/*
   Function that free all users from the database before quitting facebook.
*/
void teardown(user_t *users){
    user_t *current = users;
    while (current != NULL){
        user_t *next_node = current->next;
        
        // Use aux functions to clean up code structure
        free_user_friends(current->friends);
        free_user_posts(current->posts);

        free(current);
        current =NULL;
        current = next_node;
    }
}


/*
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
