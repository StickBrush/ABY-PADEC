#include "../extern/ABY/src/abycore/circuit/booleancircuits.h"
#include "../extern/ABY/src/abycore/circuit/arithmeticcircuits.h"
#include "../extern/ABY/src/abycore/circuit/circuit.h"
#include "../extern/ABY/src/abycore/sharing/sharing.h"
#include "../extern/ABY/src/abycore/aby/abyparty.h"
#include "../extern/ABY/src/abycore/ABY_utils/ABYconstants.h"
#include <math.h>
#include <map>
#include <cassert>

using namespace std;

enum SingleCircuitType {
    CIRC_LESS_THAN,
    CIRC_GREATER_THAN,
    CIRC_EQUAL,
    CIRC_AND,
    CIRC_OR
};

enum MultiCircuitType {
    CIRC_RANGE,
    CIRC_WITHIN
};

Circuit *createCircuit(ABYParty *party, e_sharing chosen_sharing = S_BOOL);
share *megaCircSingleInput(ABYParty *party, uint32_t input, SingleCircuitType circ, uint32_t bitlen = 32);
share *range_inner(BooleanCircuit *bc, share *x_server, share *y_server, share *x_client, share *y_client);
share *within_inner(BooleanCircuit *bc, share *x_1_server, share *x_2_server, share *y_1_server, share *y_2_server, share *x_client, share *y_client);
share *megaCircMultiInput(ABYParty *party, vector<uint32_t> input, MultiCircuitType circ, uint32_t bitlen = 32);