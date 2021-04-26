gcc -shared -o libJNIClient.so \
-Wl,--whole-archive                  \
libJNIClient.a                 \
-Wl,--no-whole-archive