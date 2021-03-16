# TCs for arduino

	TCs.h - library to get temperature for all standard thermocouples including Type B, E, J, K, N, R, S and T, knowing Type, coldJunctionTemperature and hotJunctionVoltage
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
