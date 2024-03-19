#include <iostream>
#include <string>

#include "p3.h"

using namespace std;

Info::Info() {
    this->name = "No Name Set";
    this->value = "No Value Set";
    this->next = nullptr;
}

Info::Info(std::string name, std::string value, Info *next) {
    this->name = name;
    this->value = value;
    this->next = next;
}

Info* Info::GetNext() {
    return this->next;
}

void Info::PrintNode() {
    cout << "    " << this->name << " | " << this->value << endl;
}

Contact::Contact() {
    this->first = "No First Set";
    this->last = "No Last Set";
    this->next = nullptr;
    this->headInfoList = nullptr;
    this->tailInfoList = nullptr;
}

Contact::Contact(std::string first, std::string last, Contact *next) {
    this->first = first;
    this->last = last;
    this->next = next;
    this->headInfoList = nullptr;
    this->tailInfoList = nullptr;
}

Contact* Contact::GetNext() {
    return this->next;
}

void Contact::PrintNode() {
    cout << "Contact Name: " << this->first << " " << this->last << endl;
}

// return 1 if Contact object name is higher in alphabetical order than its comparison parameter
// return 0 if they are the same exact strings
// return -1 if the contact object is lower
int Contact::Compare(Contact *comparison) {
    if (this->last == comparison->last) { //last is same
        if (this->first == comparison->first) { //first is same
            return 0;
        } else if (this->first < comparison->first) { //first is higher
            return 1;
        } else { //first is lower
            return -1;
        }
    } else if (this->last < comparison->last) { //last is higher
        return 1;
    } else { //last is lower
        return -1;
    }
}

// Contact destructor
Contact::~Contact() {
    Info *currInfo = this->headInfoList;
    Info *nextInfo;

    while (currInfo != nullptr) {
        nextInfo = currInfo->GetNext();
        delete currInfo;
        currInfo = nextInfo;
    }
}

ContactList::ContactList() {
    this->headContactList = nullptr;
    this->tailContactList = nullptr;
    this->count = 0;
}

int ContactList::getCount() {
    return this->count;
}

// print the specified contact and its information
// 1. return false and print nothing if the contact is not in the list
// 2. otherwise return true and print the contact
bool ContactList::printContact(std::ostream &os, std::string first, std::string last) {
    Contact *currContact = this->headContactList;
    bool contactExists = false;

    while (currContact != nullptr) {
        if (currContact->first == first && currContact->last == last) {
            contactExists = true;
            break;
        }
        currContact = currContact->GetNext();
    }
    
    if (!contactExists) {
        return false;
    }

    os << "Contact Name: " << currContact->first << " " << currContact->last << endl;

    Info *currInfo = currContact->headInfoList;
        
    while (currInfo != nullptr) {
        os << "    " << currInfo->name << " | " << currInfo->value << endl;
        currInfo = currInfo->GetNext();
    }

    return true;
}

// print all contacts and their information
// print nothing if the list is empty
void ContactList::print(std::ostream &os) {
    Contact *currContact = headContactList;

    while (currContact != nullptr) {
        os << "Contact Name: " << currContact->first << " " << currContact->last << endl;
        
        Info *currInfo = currContact->headInfoList;
        
        while (currInfo != nullptr) {
            os << "    " << currInfo->name << " | " << currInfo->value << endl;
            currInfo = currInfo->GetNext();
        }

        currContact = currContact->GetNext();
    }
}

// add a contact to the back of the list
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the back of the list
// - do not forget to update count
bool ContactList::addContact(std::string first, std::string last) {
    Contact *newContact = new Contact(first, last, nullptr);

    Contact *currContact = this->headContactList;
    bool contactExists = false;
    
    while (currContact != nullptr) {
        if (currContact->first == first && currContact->last == last) {
            contactExists = true;
        }
        currContact = currContact->GetNext();
    }
    
    if (contactExists) {
        return false;
    }

    // if list is empty, set head and tail to newContact, else set current tail pointer to newContact, then make newContact the new tail
    if (this->headContactList == nullptr) {
        this->headContactList = newContact;
        this->tailContactList = newContact;
    } else {
        this->tailContactList->next = newContact;
        this->tailContactList = newContact;
    }

    this->count ++;

    return true;
}

