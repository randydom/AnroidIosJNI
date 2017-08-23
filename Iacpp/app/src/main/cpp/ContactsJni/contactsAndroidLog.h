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
#include <android/log.h>

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define  LOGV(...)  __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,__VA_ARGS__)
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO   , LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN   , LOG_TAG,__VA_ARGS__)
#define  LOGF(...)  __android_log_print(ANDROID_LOG_FATAL   , LOG_TAG,__VA_ARGS__)
#define  LOGSIMPLE(...)

#endif
#endif //IACPP_CONTACTSANDROIDLOG_H
