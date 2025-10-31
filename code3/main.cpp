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
// Художественная литература
class FictionBook : public Book {
private:
    string genre;

public:
    FictionBook(string t, string a, int y, string i, string g)
        : Book(t, a, y, i), genre(g) {}

    void displayInfo() const override {
        cout << "=== ХУДОЖЕСТВЕННАЯ ЛИТЕРАТУРА ===" << endl;
        Book::displayInfo();
        cout << "Жанр: " << genre << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "Художественная литература";
    }
};
// Научная литература
class ScienceBook : public Book {
private:
    string subject;

public:
    ScienceBook(string t, string a, int y, string i, string s)
        : Book(t, a, y, i), subject(s) {}

    void displayInfo() const override {
        cout << "=== НАУЧНАЯ ЛИТЕРАТУРА ===" << endl;
        Book::displayInfo();
        cout << "Область науки: " << subject << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "Научная литература";
    }
};
// Учебник
class Textbook : public Book {
private:
    string gradeLevel;

public:
    Textbook(string t, string a, int y, string i, string gl)
        : Book(t, a, y, i), gradeLevel(gl) {}

    void displayInfo() const override {
        cout << "=== УЧЕБНИК ===" << endl;
        Book::displayInfo();
        cout << "Для: " << gradeLevel << endl;
        cout << "--------------------------------" << endl;
    }

    string getType() const override {
        return "Учебник";
    }
};
// Класс библиотеки
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
        cout << "Книга добавлена в библиотеку!" << endl;
    }

    void removeBook(string isbn) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if ((*it)->getIsbn() == isbn) {
                delete *it;
                books.erase(it);
                cout << "Книга удалена из библиотеки!" << endl;
                return;
            }
        }
        cout << "Книга с ISBN " << isbn << " не найдена!" << endl;
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
                    cout << "Книга выдана!" << endl;
                } else {
                    cout << "Книга уже выдана!" << endl;
                }
                return;
            }
        }
        cout << "Книга не найдена!" << endl;
    }

    void returnBook(string isbn) {
        for (auto book : books) {
            if (book->getIsbn() == isbn) {
                if (!book->getAvailability()) {
                    book->setAvailability(true);
                    cout << "Книга возвращена!" << endl;
                } else {
                    cout << "Книга уже в библиотеке!" << endl;
                }
                return;
            }
        }
        cout << "Книга не найдена!" << endl;
    }

    void displayAllBooks() const {
        if (books.empty()) {
            cout << "Библиотека пуста!" << endl;
            return;
        }

        cout << "\n=== ВСЕ КНИГИ В БИБЛИОТЕКЕ ===" << endl;
        for (auto book : books) {
            book->displayInfo();
        }
    }

    void displayAvailableBooks() const {
        cout << "\n=== ДОСТУПНЫЕ КНИГИ ===" << endl;
        bool found = false;
        for (auto book : books) {
            if (book->getAvailability()) {
                book->displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Нет доступных книг!" << endl;
        }
    }

    void displayStatistics() const {
        cout << "\n=== СТАТИСТИКА БИБЛИОТЕКИ ===" << endl;
        cout << "Всего книг: " << books.size() << endl;

        int availableCount = 0;
        int fictionCount = 0, scienceCount = 0, textbookCount = 0;

        for (auto book : books) {
            if (book->getAvailability()) availableCount++;

            string type = book->getType();
            if (type == "Художественная литература") fictionCount++;
            else if (type == "Научная литература") scienceCount++;
            else if (type == "Учебник") textbookCount++;
        }

        cout << "Доступно: " << availableCount << endl;
        cout << "Выдано: " << (books.size() - availableCount) << endl;
        cout << "Художественных: " << fictionCount << endl;
        cout << "Научных: " << scienceCount << endl;
        cout << "Учебников: " << textbookCount << endl;
    }
};
void addBookInteractive(Library& library) {
    cout << "\n=== ДОБАВЛЕНИЕ НОВОЙ КНИГИ ===" << endl;

    string title, author, isbn, extra;
    int year, type;

    cout << "Введите название: ";
    cin.ignore();
    getline(cin, title);

    cout << "Введите автора: ";
    getline(cin, author);

    cout << "Введите год: ";
    cin >> year;

    cout << "Введите ISBN: ";
    cin >> isbn;

    cout << "Выберите тип книги:" << endl;
    cout << "1. Художественная литература" << endl;
    cout << "2. Научная литература" << endl;
    cout << "3. Учебник" << endl;
    cout << "Ваш выбор: ";
    cin >> type;

    cin.ignore();
    switch(type) {
        case 1:
            cout << "Введите жанр: ";
            getline(cin, extra);
            library.addBook(new FictionBook(title, author, year, isbn, extra));
            break;
        case 2:
            cout << "Введите область науки: ";
            getline(cin, extra);
            library.addBook(new ScienceBook(title, author, year, isbn, extra));
            break;
        case 3:
            cout << "Введите для кого предназначен (например, '10 класс'): ";
            getline(cin, extra);
            library.addBook(new Textbook(title, author, year, isbn, extra));
            break;
        default:
            cout << "Неверный выбор типа книги!" << endl;
    }
}
void searchByAuthorInteractive(Library& library) {
    string author;
    cout << "Введите автора для поиска: ";
    cin.ignore();
    getline(cin, author);

    auto results = library.findBooksByAuthor(author);
    if (results.empty()) {
        cout << "Книги автора '" << author << "' не найдены!" << endl;
    } else {
        cout << "Найдено " << results.size() << " книг:" << endl;
        for (auto book : results) {
            book->displayInfo();
        }
    }
}

void searchByTitleInteractive(Library& library) {
    string title;
    cout << "Введите название для поиска: ";
    cin.ignore();
    getline(cin, title);

    auto results = library.findBooksByTitle(title);
    if (results.empty()) {
        cout << "Книги с названием '" << title << "' не найдены!" << endl;
    } else {
        cout << "Найдено " << results.size() << " книг:" << endl;
        for (auto book : results) {
            book->displayInfo();
        }
    }
}
