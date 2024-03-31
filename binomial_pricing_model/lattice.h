#ifndef LATTICE_H
#define LATTICE_H

#include <vector>

class Lattice {
public:
    Lattice(int num_steps, double original_spot);
    ~Lattice();
    void update_lattice(double up_movement, double down_movement, int time_step, int node_pos);
    void update_lattice_values(double option_value, int time_step, int node_pos);
    double access_lattice(int time_step, int node_pos) const;
    int get_num_steps() const;
    void print_lattice() const;

private:
    int num_steps;
    double original_spot;
    std::vector<std::vector<double>> lattice;
};

#endif // LATTICE_H
