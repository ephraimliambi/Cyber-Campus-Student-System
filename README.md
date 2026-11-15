# CYBER CAMPUS - Student Management System

A simple Student Management System built in C. Built while learning C from scratch.

## What It Does
- Add Student with Full Name, ID, Marks for C Prog, Math, Cyber
- View All Students in a clean table
- Search Student by ID (ID is unique - Primary Key)
- Calculate Class Average & Find Topper
- Save to File (`students.txt`) - Data survives after closing
- Load from File - Bring data back

## What I Learned
- "struct" to group student data
- Functions + Pointers: "int *count' when we CHANGE count, "int count" when we only READ
- "fgets()" for Full Name (not "scanf("%s")" which stops at space)
- "getchar()" vs "fgetc(file)" - Keyboard vs File are different!
- "fprintf"/ "fscanf"for File Handling
- The Flag pattern for Search ("found = 0/1")
- The Keep-Best pattern for Topper ("topperIndex")

## How To Run
```bash
gcc main.c -o student_system
./student_system
