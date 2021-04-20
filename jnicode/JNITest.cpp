#include "JNITest.h"
#include <jni.h>

JNIEXPORT jboolean JNICALL Java_JNITest_testMethod(JNIEnv *env, jobject obj, jint a, jint b)
{
    return a&b;
}