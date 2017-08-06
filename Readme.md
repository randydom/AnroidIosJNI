# Application:  IOS Android with Common c++ library Iocpp


This App is to demonstrate Android IOS using common c++ library.


Architecture:
-------------------------------Java-----------------------------------------------------------------
Java UI:
Java sources:

Root: src/java/com.sheshu.iacpp


view/ContactListActivity -- Launch activity wich will hold the ContactListActivityFragment .
view/ContactListActivityFragment -- Fragment which will hold the Ui for listview to show the contacts.
view/ContactListAdapter -- ListAdapter for the contact list.


model/ContactsListener -- Listener interface, used to call from the static callbacks from JNI.
model/ContactsSDK -- SDK interface, interface to the JNI layer and calls.
model/JContact -- Contact definition with firstname, lastname, phone number



controller/Controller is base controller interface, which is implemented in ContactListActivityFragment.java

Execution: ContactListActivity loads  ContactListActivityFragment. Which initializes controller and other views.
ContactListActivity loads the jni library 'contactsSdk-lib'. As soon as fragment loaded, will call
the native get contacts, addContact, notifyContact methods.

 native GetContacts will get the contacts syncronously. And will be loaded in the Listview in the ContactListActivityFragment.
 getContacts->native getContacts->reply fron native-> post to list with ContactsListAdapter.


 native addContact will add the contact in a std::thread with delay and report back to static method ContactsSDK->onContactAdded,
  This method will call the notifier method in the ContactListActivityFragment. And will show the toast after update in ui thread.
 ContactsSDK->onContactAdded->(ContactsListener)->onContactAdded->Toast to user.

  native notifyContactUpdated will do the similar call as above, where the last contact's phone number
  will be delayed and posted to the UI through the callback.
 ContactsSDK->onContactUpdated->(ContactsListener)->onContactUpdated->Toast to user.

 ------------------- Native layer-----------------------------------------------------------------------

 Root: main/cpp

 Native layer is bult into two parts, ContactsCore& JsonLib in a shared object and ContactsJni as container shared object.

  ContactsJni
    contactsSdkJni.cpp the glue code between java and c libraries. conversions from c to java contacts and other glue code. native api interfaces,
    callbacks for native code, which intern call java layer present here.

 ContactsCore
    api
        Core api to call, which will talk to mock webservice.
        ContactsCoreApi.cpp -- core api, called from JNI.
        ContactsCoreApi.h -- core api header file.
    model
        Contact.cpp/h Model for Contact, which is used in native and objective-c
    webservice
        ContactWebService.cpp/h mock webservice to 1. load contacts using json parser from string,
         2. return contacts from memory for getContacts call.
         3. spawn a std::thread for addContact and contactUpdated calls.

 JsonLib
    json lib from https://github.com/MJPA/SimpleJSON

    ---------------------------------IOS layer------------------------------------------------------------

IacppI is the iOS project. 

    The static library for core generates 'contacts-core-lib' static library. It will be exported to ..\distribution folder.
    All these variants rejected by xcode. xcode not linking them against code. So i have compiled all the sources in the xcode project.
    Somehow xcode not picking up folder structure. so all files were linear and .h were converted to .hpp. Android JNI and ios sources were almost equal
    apart from these header file issues.

    UI is not developed in IOS. code is tested in from the logs.

    Core lib structure is similar to the above in the project folders(not on disk, only for project visibility).
    api - api
    webservice- mock webservice
    JsonLib - json lib (thridparty)
    model - model for contact.
    ContactsIOSAPI - glue code for IOS.
        ContactsApiIos.cpp/hpp files to expose the interface with ios code. Similar to contactsSdkJni.cpp.
    ViewController.mm -- the code where this api is called and logs printed from here.

    ------------------------Technology items used for this project-------------------------------------------
    1. JNI.
    2. call back from different thread using std::thread
    3. attach the callback thread to the jvm to callback.
    4. static listener with listener interface.
    5. controller to manage these calls.
    6. a simple activity, fragment, listview, adapter, viewholder pattern.
    7. cmake to build static library, export out library, build with container shared library.
    8. Android app to test the calls and post to UI.
    9. ios code to test the calls and print to log.
    ------------------------what can be done further------------------------------------------------
    1. finding toolchain to build ios compatible library from android studio.
    2. attaching .a to the ios project.
    3. ui for ios, listview/tableview.
    4. code formatter for ios.
    5. adding code from folders retaining folder structure and build from Android code base without copying.
    6. junit and expresso recorder tests.






