#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

// Базовый абстрактный класс Book
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
        cout << "Название: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Год: " << year << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Статус: " << (isAvailable ? "Доступна" : "Выдана") << endl;
    }

    virtual string getType() const = 0;

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getYear() const { return year; }
    string getIsbn() const { return isbn; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool available) { isAvailable = available; }
};
