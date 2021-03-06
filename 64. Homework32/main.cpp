#include <iostream>
#include <map>
using namespace std;

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
    string name;  // изначально имя неизвестно

    // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
    for (const auto& item : names) {
        // если очередной год не больше данного, обновляем имя
        if (item.first <= year) {
            name = item.second;
        }
        else {
            // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
            break;
        }
    }

    return name;
}

string GetHistory(const map<int, string>& names, const string& name, const int year)
{
    string history = "";

    if (names.size() == 1)
    {
        return history;
    }

    for (auto it = names.rbegin(); it != names.rend(); ++it) {   
        if (it == names.rbegin())
        {
            continue;
        }

        if (history.size() == 0 && name == (*it).second)
        {
            continue;
        }

        if ((*prev(it)).second == (*it).second || (*it).first > year)
        {
            continue;
        }

        history += (history.size() == 0 ? "" : ", ") + (*it).second;
    }

    if (history.size() > 0)
    {
        return " (" + history + ")";
    }

    return history;
}

class Person {
public:
    void ChangeFirstName(int year, const string& firstName) {
        _firstNames[year] = firstName;
    }
    void ChangeLastName(int year, const string& lastName) {
        _lastNames[year] = lastName;
    }
    string GetFullName(int year) {
        return GetFullName(year, false);
    }
    string GetFullNameWithHistory(int year) {
        return GetFullName(year, true);
    }
private:
    map<int, string> _firstNames;
    map<int, string> _lastNames;

    string GetFullName(int year, bool isWithHistory)
    {
        // получаем имя и фамилию по состоянию на год year
        const string firstName = FindNameByYear(_firstNames, year);
        const string lastName = FindNameByYear(_lastNames, year);

        // если и имя, и фамилия неизвестны
        if (firstName.empty() && lastName.empty()) {
            return "Incognito";

            // если неизвестно только имя
        }
        else if (firstName.empty()) {
            return lastName + (isWithHistory ? GetHistory(_lastNames, lastName, year) : "") + " with unknown first name";

            // если неизвестна только фамилия
        }
        else if (lastName.empty()) {
            return firstName + (isWithHistory ? GetHistory(_firstNames, firstName, year) : "") + " with unknown last name";

            // если известны и имя, и фамилия
        }
        else {
            return firstName + (isWithHistory ? GetHistory(_firstNames, firstName, year) : "") + " " + lastName + (isWithHistory ? GetHistory(_lastNames, lastName, year) : "");
        }
    }
};

int main()
{
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}