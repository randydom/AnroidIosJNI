#include <jni.h>
#include <string>
#include "../ContactsCore/api/ContactsCoreApi.hpp"
#include  "contactsAndroidLog.h"

extern "C" {
static JavaVM *g_jvm;
//static thread_local JNIEnv *globalEnv;

static jclass java_util_ArrayList;
static jmethodID java_util_ArrayList_;
static jmethodID java_util_ArrayList_size;
static jmethodID java_util_ArrayList_get;
static jmethodID java_util_ArrayList_add;

static jclass java_com_sheshu_iacpp_ContactsSDK_JContact;
static jmethodID java_com_sheshu_iacpp_ContactsSDK_JContact_;

static jmethodID contact_get_firstname;
static jmethodID contact_get_lastname;
static jmethodID contact_get_phoneNumber;

static jclass java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class;
static jmethodID contact_callback_contact_added;
static jmethodID contact_callback_contact_updated;

std::string *getStringFromMethod(JNIEnv *env, jobject jContact, jmethodID method);
Contact *getContactFromJavaContact(JNIEnv *env, jobject jContact);
jobject getJavaObjectFromCContact(JNIEnv *env, Contact *contact);
static bool gInit;
/**
 * Method to init all classes from java and get methods with glue code.
 * @param env jni env variable. our token to the world.
 */
void init(JNIEnv *env) {
    if (!gInit) {
        env->GetJavaVM(&g_jvm);
        java_util_ArrayList = static_cast<jclass>(env->NewGlobalRef(
                env->FindClass("java/util/ArrayList")));
        java_util_ArrayList_ = env->GetMethodID(java_util_ArrayList, "<init>", "(I)V");
        java_util_ArrayList_size = env->GetMethodID(java_util_ArrayList, "size", "()I");
        java_util_ArrayList_get = env->GetMethodID(java_util_ArrayList, "get",
                                                   "(I)Ljava/lang/Object;");
        java_util_ArrayList_add = env->GetMethodID(java_util_ArrayList, "add",
                                                   "(Ljava/lang/Object;)Z");
        java_com_sheshu_iacpp_ContactsSDK_JContact = static_cast<jclass>(env->NewGlobalRef(
                env->FindClass("com/sheshu/iacpp/model/JContact")));
        java_com_sheshu_iacpp_ContactsSDK_JContact_ = env->GetMethodID(
                java_com_sheshu_iacpp_ContactsSDK_JContact, "<init>",
                "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
        contact_get_firstname = env->GetMethodID(
                java_com_sheshu_iacpp_ContactsSDK_JContact, "getFirstName",
                "()Ljava/lang/String;");
        contact_get_lastname = env->GetMethodID(
                java_com_sheshu_iacpp_ContactsSDK_JContact, "getLastName",
                "()Ljava/lang/String;");
        contact_get_phoneNumber = env->GetMethodID(
                java_com_sheshu_iacpp_ContactsSDK_JContact, "getPhoneNumber",
                "()Ljava/lang/String;");
        java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class = static_cast<jclass>(env->NewGlobalRef(
                env->FindClass("com/sheshu/iacpp/model/ContactsSDK")));
        contact_callback_contact_added = env->GetStaticMethodID(
                java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class, "onContactAdded",
                "(Lcom/sheshu/iacpp/model/JContact;)V");
        contact_callback_contact_updated = env->GetStaticMethodID(
                java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class, "onContactUpdated",
                "(Lcom/sheshu/iacpp/model/JContact;Lcom/sheshu/iacpp/model/JContact;)V");
        gInit = true;
    }
}

static ContactsCoreApi *contactsCoreApi;

void freeAllStatic(JNIEnv *env) {
    if (contactsCoreApi != nullptr)
        delete (contactsCoreApi);
    contactsCoreApi = NULL;
    env->DeleteGlobalRef(java_util_ArrayList);
    java_util_ArrayList = nullptr;
    env->DeleteGlobalRef(java_com_sheshu_iacpp_ContactsSDK_JContact);
    java_com_sheshu_iacpp_ContactsSDK_JContact = nullptr;
    env->DeleteGlobalRef(java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class);
    java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class = nullptr;
    env = nullptr;
    g_jvm = nullptr;
    gInit = false;
}

JNIEXPORT void JNICALL
Java_com_sheshu_iacpp_model_ContactsSDK_clearNativeItems(JNIEnv *env, jobject instance) {
    freeAllStatic(env);
}

ContactsCoreApi *getContactsApi() {
    if (contactsCoreApi == NULL) {
        contactsCoreApi = new ContactsCoreApi();
    }
    return contactsCoreApi;
}

int contactAdded(Contact *cContact) {
    if (g_jvm != nullptr) {
        JNIEnv *env;

        // double check it's all ok
        int getEnvStat = g_jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            LOGD("GetEnv: not attached");
            if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
                LOGD("Failed to attach");
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {
            LOGD("GetEnv: version not supported");
        }
        jobject jContact = getJavaObjectFromCContact(env, cContact);
        env->CallStaticVoidMethod(java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class,
                                  contact_callback_contact_added, jContact);
        env->DeleteLocalRef(jContact);
        env->ExceptionClear();
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
        g_jvm->DetachCurrentThread();
        LOGD("Contact added ");
    }
    return 0;
}

int contactUpdated(Contact *oldContact, Contact *newContact) {
    LOGD("Contact updated ");
    if (g_jvm != nullptr) {
        JNIEnv *env;

        // double check it's all ok
        int getEnvStat = g_jvm->GetEnv((void **) &env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            LOGD("GetEnv: not attached");
            if (g_jvm->AttachCurrentThread(&env, NULL) != 0) {
                LOGD("Failed to attach");
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {
            LOGD("GetEnv: version not supported");
        }
        jobject jOldContact = getJavaObjectFromCContact(env, oldContact);
        jobject jNewContact = getJavaObjectFromCContact(env, newContact);
        env->CallStaticVoidMethod(java_com_sheshu_iacpp_ContactsSDK_ContactsSDK_class,
                                  contact_callback_contact_updated, jOldContact, jNewContact);
        // Old contact is a copy, so need to delete here.
        delete (oldContact);
        // new contact is still referenced by our global memory, so no need to delete.
        //delete(newContact);

        env->DeleteLocalRef(jNewContact);
        env->DeleteLocalRef(jOldContact);
        env->ExceptionClear();
        if (env->ExceptionCheck()) {
            env->ExceptionDescribe();
        }
        g_jvm->DetachCurrentThread();
    }
    return 0;
}
#pragma mark - Support functions----------------------------------------------

JNIEXPORT jstring JNICALL
Java_com_sheshu_iacpp_ContactListActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
#pragma mark - JNI calls

JNIEXPORT void JNICALL
Java_com_sheshu_iacpp_model_ContactsSDK_addContact(
        JNIEnv *env,
        jobject /* this */, jobject jContact) {
    Contact *contact = getContactFromJavaContact(env, jContact);
    contactsCoreApi->addContact(contact, contactAdded);
}

JNIEXPORT void JNICALL
Java_com_sheshu_iacpp_model_ContactsSDK_notifyContactUpdated(
        JNIEnv *env,
        jobject /* this */) {
    contactsCoreApi->setListener(contactUpdated);
}

JNIEXPORT jobject JNICALL
Java_com_sheshu_iacpp_model_ContactsSDK_getContacts(
        JNIEnv *env,
        jobject /* this */) {
    init(env);
    std::vector<Contact *> *cContacts = getContactsApi()->getContacts();

    jobject javaArrayListContacts = NULL;
    // Copy elements to java arraylist
    {
        javaArrayListContacts = env->NewObject(java_util_ArrayList, java_util_ArrayList_,
                                               cContacts->size());
        for (Contact *contact: *cContacts) {
            jobject jContact = getJavaObjectFromCContact(env, contact);
            env->CallBooleanMethod(javaArrayListContacts, java_util_ArrayList_add, jContact);
            env->DeleteLocalRef(jContact);
        }
    }
    return javaArrayListContacts;
}
#pragma mark - Support functions----------------------------------------------
Contact *getContactFromJavaContact(JNIEnv *env, jobject jContact) {
    std::string *firstName = getStringFromMethod(env, jContact,
                                                 contact_get_firstname);

    std::string *lastName = getStringFromMethod(env, jContact,
                                                contact_get_lastname);

    std::string *phoneNumber = getStringFromMethod(env, jContact,
                                                   contact_get_phoneNumber);

    Contact *contact = new Contact(firstName, lastName, phoneNumber);
    return contact;
}

jobject getJavaObjectFromCContact(JNIEnv *env, Contact *contact) {
    jstring firstName = env->NewStringUTF(contact->getFirstName()->c_str());
    jstring lastName = env->NewStringUTF(contact->getLastName()->c_str());
    jstring phoneNumber = env->NewStringUTF(contact->getPhoneNumber()->c_str());

    jobject jContact = env->NewObject(java_com_sheshu_iacpp_ContactsSDK_JContact,
                                      java_com_sheshu_iacpp_ContactsSDK_JContact_, firstName,
                                      lastName, phoneNumber);
    env->DeleteLocalRef(firstName);
    env->DeleteLocalRef(lastName);
    env->DeleteLocalRef(phoneNumber);
    return jContact;
}

std::string *getStringFromMethod(JNIEnv *env, jobject jContact, jmethodID method) {
    jobject jstringObj = env->CallObjectMethod(jContact,
                                               method, 0);

    const char *strReturn = env->GetStringUTFChars((jstring) jstringObj, 0);
    std::string *stdString = new std::string(strReturn);
    env->ReleaseStringUTFChars((jstring) jstringObj, strReturn);
    return stdString;
}
}