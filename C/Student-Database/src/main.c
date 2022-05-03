#include "../include/HashMap.h"

#define printfString(format, args...) fprintf(stdout, format, args)
#define printString(string) fprintf(stdout, "%s\n", string)
#define printCmd(string) fprintf(stdout, "$ %s\n-> ", string)

#define DEVIDER "=============================="

static Student *students = NULL;

int readInt() {
    // Terminate all \n character in stdout, if it was printed right before calling this function
    scanf("\n");
    int invalid = 0;
    int result = 0;
    char current = '-';
    while (1) {
        scanf("%c", &current);
        if (current == '\n')
            break;
        current -= '0';
        if (current >= 0 && current <= 9)
            result = (result * 10) + current;
        else
            invalid = 1;
    }
    if (invalid)
        result = 0;
    return result;
}

void readLine(int totalCharsToRead, char *cache) {
    // Terminate all \n character in stdout, if it was printed right before calling this function
    scanf("\n");
    char current = '-';
    for (int i = 0; i < totalCharsToRead; i++) {
        scanf("%c", &current);
        if (current == '\n') {
            cache[i] = '\0';
            // Trimming spaces from right side
            while (cache[--i] == ' ') {
                cache[i] = '\0';
            }
            break;
        }
        cache[i] = current;
    }
}

void printStudent(Student student) {
    printfString("     ID : %d\n   Name : %s\nAddress : %s\n    Age : %d\n    GPA : %.2f\n",
        student.id, student.name, student.address, student.age, student.gpa);
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
		        	if (current -> id != 0) {
		        	    studentCount++;
		        	    printStudent(*current);
                        printString(DEVIDER);
		        	}
			        current = current -> next;
	        	}
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printfString("Total %d students found in database\n", studentCount);
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
    } else if (students[hash_value].next != NULL) {
        Student *current = students[hash_value].next;
        while (current != NULL) {
            if (current -> id == id) {
                student = current;
                studentNotFound = 0;
            }
            current = current -> next;
        }
    }

    if (studentNotFound) {
        printString("Student not found");
    } else if (student != NULL) {
        printCmd("Enter Name");
        readLine(name_size, student -> name);
        printCmd("Enter Address");
        readLine(address_size, student -> address);
        GetStudentAge: {
            printCmd("Enter Age");
            student -> age = readInt();
        }
        if (student -> age == 0) {
            printString("Invalid Age");
            goto GetStudentAge;
        }
        GetStudentGPA: {
            printCmd("Enter GPA");
            scanf("%lf", &(student -> gpa));
        }
        if (student -> gpa == 0.0) {
            printString("Invalid GPA");
            goto GetStudentGPA;
        }
        printString("Data Updated");
    }
}

void replaceStudent(Student *one, Student *two) {
    if (two != NULL) {
        one -> id = two -> id;
        strcpy(one -> name, two -> name);
        strcpy(one -> address, two -> address);
        one -> age = two -> age;
        one -> gpa = two -> gpa;
        one -> next = two -> next;
    } else {
        one -> id = 0;
        one -> name[0] = '\0';
        one -> address[0] = '\0';
        one -> age = 0;
        one -> gpa = 0.0;
    }
        
}

void deleteStudent() {
    int id, hash_value, studentNotFound = 1;
    printCmd("Enter Student ID");
    id = readInt();

    hash_value = hash(id);

    if (students[hash_value].id == id) {
        studentNotFound = 0;
        replaceStudent(&students[hash_value], students[hash_value].next);
    } else if (students[hash_value].next != NULL) {
        Student *previous = &students[hash_value];
        Student *current = students[hash_value].next;
        while (current != NULL) {
            if (current -> id == id) {
                studentNotFound = 0;
                previous -> next = current -> next;
            }
            previous = current;
            current = current -> next;
        }
    }

    if (studentNotFound)
        printString("Student not found");
    else
        printString("Student deleted from database");
}

int compareName(char *first, char *second) {
    char *found = strstr(first, second);
    
    if (found == NULL)
        return 0;
    else {
        return 1;
    }
}

