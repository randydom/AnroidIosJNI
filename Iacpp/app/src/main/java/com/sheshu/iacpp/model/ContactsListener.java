package com.sheshu.iacpp.model;

/**
 * Created by Sheshu on 8/2/17.
 */
public interface ContactsListener {
    public void onContactAdded(JContact contact);
    public void onContactUpdated(JContact oldContact, JContact newContact);
}
