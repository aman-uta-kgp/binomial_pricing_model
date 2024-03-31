#include "crr_binomial.h";
#include <math.h>
#include <iostream>

using namespace std;

crr::crr(float volatility,
	float delta_time,
	float interest_rate,
	float spot_price,
	float strike_price
) {
	vol = volatility;
	delta_t = delta_time;
	rate = interest_rate;
	spot = spot_price;
	strike = strike_price;

}

crr::~crr() {}

float crr::get_price_up() {
	double sqrt_delta_t = sqrt(delta_t);
	return spot * exp(vol * sqrt_delta_t);
}

float crr::get_price_down() {
	double sqrt_delta_t = sqrt(delta_t);
	return spot * exp(-1*vol * sqrt_delta_t);
}

float crr::get_p_factor() {
	double u = get_price_up() / spot;
	double d = get_price_down() / spot;
	return  (exp(1 * rate * delta_t) - d) / (u - d);
	
}

float crr::get_value_f() {
	float f_u = max(0.0f, get_price_up() - strike);
	float f_d = max(0.0f, get_price_down() - strike);

	float disc = exp(-1 * rate * delta_t);

	return (disc * (get_p_factor() * f_u + (1 - get_p_factor()) * f_d));
}


