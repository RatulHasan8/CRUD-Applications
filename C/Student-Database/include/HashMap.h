#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define name_size 20
#define address_size 50
#define table_size 263

struct Student {
	int id, age;
	double gpa;
	char name[name_size], address[address_size];
	struct Student *next;
};
typedef struct Student Student;

int databaseSize();

int hash(int key);

Student getStudent(Student *map, int id);

void putStudent(Student *map, int id, char name[name_size], char address[address_size], int age, double gpa);

void clearStudentA(Student *student);

void clearStudent(Student student);

Student *createDatabase();