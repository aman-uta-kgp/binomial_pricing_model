#include <vector>
#include <iostream>
#include "lattice.h"
#include <iomanip>

using namespace std;

Lattice::Lattice(int n, double s_0) {
    num_steps = n;
    original_spot = s_0;
    // Initialize the lattice with dimensions num_steps x num_steps
    lattice.resize(num_steps, std::vector<double>(num_steps, -999999.0));
    lattice[0][0] = original_spot;


}

Lattice::~Lattice() {}

void Lattice::update_lattice(double up_movement, double down_movement,  int j, int t) {
    // Check if the lattice has been initialized
    if (lattice.empty()) {
        // Handle error: Lattice is not initialized
        return;
    }

    lattice[j][t + 1.0] = up_movement;
    lattice[j + 1.0][t + 1.0] = down_movement;
}

double Lattice::access_lattice(int node_pos, int time_step) const {
    // Check if the lattice has been initialized
    if (lattice.empty()) {
        // Handle error: Lattice is not initialized
        return 0.0; // Return a default value
    }

    // Check if the time step and node indices are valid
    if (time_step < 0 || time_step >= num_steps || node_pos < 0 || node_pos >= num_steps) {
        // Handle error: Invalid time step or node index
        return 0.0; // Return a default value
    }

    // Return the value at the specified time step and node
    return lattice[node_pos][time_step];
}

int Lattice::get_num_steps() const {
    return num_steps;
}

void Lattice::print_lattice() const {
    // Check if the lattice has been initialized
    if (lattice.empty()) {
        cout << "Lattice is not initialized." << endl;
        return;
    }

    const double uninitialized_value = -999999.0; // Choose a special value to indicate uninitialized elements

    // Print the lattice
    for (int i = 0; i < num_steps; ++i) {
        for (int j = 0; j < num_steps; ++j) {
             /*Check if the value at the position is uninitialized*/
            if (lattice[i][j] == uninitialized_value) {
                // Print null value for positions that haven't been assigned any values
                std::cout << std::setw(8) << " ";
            }
            else {
                // Print the value at the position
                std::cout << std::setw(8) << lattice[i][j];
            }
        }
        std::cout << std::endl;
    }
}

void Lattice::update_lattice_values(double option_value,  int node_pos, int time_step) {
    lattice[node_pos][time_step] = option_value;
}

