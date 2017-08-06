package com.sheshu.iacpp.model;

import java.util.ArrayList;

/**
 * Created by Sheshu on 8/2/17.
 */
public class JContact {
    private String mFirstName;
    private String mLastName;
    private String mPhoneNumber;
    public JContact(String firstName, String lastName, String phoneNumber) {
        mFirstName = firstName;
        mLastName = lastName;
        mPhoneNumber = phoneNumber;
        ArrayList<JContact> mylist = new ArrayList<>(10);
    }
    public String getFirstName() {
        return mFirstName;
    }
    public void setFirstName(String firstName) {
        this.mFirstName = firstName;
    }
    public String getLastName() {
        return mLastName;
    }
    public void setLastName(String lastName) {
        this.mLastName = lastName;
    }
    public String getPhoneNumber() {
        return mPhoneNumber;
    }
    public void setPhoneNumber(String phoneNumber) {
        this.mPhoneNumber = phoneNumber;
    }
}
