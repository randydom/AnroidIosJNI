//
// Created by SheshuKumar Inguva on 8/2/17.
//

#include "ContactsCoreApi.hpp"
#include <atomic>

extern std::atomic_bool gStopNotifierThread;

ContactsCoreApi::ContactsCoreApi() {
    initData();
}

void killNotifierThread(std::thread *thread) {
    if (thread != nullptr && thread->joinable()) {
        thread->join();
        delete (thread);
    }
}

ContactsCoreApi::~ContactsCoreApi() {
    gStopNotifierThread = true;
    killNotifierThread(mNotifierThread);
    mNotifierThread = nullptr;
    clearData();
}

std::vector<Contact *> *ContactsCoreApi::getContacts() {
    // :: will link it to extern c function, avoiding self call
    return ::getContacts();
}

void ContactsCoreApi::addContact(Contact *contact, int (*callback)(Contact *)) {
    addContactWebservice(contact, callback);
}

void ContactsCoreApi::setListener(int (*callback)(Contact *, Contact *)) {
    this->mNotifierThread = notifyUpdateContact(callback);
}
