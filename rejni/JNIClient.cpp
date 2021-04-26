#include "JNIClient.h"
#include "extern/circ_lib/circs_client.h"

JNIEXPORT void JNICALL Java_JNIClient_testMethod(JNIEnv *env, jobject obj, jint a){
    ABYParty *party = createClient();

    megaCircSingleInput(party, (uint32_t) a);

    party->ExecCircuit();

    delete party;
}