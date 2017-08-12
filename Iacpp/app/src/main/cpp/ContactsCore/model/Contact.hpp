//
// Created by SheshuKumar Inguva on 8/2/17.
//

#ifndef IACPP_CONTACT_H
#define IACPP_CONTACT_H

#include <string>

class Contact {
public:
    std::string *getFirstName();

    void setFirstName(std::string *firstName);

    std::string *getLastName();

    void setLastName(std::string *lastName);

    std::string *getPhoneNumber();

    void setPhoneNumber(std::string *phoneNumber);

    Contact() {
    }

    Contact(std::string *aFirstName, std::string *aLastName,
            std::string *aPhoneNumber);

    ~Contact();

private:
    std::string *phoneNumber;
    std::string *firstName;
    std::string *lastName;
};

#endif //IACPP_CONTACT_H
