//
// Created by SheshuKumar Inguva on 8/2/17.
//

#include "ContactsCoreApi.h"

ContactsCoreApi::ContactsCoreApi() {
    initData();
}

std::vector<Contact *> *ContactsCoreApi::getContacts() {
    // :: will link it to extern c function, avoiding self call
    return ::getContacts();
}

void ContactsCoreApi::addContact(Contact *contact, int (*callback)(Contact *)) {
    addContactWebservice(contact, callback);
}

void ContactsCoreApi::setListener(int (*callback)(Contact *, Contact *)) {
    notifyUpdateContact(callback);
}
