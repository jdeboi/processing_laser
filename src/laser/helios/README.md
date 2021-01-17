

in parent directory:
----
dir='laser/helios/jnihelios'
javac ./$dir/JNIHelios.java
javac -h ./$dir ./$dir/JNIHelios.java


g++ -I"$JAVA_HOME/include" -std=c++14 -I"$JAVA_HOME/include/darwin/" $dir/HeliosDac.cpp $dir/laser_helios_jnihelios_JNIHelios.cpp -o $dir/libjnihelios.dylib $dir/libusb-1.0.0.dylib


libjnihelios.jnilib
libhello.dylib
 
java -Djava.library.path=./$dir ./$dir/JNIHelios.java

https://dhilst.github.io/2016/10/15/JNI-CPP.html

////////////////////
People.java -> JNIHelios.java (java class with native declarations)
libpeople.h -> HeliosDac.h (This is our native (C++) class. Is almost identical, 
    to the java class with the exception that here we declare. In real
    world you will have to link the _jni.so to the
    .so that implements the class and its methods.
    // This is the above header declaring and
    // initializing People class. As said before on real
    // world applications you would need to link this
    // file with the application's library.

libpeople_jni.cpp -> jnihelios_JNIHelios.cpp (jni wrapper over libpeop)
    #include "People.h" -> jnihelios_JNIHelios.h
 


// This header is generate by javah tool.
#include "People.h"
