#include <iostream>
#include <dai/factorgraph.h>

using namespace std;
using namespace dai;

int main()
{
    // Define variables
    Var X0(0, 2); // Variable with ID 0 and 2 states
    Var X1(1, 2); // Variable with ID 1 and 2 states

    // Define factors
    vector<Factor> factors;
    factors.push_back(Factor(X0));
    factors.push_back(Factor(X1));

    // Construct factor graph
    FactorGraph fg(factors);

    // Print out the factor graph
    cout << "Factor Graph:\n"
         << fg << endl;

    // Clamp variable X0 to state 1
    size_t x0_value = 1;
    fg.clamp(0, x0_value);

    // Print out the factor graph after clamping
    cout << "Factor Graph after clamping X0 to state " << x0_value << ":\n"
         << fg << endl;

    return 0;
}