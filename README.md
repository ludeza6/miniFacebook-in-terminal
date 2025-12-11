# linkedlist-social-network

Social Network Management System
**SYSC 2006 – Foundations of Imperative Programming
**
A command-line social-network simulation built in C, featuring user accounts, password management, friends lists, and post timelines all implemented using dynamically allocated linked lists.

This project was created as part of the SYSC 2006 course at Carleton University.

📌 Overview

This program simulates a simplified social-media platform. It loads an initial set of users from a CSV file, then provides an interactive menu allowing you to:
  -  Register users
  -  Update passwords
  -  Add/remove friends
  -  Add/remove posts
  -  Display posts (optionally in chunks)

All data structures are built manually using linked lists, emphasizing memory management, sorting, and pointer manipulation.


**📄 CSV File Format
**
The program expects a file named user_details.csv in the same directory as the executable. Friends and posts are optional, and the CSV loader automatically inserts them into the correct sorted lists.


**🚀 Features
**
✔ Register Users: Users inserted in alphabetical order, password validation (min 8 characters).
✔ Update Passwords: Requires matching current password, safely updates stored value.
✔ Manage Posts: Add posts (pushed onto stack), delete most recent post, display all posts or in groups of N.
✔ Manage Friends: Add friends (sorted insertion), delete friends, display all friends.
✔ Memory-Safe: All nodes are dynamically allocated and freed on program exit.


**🛠 Build & Run
**
Compile and Run with:
gcc -g *.c -o A03
./A03
