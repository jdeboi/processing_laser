
/*
 https://gist.github.com/DmitrySoshnikov/8b1599a5197b5469c8cc07025f600fdb
 gcc -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/darwin/" laser_library_LaserJNI.cppm-o laser_library_LaserJNI.o 
 
 g++ -c -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/darwin laser_library_LaserJNI.cpp -o laser_library_LaserJNI.o
 
 gcc -I"$JAVA_HOME/include" -I"$JAVA_HOME/include/darwin/" -o libjnilaser.jnilib -shared laser_library_LaserJNI.cpp
 
 */

#include <stdio.h>
#include <jni.h>
#include "laser_helios_jnihelios_JNIHelios.h"
#include "HeliosDac.h"

// This is the:
// private native long nativeNew(int age, String name)
// method. We allocate a new object with new operator.
// Pay attention that there is no delete call on this
// code so once the GC collect People object its
// native counterpart keeps in memory resulting in
// memory leak. Fixing this is left to user as an
// exercice.
extern "C"
JNIEXPORT jlong Java_laser_helios_jnihelios_JNIHelios_nativeNew
(JNIEnv *env, jobject self)
{
	// Here we allocate our new object and return
	// its pointer casted as a jlong;
	HeliosDac *h = new HeliosDac();
	return reinterpret_cast<jlong>(h);	
}

// https://dhilst.github.io/2016/10/15/JNI-CPP.html
// This function is a helper providing the boiler
// plate code to return the native object from
// Java object. The "nativeObjectPointer" is reached
// from this code, casted to HeliosDac's pointer and
// returned. This will be used in all our native
// methods wrappers to recover the object before
// invoking it's methods.
static HeliosDac *getObject(JNIEnv *env, jobject self)
{
	jclass cls = env->GetObjectClass(self);
	if (!cls)
		env->FatalError("bbbGetObjectClass failed");

	jfieldID nativeObjectPointerID = env->GetFieldID(cls, "nativeObjectPointer", "J");
	if (!nativeObjectPointerID)
		env->FatalError("GetFieldID failed");

	jlong nativeObjectPointer = env->GetLongField(self, nativeObjectPointerID);	
	return reinterpret_cast<HeliosDac *>(nativeObjectPointer);
}

extern "C"
JNIEXPORT void JNICALL Java_laser_helios_jnihelios_JNIHelios_sayHello
  (JNIEnv* env, jobject thisObject) {
    printf("Hello from C++ !!");
}


/*
 * Class:     jnihelios_JNIHelios
 * Method:    OpenDevices
 * Signature: ()I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_OpenDevices
  (JNIEnv *env, jobject self) {
    HeliosDac *_self = getObject(env, self);
	  return static_cast<jint>(_self->OpenDevices());
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    CloseDevices
 * Signature: ()I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_CloseDevices
  (JNIEnv *env, jobject self) {
    HeliosDac *_self = getObject(env, self);
	  return static_cast<jint>(_self->CloseDevices());
  }

/*
 * Class:     jnihelios_JNIHelios
 * Method:    WriteFrame
 * Signature: (IIB[Ljnihelios/HeliosPoint;)I
 * unsigned int devNum, unsigned int pps, std::uint8_t flags, HeliosPoint* points, unsigned int numOfPoints
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_WriteFrame
  (JNIEnv *env, jobject self, jint devNum, jint pps, jbyte flags, jobjectArray heliosPoints, jint numPoints) {
   
    HeliosDac *_self = getObject(env, self);
    // TODO points

    jclass jcls=env->FindClass("laser/helios/jnihelios/HeliosPoint");
    if (!jcls)
		  env->FatalError("aaaaaGetObjectClass failed");
    // jobject jobj=env->AllocateObject(jcls);

    HeliosPoint frame[numPoints];

    for (int i = 0; i < numPoints; i++ ) {
      jobject jobj = env->GetObjectArrayElement(heliosPoints, i);

      jfieldID xID = env->GetFieldID(jcls, "x", "S");
      jint x = env->GetShortField(jobj, xID);

      jfieldID yID = env->GetFieldID(jcls, "y", "S");
      jint y = env->GetShortField(jobj, yID);

      jfieldID rID = env->GetFieldID(jcls, "r", "B");
      jint r = env->GetByteField(jobj, rID);

      jfieldID gID = env->GetFieldID(jcls, "g", "B");
      jint g = env->GetByteField(jobj, gID);

      jfieldID bID = env->GetFieldID(jcls, "b", "B");
      jint b = env->GetByteField(jobj, bID);

      jfieldID iID = env->GetFieldID(jcls, "intensity", "B");
      jint intensity = env->GetByteField(jobj, iID);

      
      frame[i].x = x;
      frame[i].y = y;
      frame[i].r = r;
      frame[i].g = g;
      frame[i].b = b;
      frame[i].i = intensity;
    }
    

    // HeliosPoints 
	  return static_cast<jint>(_self->WriteFrame(devNum, pps, flags, &frame[0], numPoints));
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    GetStatus
 * Signature: (I)I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetStatus
  (JNIEnv *env, jobject self, jint devNum){ 
    HeliosDac *_self = getObject(env, self);
	  return static_cast<jint>(_self->GetStatus(devNum));
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    GetFirmwareVersion
 * Signature: (I)I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetFirmwareVersion
  (JNIEnv *env, jobject self, jint devNum) {
    HeliosDac *_self = getObject(env, self);
	  return static_cast<jint>(_self->GetFirmwareVersion(devNum));
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    GetName
 * Signature: (ILjava/lang/String;)I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_GetName
  (JNIEnv *env, jobject self, jint devNum, jstring dacName) {
	// Boiler plate code to convert java String
	// to (char *) then to std::string.
	 char *raw = (char*) env->GetStringUTFChars(dacName, NULL);
  // use char
  HeliosDac *_self = getObject(env, self);
	jint val = static_cast<jint>(_self->GetName(devNum, raw));
	env->ReleaseStringUTFChars(dacName, raw);
  return val;
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    SetName
 * Signature: (ILjava/lang/String;)I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_SetName
  (JNIEnv *env, jobject self, jint devNum, jstring name) {
     char *raw = (char*)env->GetStringUTFChars(name, NULL);

  HeliosDac *_self = getObject(env, self);
	jint val = static_cast<jint>(_self->GetName(devNum, raw));
	env->ReleaseStringUTFChars(name, raw);
  return val;
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    Stop
 * Signature: (I)I
 */
 extern "C"
JNIEXPORT jint JNICALL Java_laser_helios_jnihelios_JNIHelios_Stop
  (JNIEnv *env, jobject self, jint devNum) {
     HeliosDac *_self = getObject(env, self);
	  return static_cast<jint>(_self->Stop(devNum));
}

/*
 * Class:     jnihelios_JNIHelios
 * Method:    SetShutter
 * Signature: (IZ)I
 */
// JNIEXPORT jint JNICALL Java_jnihelios_JNIHelios_SetShutter
//   (JNIEnv *env, jobject self, jint devNum, jboolean) {
//   }
