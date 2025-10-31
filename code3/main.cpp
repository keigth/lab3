#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// ������� ����������� ����� Book
class Book {
protected:
    string title;
    string author;
    int year;
    string isbn;
    bool isAvailable;

public:
    Book(string t, string a, int y, string i)
        : title(t), author(a), year(y), isbn(i), isAvailable(true) {}

    virtual ~Book() {}

    virtual void displayInfo() const {
        cout << "��������: " << title << endl;
        cout << "�����: " << author << endl;
        cout << "���: " << year << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "������: " << (isAvailable ? "��������" : "������") << endl;
    }

    virtual string getType() const = 0;

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getIsbn() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool available) { isAvailable = available; }
};
// �������������� ����������
class FictionBook : public Book {
private:
    string genre;

public:
    FictionBook(string t, string a, int y, string i, string g)
        : Book(t, a, y, i), genre(g) {}

    void displayInfo() const override {
        cout << "=== �������������� ���������� ===" << endl;
        Book::displayInfo();
        cout << "����: " << genre << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "�������������� ����������";
    }
};
// ������� ����������
class ScienceBook : public Book {
private:
    string subject;

public:
    ScienceBook(string t, string a, int y, string i, string s)
        : Book(t, a, y, i), subject(s) {}

    void displayInfo() const override {
        cout << "=== ������� ���������� ===" << endl;
        Book::displayInfo();
        cout << "������� �����: " << subject << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "������� ����������";
    }
};
// �������
class Textbook : public Book {
private:
    string gradeLevel;

public:
    Textbook(string t, string a, int y, string i, string gl)
        : Book(t, a, y, i), gradeLevel(gl) {}

    void displayInfo() const override {
        cout << "=== ������� ===" << endl;
        Book::displayInfo();
        cout << "���: " << gradeLevel << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "�������";
    }
};
