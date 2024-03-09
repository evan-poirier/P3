#ifndef _P3_H_
#define _P3_H_

#include <iostream>
#include <string>

class Info {
public:
    std::string name;
    std::string value;
    Info *next;

    Info();
    Info(std::string name, std::string value, Info *next = nullptr);
    Info* GetNext();
    void PrintNode();
};

class Contact {
public:
    std::string first;
    std::string last;
    Contact *next;
    Info *headInfoList;
    Info *tailInfoList;

    Contact();
    Contact(std::string first, std::string last, Contact *next = nullptr);
    Contact* GetNext(); //returns pointer to next node in LL
    void PrintNode();
    int Compare(Contact *comparison); //compares 2 contact objects alphabetically
};

class ContactList {
private:
    Contact *headContactList;
    Contact *tailContactList;
    int count;
public:
    ContactList();

    int getCount();
    
    bool printContact(std::ostream &os, std::string first, std::string last);
    void print(std::ostream &os);

    bool addContact(std::string first, std::string last);
    bool addInfo(std::string first, std::string last, std::string infoName, std::string infoVal);

    bool addContactOrdered(std::string first, std::string last);
    bool addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal);
    
    bool removeContact(std::string first, std::string last);
    bool removeInfo(std::string first, std::string last, std::string infoName);

    ~ContactList();
    ContactList(const ContactList &src);
    const ContactList &operator=(const ContactList &src);
};

#endif