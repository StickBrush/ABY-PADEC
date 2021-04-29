#include "../extern/ABY/src/abycore/circuit/booleancircuits.h"
#include "../extern/ABY/src/abycore/circuit/arithmeticcircuits.h"
#include "../extern/ABY/src/abycore/circuit/circuit.h"
#include "../extern/ABY/src/abycore/sharing/sharing.h"
#include "../extern/ABY/src/abycore/aby/abyparty.h"
#include "../extern/ABY/src/abycore/ABY_utils/ABYconstants.h"
#include <math.h>
#include <cassert>

using namespace std;

ABYParty *createClient(string ip_address = "127.0.0.1", int port = 7766U, seclvl seclvl = LT, uint32_t bitlen = 32U, uint32_t threads = 1U, string aby_circ_dir = "./extern/ABY/bin/circ");
Circuit* createCircuit(ABYParty *party, e_sharing chosen_sharing);
share *megaCircSingleInput(ABYParty *party, uint32_t input, uint32_t bitlen = 32);
share *range_inner(BooleanCircuit *bc, share *x_server, share *y_server, share *x_client, share *y_client);
share *within_inner(BooleanCircuit *bc, share *x_1_server, share *x_2_server, share *y_1_server, share *y_2_server, share *x_client, share *y_client);
share *megaCircMultiInput(ABYParty *party, vector<uint32_t> input, uint32_t bitlen = 32);