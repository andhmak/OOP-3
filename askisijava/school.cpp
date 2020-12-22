/* File: school.cpp */

#include <iostream>
#include "school.h"

using namespace std;

// Συναρτήσεις της Person

// Constructor
Person::Person(const char* init_name, short init_floor_num, short init_classroom_num)
:   name(init_name), floor_num(init_floor_num), classroom_num(init_classroom_num), in(false), tiredness(0) { }

// Destructor
Person::~Person() { }

// Συναρτήσεις της Student

// Constructor
Student::Student(const char* init_name, short init_floor_num, short init_classroom_num)
:   Person(init_name, init_floor_num, init_classroom_num)
{
    cout << "A New Student has been created!" << endl;
    cout << get_name() << endl;
    cout << "Floor " << get_floor_num() + 1 << ", classroom " << get_classroom_num() + 1 << endl;
}

// Destructor
Student::~Student() {
}

// Αρχικοποίηση στατικών μελών της Junior

int Junior::lj = 0;

// Αρχικοποίηση στατικών μελών της Senior

int Senior::ls = 0;

// Συναρτήσεις και αρχικοποίηση στατικών μελών της Teacher

int Teacher::lt = 0;

// Constructor
Teacher::Teacher(const char* init_name, short init_floor_num, short init_classroom_num)
:   Person(init_name, init_floor_num, init_classroom_num)
{
    cout << "A New Teacher has been created!" << endl;
    cout << get_name() << endl;
    cout << "Floor " << get_floor_num() + 1 << ", classroom " << get_classroom_num() + 1 << endl;
}

// Destructor
Teacher::~Teacher() {
}

// Συναρτήσεις της Area

// Destructor
Area::~Area() { }

// Αφαιρεί τον μαθητή από τον χώρο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
Student* Area::exit() {
    Student* to_return = student;
    student = NULL;
    return to_return;
}

// Συναρτήσεις της Yard

// Βάζει τον μαθητή/όρισμα στην αυλή
void Yard::enter(Student& new_student) {
    cout << new_student.get_name() << " enters schoolyard!" << endl;
    Area::enter(new_student);
}

// Αφαιρεί τον μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
Student* Yard::exit() {
    Student* exiting = Area::exit();
    cout << exiting->get_name() << " exits schoolyard!" << endl;
    return exiting;
}

// Συναρτήσεις της Stairs

// Βάζει τον μαθητή/όρισμα στο κλιμακοστάσιο
void Stairs::enter(Student& new_student) {
    cout << new_student.get_name() << " enters stairs!" << endl;
    Area::enter(new_student);
}

// Αφαιρεί τον μαθητή από το κλιμακοστάσιο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
Student* Stairs::exit() {
    Student* exiting = Area::exit();
    cout << exiting->get_name() << " exits stairs!" << endl;
    return exiting;
}

// Συναρτήσεις της Corridor

// Βάζει τον μαθητή/όρισμα στον διάδρομο
void Corridor::enter(Student& new_student) {
    cout << new_student.get_name() << " enters corridor!" << endl;
    Area::enter(new_student);
}

// Αφαιρεί τον μαθητή από τον διάδρομο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
Student* Corridor::exit() {
    Student* exiting = Area::exit();
    cout << exiting->get_name() << " exits corridor!" << endl;
    return exiting;
}

// Συναρτήσεις της Classroom

// Constructor
Classroom::Classroom(int init_capacity)
: capacity(init_capacity), students(new Student*[init_capacity]), student_num(0), teacher(NULL)
{
    cout << "A New Classroom has been created!" << endl;
}

// Destructor
Classroom::~Classroom() {
    delete[] students;
}

// Βάζει τον μαθητή/όρισμα στην τάξη
void Classroom::enter(Student& student) {
    if (student_num != capacity) {
        cout << student.get_name() << " enters classroom!" << endl;
        students[student_num] = &student;
        student_num++;
        student.set_in(true);
    }
}

// Αφαιρεί τον τελευταίο μαθητή από την τάξη και επιστρέφει δείκτη σε αυτόν
Student* Classroom::exit() {
    if (student_num == 0) {
        return NULL;
    }
    Student* to_exit = students[student_num - 1];
    cout << to_exit->get_name() << " exits classroom!" << endl;
    to_exit->set_in(false);
    student_num--;
    return to_exit;
}

