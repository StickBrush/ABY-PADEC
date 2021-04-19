#include "./circ_lib/circs_server.hpp"

using namespace std;

int main()
{
    ABYParty* party = new ABYParty(SERVER, "127.0.0.1", (uint16_t)7766U, LT, 3U, 1U, MT_OT, 65536U, "./extern/ABY/bin/circ/");

    uint32_t input_array[4] = {1, 1, 2, 2};

    vector<uint32_t> input = vector<uint32_t>(input_array, input_array + 4);

    share* output = megaCircMultiInput(party, input, CIRC_WITHIN);

    party->ExecCircuit();

    uint32_t clear_out = output->get_clear_value<uint32_t>();

    cout << "Output: " << clear_out << endl;

    delete party;

    return 0;
}