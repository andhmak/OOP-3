/* File: main.cpp */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "school.h"
#include "names.h"

using namespace std;

// Συνάρτηση τυχαίας αναδιάταξης μονοδιάστατου πίνακα δεικτών σε Student
void shuffle(Student* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		Student* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

// Συνάρτηση τυχαίας αναδιάταξης μονοδιάστατου πίνακα δεικτών σε Teacher
void shuffle(Teacher* array[], int size) {
	for (int i = 0; i < size; i++) {
		int new_pos = i + rand() / (RAND_MAX / (size - i) + 1);
		Teacher* temp = array[new_pos];
		array[new_pos] = array[i];
		array[i] = temp;
	}
}

int main(int argc, char* argv[]) {
    // αρχικοποίηση με ορίσματα από γραμμή εντολής
    if (argc != 6) {
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    int cclass = atoi(argv[1]), n = atoi(argv[5]);
    if (cclass < 0) {
        cerr << "Class capacity (first argument) must be non-negative" << endl;
        return 2;
    }
    if (n < 0) {
        cerr << "Hours of operation (fifth argument) must be non-negative" << endl;
        return 3;
    }
    Junior::set_lj(atoi(argv[2]));
    Senior::set_ls(atoi(argv[3]));
    Teacher::set_lt(atoi(argv[4]));


    // αρχικοποίηση της rand()
    srand(time(NULL));

    // δημιουργία μαθητών, με τυχαία ονόματα
    const int student_num = cclass*18;
    Student* students[student_num];
    for (int i = 0 ; i < 3 ; i++) {
        for (int j = 0 ; j < 3 ; j++) {
            for (int k = 0 ; k < cclass ; k++) {
                students[cclass*6*i + cclass*j + k] = new Junior(names[i + j % 48], i, j);
            }
        }
        for (int j = 3 ; j < 6 ; j++) {
            for (int k = 0 ; k < cclass ; k++) {
                students[cclass*6*i + cclass*j + k] = new Senior(names[i + j % 48], i, j);
            }
        }
    }

    // δημιουργία δασκάλων, με τυχαία ονόματα
    Teacher* teachers[18];
    for (int i = 0 ; i < 18 ; i++) {
        teachers[i] = new Teacher(names[i % 48], i / 6, i % 6);
    }

    // δημιουργία σχολείου
    School school(cclass);

    // "ανακάτεμα" μαθητών
    shuffle(students, student_num);
    shuffle(teachers, 18);

    // είσοδος μαθητών στο σχολείο
    for (int i = 0 ; i < student_num ; i++) {   // όλοι τους μαθητές
        school.enter(*students[i]);
    }
    
    // τοποθέτηση δασκάλων στο σχολείο
    for (int i = 0 ; i < 18 ; i++) {   // όλοι τους μαθητές
        school.place(*teachers[i]);
    }

    // λειτουργεία του σχολείου
    school.operate(n);

    // εκτύπωση του σχολείου
    school.print();

    // εκκένωση του σχολείου
    school.empty();

    // απελευθέρωση μνήμης μαθητών
    for (int i = 0 ; i < student_num ; i++) {
        delete students[i];
    }

    // απελευθέρωση μνήμης δασκάλων
    for (int i = 0 ; i < 18 ; i++) {
        delete teachers[i];
    }

    return 0;
}