// Τοποθετεί τον δάσκαλο/όρισμα στην τάξη
void Classroom::place(Teacher& teacher_in) {
    teacher = &teacher_in;
    teacher_in.set_in(true);
}

void Classroom::teacher_out() {
    cout << teacher->get_name() << endl;
    cout << "Floor " << teacher->get_floor_num() + 1 << ", classroom " << teacher->get_classroom_num() + 1 << endl;
    cout << "...teacher is out!" << endl;
    teacher->set_in(false);
}

//Ο δάσκαλος μιας αίθουσας βγαίνει από την αίθουσα αυτή (teacherout), αλλάζοντας τη σχετικήένδειξή του
//να δηλώνει ότι βρίσκεται εκτός του τμήματός του και εκτυπώνοντας τα στοιχεία του καιτο μήνυμα"...teacher is out!".

// Βάζει τον δάσκαλο της τάξης να διδάξει (teach) και τους μαθητές να παρακολουθήσουν (attend) για hours ώρες
void Classroom::operate(int hours) {
    if (teacher != NULL) {
        teacher->teach(hours);
    }
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->attend(hours);
    }
}

// Συνάρτηση εκτύπωσης της Classroom
void Classroom::print(short classroom_number) const {
    cout << "People in class " << classroom_number + 1 << " are: " << endl;
    for (int i = 0 ; i < student_num ; i++) {
        students[i]->print();
    }
    if (teacher != NULL) {
        teacher->print();
    }
}

// Συναρτήσεις της Floor

// Constructor
Floor::Floor(int cclass) {
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i] = new Classroom(cclass);
    }
    cout << "A New Floor has been created!" << endl;
}

// Destructor
Floor::~Floor() {
    for (char i = 0 ; i < 6 ; i++) {
        delete classrooms[i];
    }
}

// Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
void Floor::enter(Student& student) {
    cout << student.get_name() << " enters floor!" << endl;
    corridor.enter(student);
    corridor.exit();
    classrooms[student.get_classroom_num()]->enter(student);
}

Student* Floor::exit() {
    Student* to_exit = NULL;
    for (char i = 0 ; i < 6 ; i++) {
        to_exit = classrooms[i]->exit();
        if (to_exit != NULL) {
            break;
        }
    }
    if (to_exit == NULL) {
        return NULL;
    }
    cout << to_exit->get_name() << " starts exiting!" << endl;
    corridor.enter(*to_exit);
    corridor.exit();
    return to_exit;
}

void Floor::teachers_out() {
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i]->teacher_out();
    }
}

// Λειτουργεί (operate) όλες τις τάξεις του ορόφου για hours ώρες
void Floor::operate(int hours) const {
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i]->operate(hours);
    }
}

// Συνάρτηση εκτύπωσης της Floor
void Floor::print(short floor_number) const {
    cout << "Floor number " << floor_number + 1 << " contains: " << endl;
    for (char i = 0 ; i < 6 ; i++) {
        classrooms[i]->print(i);
    }
}

// Συναρτήσεις της School

// Constructor
School::School(int cclass) {
    for (char i = 0 ; i < 3 ; i++) {
        floors[i] = new Floor(cclass);
    }
    cout << "A New School has been created!" << endl;
}

// Destructor
School::~School() {
    for (char i = 0 ; i < 3 ; i++) {
        delete floors[i];
    }
}

// Βάζει τον μαθητή/όρισμα στο σχολείο/στην τάξη του
void School::enter(Student& student) {
    cout << student.get_name() << " enters school!" << endl;
    yard.enter(student);
    yard.exit();
    stairs.enter(student);
    stairs.exit();
    floors[student.get_floor_num()]->enter(student);
}

// Λειτουργεί (operate) όλους τους ορόφους του σχολείου για hours ώρες
void School::operate(int hours) const {
    for (char i = 0 ; i < 3 ; i++) {
        floors[i]->operate(hours);
    }
}

void School::empty() {
    Student* to_exit;
    for (char i = 0 ; i < 3 ; i++) {
        while ((to_exit =  floors[i]->exit()) != NULL) {
            stairs.enter(*to_exit);
            stairs.exit();
            yard.enter(*to_exit);
            yard.exit();
        }
    }
    for (char i = 0 ; i < 3 ; i++) {
        floors[i]->teachers_out();
    }
}

// Συνάρτηση εκτύπωσης της School
void School::print() const {
    cout << "School life consists of: " << endl;
    for (char i = 0 ; i < 3 ; i++) {
        floors[i]->print(i);
    }
}