//
// Created by SheshuKumar Inguva on 8/2/17.
//

#ifndef IACPP_CONTACTS_H
#define IACPP_CONTACTS_H

#include <vector>
#include "../model/Contact.hpp"

extern "C" {
extern void notifyUpdateContact(int (*callback)(Contact *, Contact *));
extern void clearData();
extern std::vector<Contact *> *initData();
extern void addContactWebservice(Contact *contact, int (*callback)(Contact *));
extern std::vector<Contact *> *getContacts();
}
#endif //IACPP_CONTACTS_H