// add info to the back of a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the back of the contact's list and return true
bool ContactList::addInfo(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Info *newInfo = new Info(infoName, infoVal, nullptr);

    Contact *currContact = this->headContactList;

    bool contactExists = false;

    // go through list of contacts. if contact is found, stop on that node.
    while (currContact != nullptr) {
        if (currContact->first == first && currContact->last == last) {
            contactExists = true;
            break;
        }
        currContact = currContact->GetNext();
    }

    // if the specified contact wasnt found
    if (!contactExists) {
        return false;
    }

    Info *currInfo = currContact->headInfoList;

    // for found contact node, see if info is already there
    while (currInfo != nullptr) {
        // if it is, update value and end function
        if (infoName == currInfo->name) {
            currInfo->value = infoVal;
            return true;
        }
        currInfo = currInfo->GetNext();
    }

    if (currContact->headInfoList == nullptr) {
        currContact->headInfoList = newInfo;
        currContact->tailInfoList = newInfo;
    } else {
        currContact->tailInfoList->next = newInfo;
        currContact->tailInfoList = newInfo;
    }
    
    return true;
}

// add a contact to the list in ascending order by last name
//     if last names are equal, then order by first name ascending
// 1. return false and do nothing if the contact is already in the list
// 2. otherwise return true and add the contact to the list
// - do not forget to update count
// - compare strings with the built-in comparison operators: <, >, ==, etc.
// - a compare method/function is recommended
bool ContactList::addContactOrdered(std::string first, std::string last) {
    Contact *newContact = new Contact(first, last, nullptr);
    
    Contact *currContact = this->headContactList;
    Contact *prevContact = nullptr;

    // if the list is empty, just add the contact and return true
    if (currContact == nullptr) {
        this->headContactList = newContact;
        this->tailContactList = newContact;
        count ++;
        return true;
    }

    // go through list
    while (currContact != nullptr) {
        if (newContact->Compare(currContact) == 1) { //if new contact comes before current contact
            if (prevContact == nullptr) {
                this->headContactList = newContact;
                newContact->next = currContact;
                count ++;
                return true;
            } else {
                prevContact->next = newContact;
                newContact->next = currContact;
                count ++;
                return true;
            }
        } else if (newContact->Compare(currContact) == 0) { //if new contact is equal to current contact
            return false;
        } else {
            prevContact = currContact;
            currContact = currContact->GetNext();
        }
    }

    // at this point, the contact is not already in the list, and hasnt been inserted.
    ContactList::addContact(first, last);

    return true;
}

// add info to a contact's info list in ascending order by infoName
// 1. return false and do nothing if the contact is not in the list
// 2. if the infoName is already in the info list, update the infoValue and return true
// 3. otherwise add the info to the contact's list and return true
bool ContactList::addInfoOrdered(std::string first, std::string last, std::string infoName, std::string infoVal) {
    Info *newInfo = new Info(infoName, infoVal, nullptr);

    Contact *currContact = this->headContactList;

    bool contactExists = false;

    // go through list of contacts. if contact is found, stop on that node.
    while (currContact != nullptr) {
        if (currContact->first == first && currContact->last == last) {
            contactExists = true;
            break;
        }
        currContact = currContact->GetNext();
    }

    // if the specified contact wasnt found
    if (!contactExists) {
        return false;
    }
    
    /////////////////////
    //done finding contact. Time to do info stuff
    /////////////////////

    Info *currInfo = currContact->headInfoList;
    Info *prevInfo = nullptr;

    while (currInfo != nullptr) {
        // if it is, update value and end function
        if (infoName == currInfo->name) {
            currInfo->value = infoVal;
            return true;
        } else if (infoName < currInfo->name) {
            if (prevInfo == nullptr) {
                newInfo->next = currInfo;
                currContact->headInfoList = newInfo;
                return true;
            } else {
                newInfo->next = currInfo;
                prevInfo->next = newInfo;
            }
        } else {
            currInfo = currInfo->GetNext();
        }
    }

    // if infoname isnt in info list, and info hasnt been added yet, add to end
    ContactList::addInfo(first, last, infoName, infoVal);

    return true;
}


// NOT FINISHED, have to create and implement Contact deconstructor
// remove the contact and its info from the list
// 1. return false and do nothing if the contact is not in the list
// 2. otherwise return true and remove the contact and its info
// - do not forget to update count
bool ContactList::removeContact(std::string first, std::string last) {
    Contact *currContact = this->headContactList;
    Contact *prevContact = nullptr;

    while (currContact != nullptr) {
        if (currContact->last == last && currContact->first == first) {
            if (prevContact == nullptr) {
                this->headContactList = currContact->next;
            } else {
                prevContact->next = currContact->next;
            }

            delete currContact;
            this->count --;
            return true;
        }
        prevContact = currContact;
        currContact = currContact->next;
    }

    return false;
}

