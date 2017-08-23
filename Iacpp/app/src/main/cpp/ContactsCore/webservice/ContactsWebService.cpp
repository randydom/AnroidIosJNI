#include "ContactsWebService.hpp"
#include "../../JsonLib/JSONValue.hpp"
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <algorithm>
#include <atomic>

using namespace std;

extern "C" {
std::string contacts = "[{\"first\" : \"Alexander\",\"last\" : \"Bell\",\"phone\" : \"+16170000001\"},"
        "{\"first\" : \"Thomas\",\"last\" : \"Watson\",\"phone\" : \"+16170000002\"},"
        "{\"first\" : \"Elisha\",\"last\" : \"Gray\",\"phone\" : \"+18476003599\"},"
        "{\"first\" : \"Antonio\",\"last\" : \"Meucci\",\"phone\" : \"+17188763245\"},"
        "{\"first\" : \"Guglielmo\",\"last\" : \"Marconi\",\"phone\" : \"+39051203222\"},"
        "{\"first\" : \"Samuel\",\"last\" : \"Morse\",\"phone\" : \"+16172419876\"},"
        "{\"first\" : \"Tim\",\"last\" : \"Berners-Lee\",\"phone\" : \"+44204549898\"},"
        "{\"first\" : \"John\",\"last\" : \"Baird\",\"phone\" : \"+4408458591006\"},"
        "{\"first\" : \"Thomas\",\"last\" : \"Edison\",\"phone\" : \"+19086575678\"}]";

static std::vector<Contact *> *sData;

std::vector<Contact *> *makeData() {




    // Parse example data
    JSONValue *value = JSON::Parse(contacts.c_str());

    string firstChars = "first";
    string lastChars = "last";
    string phoneChars = "phone";

    wstring firstKey(firstChars.begin(), firstChars.end());
    wstring lastKey(lastChars.begin(), lastChars.end());
    wstring phoneKey(phoneChars.begin(), phoneChars.end());

    // Did it go wrong?
    if (value == NULL) {
        printf("Example code failed to parse, did you change it?\r\n");
    } else {

        // Retrieve the main object
        JSONArray root;
        if (!value->IsArray()) {
            printf("The root element is not an object, did you change the example?\r\n");
        } else {
            root = value->AsArray();
            for (int i = 0; i < root.size(); i++) {
                JSONObject contactRow = root[i]->AsObject();

                std::wstring firstName = contactRow[firstKey]->AsString();
                std::wstring lastName = contactRow[lastKey]->AsString();
                std::wstring phoneNumber = contactRow[phoneKey]->AsString();

                Contact *contact = new Contact(new std::string(firstName.begin(), firstName.end()),
                                               new std::string(lastName.begin(), lastName.end()),
                                               new std::string(phoneNumber.begin(),
                                                               phoneNumber.end()));
                sData->push_back(contact);
            }
        }
    }
    return sData;
}

std::vector<Contact *> *getContacts() {
    return sData;
}

void addContactLocal(Contact *contact, int(*addedCallback)(Contact *)) {
    // timepass for few milli seconds, to feel async
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // Add to list
    sData->push_back(contact);
    // return
    addedCallback(contact);
}

void addContactWebservice(Contact *contact, int (*callback)(Contact *)) {
    // create thread and return.
    std::thread t(addContactLocal, contact, callback);
    t.detach();
}

std::atomic_bool gStopNotifierThread;

void notifyUpdateDelayed(int (*callback)(Contact *, Contact *)) {

    // Keeping the infinite loop. When app exits, it should be stopped by killing the thread.
    while (!gStopNotifierThread) {
        std::srand(std::time(0)); // use current time as seed for random generator
        int random_variable = std::rand();
        // cut the random time to 10seconds.
        random_variable %= 10000;
        // timepass for few milli seconds, to feel async
        std::this_thread::sleep_for(std::chrono::milliseconds(random_variable));

        //After waiting for random time. pick a random item from list and update it.
        random_variable = std::rand();
        if(!gStopNotifierThread && sData!= nullptr){
            int randomIndex = random_variable % (sData->size());

            Contact *lastContact = sData->at(randomIndex);
            if (lastContact != nullptr) {
                // Copy out the object to old contact
                Contact *oldContact = new Contact(new std::string(*lastContact->getFirstName()),
                                                  new std::string(*lastContact->getLastName()),
                                                  new std::string(*lastContact->getPhoneNumber()));
                std::string *phoneNumber = lastContact->getPhoneNumber();
                //phoneNumber = std::reverse_copy(phoneNumber->begin(), phoneNumber->end(),phoneNumber);
                std::reverse(phoneNumber->begin(), phoneNumber->end());
                //lastContact->setPhoneNumber(phoneNumber);
                // callback
                callback(oldContact, lastContact);
            }
        }

    }
}

std::thread *notifyUpdateContact(int (*callback)(Contact *, Contact *)) {
    gStopNotifierThread = false;
    // create thread and return.
    std::thread *t = new std::thread(notifyUpdateDelayed, callback);
    t->detach();
    return t;
}

std::vector<Contact *> *initData() {
    // hook the sData to jni env to cleanp.
    sData = new std::vector<Contact *>();
    makeData();
    return sData;
}

void clearData() {
    if (sData != NULL) {
        unsigned long count = sData->size();
        for (int i = 0; i < count; i++) {
            Contact *item = sData->at(i);
            if (item != NULL)
                delete (item);
        }
        delete (sData);
        sData = nullptr;
    }
}
}
