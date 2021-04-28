# How to make a proper Makefile!

# 0. Make a default rule! It should let you recompile your libs.

.PHONY: all
all: libJNIMeth.so

# 1. Create a way to get headers!

NativeMeth.class: NativeMeth.java
	javac NativeMeth.java

NativeMeth.h: NativeMeth.class
	javac -h . NativeMeth.java

.PHONY: headers
headers: NativeMeth.h

# 2. Compile your libs!

libJNIMeth.so: NativeMeth.cpp NativeMeth.h
	mkdir build;cd build && cmake .. && make && cp libJNIMeth.so .. && cd ..

.PHONY: libs
libs: libJNIMeth.so

# 3. Install your libs!
/usr/lib/libJNIMeth.so: libJNIMeth.so
	cp libJNIMeth.so /usr/lib/

.PHONY: install
install: /usr/lib/libJNIMeth.so

# 4. Compile your Java files!
Client.class: Client.java
	javac Client.java

Server.class: Server.java
	javac Server.java

.PHONY: java
java: Client.class Server.class

# 5. Launch through make! (This should be useful if you don't want to install libs)
.PHONY: run_client
run_client: Client.class libJNIMeth.so
	java -Djava.library.path=. Client

.PHONY: run_server
run_server: Server.class libJNIMeth.so
	java -Djava.library.path=. Server

# 6. Clean!
.PHONY: clean

clean:
	rm -rf build;rm *.class;rm libJNIMeth.so;rm *.h