#include "JNIServer.h"
#include "extern/circ_lib/circs_server.h"

JNIEXPORT void JNICALL Java_JNIServer_testMethod(JNIEnv *env, jobject obj, jint a)
{
    ABYParty *party = createClient();

    megaCircSingleInput(party, (uint32_t) a, CIRC_EQUAL);

    party->ExecCircuit();

    delete party;
}