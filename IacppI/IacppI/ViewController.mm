//
//  ViewController.m
//  IacppI
//
//  Created by SheshuKumar Inguva on 8/5/17.
//  Copyright © 2017 SheshuKumar Inguva. All rights reserved.
//

#import "ViewController.h"
#import "ContactsApiIos.hpp"
#include <vector>
@interface ViewController ()
@end
@implementation ViewController
NSString* stdStringToNSString(std::string stdString);
/*
 //TODO: How to call to member method pointers?
- (int) onContactAdded:(Contact*) contact{
    NSLog(@"Contact firstName: %@",contact->getFirstName());
    return 0;
}


- (int) onContactUpdated:(Contact*) oldContact newContactItem:(Contact*)newContact{

    NSLog(@"ContactUpdated oldNumber %@ new number: %@", oldContact->getPhoneNumber(), newContact->getPhoneNumber());
    return 1;
}

*/

void printContact(Contact* contact){
    NSLog(@"FirstName: %@ LastName: %@ PhoneNumber: %@ ",stdStringToNSString(contact->getFirstName()),                                                                             stdStringToNSString(contact->getLastName()),                                                                                                 stdStringToNSString(contact->getPhoneNumber()));
}


int onContactAdded(Contact* contact){
    //[self onContactAdded:contact];
     NSLog(@"Contact firstName: %@",stdStringToNSString(contact->getFirstName()));
    return 0;
}

int onContactUpdated(Contact* oldContact, Contact* newContact){

    NSLog(@"ContactUpdated oldNumber %@ new number: %@", stdStringToNSString(oldContact->getPhoneNumber()),
          stdStringToNSString(newContact->getPhoneNumber()));
    return 0;
}


void printContacts(std::vector<Contact *> * retrievedContacts){

    std::for_each(retrievedContacts->begin(), retrievedContacts->end(), ^(Contact * contact) {

        printContact(contact);

    });

}

- (void)viewDidLoad {
    [super viewDidLoad];

    std::vector<Contact *> * retrievedContacts = getAllContacts();// Do any additional setup after loading the view, typically from a nib.

    printContacts(retrievedContacts);

    NSLog(@"test ");

    Contact* contact =new Contact(new std::string("FirstName20")
                                 ,new std::string("LastName20")
                                 ,new std::string("1155336"));

    addContact(contact,&onContactAdded);

    setContactUpdatedListener(&onContactUpdated);


}



NSString* stdStringToNSString(std::string* stdString){
    NSString *convertedString = [NSString stringWithCString:stdString->c_str()
                                                encoding:[NSString defaultCStringEncoding]];
    return convertedString;
}



- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
