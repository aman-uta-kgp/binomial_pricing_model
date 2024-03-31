#include <iostream>
#include<math.h> 
#include "crr_binomial.h"
#include "lattice.h"
#include <string>

using namespace std;


enum BinomialExecution
{
	num_time_steps = 1,
	spot_t_0 = 2,
	volatility = 3,
	delta_time = 4,
	interest_rate = 5,
	strike_price = 6	
};


int main(int argc, const char* argv[]) {

	// Check if the expected number of command line arguments is provided
	if (argc != 7) {
		std::cerr << "Usage: " << argv[0] << " <num_time_steps> <spot_t_0> <volatility> <delta_time> <interest_rate> <strike_price>\n";
		return 1; // Return error code
	}

	// Convert command line arguments to double
	double num_time_steps = std::stod(argv[BinomialExecution::num_time_steps]);
	double spot_t_0 = std::stod(argv[BinomialExecution::spot_t_0]);
	double volatility = std::stod(argv[BinomialExecution::volatility]);
	double delta_time = std::stod(argv[BinomialExecution::delta_time]);
	double interest_rate = std::stod(argv[BinomialExecution::interest_rate]);
	double strike_price = std::stod(argv[BinomialExecution::strike_price]);



	Lattice lattice(num_time_steps, spot_t_0);
	

	for (int t = 0; t < num_time_steps-1; t++) {
		for (int node = 0; node <= t; node++) {
			
			double spot_t = lattice.access_lattice(node, t);
			crr crr_forward(volatility, delta_time, interest_rate, lattice.access_lattice(node, t), strike_price);

			double up_price = crr_forward.get_price_up();
			double down_price = crr_forward.get_price_down();

			lattice.update_lattice(up_price, down_price, node, t);			
		}
	}
	cout << "Spot Price Lattice using CRR strategy for price movements" << endl;
	lattice.print_lattice();

	Lattice lattice_values(num_time_steps, 0);

	//option values at last set of nodes

	for (int node = 0; node < num_time_steps; node++) {
		double spot = lattice.access_lattice(node, num_time_steps-1);
		double option_value = max(0.0, spot - strike_price);
		lattice_values.update_lattice_values(option_value, node, num_time_steps-1);
	}


	// backward propagation through lattice

	for (int t = num_time_steps-2; t >= 0; t--) {
		for (int node = 0; node <= t; node++) {

			double val_upward_movement = lattice_values.access_lattice(node, t+1);
			double val_downward_movement = lattice_values.access_lattice( node+1, t+1);
			crr crr_backward(volatility, delta_time, interest_rate, lattice.access_lattice(node, t), strike_price);
			double p_val = crr_backward.get_p_factor();

			double option_value = exp(-1 * interest_rate * delta_time) * 
				((p_val * val_upward_movement) + ((1 - p_val) * val_downward_movement));

			lattice_values.update_lattice_values(option_value, node, t);

		}
	}
	cout << "Option Value Lattice using CRR strategy" << endl;
	lattice_values.print_lattice();

	cout << "Option Value : " << lattice_values.access_lattice(0, 0) << endl;
}