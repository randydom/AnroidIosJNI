package com.sheshu.iacpp.view;

import android.app.Activity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import com.sheshu.iacpp.R;
import com.sheshu.iacpp.model.JContact;

import java.util.ArrayList;

/**
 * Created by Sheshu on 8/5/17.
 */
class ContactsListAdapter extends BaseAdapter {
    private final LayoutInflater mInflator;
    private ArrayList<JContact> mContactsList;
    ContactsListAdapter(ArrayList<JContact> contacts, Activity activity) {
        mContactsList = contacts;
        mInflator = activity.getLayoutInflater();
    }
    public void setContacts(ArrayList<JContact> contacts) {
        mContactsList = contacts;
        notifyDataSetChanged();
    }
    @Override
    public int getCount() {
        return mContactsList != null ? mContactsList.size() : 0;
    }
    @Override
    public Object getItem(int i) {
        return (mContactsList != null && mContactsList.size() > i) ? mContactsList.get(i) : null;
    }
    @Override
    public long getItemId(int i) {
        return 0;
    }
    @Override
    public View getView(int i, View convertView, ViewGroup viewGroup) {
        if (convertView == null) {
            convertView = mInflator.inflate(R.layout.contacts_row, viewGroup, false);
            convertView.setTag(new ViewHolder(convertView));
        }
        ViewHolder vh = (ViewHolder) convertView.getTag();
        if (vh != null) {
            JContact contact = (mContactsList != null && i < mContactsList.size()) ? mContactsList.get(i) : null;
            if (contact != null)
                vh.setName(contact.getFirstName(), contact.getLastName());
        }
        return convertView;
    }
    class ViewHolder {
        final TextView mFirstName;
        final TextView mLastName;
        ViewHolder(View view) {
            mFirstName = view.findViewById(R.id.first_name);
            mLastName = view.findViewById(R.id.last_name);
        }
        void setName(String firstname, String lastName) {
            mFirstName.setText(firstname);
            mLastName.setText(lastName);
        }
    }
}
