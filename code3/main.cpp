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
// ����� ����������
class Library {
private:
    vector<Book*> books;

public:
    ~Library() {
        for (auto book : books) {
            delete book;
        }
    }

    void addBook(Book* book) {
        books.push_back(book);
        cout << "����� ��������� � ����������!" << endl;
    }

    void removeBook(string isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getIsbn() == isbn) {
                delete *it;
                books.erase(it);
                cout << "����� ������� �� ����������!" << endl;
                return;
            }
        }
        cout << "����� � ISBN " << isbn << " �� �������!" << endl;
    }

    vector<Book*> findBooksByAuthor(string author) const {
        vector<Book*> result;
        for (auto book : books) {
            if (book->getAuthor() == author) {
                result.push_back(book);
            }
        }
        return result;
    }

    vector<Book*> findBooksByTitle(string title) const {
        vector<Book*> result;
        for (auto book : books) {
            if (book->getTitle() == title) {
                result.push_back(book);
            }
        }
        return result;
    }

    vector<Book*> findBooksByYear(int year) const {
        vector<Book*> result;
        for (auto book : books) {
            if (book->getYear() == year) {
                result.push_back(book);
            }
        }
        return result;
    }

    void borrowBook(string isbn) {
        for (auto book : books) {
            if (book->getIsbn() == isbn) {
                if (book->getAvailability()) {
                    book->setAvailability(false);
                    cout << "����� ������!" << endl;
                } else {
                    cout << "����� ��� ������!" << endl;
                }
                return;
            }
        }
        cout << "����� �� �������!" << endl;
    }

    void returnBook(string isbn) {
        for (auto book : books) {
            if (book->getIsbn() == isbn) {
                if (!book->getAvailability()) {
                    book->setAvailability(true);
                    cout << "����� ����������!" << endl;
                } else {
                    cout << "����� ��� � ����������!" << endl;
                }
                return;
            }
        }
        cout << "����� �� �������!" << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "���������� �����!" << endl;
            return;
        }

        cout << "\n=== ��� ����� � ���������� ===" << endl;
        for (auto book : books) {
            book->displayInfo();
        }
    }

    void displayAvailableBooks() const {
        cout << "\n=== ��������� ����� ===" << endl;
        bool found = false;
        for (auto book : books) {
            if (book->getAvailability()) {
                book->displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "��� ��������� ����!" << endl;
        }
    }

    void displayStatistics() const {
        cout << "\n=== ���������� ���������� ===" << endl;
        cout << "����� ����: " << books.size() << endl;

        int availableCount = 0;
        int fictionCount = 0, scienceCount = 0, textbookCount = 0;

        for (auto book : books) {
            if (book->getAvailability()) availableCount++;

            string type = book->getType();
            if (type == "�������������� ����������") fictionCount++;
            else if (type == "������� ����������") scienceCount++;
            else if (type == "�������") textbookCount++;
        }

        cout << "��������: " << availableCount << endl;
        cout << "������: " << (books.size() - availableCount) << endl;
        cout << "��������������: " << fictionCount << endl;
        cout << "�������: " << scienceCount << endl;
        cout << "���������: " << textbookCount << endl;
    }
};
void addBookInteractive(Library& library) {
    cout << "\n=== ���������� ����� ����� ===" << endl;

    string title, author, isbn, extra;
    int year, type;

    cout << "������� ��������: ";
    cin.ignore();
    getline(cin, title);

    cout << "������� ������: ";
    getline(cin, author);

    cout << "������� ���: ";
    cin >> year;

    cout << "������� ISBN: ";
    cin >> isbn;

    cout << "�������� ��� �����:" << endl;
    cout << "1. �������������� ����������" << endl;
    cout << "2. ������� ����������" << endl;
    cout << "3. �������" << endl;
    cout << "��� �����: ";
    cin >> type;

    cin.ignore();
    switch(type) {
        case 1:
            cout << "������� ����: ";
            getline(cin, extra);
            library.addBook(new FictionBook(title, author, year, isbn, extra));
            break;
        case 2:
            cout << "������� ������� �����: ";
            getline(cin, extra);
            library.addBook(new ScienceBook(title, author, year, isbn, extra));
            break;
        case 3:
            cout << "������� ��� ���� ������������ (��������, '10 �����'): ";
            getline(cin, extra);
            library.addBook(new Textbook(title, author, year, isbn, extra));
            break;
        default:
            cout << "�������� ����� ���� �����!" << endl;
    }
}
void searchByAuthorInteractive(Library& library) {
    string author;
    cout << "������� ������ ��� ������: ";
    cin.ignore();
    getline(cin, author);

    auto results = library.findBooksByAuthor(author);
    if (results.empty()) {
        cout << "����� ������ '" << author << "' �� �������!" << endl;
    } else {
        cout << "������� " << results.size() << " ����:" << endl;
        for (auto book : results) {
            book->displayInfo();
        }
    }
}

void searchByTitleInteractive(Library& library) {
    string title;
    cout << "������� �������� ��� ������: ";
    cin.ignore();
    getline(cin, title);

    auto results = library.findBooksByTitle(title);
    if (results.empty()) {
        cout << "����� � ��������� '" << title << "' �� �������!" << endl;
    } else {
        cout << "������� " << results.size() << " ����:" << endl;
        for (auto book : results) {
            book->displayInfo();
        }
    }
}
