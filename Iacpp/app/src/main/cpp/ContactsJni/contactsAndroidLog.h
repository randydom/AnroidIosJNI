//
// Created by SheshuKumar Inguva on 8/4/17.
//

#ifndef IACPP_CONTACTSANDROIDLOG_H
#define IACPP_CONTACTSANDROIDLOG_H

#include <Android/log.h>

#define LOG_TAG "ContactsLog"
#ifdef NDEBUG

#define LOGD(...)

#else
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#endif
#endif //IACPP_CONTACTSANDROIDLOG_H
