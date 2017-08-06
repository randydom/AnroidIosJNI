//
// Created by SheshuKumar Inguva on 8/2/17.
//

#ifndef IACPP_CONTACTSCOREAPI_H
#define IACPP_CONTACTSCOREAPI_H

#include <string.h>
#include "Contact.hpp"

class ContactsCoreApi {

public:
    ContactsCoreApi();

    std::vector<Contact *> *getContacts();

    void addContact(Contact *contact, int (*callback)(Contact *));

    void setListener(int (*callback)(Contact *,Contact*));


};


#endif //IACPP_CONTACTSCOREAPI_H
