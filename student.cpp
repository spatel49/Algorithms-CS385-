/*******************************************************************************
 * Name    : student.cpp
 * Author  : Siddhanth Patel
 * Version : 1.0
 * Date    : September 6, 2019
 * Description : Student Class that lets user input student full name, gpa, and id and view the output of all students and failing students.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class Student{
    private:
        string first_;
        string last_;
        float gpa_;
        int id_;

    public:
    Student(string first, string last, float gpa, int id): first_{first}, last_{last}, gpa_{gpa}, id_{id}  {}

    string full_name() const {
        return first_ + " " + last_;
    }

    float gpa() const{
        return gpa_;
    }

    int id() const{
        return id_;
    }

    void print_info() const {
        cout << full_name() << ", GPA: " << fixed << setprecision(2) << gpa() << ", ID: " << id() << endl;
    }
};

vector<Student> find_failing_students(const vector<Student> &students){
    vector<Student> failing_students;
    //Iterates through the students vector, appending each students whose gpa is less than 1.0 to the failing students vector.
    for (size_t index = 0; index < students.size(); index++) {
        if(students[index].gpa() < 1.0){
            failing_students.push_back(students[index]);
        }
    }
    return failing_students;
}

void print_students(const vector<Student> &students){
    //Iterates through the students vector, calling print_info for each student.
    for (auto it = begin (students); it != end (students); ++it) {
        it->print_info();
        }
}

int main(){
    string first_name, last_name;
    float gpa;
    int id;
    char repeat;
    vector<Student> students;

    do{
        cout << "Enter student's first name: ";
        cin >> first_name;
        cout << "Enter student's last name: ";
        cin >> last_name;
        gpa = -1;
        while(gpa < 0 || gpa > 4){
            cout << "Enter student's GPA (0.0-4.0): ";
            cin >> gpa;
        }
        cout << "Enter student's ID: ";
        cin >> id;
        students.push_back(Student(first_name, last_name, gpa, id));
        cout << "Add another student to database (Y/N)? ";
        cin >> repeat;

    } while ( repeat == 'Y' || repeat ==  'y');

    cout << endl << "All students:" << endl;
    print_students(students);

    cout << endl << "Failing students:" ;
    //TODO
    //Print a space and the word 'None' on the same line if no students are failing.
    //Otherwise, a print each failing student on a separate line.

	if (find_failing_students(students).empty()){
		cout << " None";
	} else {
		cout << endl;
		print_students(find_failing_students(students));
	}
    return 0;
    }
