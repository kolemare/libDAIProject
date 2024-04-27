#include "Sprinkler.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using namespace dai;

void Sprinkler::runSprinkler()
{
    Var C(0, 2); // Cloudy
    Var S(1, 2); // Sprinkler
    Var R(2, 2); // Rain
    Var W(3, 2); // Wetgrass

    // Define factors
    Factor P_C(C);
    P_C.set(0, 0.5);
    P_C.set(1, 0.5);

    Factor P_S_given_C(VarSet(S, C));
    P_S_given_C.set(0, 0.5);
    P_S_given_C.set(1, 0.9);
    P_S_given_C.set(2, 0.5);
    P_S_given_C.set(3, 0.1);

    Factor P_R_given_C(VarSet(R, C));
    P_R_given_C.set(0, 0.8);
    P_R_given_C.set(1, 0.2);
    P_R_given_C.set(2, 0.2);
    P_R_given_C.set(3, 0.8);

    Factor P_W_given_S_R(VarSet(S, R) | W);
    P_W_given_S_R.set(0, 1.0);
    P_W_given_S_R.set(1, 0.1);
    P_W_given_S_R.set(2, 0.1);
    P_W_given_S_R.set(3, 0.01);
    P_W_given_S_R.set(4, 0.0);
    P_W_given_S_R.set(5, 0.9);
    P_W_given_S_R.set(6, 0.9);
    P_W_given_S_R.set(7, 0.99);

    vector<Factor> SprinklerFactors;
    SprinklerFactors.push_back(P_C);
    SprinklerFactors.push_back(P_R_given_C);
    SprinklerFactors.push_back(P_S_given_C);
    SprinklerFactors.push_back(P_W_given_S_R);
    FactorGraph SprinklerNetwork(SprinklerFactors);

    // Write factorgraph to a file
    SprinklerNetwork.WriteToFile("sprinkler.fg");
    cout << "Sprinkler network written to sprinkler.fg" << endl;

    // Output some information about the factorgraph
    cout << SprinklerNetwork.nrVars() << " variables" << endl;
    cout << SprinklerNetwork.nrFactors() << " factors" << endl;

    // Calculate joint probability of all four variables
    Factor P;
    for (size_t I = 0; I < SprinklerNetwork.nrFactors(); I++)
    {
        P *= SprinklerNetwork.factor(I);
    }

    // P.normalize(); // Not necessary: a Bayesian network is already normalized by definition
    // Calculate some probabilities
    Real denom = P.marginal(W)[1];
    cout << "P(W=1) = " << denom << endl;
    cout << "P(S=1 | W=1) = " << P.marginal(VarSet(S, W))[3] / denom << endl;
    cout << "P(R=1 | W=1) = " << P.marginal(VarSet(R, W))[3] / denom << endl;
    return;
}