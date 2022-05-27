#include "../include/HashMap.h"
#include "../include/custom-stdin.h"

#define printf(format, args...) fprintf(stdout, format, args)
#define printString(string) fprintf(stdout, "%s\n", string)
#define printCmd(string) fprintf(stdout, "$ %s\n-> ", string)

#define DEVIDER "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"

static Student *students = NULL;

void printStudent(Student student) {
    printf("     ID : %d\n", student.id);
    printf("   Name : %s\n", student.name);
    printf("Address : %s\n", student.address);
    printf("    Age : %d\n", student.age);
    printf("    GPA : %.2f\n", student.gpa);
}

void listAllStudents() {
    int studentCount = 0, noStudent = 1, firstDivider = 1;
    for (int i = 0; i < table_size; i++) {
        if (students[i].id != 0) {
            noStudent = 0;
            if (firstDivider) {
                firstDivider = 0;
                printString(DEVIDER);
            }
            studentCount++;
            printStudent(students[i]);
            printString(DEVIDER);
            if (students[i].next != NULL) {
                Student *current = students[i].next;
                while (current != NULL) {
                    if (current->id != 0) {
                        studentCount++;
                        printStudent(*current);
                        printString(DEVIDER);
                    }
                    current = current->next;
                }
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printf("Total %d students found in database\n", studentCount);
}

void updateStudent() {
    int id, hash_value, studentNotFound = 1;
    Student *student = NULL;

    printCmd("Enter Student ID");
    id = readInt();
    hash_value = hash(id);

    if (students[hash_value].id == id) {
        studentNotFound = 0;
        student = &students[hash_value];
    }
    else if (students[hash_value].next != NULL) {
        Student *current = students[hash_value].next;
        while (current != NULL) {
            if (current->id == id) {
                student = current;
                studentNotFound = 0;
            }
            current = current->next;
        }
    }

    if (studentNotFound)
        printString("Student not found");
    else if (student != NULL) {
        printCmd("Enter Name");
        readLine(name_size, student->name);
        printCmd("Enter Address");
        readLine(address_size, student->address);
        while (1) {
            printCmd("Enter Age");
            student->age = readInt();

            if (student->age <= 0)
                printString("Invalid Age");
            else
                break;
        }
        while (1) {
            printCmd("Enter GPA");
            student->gpa = readDouble();

            if (student->gpa <= 0.0)
                printString("Invalid GPA");
            else
                break;
        }
        printString("Data Updated");
    }
}

void replaceStudent(Student *one, Student *two) {
    if (two != NULL) {
        one->id = two->id;
        strcpy(one->name, two->name);
        strcpy(one->address, two->address);
        one->age = two->age;
        one->gpa = two->gpa;
        one->next = two->next;
    }
    else
        *one = (Student){0};
}

void deleteStudent() {
    int id, hash_value, studentNotFound = 1;
    printCmd("Enter Student ID");
    id = readInt();

    hash_value = hash(id);

    if (students[hash_value].id == id) {
        studentNotFound = 0;
        replaceStudent(&students[hash_value], students[hash_value].next);
    }
    else if (students[hash_value].next != NULL) {
        Student *previous = &students[hash_value];
        Student *current = students[hash_value].next;
        while (current != NULL) {
            if (current->id == id) {
                studentNotFound = 0;
                previous->next = current->next;
            }
            previous = current;
            current = current->next;
        }
    }

    if (studentNotFound)
        printString("Student not found");
    else
        printString("Student deleted from database");
}

int match(char *a, char *b, int beginning) {
    if (!beginning && a[-1] != ' ' && a[-1] != '.' && a[-1] != ',')
        return 0;
    while (*b != '\0')
        if (*a++ != *b++)
            return 0;
    return (*a == ' ' || *a == '\0' || *a == ',');
}

int compare(char *base, char *pattern) {
    int matched = match(base, pattern, 1);
    
    while (*base++ != '\0') {
        if (matched)
            return 1;
        matched = match(base, pattern, 0);
    }
    return 0;
}

void searchStudentName() {
    int noStudent = 1, firstDivider = 1, studentCount = 0;
    char name[name_size];
    printCmd("Enter Student Name");
    readLine(name_size, name);

    for (int i = 0; i < table_size; i++) {
        if (students[i].id != 0) {
            if (compare(students[i].name, name)) {
                noStudent = 0, studentCount++;
                if (firstDivider) {
                    firstDivider = 0;
                    printString(DEVIDER);
                }
                printStudent(students[i]);
                printString(DEVIDER);
            }
            if (students[i].next != NULL) {
                Student *current = students[i].next;
                while (current != NULL) {
                    if (compare(current->name, name)) {
                        noStudent = 0, studentCount++;
                        if (firstDivider) {
                            firstDivider = 0;
                            printString(DEVIDER);
                        }
                        printStudent(*current);
                        printString(DEVIDER);
                    }
                    current = current->next;
                }
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printf("Total %d students found with given name\n", studentCount);
}

void searchStudentAddress() {
    int noStudent = 1, firstDivider = 1, studentCount = 0;
    char address [address_size];
    printCmd("Enter Address");
    readLine(address_size, address);

    for (int i = 0; i < table_size; i++) {
        if (students[i].id != 0) {
            if (compare(students[i].address, address)) {
                noStudent = 0, studentCount++;
                if (firstDivider) {
                    firstDivider = 0;
                    printString(DEVIDER);
                }
                printStudent(students[i]);
                printString(DEVIDER);
            }
            if (students[i].next != NULL) {
                Student *current = students[i].next;
                while (current != NULL) {
                    if (compare(current->address, address)) {
                        noStudent = 0, studentCount++;
                        if (firstDivider) {
                            firstDivider = 0;
                            printString(DEVIDER);
                        }
                        printStudent(*current);
                        printString(DEVIDER);
                    }
                    current = current->next;
                }
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printf("Total %d students found with given address\n", studentCount);
}

void searchStudentAge() {
    int noStudent = 1, firstDivider = 1, studentCount = 0, age;
    while (1) {
        printCmd("Enter Age");
        age = readInt();
        if (age <= 0)
            printString("Invalid Age");
        else
            break;
    }

    for (int i = 0; i < table_size; i++) {
        if (students[i].age == age) {
            noStudent = 0, studentCount++;
            if (firstDivider) {
                firstDivider = 0;
                printString(DEVIDER);
            }
            printStudent(students[i]);
            printString(DEVIDER);
        }
        if (students[i].next != NULL) {
            Student *current = students[i].next;
            while (current != NULL) {
                if (current->age == age) {
                    noStudent = 0, studentCount++;
                    if (firstDivider) {
                        firstDivider = 0;
                        printString(DEVIDER);
                    }
                    printStudent(*current);
                    printString(DEVIDER);
                }
                current = current->next;
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printf("Total %d students found with the given age\n", studentCount);
}

void searchStudentID() {
    int id;
    printCmd("Enter Student ID");
    id = readInt();

    Student student = getStudent(students, id);
    if (student.id <= 0)
        printString("Student not found");
    else {
        printString(DEVIDER);
        printStudent(student);
        printString(DEVIDER);
    }
}

void createStudent() {
    int id = 0, age = 0;
    double gpa = 0.0;
    char name[name_size], address[address_size];

    while (1) {
        printCmd("Enter Student ID");
        id = readInt();
        if (getStudent(students, id).id != 0)
            printString("Student ID Exists");
        else if (id <= 0)
            printString("Invalid ID");
        else
            break;
    }
    printCmd("Enter Name");
    readLine(name_size, name);
    printCmd("Enter Address");
    readLine(address_size, address);
    while (1) {
        printCmd("Enter Age");
        age = readInt();
        if (age <= 0)
            printString("Invalid Age");
        else
            break;
    }
    while (1) {
        printCmd("Enter GPA");
        gpa = readDouble();
        if (gpa <= 0.0)
            printString("Invalid GPA");
        else
            break;
    }

    putStudent(students, id, name, address, age, gpa);
    printString("Student Added To Database");
}

/** Debugging functions **/
void test() {
    putStudent(students, 12, "Arif Rahimullah", "Durbin, Gulshan", 17, 4.63);
    putStudent(students, 538, "Mahin Mia", "ST.House, Polton", 17, 5.00);
    putStudent(students, 801, "Rahim Alam", "Karim Bazar, Sazipur", 18, 4.29);
    putStudent(students, 1064, "A.Mahin Begum", "No.1 Gazirchat, Bhairov", 18, 5.00);
}

void randomChar(char name[]) {
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    name[0] = upper[rand() % 25];
    for (int i = 1; i < 10; i++)
        name[i] = lower[rand() % 25];
}

void randomInput() {
    srand(time(0));
    char name[] = "abcdefghij";
    for (int i = 0; i < 2000; i++) {
        randomChar(name);
        putStudent(students, abs((int)(rand() * rand() + rand() / 0.5)), name, "Kathgora", 18, rand() % 4 + 1.9);
    }
}
/** End of debugging functions **/

int main() {
    char command[14];
    Student database[table_size];
    students = createStaticDatabase(database);
    // Comment out the line below, it's meant for debugging purposes
    test();
    printString("Running - Student Database CRUD Application");
    while (1) {
        printCmd("Enter Command");
        readLine(sizeof(command)/sizeof(*command), command);
        if (!strcmp(command, "create"))
            createStudent();
        else if (!strcmp(command, "update"))
            updateStudent();
        else if (!strcmp(command, "search id"))
            searchStudentID();
        else if (!strcmp(command, "search name"))
            searchStudentName();
        else if (!strcmp(command, "search address"))
            searchStudentAddress();
        else if (!strcmp(command, "search age"))
            searchStudentAge();
        else if (!strcmp(command, "list"))
            listAllStudents();
        else if (!strcmp(command, "delete"))
            deleteStudent();
        else if (!strcmp(command, "clear")) {
            clearStaticDatabase(database);
            printString("Database cleared");
        }
        else if (!strcmp(command, "stop")) {
            printString("Application stopped");
            break;
        }
        else if (!strcmp(command, "help"))
            printString("create         - Add a student in database\n"
                        "update         - Update a student info in database\n"
                        "search id      - Find a student with specific id\n"
                        "search name    - Find all students with similar name\n"
                        "search address - Find all students with similar address\n"
                        "search age     - Find all students with same age\n"
                        "delete         - Delete a student from database\n"
                        "list           - List of all students in database\n"
                        "clear          - Clear students database\n"
                        "stop           - Stop this application");
        else
            printString("Unknown command");
    }
    return 0;
}