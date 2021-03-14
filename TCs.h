/*
	TCs.h - library to get temperature for all standard thermocouples, knowing Type, coldJunctionTemperature and hotJunctionVoltage
	created by Dieter Reichl, 2021-03
	released into public domain

	using it by getTemp_C (float hotJunctionVoltage, float coldJunctionTemp, char Type) with parameters:
		hotJunctionVoltage: in mV
		coldJunctionTemp: in °C
		Type: simply by respective character

	code has been created to use ADS1118 and ADS1220 as thermometer and temp controller, just by connecting themocouple at their inputs
	calculation is using parameters from NIST for polynominal approximation from here https://srdata.nist.gov/its90/type_b/bcoefficients_inverse.html, by Horner method for best accuracy and maximum speed
	parameters are kept in matrix and stored and used by PROGMEM

	has been compared against routines on basis of LookUpTable to receive less than 0.05K error, and more compact routine and was found the most fastest one with similiar size, but maybe just due to my limited capabilities

*/


#ifndef TCs_h
#define TCs_h


class TCs {

private:
          float InvPHorner ( float x, float * _in, int column, int lines );   // calculation of polynom for inverse NIST table using Horner's method
          float    PHorner ( float x, float * _in, int column, int lines );   // calculation of polynom for NIST table using Horner's method, including Gaussian part for Type 'K' 
          float _OutOfRange = -300.0;

public:
          // hotJunctionVoltage in 'mV', hotJunctionVoltage in '°C', Type as Character 'B', 'E', 'J', 'K', 'N', 'R', 'S', 'T', Temp is returned as float in °C
         float getTemp_C (float hotJunctionVoltage, float coldJunctionTemp, char Type);
};
#endif
