#include <bits/stdc++.h>
using namespace std;

class Student
{
private:
    string Name, RollNo;
    float CGPA;

public:
    Student() : Name(""), RollNo(""), CGPA(0.0) {}

    void setName(const string &name)
    {
        Name = name;
    }

    void setRollNo(const string &rollNo)
    {
        RollNo = rollNo;
    }

    void setCGPA(float cgpa)
    {
        if (cgpa >= 0.0 && cgpa <= 10.0)
            CGPA = cgpa;
        else
            cout << "Invalid CGPA! Must be between 0.0 and 10.0" << endl;
    }

    string getName() const
    {
        return Name;
    }

    string getRollNo() const
    {
        return RollNo;
    }

    float getCGPA() const
    {
        return CGPA;
    }
};

void addStudent(Student &s)
{
    string name, rollNo;
    float cgpa;

    cout << "Enter Name Of Student: ";
    cin.ignore();       // To clear the buffer
    getline(cin, name); // Allows spaces in name
    s.setName(name);

    cout << "Enter RollNo of Student: ";
    cin >> rollNo;
    s.setRollNo(rollNo);

    cout << "Enter CGPA of Student: ";
    cin >> cgpa;
    s.setCGPA(cgpa);

    ofstream out("Student.txt", ios::app);
    if (!out)
    {
        cout << "ERROR: File Not Opened!" << endl;
        return;
    }

    out << s.getName() << " : " << s.getRollNo() << " : " << s.getCGPA() << endl;
    cout << "Student Added Successfully!" << endl;
    out.close();
}

void search(const Student &s)
{
    string name;
    cout << "Enter Name of Student: ";
    cin.ignore();
    getline(cin, name);

    ifstream in("Student.txt");
    if (!in)
    {
        cout << "Error: File Cannot Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line))
    {
        int pos = line.find(name);
        if (pos != string::npos)
        {
            cout << " Name | RollNo | CGPA" << endl;
            cout << line << endl;
            found = true;
            break; // Exit after finding the first occurrence
        }
    }
    if (!found)
    {
        cout << "Student Not Found!" << endl;
    }
    in.close();
}

void update()
{
    string rollNo;
    cout << "Enter RollNo of Student: ";
    cin >> rollNo;

    ifstream in("Student.txt");
    if (!in)
    {
        cout << "Error: File Cannot Open!" << endl;
        return;
    }

    ofstream out("StudentTemp.txt");
    if (!out)
    {
        cout << "Error: Could not open temp file!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line))
    {
        int pos = line.find(rollNo);
        if (pos != string::npos)
        {
            found = true;
            float newcgpa;
            cout << "Enter New CGPA: ";
            cin >> newcgpa;

            if (newcgpa < 0.0 || newcgpa > 10.0)
            {
                cout << "Invalid CGPA!" << endl;
                out << line << endl; // Write original line without change
                continue;
            }

            stringstream ss;
            ss << newcgpa;
            string newCGPA = ss.str();

            int cgpaPos = line.find_last_of(':');
            line.replace(cgpaPos + 2, string::npos, newCGPA);
            cout << "CGPA updated for: " << rollNo << endl;
        }
        out << line << endl;
    }

    if (!found)
    {
        cout << "Student Not Found!" << endl;
    }

    in.close();
    out.close();
    remove("Student.txt");
    rename("StudentTemp.txt", "Student.txt");
}

int main()
{
    Student s;
    bool exit = false;
    while (!exit)
    {
        cout << "Welcome To Student Management System" << endl;
        cout << "************************************" << endl;
        cout << "1. Add Student." << endl;
        cout << "2. Search Student." << endl;
        cout << "3. Update Student." << endl;
        cout << "4. Exit" << endl;
        cout << "Enter Choice: ";
        int val;
        cin >> val;

        switch (val)
        {
        case 1:
            addStudent(s);
            break;
        case 2:
            search(s);
            break;
        case 3:
            update();
            break;
        case 4:
            exit = true;
            cout << "Goodbye!" << endl;
            break;
        default:
            cout << "Invalid Choice!" << endl;
        }
    }

    return 0;
}
