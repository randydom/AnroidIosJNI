//
//  ContactsApiIos.cpp
//  IacppI
//
//  Created by SheshuKumar Inguva on 8/5/17.
//  Copyright © 2017 SheshuKumar Inguva. All rights reserved.
//

#include "ContactsApiIos.hpp"
extern "C"{


    static ContactsCoreApi *contactsCoreApi;

    void freeAllStatic(){

        if(contactsCoreApi!= nullptr)
            delete(contactsCoreApi);
        contactsCoreApi = NULL;




    }


    ContactsCoreApi *getContactsApi() {

        if (contactsCoreApi == NULL) {
            contactsCoreApi = new ContactsCoreApi();

        }
        return contactsCoreApi;
    }


    std::vector<Contact *> * getAllContacts(){

        return getContactsApi()->getContacts();



    }

    void addContact(Contact* contact, int (*callback)(Contact *))
    {
        return getContactsApi()->addContact(contact, callback);

    }

    void setContactUpdatedListener(int (*callback)(Contact *, Contact*)){
        
        
        getContactsApi()->setListener(callback);
    }
    
    
    
    
    
}
