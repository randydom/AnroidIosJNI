//
// Created by SheshuKumar Inguva on 8/2/17.
//

#include "Contact.hpp"

std::string *Contact::getFirstName() {
    return firstName;
}

void Contact::setFirstName(std::string *firstName) {
    this->firstName = firstName;
}

std::string *Contact::getLastName() {
    return lastName;
}

void Contact::setLastName(std::string *lastName) {
    this->lastName = lastName;
}

std::string *Contact::getPhoneNumber() {
    return phoneNumber;
}

void Contact::setPhoneNumber(std::string *phoneNumber) {
    this->phoneNumber = phoneNumber;
}

Contact::Contact(std::string *aFirstName, std::string *aLastName,
                 std::string *aPhoneNumber) {
    phoneNumber = aPhoneNumber;
    firstName = aFirstName;
    lastName = aLastName;
}

Contact::~Contact() {
    if (firstName != NULL) {
        delete (firstName);
        firstName = NULL;
    }
    if (lastName != NULL) {
        delete (lastName);
        lastName = NULL;
    }
    if (phoneNumber != NULL) {
        delete (phoneNumber);
        phoneNumber = NULL;
    }
}
