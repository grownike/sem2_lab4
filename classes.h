#include "iostream"

#pragma once

#include "string"

using namespace std;


class ComplexNumber {

private:
    double Re = 0;
    double Im = 0;

public:

    ComplexNumber() {};

    ComplexNumber(int a) {
        Re = 0;
        Im = 0;
    };

    ComplexNumber(double re, double im) {
        Re = re;
        Im = im;
    }

    ComplexNumber(const ComplexNumber &c) {
        Re = c.Re;
        Im = c.Im;
    }

    ComplexNumber &operator=(const ComplexNumber &c) {
        Re = c.Re;
        Im = c.Im;
        return (*this);
    }

    bool operator==(ComplexNumber &c) const {
        if (Re == c.Re and Im == c.Im) {
            return true;
        }
        return false;

    }

    ComplexNumber &operator=(int a) {
        Re = 0;
        Im = 0;
        return (*this);
    }

    friend istream &operator>>(istream &stream, ComplexNumber &object) {
        cout << "Input Re and Im: ";
        stream >> object.Re;
        stream >> object.Im;
        return stream;
    }

    friend ostream &operator<<(ostream &stream, ComplexNumber &object) {
        stream << object.Re;
        if (object.Im >= 0) {
            stream << '+' << object.Im << 'i';
        } else {
            stream << object.Im << 'i';
        }
        return stream;
    }


};

class Students {
private:
    int age;
    string name;
    string surname;
    int course;

public:

    Students() {};

    Students(const Students &c) {
        age = c.age;
        name = c.name;
        surname = c.surname;
        course = c.course;
    }

    Students(string a, string b, int c, int d) {
        age = c;
        surname = a;
        name = b;
        course = d;
    }

    Students(int a) {
        age = 0;
        name = "***";
        surname = "***";
        course = 0;
    }

    Students &operator=(int a) {
        age = 0;
        name = "***";
        surname = "***";
        course = 0;
        return (*this);
    }

    Students &operator=(const Students &c) {
        age = c.age;
        name = c.name;
        surname = c.surname;
        course = c.course;
        return (*this);
    }

    friend istream &operator>>(istream &stream, Students &object) {
        cout << "Input name, surname, age, course: ";
        stream >> object.surname;
        stream >> object.name;
        stream >> object.age;
        stream >> object.course;
        return stream;
    }

    friend ostream &operator<<(ostream &stream, Students &object) {
        stream << object.surname << " ";
        stream << object.name << " ";
        stream << object.age << " ";
        stream << object.course << "     ";
        return stream;
    }

    bool operator==(Students &c) const {
        if ((age == c.age and course == c.course) and (name == c.name and surname == c.surname)) {
            return true;
        }
        return false;

    }


};

class Teachers {
private:
    int age;
    string name;
    string surname;
    string subject;
public:
    Teachers() {};

    Teachers(const Teachers &c) {
        age = c.age;
        name = c.name;
        surname = c.surname;
        subject = c.subject;
    }

    Teachers(string a, string b, int c, string d) {
        age = c;
        surname = a;
        name = b;
        subject = d;
    }

    Teachers(int a) {
        age = 0;
        name = "***";
        surname = "***";
        subject = "***";
    }

    friend istream &operator>>(istream &stream, Teachers &object) {
        cout << "Input name, surname, age, subject: ";
        stream >> object.surname;
        stream >> object.name;
        stream >> object.age;
        stream >> object.subject;
        return stream;
    }

    friend ostream &operator<<(ostream &stream, Teachers &object) {
        stream << object.surname << " ";
        stream << object.name << " ";
        stream << object.age << " ";
        stream << object.subject << "     ";
        return stream;
    }

    bool operator==(Teachers &c) const {
        if ((age == c.age and subject == c.subject) and (name == c.name and surname == c.surname)) {
            return true;
        }
        return false;

    }

    Teachers &operator=(const Teachers &c) {
        age = c.age;
        name = c.name;
        surname = c.surname;
        subject = c.subject;
        return (*this);
    }

    Teachers &operator=(int a) {
        age = 0;
        name = "***";
        surname = "***";
        subject = "***";
        return (*this);
    }

};

class Chars {
private:
    string data;

public:

    Chars(string a) {
        data = a;
    }

    Chars() {};

    Chars(const Chars &c) {
        data = c.data;
    }

    Chars(const int a) {
        data = "0";
    }

    bool operator==(Chars &c) const {
        if (data == c.data) {
            return true;
        }
        return false;

    }

    Chars &operator=(const Chars &c) {
        data = c.data;
        return (*this);
    }

    Chars &operator=(int a) {
        data = "***";
        return *this;
    }

    friend istream &operator>>(istream &stream, Chars &object) {
        cout << "Input char os string: ";
        stream >> object.data;
        return stream;
    }

    friend ostream &operator<<(ostream &stream, Chars &object) {
        stream << object.data;
        return stream;
    }

};





