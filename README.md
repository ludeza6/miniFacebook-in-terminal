# linkedlist-social-network

Overview

This project is a command-line social network management system written in C, designed to demonstrate structured programming, dynamic memory management, and data organization using linked lists.

The application simulates core social network functionality, including user accounts, friend relationships, and post timelines. All data structures are implemented manually without external libraries, with a strong emphasis on correctness, maintainability, and safe memory handling.

This project was developed as part of an undergraduate systems programming course at Carleton University.

**Key Features:
**
- Register users with validation rules
- Update passwords with verification
- Alphabetical insertion of users using linked lists
- Add and remove friends
- Friends stored in sorted linked lists
- Display complete friends lists
- Add posts to a user timeline
- Remove most recent posts (stack-based behavior)
- Display posts fully or in configurable chunks
- Loads initial user data from a CSV file
- Automatically constructs internal data structures on startup
- All nodes dynamically allocated
- Explicit cleanup of all allocated memory on program exit
- Designed to avoid memory leaks and dangling pointers


**Technical Details
**

Language: C

Core Concepts:
- Singly linked lists
- Dynamic memory allocation
- Pointer manipulation
- Modular program design (.c / .h separation)
- Manual memory management

**Input Format:
**
CSV file (user_details.csv) containing user records
Friends and posts are optional and inserted into sorted structures automatically

**Build and Run
**
Compile the program using gcc:
gcc -g *.c -o A03

Run the executable:
./A03

Ensure user_details.csv is located in the same directory as the executable.

**Purpose and Learning Outcomes
**
This project was created to strengthen understanding of:
- Low-level data structures
- Structured program design
- Debugging and validation
- Memory-safe coding practices in C
