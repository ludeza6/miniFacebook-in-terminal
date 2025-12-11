/********* main.c ********
*/



#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "a3_functions.h"
#include "a3_nodes.h"

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }

    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);
    
    fclose(csv_file);

    unsigned short int menu_opt;
    bool running = true;
    char u_name[30]; // Declare u_name here once for all cases

    do {
        printf("\nWelcome!\n");
        print_menu();
        fscanf(stdin, "%hd", &menu_opt);
        
        // Handle Exit immediately
        if (menu_opt == 6){
            printf("Goodbye! See you next time!");
            running = false;
        }
        else if (menu_opt < 1 || menu_opt > 6){
            printf("Error: Invalid option. Please select a valid option from the menu!\n");
        }
        else {
            clear_user_input(); 
            
            switch(menu_opt){
                case 1: 
                    {
                        char p_word[15]; // Declare variables before the case label
                        printf("Enter a username: ");
                        get_string_input(u_name, sizeof(u_name));

                        if (find_user(users, u_name) != NULL){
                            printf("Error: Username already exists! Please use a different username.\n");
                        } else {
                            clear_user_input();
                            printf("Enter a password up to 14 characters long: ");
                            get_string_input(p_word, sizeof(p_word));

                            // Validate password length
                            while (strlen(p_word) < 8){
                                printf("Error: Password length cannot be shorter than 8. Please try again: ");
                                get_string_input(p_word, sizeof(p_word));
                            }

                            users = add_user(users, u_name, p_word); 
                        }
                    }
                    break;

                case 2: 
                    {
                        char old_pw[15], new_pw[15]; // Declare variables before the case label
                        printf("Enter a username to update their password: ");
                        get_string_input(u_name, sizeof(u_name));

                        user_t *target = find_user(users, u_name);

                        if (target == NULL){
                            printf("Error: Username does not exist!\n");
                        } else {
                            printf("Enter the current password: ");
                            get_string_input(old_pw, sizeof(old_pw));

                            if (strcmp(target->password, old_pw) == 0){
                                printf("Enter a new password up to 14 characters long: ");
                                get_string_input(new_pw, sizeof(new_pw));

                                while (strlen(new_pw) < 8){
                                    printf("Error: Password length cannot be shorter than 8. Please try again: ");
                                    get_string_input(new_pw, sizeof(new_pw));
                                }
                                change_user_password(users, u_name, new_pw);
                            } else {
                                printf("Error: No match was found for the input password!\n");
                            }
                        }
                    }
                    break;

                case 3: 
                    {
                        printf("Enter a username to manage their posts: ");
                        get_string_input(u_name, sizeof(u_name));

                        user_t *target = find_user(users, u_name);
                        
                        if (target == NULL) {
                            printf("Error: Username does not exist!\n");
                        } else {
                            printf("-------------------------------------------\n");
                            printf("Managing %s's posts\n", u_name);
                            printf("-------------------------------------------\n");
                            
                            if (target->posts == NULL){
                                printf("Note: There are no posts available for %s\n", u_name);
                            }

                            unsigned short int sub_choice;
                            bool in_submenu = true;

                            // Submenu loop
                            while (in_submenu){
                                print_posts_menu();
                                fscanf(stdin, "%hd", &sub_choice);
                                clear_user_input();

                                if (sub_choice == 1){ 
                                    char content[250];
                                    printf("Enter your post content: ");
                                    scanf(" %[^\n]s", content); // Alternative to fgets for variety
                                    add_post(target, content);
                                    display_all_user_posts(target);
                                } else if (sub_choice == 2){ 
                                    if (delete_post(target)){
                                        display_all_user_posts(target);
                                    } else {
                                        printf("Error: No post to be deleted!\n");
                                    }
                                } else if (sub_choice == 3){ 
                                    in_submenu = false;
                                } else {
                                    printf("Error: Enter a valid choice!\n");
                                }
                            }
                        }
                    }
                    break;

                case 4: 
                    {
                        printf("Enter a username to update their friends: ");
                        get_string_input(u_name, sizeof(u_name));
                        
                        user_t *target = find_user(users, u_name);

                        if (target == NULL){
                            printf("Error: Username does not exist!\n");
                        } else {
                            printf("-------------------------------------------\n");
                            printf("\tManaging %s's friends\n", u_name);
                            printf("-------------------------------------------\n");
                            
                            unsigned short int sub_choice;
                            bool in_submenu = true;

                            while (in_submenu){
                                print_friends_menu();
                                fscanf(stdin, "%hd", &sub_choice);
                                clear_user_input();
                                
                                char friend_name[30];
                                
                                if (sub_choice == 1){ 
                                    printf("Enter a new friend's name: ");
                                    get_string_input(friend_name, sizeof(friend_name));
                                    add_friend(target, friend_name);
                                } else if (sub_choice == 2){ 
                                    printf("List of %s's friends:\n", u_name);
                                    display_user_friends(target);
                                    
                                    printf("Enter a friend's name to delete: ");
                                    get_string_input(friend_name, sizeof(friend_name));

                                    bool exists = false;
                                    // Loop to check existence
                                    for (friend_t *f = target->friends; f != NULL; f = f->next){
                                        if (strcmp(f->username, friend_name) == 0){
                                            exists = true;
                                        }
                                    }

                                    if (exists){
                                        delete_friend(target, friend_name); 
                                        printf("Updated list of %s's friends:\n", u_name);
                                        display_user_friends(target);
                                    } else {
                                        printf("Error: No friend with the name %s was found\n", friend_name);
                                    }
                                } else if (sub_choice == 3){ 
                                    in_submenu = false;
                                } else { 
                                    printf("Error: Enter a valid choice!\n");
                                }
                            }
                        }
                    }
                    break;

                case 5:
                    {
                        printf("Enter a username to display their posts: ");
                        get_string_input(u_name, sizeof(u_name));
                        
                        user_t *target = find_user(users, u_name);
                        if (target == NULL){
                            printf("Error: Username does not exist!\n");
                        } else {
                            display_posts_by_n(target, 3);
                        }
                    }
                    break;
            }
        }
    } while (running);

    teardown(users); // if user selects option 6 (exit)

    return 0;
}

