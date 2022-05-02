#include "HashMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const Student EmptyStudent = {0, 0, 0.0, NULL, "", ""};

int databaseSize() {
    return 263;
}

int hash(int key) {
	return abs(key % databaseSize());
}

Student getStudent(Student *map, int id) {
	int hash_value = hash(id);
	
	if (map[hash_value].id == id) {
		return map[hash_value];
	}
	else if (map[hash_value].next != NULL) {
		Student *current = map[hash_value].next;
		while (current != NULL) {
			if (current -> id == id)
				return *current;
			current = current -> next;
		}
	}
	return EmptyStudent;
}

void putStudent(Student *map, int id, char name[20], char address[50], int age, double gpa) {
	int hash_value = hash(id);
	
	if (map[hash_value].id != id && map[hash_value].id != 0) {
	    Student *tail = malloc(sizeof(Student));
		tail -> id = id;
		strcpy(tail -> name, name);
		strcpy(tail -> address, address);
		tail -> age = age;
		tail -> gpa = gpa;
		tail -> next = map[hash_value].next;
		map[hash_value].next = tail;
	} else {
		map[hash_value].id = id;
		strcpy(map[hash_value].name, name);
		strcpy(map[hash_value].address, address);
		map[hash_value].age = age;
		map[hash_value].gpa = gpa;
	}
}

Student *createDatabase() {
	Student *temp = malloc(databaseSize() * sizeof(Student));
	return temp;
}