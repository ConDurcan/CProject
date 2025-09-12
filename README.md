Fleet Management System
This is a console-based application written in C for managing a fleet of vehicles. The program uses a linked list data structure to store and manipulate machine data, which includes details such as chassis number, make, model, and service history. The system supports data persistence by saving and loading all records to and from a local file.

Features
Vehicle Management: Add, search for, update, and delete individual vehicle records.

Persistent Storage: All fleet data is automatically saved to a local file (fleet.txt) upon exit and loaded when the program starts.

User Authentication: A simple login system with a hidden password input to secure access.

Data Reporting: Generate statistics on vehicle breakdowns and a comprehensive report of all machine details to a text file (report.txt).

Data Sorting: View all machines sorted in ascending order of their current value.

Technologies Used
C: The core programming language used to build the application logic.

Linked Lists: The primary data structure for efficient storage and management of vehicle records.

File I/O: Utilizes C standard library functions to read from and write data to files.

How to Run
Compile the code:
Use a C compiler, such as GCC, to compile the source file.

gcc -o main main.c

Run the executable:
Execute the compiled file from your terminal.

./main

Log In:
Upon first run, you will be prompted to create a username and password. On subsequent runs, you will use these credentials to log in.

Author
ConDurcan
Conor Durcan - G00435598

https://github.com/ConDurcan
