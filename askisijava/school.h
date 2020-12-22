/* File: school.h */

#include <iostream>
#include <string>

// Κλάση που αναπαριστά έναν άνθρωπο/μέλος σχολείου (σε αυτήν την περίπτωση μαθητή ή καθηγητή)
class Person {
    std::string name;       // όνομα του ανθρώπου
    short floor_num;        // αριθμός ορόφου όπου βρίσκεται η τάξη/προορισμός του
    short classroom_num;    // αριθμός/θέση της τάξης/προορισμού του στον όροφο
    protected:
        bool in;            // αν βρίσκεται μέσα στην τάξη ή όχι
        int tiredness;      // βαθμός κούρασης
    public:
        Person(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        virtual ~Person() = 0;
        void set_in(bool is_in) { in = is_in; }                                     // Mutator
        std::string get_name() const { return name; }                               // +
        short get_floor_num() const { return floor_num; }                           // |  Accessors
        short get_classroom_num() const { return classroom_num; }                   // +
};

// Κλάση που αναπαριστά έναν μαθητή
class Student : public Person {
    public:
        Student(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Student();                                                                 // Destructor (εκτυπώνει και τα δεδομένα του μαθητή)
        virtual void attend(int hours) = 0; // Αυξάνει την κούραση του μαθητή ανάλογα του αριθμού των ορών/όρισμα και του είδους του μαθητή
        void print() const { std::cout << get_name() << ", tiredness: " << tiredness << std::endl; }    // Εκτυπώνει το όνομα του μαθητή
};

// Κλάση που αναπαριστά έναν μαθητή μικρής τάξης
class Junior : public Student {
    static int lj;  // ρυθμός κούρασης μαθητών μικρής τάξης
    public:
        Junior(const char* init_name, short init_floor_num, short init_classroom_num)   // Constructor
        :   Student(init_name, init_floor_num, init_classroom_num) { }
        static void set_lj(int new_lj) { lj = new_lj; }     // Τροποποιεί τον ρυθμό κούρασης των μαθητών μικρής τάξης
        void attend(int hours) { tiredness += lj*hours; }   // Αυξάνει την κούραση του μαθητή ανάλογα τον αριθμό των ορών/όρισμα
                                                            // και τον ρυθμό κούρασης των μαθητών μικρής τάξης
};

// Κλάση που αναπαριστά έναν μαθητή μεγάλης τάξης
class Senior : public Student {
    static int ls;  // ρυθμός κούρασης μαθητών μαγάλης τάξης
    public:
        Senior(const char* init_name, short init_floor_num, short init_classroom_num)   // Constructor
        :   Student(init_name, init_floor_num, init_classroom_num) { }
        static void set_ls(int new_ls) { ls = new_ls; }     // Τροποποιεί τον ρυθμό κούρασης των μαθητών μεγάλης τάξης
        void attend(int hours) { tiredness += ls*hours; }   // Αυξάνει την κούραση του μαθητή ανάλογα τον αριθμό των ορών/όρισμα
                                                            // και τον ρυθμό κούρασης των μαθητών μεγάλης τάξης
};

// Κλάση που αναπαριστά έναν δάσκαλο
class Teacher : public Person {
    static int lt;  // ρυθμός κούρασης δασκάλων
    public:
        Teacher(const char* init_name, short init_floor_num, short init_classroom_num); // Constructor
        ~Teacher();                                                                     // Destructor (εκτυπώνει και τα δεδομένα του δασκάλου)
        static void set_lt(int new_lt) { lt = new_lt; }     // Τροποποιεί τον ρυθμό κούρασης των δασκάλων
        void teach(int hours) { tiredness += lt*hours; }    // Αυξάνει την κούραση του δασκάλου ανάλογα τον αριθμό των ορών/όρισμα
                                                            // και τον ρυθμό κούρασης των δασκάλων
        void print() const { std::cout << "The teacher is: " << get_name() << ", tiredness: " << tiredness << std::endl; }  // Εκτυπώνει το όνομα
};

// Κλάση που αναπαριστά έναν χώρο όπου μπαίνουν/βγαίνουν μαθητές, με έναν μαθητή μέσα την φορά
class Area {
    Student* student;   // δείκτης στον μαθητή που βρίσκεται στον χώρο
    public:
        Area() : student(NULL) { }          // Constructor
        virtual ~Area() = 0;                // Destructor
        void enter(Student& new_student) { student = &new_student; }    // Βάζει τον μαθητή/όρισμα στον χώρο
        Student* exit();        // Αφαιρεί τον μαθητή από τον χώρο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
};

// Κλάση που αναπαριστά μια αυλή
class Yard : public Area {
    public:
        Yard() { std::cout << "A New Yard has been created!" << std::endl; }    // Constructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στην αυλή
        Student* exit();                    // Αφαιρεί τον μαθητή από την αυλή και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
};

// Κλάση που αναπαριστά ένα κλιμακοστάσιο
class Stairs : public Area {
    public:
        Stairs() { std::cout << "New Stairs has been created!" << std::endl; }  // Constructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στο κλιμακοστάσιο
        Student* exit();            // Αφαιρεί τον μαθητή από το κλιμακοστάσιο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
};

// Κλάση που αναπαριστά έναν διάδρομο
class Corridor : public Area {
    public:
        Corridor() { std::cout << "A New Corridor has been created!" << std::endl; }    // Constructor
        void enter(Student& new_student);   // Βάζει τον μαθητή/όρισμα στον διάδρομο
        Student* exit();                // Αφαιρεί τον μαθητή από τον διάδρομο και επιστρέφει δείκτη σε αυτόν, NULL αν δεν υπάρχει μαθητής
};

// Κλάση που αναπαριστά μια τάξη
class Classroom {
    int capacity;       // χωρητικότητα σε μαθητές
    Student** students; // πίνακας μαθητών (δεικτών σε αντικείμενα μαθητών) που βρίσκονται στην τάξη
    Teacher* teacher;   // ο δάσκαλος που βρίσκεται στην τάξη (δείκτης στο αντικείμενο του δασκάλου, αν δεν έχει φτάσει είναι NULL)
    int student_num;    // πλήθος μαθητών που βρίσκονται στην τάξη
    public:
        Classroom(int init_capacity);       // Constructor
        ~Classroom();                       // Destructor
        void enter(Student& student);       // Βάζει τον μαθητή/όρισμα στην τάξη
        Student* exit();                    // Αφαιρεί τον τελευταίο μαθητή από την τάξη και επιστρέφει δείκτη σε αυτόν
        void place(Teacher& teacher_in);    // Θέτει τον δάσκαλο/όρισμα ως τον δάσκαλο της τάξης, ενημερώνοντάς τον πως εισήλθε
        void teacher_out();
        void operate(int hours);            // Βάζει τον δάσκαλο της τάξης να διδάξει (teach) και τους μαθητές να παρακολουθήσουν (attend) για hours ώρες
        void print(short classroom_number) const;   // Εκτυπώνει τους μαθητές και τον δάσκαλο που βρίσκονται στην τάξη
};

// Κλάση που αναπαριστά έναν όροφο
class Floor {
    Classroom* classrooms[6];  // πίνακας τάξεων (δεικτών σε αντικείμενα τάξεων) του ορόφου 
    Corridor corridor;  // ο διάδρομος του ορόφου
    public:
        Floor(int cclass);                  // Constructor
        ~Floor();                           // Destructor
        void enter(Student& student);       // Βάζει τον μαθητή/όρισμα στον όροφο, βάζοντάς τον στον διάδρομο αν χωράει
        Student* exit();
        void place(Teacher& teacher) { classrooms[teacher.get_classroom_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα στον όροφό του,
                                                                                                    // τοποθετώντας τον στην τάξη του
        void teachers_out();
        void operate(int hours) const;  // Λειτουργεί (operate) όλες τις τάξεις του ορόφου για hours ώρες
        void print(short floor_number) const;   // Εκτυπώνει τον διάδρομο και τις τάξεις του ορόφου
};

// Κλάση που αναπαριστά ένα σχολείο
class School {
    Yard yard;          // η αυλή του σχολείου
    Stairs stairs;      // το κλιμακοστάσιο του σχολείου
    Floor* floors[3];   // πίνακας ορόφων (δεικτών σε αντικείμενα ορόφων) του σχολείου
    public:
        School(int cclass); // Constructor
        ~School();          // Destructor
        void enter(Student& student);   // Βάζει τον μαθητή/όρισμα στο σχολείο, πηγαίνοντάς τον μέχρι την τάξη του
        void place(Teacher& teacher) { floors[teacher.get_floor_num()]->place(teacher); }   // Τοποθετεί τον δάσκαλο/όρισμα στο σχολείο,
                                                                                            // τοποθετώντας τον στο όροφό του
        void operate(int hours) const;  // Λειτουργεί (operate) όλους τους ορόφους του σχολείου για hours ώρες
        void empty();
        void print() const; // Εκτυπώνει την αυλή, το κλιμακοστάσιο και τους ορόφους του σχολείου
};