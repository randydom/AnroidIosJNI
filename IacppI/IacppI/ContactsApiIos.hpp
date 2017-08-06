//
//  ContactsApiIos.hpp
//  IacppI
//
//  Created by SheshuKumar Inguva on 8/5/17.
//  Copyright © 2017 SheshuKumar Inguva. All rights reserved.
//

#ifndef ContactsApiIos_hpp
#define ContactsApiIos_hpp

#include <stdio.h>
#import "ContactsCoreApi.hpp"
#import "Contact.hpp"
extern "C"{
void freeAllStatic();
ContactsCoreApi *getContactsApi();
std::vector<Contact *> * getAllContacts();
void addContact(Contact* contact, int (*callback)(Contact *));
void setContactUpdatedListener(int (*callback)(Contact *, Contact*));


}
#endif /* ContactsApiIos_hpp */
