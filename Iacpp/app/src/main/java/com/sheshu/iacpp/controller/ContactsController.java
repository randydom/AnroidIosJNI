package com.sheshu.iacpp.controller;

import android.util.Log;
import android.widget.Toast;

import com.sheshu.iacpp.model.ContactsListener;
import com.sheshu.iacpp.model.ContactsSDK;
import com.sheshu.iacpp.model.JContact;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * Created by Sheshu on 8/23/17.
 */
public class ContactsController implements Controller {
    private static final String TAG = "ContactsController";
    private final ContactsListener mNativeListener;
    private ContactsSDK contactsSDK;

    public ContactsController(ContactsListener listener){
        mNativeListener = listener;
    }



    @Override
    public void initNativeSdk() {
        // make sure somebody loads native library System.loadLibrary("contactsSdk-lib");
        contactsSDK = new ContactsSDK();
    }

    @Override
    public void setSdkStaticListener() {
        contactsSDK.setStaticListener(mNativeListener);
    }

    @Override
    public ArrayList<JContact> getContactsFromNative() {
        ArrayList<JContact> contactsFromNative = contactsSDK.getContacts();
        Log.e(TAG, contactsFromNative.toString() + contactsFromNative.size() + Arrays.deepToString(contactsFromNative.toArray()));
        return contactsFromNative;
    }

    @Override
    public void addContactNative(JContact contact) {
        contactsSDK.addContact(contact);
    }

    @Override
    public void triggerContactUpdateNative() {
        contactsSDK.notifyContactUpdated();
    }

    public void clearNativeItems() {
        contactsSDK.clearNativeItems();
    }


}
