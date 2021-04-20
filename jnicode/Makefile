# How to create a JNI-suitable makefile!

# Step 1 -> Set variables for what you will use!
# CC -> C/C++ compiler
CC=g++
# CFLAGS -> C/C++ compiler flags
CFLAGS=-Wall
# JFILES -> Java files
JFILES=JNITest.java
# CNAME -> Classname
CNAME=JNITest
# JCFILES -> Java class files
JCFILES=JNITest.class
# HFILES -> Header files
HFILES=JNITest.h
# CFILES -> C/C++ files
CFILES=JNITest.cpp
# JC -> Java compiler
JC=javac
# LF -> Library filename
LF=libjnitest.so
# SONAME
SONAME=jnitest.so
# CJNI -> JNI C/C++ compiler includes
CJNI=-I/usr/lib/jvm/java-11-openjdk-amd64/include/ -I/usr/lib/jvm/java-11-openjdk-amd64/include/linux/

.PHONY: run
run: $(LF) $(JCFILES)
	java -Djava.library.path=. $(CNAME)

$(JCFILES): $(JFILES)
	javac $(JFILES)

$(HFILES): $(JCFILES)
	$(JC) -h . $(JFILES)

.PHONY: header
header: $(HFILES)

$(LF): $(HFILES) $(CFILES)
	$(CC) $(CJNI) -o $(LF) -Wl,-soname,$(SONAME) -shared $(CFILES) -lc

.PHONY: clean
clean:
	rm *.h *.so *.class