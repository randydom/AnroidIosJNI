//
// Created by SheshuKumar Inguva on 8/2/17.
//

#ifndef IACPP_CONTACTSCOREAPI_H
#define IACPP_CONTACTSCOREAPI_H

#include <string>
#include <vector>
#include "../model/Contact.h"
#include "../webservice/ContactsWebService.h"

class ContactsCoreApi {
public:
    ContactsCoreApi();

    std::vector<Contact *> *getContacts();

    void addContact(Contact *contact, int (*callback)(Contact *));

    void setListener(int (*callback)(Contact *, Contact *));
};

#endif //IACPP_CONTACTSCOREAPI_H
