#include <stdio.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float marks[3];
    float average;
    char grade;
};

// STEP 2A: Our first REAL function
// STEP 2A - UPDATED: Now takes FULL NAME
void addStudent(struct Student students[], int *count)
{
    printf("\n--- Add New Student ---\n");

    printf("Enter Student ID: ");
    scanf("%d", &students[*count].id);

    // EAT the leftover Enter from ID input
    // If we don't do this, fgets will think name is empty!
    getchar();

    printf("Enter Student FULL Name: ");
    fgets(students[*count].name, 50, stdin);

    // REMOVE the \n that fgets adds at the end
    // "Maydah Nakato\n" becomes "Maydah Nakato"
    students[*count].name[strcspn(students[*count].name, "\n")] = '\0';

    printf("Enter Marks for C Programming: ");
    scanf("%f", &students[*count].marks[0]);

    printf("Enter Marks for Math: ");
    scanf("%f", &students[*count].marks[1]);

    printf("Enter Marks for Cyber: ");
    scanf("%f", &students[*count].marks[2]);

    students[*count].average = (students[*count].marks[0] + students[*count].marks[1] + students[*count].marks[2]) / 3;

    if(students[*count].average >= 70)
        students[*count].grade = 'A';
    else if(students[*count].average >= 60)
        students[*count].grade = 'B';
    else if(students[*count].average >= 50)
        students[*count].grade = 'C';
    else if(students[*count].average >= 40)
        students[*count].grade = 'D';
    else
        students[*count].grade = 'F';

    printf("Student Added! Name = %s, Average = %.2f, Grade = %c\n", students[*count].name, students[*count].average, students[*count].grade);

    (*count)++;
}
// STEP 3: View All Students
void viewAllStudents(struct Student students[], int count)
{
    printf("\n--- All Students ---\n");

    if(count == 0)
    {
        printf("No students added yet! Please add a student first.\n");
        return;
    }

    printf("%-5s %-30s %-10s %-10s %-10s %-10s %-5s \n","ID", "Name", "C prog", "Math", "Cyber", "Average", "Grade");
    printf("----------------------------------------------------------------------\n");

    for(int i = 0; i < count; i++)
    {
        printf("%-5d %-30s %-10.2f %-10.2f %-10.2f %-10.2f %-5c\n",
               students[i].id,
               students[i].name,
               students[i].marks[0],
               students[i].marks[1],
               students[i].marks[2],
               students[i].average,
               students[i].grade);
    }
    printf("Total Students: %d\n", count);
}
// STEP 4A: Search Student by ID
// Why NO pointer for count? We only READ, we don't CHANGE.
void searchStudent(struct Student students[], int count)
{
    printf("\n--- Search Student ---\n");

    if(count == 0)
    {
        printf("No students yet!\n");
        return;
    }

    int searchId;
    printf("Enter ID to search: ");
    scanf("%d", &searchId);

    int found = 0; // 0 = Not found yet

    for(int i = 0; i < count; i++)
    {
        if(students[i].id == searchId)
        {
            printf("FOUND!\n");
            printf("ID: %d, Name: %s, Average: %.2f, Grade: %c\n",
                   students[i].id, students[i].name, students[i].average, students[i].grade);
            found = 1;
            break; // Stop! We found him, no need to check others
        }
    }

    if(found == 0)
    {
        printf("Student with ID %d NOT FOUND!\n", searchId);
    }
}

// STEP 4B: Class Average & Topper
void classStats(struct Student students[], int count)
{
    printf("\n--- Class Average & Topper ---\n");

    if(count == 0)
    {
        printf("No students yet!\n");
        return;
    }

    float total = 0;
    int topperIndex = 0; // Assume first student is topper

    for(int i = 0; i < count; i++)
    {
        total = total + students[i].average;

        // If this student is better than current topper, replace him
        if(students[i].average > students[topperIndex].average)
        {
            topperIndex = i;
        }
    }

    float classAvg = total / count;

    printf("Total Students: %d\n", count);
    printf("Class Average: %.2f\n", classAvg);
    printf("Topper: %s (ID: %d) with Average %.2f, Grade %c\n",
           students[topperIndex].name,
           students[topperIndex].id,
           students[topperIndex].average,
           students[topperIndex].grade);
}
// STEP 5A: Save to File
void saveToFile(struct Student students[], int count)
{
    printf("\n--- Save to File ---\n");

    FILE *file = fopen("students.txt", "w"); // "w" = Write, create new file

    if(file == NULL)
    {
        printf("Error! Could not save file!\n");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        // Save 1 student in 3 lines: ID, Name, Marks+Average+Grade
        fprintf(file, "%d\n", students[i].id);
        fprintf(file, "%s\n", students[i].name);
        fprintf(file, "%.2f %.2f %.2f %.2f %c\n",
                students[i].marks[0],
                students[i].marks[1],
                students[i].marks[2],
                students[i].average,
                students[i].grade);
    }

    fclose(file); // ALWAYS close!
    printf("Saved %d students to students.txt successfully!\n", count);
}

// STEP 5B: Load from File
// Why pointer for count? Because Load CHANGES count! Like Add did.
void loadFromFile(struct Student students[], int *count)
{
    printf("\n--- Load from File ---\n");

    FILE *file = fopen("students.txt", "r"); // "r" = Read

    if(file == NULL)
    {
        printf("No saved file found! Save first.\n");
        return;
    }

    *count = 0; // Start fresh, erase old data in memory

    // Read until file ends. fscanf returns 1 if it read an ID successfully
        while(fscanf(file, "%d", &students[*count].id) == 1)
    {
        fgetc(file); // FIXED: Eat Enter from FILE, not keyboard!

        // Read full name line
        fgets(students[*count].name, 50, file);
        students[*count].name[strcspn(students[*count].name, "\n")] = '\0';

        // Read marks line. SPACE before %c so it gets real Grade!
        fscanf(file, "%f %f %f %f %c",
               &students[*count].marks[0],
               &students[*count].marks[1],
               &students[*count].marks[2],
               &students[*count].average,
               &students[*count].grade);

        (*count)++; // We loaded 1 more
    }

    fclose(file);
    printf("Loaded %d students from students.txt successfully!\n", *count);
}

int main()
{
    struct Student students[100];
    int count = 0;
    int choice;

    do
    {
        printf("\n--- CYBER CAMPUS - STUDENT SYSTEM ---\n");
        printf("1. Add New Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by ID\n");
        printf("4. Calculate Class Average & Topper\n");
        printf("5. Save to File\n");
        printf("6. Load from File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent(students, &count);
                break;
            case 2:
                viewAllStudents(students, count);
                break;
            case 3:
                searchStudent(students, count);
                break;
            case 4:
                classStats(students, count);
                break;
            case 5:
                saveToFile(students, count);
                break;
            case 6:
                loadFromFile(students, &count); // & because Load CHANGES count!
                break;
            case 7:
                printf("Goodbye! Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try 1-7\n");
        }

    } while(choice != 7);

    return 0;
}
