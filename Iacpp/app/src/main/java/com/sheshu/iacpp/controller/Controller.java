package com.sheshu.iacpp.controller;

import com.sheshu.iacpp.model.JContact;

import java.util.ArrayList;

/**
 * Created by Sheshu on 8/5/17.
 */
public interface Controller {
    void initNativeSdk();
    void setSdkStaticListener();
    ArrayList<JContact> getContactsFromNative();
    void addContactNative(JContact contact);
    void triggerContactUpdateNative();
    void updateUiList();
    void showToast(JContact contact, boolean isUpdated);
    void clearNativeItems();
}
