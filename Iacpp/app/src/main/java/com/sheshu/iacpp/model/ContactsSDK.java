package com.sheshu.iacpp.model;

import java.util.ArrayList;

/**
 * Created by Sheshu on 8/2/17.
 */
public class ContactsSDK {
    static ContactsListener sContactsListener;
    public static void onContactAdded(JContact contact) {
        if (sContactsListener != null) {
            sContactsListener.onContactAdded(contact);
        }
    }
    public static void onContactUpdated(JContact oldContact, JContact newContact) {
        if (sContactsListener != null) {
            sContactsListener.onContactUpdated(oldContact, newContact);
        }
    }
    public void setStaticListener(ContactsListener listener) {
        sContactsListener = listener;
    }
    public native void addContact(JContact contact);
    public native ArrayList<JContact> getContacts();
    public native void notifyContactUpdated();
}
