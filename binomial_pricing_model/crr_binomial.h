#pragma once
#include <iostream>

class crr {
public: 
	crr(float , float, float, float, float);

	~crr();

	float getprice_t0();
	float get_price_up();
	float get_price_down();
	float get_p_factor();
	float get_value_f();

private:
	float delta_t;
	float vol;
	float rate;
	float spot;
	float strike;
	float f_value;
	float p_factor;
	float u;
	float d;
	float f_u;
	float f_d;
	
};