void searchStudentName() {
    int noStudent = 1, firstDivider = 1, studentCount = 0;
    char name[name_size];
    printCmd("Enter Student Name");
    readLine(name_size, name);

    for (int i = 0; i < table_size; i++) {
        if (students[i].id != 0) {
            if (compareName(students[i].name, name)) {
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
		        	if (compareName(current -> name, name)) {
		        	    noStudent = 0, studentCount++;
		        	    if (firstDivider) {
                            firstDivider = 0;
                            printString(DEVIDER);
                        }
		        	    printStudent(*current);
                        printString(DEVIDER);
		        	}
			        current = current -> next;
	        	}
            }
        }
    }
    if (noStudent)
        printString("No Student Found");
    else
        printfString("Total %d students found with given name\n", studentCount);
}

void searchStudentAge() {
    int noStudent = 1, firstDivider = 1, studentCount = 0, age;
    GetStudentAge: {
        printCmd("Enter Age");
        age = readInt();
    }
    if (age == 0) {
        printString("Invalid Age");
        goto GetStudentAge;
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
                if (current -> age == age) {
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
        printfString("Total %d students found with given age\n", studentCount);
}

void searchStudentID() {
    int id;
    printCmd("Enter Student ID");
    id = readInt();

    Student student = getStudent(students, id);
    if (student.id == 0)
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

    GetStudentID: {
        printCmd("Enter Student ID");
        id = readInt();
    }
    if (getStudent(students, id).id != 0) {
        printString("Student ID Exists");
        goto GetStudentID;
    } else if (id == 0) {
        printString("Invalid ID");
        goto GetStudentID;
    }
    printCmd("Enter Name");
    readLine(name_size, name);
    printCmd("Enter Address");
    readLine(address_size, address);
    GetStudentAge: {
        printCmd("Enter Age");
        age = readInt();
    }
    if (age == 0) {
        printString("Invalid Age");
        goto GetStudentAge;
    }
    GetStudentGPA: {
        printCmd("Enter GPA");
        scanf("%lf", &gpa);
    }
    if (gpa == 0.0) {
        printString("Invalid GPA");
        goto GetStudentGPA;
    }

    putStudent(students, id, name, address, age, gpa);
    printString("Student Added To Database");
}

/** Debugging functions **/
void test() {
    putStudent(students, 12, "Rifat", "Durgapur", 17, 4.63);
    putStudent(students, 538, "Mahin", "Ashulia", 17, 5.00);
    putStudent(students, 801, "Rahim", "Kathgora", 18, 4.29);
    putStudent(students, 1064, "Mahin", "Kathgora", 18, 5.00);
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

int main() {
    char command[11];
    students = createDatabase();
    // Comment out below two lines
    test(); 
    printString("Running Student Database CRUD Application");
    Executive : {
        printCmd("Enter Command");
        readLine(11, command);
        if (!strcmp(command, "create"))
            createStudent();
        else if (!strcmp(command, "update"))
            updateStudent();
        else if (!strcmp(command, "search id"))
            searchStudentID();
        else if (!strcmp(command, "search name"))
            searchStudentName();
        else if (!strcmp(command, "search age"))
            searchStudentAge();
        else if (!strcmp(command, "list"))
            listAllStudents();
        else if (!strcmp(command, "delete"))
            deleteStudent();
        else if (!strcmp(command, "clear")) {
            students = createDatabase();
            printString("Database cleared");
        } else if (!strcmp(command, "stop")) {
            printString("Application stopped");
            exit(0);
        } else if (!strcmp(command, "help"))
            printString("create      - Add a student in database\n"
                        "update      - Update a student info in database\n"
                        "search id   - Find a student with specific id\n"
                        "search name - Find a student with similar name\n"
                        "search age  - Find all students with given age\n"
                        "delete      - Delete a student from database\n"
                        "list        - List of all students in database\n"
                        "clear       - Clear students database\n"
                        "stop        - Stop this application");
        else
            printString("Unknown command");
    }
    goto Executive;
    return 0;
}