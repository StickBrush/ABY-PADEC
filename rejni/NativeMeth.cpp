#include "NativeMeth.h"
#include "extern/unified_circ_lib/circs.h"

/*
 * Class:     NativeMeth
 * Method:    singleInputServer
 * Signature: (II)I
 */
JNIEXPORT jint JNICALL Java_NativeMeth_singleInputServer(JNIEnv *env, jobject obj, jint input, jint type){
    SingleCircuitType s_type = static_cast<SingleCircuitType>(type);
    
    cerr << "Executing SingleInputServer" << endl;

    ABYParty *party = createServer();

    share* output = megaCircSingleInputServer(party, (uint32_t)input, s_type);

    party->ExecCircuit();

    uint32_t clear_out = output->get_clear_value<uint32_t>();

    delete party;

    return (jint)clear_out;
}

/*
 * Class:     NativeMeth
 * Method:    singleInputClient
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_NativeMeth_singleInputClient(JNIEnv *env, jobject obj, jint input){
    cerr << "Executing SingleInputClient" << endl;

    ABYParty *party = createClient();

    megaCircSingleInputClient(party, (uint32_t)input);

    party->ExecCircuit();

    delete party;
}

/*
 * Class:     NativeMeth
 * Method:    multiInputServer
 * Signature: ([II)I
 */
JNIEXPORT jint JNICALL Java_NativeMeth_multiInputServer(JNIEnv *env, jobject obj, jintArray input, jint type){
    return (jint)0;
}

/*
 * Class:     NativeMeth
 * Method:    multiInputClient
 * Signature: ([I)V
 */
JNIEXPORT void JNICALL Java_NativeMeth_multiInputClient(JNIEnv *env, jobject obj, jintArray input){

}