// remove the info from a contact's info list
// 1. return false and do nothing if the contact is not in the list
// 2. return false and do nothing if the info is not in the contact's info list
// 3. otherwise return true and remove the info from the contact's list
bool ContactList::removeInfo(std::string first, std::string last, std::string infoName) {
    Contact *currContact = this->headContactList;
    bool contactExists = false;

     // go through list of contacts. if contact is found, stop on that node.
    while (currContact != nullptr) {
        if (currContact->first == first && currContact->last == last) {
            contactExists = true;
            break;
        }
        currContact = currContact->GetNext();
    }

    // if the specified contact wasnt found
    if (!contactExists) {
        return false;
    }

    Info *currInfo = currContact->headInfoList;
    Info *prevInfo = nullptr;

    while (currInfo != nullptr) {
        if (currInfo->name == infoName) {
            if (prevInfo == nullptr) {
                currContact->headInfoList = currInfo->next;
            } else {
                prevInfo->next = currInfo->next;
            }

            delete currInfo;
            return true;
        }
        prevInfo = currInfo;
        currInfo = currInfo->next;
    }

    return false;
}

// destroy the list by removing all contacts and their infos
ContactList::~ContactList() {
    Contact *currContact = this->headContactList;
    Contact *nextContact;

    while (currContact != nullptr) {
        nextContact = currContact->GetNext();
        delete currContact;
        currContact = nextContact;
    }
}

// deep copy the source list
// - do not forget to update count
ContactList::ContactList(const ContactList &src) {
    // update count
    count = src.count;

    // if source list is empty, set head to empty and return
    if (src.headContactList == nullptr) {
        headContactList = nullptr;
        return;
    }

    // create current source node
    Contact *srcCurr = src.headContactList;
    
    // create current new node and make it the head
    Contact *newCurr = new Contact(srcCurr->first, srcCurr->last, nullptr);
    headContactList = newCurr;

    // update current source node
    srcCurr = srcCurr->next;

    while (srcCurr != nullptr) {
        newCurr->next = new Contact(srcCurr->first, srcCurr->last, nullptr);
        newCurr = newCurr->next;
        srcCurr = srcCurr->next;
    }

    tailContactList = newCurr;

    
    // set current node back to beginning in order to go through and add info
    srcCurr = src.headContactList;

    // add info
    while (srcCurr != nullptr) {
        Info *currInfo = srcCurr->headInfoList;

        while (currInfo != nullptr) {
            addInfo(srcCurr->first, srcCurr->last, currInfo->name, currInfo->value);
            currInfo = currInfo->next;
        }
        srcCurr = srcCurr->next;
    }
}
    

// remove all contacts and their info then deep copy the source list
// - do not forget to update count
const ContactList &ContactList::operator=(const ContactList &src) {
    if (this != &src) {
        Contact *currDelete = headContactList;

        // delete each contact in list
        while (currDelete != nullptr) {
            Contact *nextToDelete = currDelete->next;
            delete currDelete;
            currDelete = nextToDelete;
        }

        headContactList = nullptr;

        // update count
        count = src.count;

        // if source list is empty, set head to empty and return
        if (src.headContactList == nullptr) {
            return *this;
        }

        // create current source node
        Contact *srcCurr = src.headContactList;
        
        // create current new node and make it the head
        Contact *newCurr = new Contact(srcCurr->first, srcCurr->last, nullptr);
        headContactList = newCurr;

        // update current source node
        srcCurr = srcCurr->next;

        while (srcCurr != nullptr) {
            newCurr->next = new Contact(srcCurr->first, srcCurr->last, nullptr);
            newCurr = newCurr->next;
            srcCurr = srcCurr->next;
        }

        tailContactList = newCurr;

        
        // set current node back to beginning in order to go through and add info
        srcCurr = src.headContactList;

        // add info
        while (srcCurr != nullptr) {
            Info *currInfo = srcCurr->headInfoList;

            while (currInfo != nullptr) {
                addInfo(srcCurr->first, srcCurr->last, currInfo->name, currInfo->value);
                currInfo = currInfo->next;
            }
            srcCurr = srcCurr->next;
        }
    }
    return *this;
}