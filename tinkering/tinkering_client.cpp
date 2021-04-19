#include "./circ_lib/circs_client.hpp"

using namespace std;

int main()
{
    ABYParty *party = new ABYParty(CLIENT, "127.0.0.1", (uint16_t)7766U, LT, 3U, 1U, MT_OT, 65536U, "./extern/ABY/bin/circ/");

    uint32_t input_array[2] = {0, 0};

    vector<uint32_t> input = vector<uint32_t>(input_array, input_array+2);

    share *output = megaCircMultiInput(party, input);

    party->ExecCircuit();
    
    delete party;

    return 0;
}