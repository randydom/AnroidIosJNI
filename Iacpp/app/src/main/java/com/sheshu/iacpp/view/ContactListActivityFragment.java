package com.sheshu.iacpp.view;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.Fragment;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.Toast;

import com.sheshu.iacpp.R;
import com.sheshu.iacpp.controller.ContactsController;
import com.sheshu.iacpp.controller.Controller;
import com.sheshu.iacpp.model.ContactsListener;
import com.sheshu.iacpp.model.JContact;

/**
 * A placeholder fragment containing a simple view.
 */
public class ContactListActivityFragment extends Fragment {
    private static final String TAG = "ContactsFragment";
    ListView mListView;
    ContactsListAdapter mListAdapter;

    void updateContactsList() {
        mListAdapter.setContacts(mController.getContactsFromNative());
    }

    // Controller for ndk calls.
    Controller mController;
    private ContactsListener mNativeListener = new ContactsListener() {
        @Override
        public void onContactAdded(final JContact contact) {
            Log.e(TAG, "GOT CALLBACK FROM NATIVE" + contact.getFirstName() + " contact added");
            getActivity().runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(getActivity(), "Contact Created: " + contact.getFirstName() + " " + contact.getPhoneNumber(), Toast.LENGTH_SHORT).show();
                }
            });
        }

        @Override
        public void onContactUpdated(final JContact newContact, final JContact oldContact) {
            Log.e(TAG, "onContactUpdated" + oldContact.getFirstName() + " contact updated" + " new contact: " + newContact);
            // callback will be in different thread, so use this block to render list in main thread.
            if (getActivity() != null && !getActivity().isFinishing() && !getActivity().isDestroyed()) {
                getActivity().runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(getActivity(), "Old Number : " + oldContact.getPhoneNumber() + " New number" + newContact.getPhoneNumber(), Toast.LENGTH_SHORT).show();
                        updateContactsList();
                    }
                });
            }
        }
    };

    public ContactListActivityFragment() {
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_contact_list, container, false);
        Toolbar toolbar = (Toolbar) view.findViewById(R.id.toolbar);
        ((AppCompatActivity) getActivity()).setSupportActionBar(toolbar);
        mController = new ContactsController(mNativeListener);
        FloatingActionButton fab = (FloatingActionButton) view.findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "Refreshing list", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();
                // get contacts from native and try to load in the list
                mListAdapter.setContacts(mController.getContactsFromNative());
            }
        });
        mListView = view.findViewById(R.id.contacts_list);
        mListAdapter = new ContactsListAdapter(null, getActivity());
        mListView.setAdapter(mListAdapter);
        return view;
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);
        // Init the library,
        // These two calls can be combined.
        mController.initNativeSdk();
        mController.setSdkStaticListener();
        // get contacts from native and try to load in the list
        mListAdapter.setContacts(mController.getContactsFromNative());
        // Test trigger native contacts.
        mController.triggerContactUpdateNative();
        // Test add native
        mController.addContactNative(new JContact("FirstName10", "Lastname10", "11122233"));
        mListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                JContact contact = ((JContact) mListAdapter.getItem(i));
                Toast.makeText(getActivity(), "Contact : " + contact.getFirstName() + " has phone number" + contact.getPhoneNumber(), Toast.LENGTH_SHORT).show();
            }
        });
    }

    @Override
    public void onPause() {
        mController.clearNativeItems();
        super.onPause();
    }
}
