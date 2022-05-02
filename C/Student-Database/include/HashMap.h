#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Student {
	int id, age;
	double gpa;
	struct Student *next;
	char name[20], address[50];
};
typedef struct Student Student;

int databaseSize();

int hash(int key);

Student getStudent(Student *map, int id);

void putStudent(Student *map, int id, char *name, char *address, int age, double gpa);

void clearStudentA(Student *student);

void clearStudent(Student student);

Student *createDatabase();