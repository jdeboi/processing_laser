/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class laser_helios_jnihelios_JNIHelios */

#ifndef _Included_laser_helios_jnihelios_JNIHelios
#define _Included_laser_helios_jnihelios_JNIHelios
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    nativeNew
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_laser_helios_jnihelios_JNIHelios_nativeNew
  (JNIEnv *, jobject);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    sayHello
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_laser_helios_jnihelios_JNIHelios_sayHello
  (JNIEnv *, jobject);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    OpenDevices
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_OpenDevices
  (JNIEnv *, jobject);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    CloseDevices
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_CloseDevices
  (JNIEnv *, jobject);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    WriteFrame
 * Signature: (IIB[Llaser/helios/jnihelios/HeliosPoint;I)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_WriteFrame
  (JNIEnv *, jobject, jint, jint, jbyte, jobjectArray, jint);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    GetStatus
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetStatus
  (JNIEnv *, jobject, jint);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    GetFirmwareVersion
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetFirmwareVersion
  (JNIEnv *, jobject, jint);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    GetName
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetName
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    SetName
 * Signature: (ILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_SetName
  (JNIEnv *, jobject, jint, jstring);

/*
 * Class:     laser_helios_jnihelios_JNIHelios
 * Method:    Stop
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_Stop
  (JNIEnv *, jobject, jint);

#ifdef __cplusplus
}
#endif
#endif
