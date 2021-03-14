#include <TCs.h>
//#include "./TCs.h"
#include <Arduino.h>

// inverse NIST table d0-10; t90 = d0 + d1E + d2E^2 + ... dnE^n where E is in mV and t90 is in °C
// values taken from https://srdata.nist.gov/its90/type_b/bcoefficients_inverse.html
//
const static PROGMEM float invP_NISTtable [] = {        // virtually organized 11 lines x 23 columns
//   0.291 < B < 2.431   2.431 < B < 13.820  -8.825 < E < 0      0 < E < 76.373      -8.095 < J < 0      0 < J < 42.919    42.919 < J < 69.553 -5.891 < K < 0      0 < K < 20.644    20.644 < K < 54.886 -3.990 < N < 0    0 < N < 20.613    20.613 < N < 47.513 -0.226 < R < 1.923 1.923 < R < 13.228   11.361 < R < 19.739   19.739 < R < 21.103   -0.235 < S < 1.874  1.874 < S < 11.950    10.332 < S < 17.536   17.536 < S < 18.693   -5.603 < T < 0      0 < T < 20.872    
      9.8423321E+01  ,    2.1315071E+02  ,    0.0000000E+00  ,    0.0000000E+00  ,    0.0000000E+00  ,    0.000000E+00 ,   -3.11358187E+03 ,    0.0000000E+00  ,    0.000000E+00 ,   -1.318058E+02 ,    0.0000000E+00  ,    0.00000E+00  ,    1.972485E+01 ,    0.0000000E+00  ,    1.334584505E+01  ,   -8.199599416E+01  ,    3.406177836E+04  ,    0.00000000E+00 ,    1.291507177E+01  ,   -8.087801117E+01  ,    5.333875126E+04  ,    0.0000000E+00  ,    0.000000E+00  , 
      6.9971500E+02  ,    2.8510504E+02  ,    1.6977288E+01  ,    1.7057035E+01  ,    1.9528268E+01  ,    1.978425E+01 ,    3.00543684E+02 ,    2.5173462E+01  ,    2.508355E+01 ,    4.830222E+01 ,    3.8436847E+01  ,    3.86896E+01  ,    3.300943E+01 ,    1.8891380E+02  ,    1.472644573E+02  ,    1.553962042E+02  ,   -7.023729171E+03  ,    1.84949460E+02 ,    1.466298863E+02  ,    1.621573104E+02  ,   -1.235892298E+04  ,    2.5949192E+01  ,    2.592800E+01  , 
     -8.4765304E+02  ,   -5.2742887E+01  ,   -4.3514970E-01  ,   -2.3301759E-01  ,   -1.2286185E+00  ,   -2.001204E-01 ,   -9.94773230E+00 ,   -1.1662878E+00  ,    7.860106E-02 ,   -1.646031E+00 ,    1.1010485E+00  ,   -1.08267E+00  ,   -3.915159E-01 ,   -9.3835290E+01  ,   -1.844024844E+01  ,   -8.342197663E+00  ,    5.582903813E+02  ,   -8.00504062E+01 ,   -1.534713402E+01  ,   -8.536869453E+00  ,    1.092657613E+03  ,   -2.1316967E-01  ,   -7.602961E-01  , 
      1.0052644E+03  ,    9.9160804E+00  ,   -1.5859697E-01  ,    6.5435585E-03  ,   -1.0752178E+00  ,    1.036969E-02 ,    1.70276630E-01 ,   -1.0833638E+00  ,   -2.503131E-01 ,    5.464731E-02 ,    5.2229312E+00  ,    4.70205E-02  ,    9.855391E-03 ,    1.3068619E+02  ,    4.031129726E+00  ,    4.279433549E-01  ,   -1.952394635E+01  ,    1.02237430E+02 ,    3.145945973E+00  ,    4.719686976E-01  ,   -4.265693686E+01  ,    7.9018692E-01  ,    4.637791E-02  , 
     -8.3345952E+02  ,   -1.2965303E+00  ,   -9.2502871E-02  ,   -7.3562749E-05  ,   -5.9086933E-01  ,   -2.549687E-04 ,   -1.43033468E-03 ,   -8.9773540E-01  ,    8.315270E-02 ,   -9.650715E-04 ,    7.2060525E+00  ,   -2.12169E-06  ,   -1.274371E-04 ,   -2.2703580E+02  ,   -6.249428360E-01  ,   -1.191577910E-02  ,    2.560740231E-01  ,   -1.52248592E+02 ,   -4.163257839E-01  ,   -1.441693666E-02  ,    6.247205420E-01  ,    4.2527777E-01  ,   -2.165394E-03  , 
      4.5508542E+02  ,    1.1195870E-01  ,   -2.6084314E-02  ,   -1.7896001E-06  ,   -1.7256713E-01  ,    3.585153E-06 ,    4.73886084E-06 ,   -3.7342377E-01  ,   -1.228034E-02 ,    8.802193E-06 ,    5.8488586E+00  ,   -1.17272E-04  ,    7.767022E-07 ,    3.5145659E+02  ,    6.468412046E-02  ,    1.492290091E-04  ,    0.000000000E+00  ,    1.88821343E+02 ,    3.187963771E-02  ,    2.081618890E-04  ,    0.000000000E+00  ,    1.3304473E-01  ,    6.048144E-05  , 
     -1.5523037E+02  ,   -6.0625199E-03  ,   -4.1360199E-03  ,    8.4036165E-08  ,   -2.8131513E-02  ,   -5.344285E-08 ,    0.00000000E+00 ,   -8.6632643E-02  ,    9.804036E-04 ,   -3.110810E-08 ,    2.7754916E+00  ,    5.39280E-06  ,    0.000000E+00 ,   -3.8953900E+02  ,   -4.458750426E-03  ,    0.000000000E+00  ,    0.000000000E+00  ,   -1.59085941E+02 ,   -1.291637500E-03  ,    0.000000000E+00  ,    0.000000000E+00  ,    2.0241446E-02  ,   -7.293422E-07  , 
      2.9886750E+01  ,    1.8661696E-04  ,   -3.4034030E-04  ,   -1.3735879E-09  ,   -2.3963370E-03  ,    5.099890E-10 ,    0.00000000E+00 ,   -1.0450598E-02  ,   -4.413030E-05 ,    0.000000E+00 ,    7.7075166E-01  ,   -7.98156E-08  ,    0.000000E+00 ,    2.8239471E+02  ,    1.994710149E-04  ,    0.000000000E+00  ,    0.000000000E+00  ,    8.23027880E+01 ,    2.183475087E-05  ,    0.000000000E+00  ,    0.000000000E+00  ,    1.2668171E-03  ,    0.000000E+00  , 
     -2.4742860E+00  ,   -2.4878585E-06  ,   -1.1564890E-05  ,    1.0629823E-11  ,   -8.3823321E-05  ,    0.000000E+00 ,    0.00000000E+00 ,   -5.1920577E-04  ,    1.057734E-06 ,    0.000000E+00 ,    1.1582665E-01  ,    0.00000E+00  ,    0.000000E+00 ,   -1.2607281E+02  ,   -5.313401790E-06  ,    0.000000000E+00  ,    0.000000000E+00  ,   -2.34181944E+01 ,   -1.447379511E-07  ,    0.000000000E+00  ,    0.000000000E+00  ,    0.0000000E+00  ,    0.000000E+00  , 
      0.0000000E+00  ,    0.0000000E+00  ,    0.0000000E+00 ,    -3.2447087E-14  ,    0.0000000E+00  ,    0.000000E+00 ,    0.00000000E+00 ,    0.0000000E+00  ,   -1.052755E-08 ,    0.000000E+00 ,    7.3138868E-03  ,    0.00000E+00  ,    0.000000E+00 ,    3.1353611E+01  ,    6.481976217E-08  ,    0.000000000E+00  ,    0.000000000E+00  ,    2.79786260E+00 ,    8.211272125E-09  ,    0.000000000E+00  ,    0.000000000E+00  ,    0.0000000E+00  ,    0.000000E+00  , 
      0.0000000E+00  ,    0.0000000E+00  ,    0.0000000E+00  ,    0.0000000E+00  ,    0.0000000E+00  ,    0.000000E+00 ,    0.00000000E+00 ,    0.0000000E+00  ,    0.000000E+00 ,    0.000000E+00 ,    0.0000000E+00  ,    0.00000E+00  ,    0.000000E+00 ,   -3.3187769E+00  ,    0.000000000E+00  ,    0.000000000E+00  ,    0.000000000E+00  ,    0.00000000E+00 ,    0.000000000E+00  ,    0.000000000E+00  ,    0.000000000E+00  ,    0.0000000E+00  ,    0.000000E+00 
};

// NIST table c0-14; E = c0 + c1t90 + c2t90^2 + ... cnt90^n + a0*exp(a1(t90-a2)^2 where E is in mV and t90 is in °C
// values taken from https://srdata.nist.gov/its90/type_b/bcoefficients.html
//
const static PROGMEM float P_NISTtable [] = {       // virtually organized 18 lines x 18 columns
//            0 < B < 630.615       630.615 < B < 1820    -270 < E < 0          0 < E < 1000          -210 < J < 760        760 < J < 1200       -270 < K < 0           0 < K < 1372         -270 < N < 760         0 < N < 1300         -50 < R < 1064.18      1064.18 < R < 1664.5  1664.5 < R < 1768.1  -50 < S < 1064.18      1064.18 < S < 1664.5  1664.5 < S < 1768.1  -270 < T < 0           0 < T < 400         
/*  c0 = */   0.000000000000E+00 , -0.389381686210E+01 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.296456256810E+03 ,  0.000000000000E+00 , -0.176004136860E-01 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.295157925316E+01 ,  0.152232118209E+03 ,  0.000000000000E+00 ,  0.132900444085E+01 ,  0.146628232636E+03 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  
/*  c1 = */  -0.246508183460E-03 ,  0.285717474700E-01 ,  0.586655087080E-01 ,  0.586655087100E-01 ,  0.503811878150E-01 , -0.149761277860E+01 ,  0.394501280250E-01 ,  0.389212049750E-01 ,  0.261591059620E-01 ,  0.259293946010E-01 ,  0.528961729765E-02 , -0.252061251332E-02 , -0.268819888545E+00 ,  0.540313308631E-02 ,  0.334509311344E-02 , -0.258430516752E+00 ,  0.387481063640E-01 ,  0.387481063640E-01 ,  
/*  c2 = */   0.590404211710E-05 , -0.848851047850E-04 ,  0.454109771240E-04 ,  0.450322755820E-04 ,  0.304758369300E-04 ,  0.317871039240E-02 ,  0.236223735980E-04 ,  0.185587700320E-04 ,  0.109574842280E-04 ,  0.157101418800E-04 ,  0.139166589782E-04 ,  0.159564501865E-04 ,  0.171280280471E-03 ,  0.125934289740E-04 ,  0.654805192818E-05 ,  0.163693574641E-03 ,  0.441944343470E-04 ,  0.332922278800E-04 ,  
/*  c3 = */  -0.132579316360E-08 ,  0.157852801640E-06 , -0.779980486860E-06 ,  0.289084072120E-07 , -0.856810657200E-07 , -0.318476867010E-05 , -0.328589067840E-06 , -0.994575928740E-07 , -0.938411115540E-07 ,  0.438256272370E-07 , -0.238855693017E-07 , -0.764085947576E-08 , -0.345895706453E-07 , -0.232477968689E-07 , -0.164856259209E-08 , -0.330439046987E-07 ,  0.118443231050E-06 ,  0.206182434040E-06 ,  
/*  c4 = */   0.156682919010E-11 , -0.168353448640E-09 , -0.258001608430E-07 , -0.330568966520E-09 ,  0.132281952950E-09 ,  0.157208190040E-08 , -0.499048287770E-08 ,  0.318409457190E-09 , -0.464120397590E-10 , -0.252611697940E-09 ,  0.356916001063E-10 ,  0.205305291024E-11 , -0.934633971046E-14 ,  0.322028823036E-10 ,  0.129989605174E-13 , -0.943223690612E-14 ,  0.200329735540E-07 , -0.218822568460E-08 ,  
/*  c5 = */  -0.169445292400E-14 ,  0.111097940130E-12 , -0.594525830570E-09 ,  0.650244032700E-12 , -0.170529583370E-12 , -0.306913690560E-12 , -0.675090591730E-10 , -0.560728448890E-12 , -0.263033577160E-11 ,  0.643118193390E-12 , -0.462347666298E-13 , -0.293359668173E-15 ,  0.000000000000E+00 , -0.331465196389E-13 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.901380195590E-09 ,  0.109968809280E-10 ,  
/*  c6 = */   0.629903470940E-18 , -0.445154310330E-16 , -0.932140586670E-11 , -0.191974955040E-15 ,  0.209480906970E-15 ,  0.000000000000E+00 , -0.574103274280E-12 ,  0.560750590590E-15 , -0.226534380030E-13 , -0.100634715190E-14 ,  0.500777441034E-16 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.255744251786E-16 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.226511565930E-10 , -0.308157587720E-13 ,  
/*  c7 = */   0.989756408210E-20 ,  0.000000000000E+00 , -0.102876055340E-12 , -0.125366004970E-17 , -0.125383953360E-18 ,  0.000000000000E+00 , -0.310888728940E-14 , -0.320207200030E-18 , -0.760893007910E-16 ,  0.997453389920E-18 , -0.373105886191E-19 ,  0.000000000000E+00 ,  0.000000000000E+00 , -0.125068871393E-19 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.360711542050E-12 ,  0.454791352900E-16 ,  
/*  c8 = */  -0.937913302890E-24 ,  0.000000000000E+00 , -0.803701236210E-15 ,  0.214892175690E-20 ,  0.156317256970E-22 ,  0.000000000000E+00 , -0.104516093650E-16 ,  0.971511471520E-22 , -0.934196678350E-19 , -0.608632456070E-21 ,  0.157716482367E-22 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.271443176145E-23 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.384939398830E-14 , -0.275129016730E-19 ,  
/*  c9 = */   0.000000000000E+00 ,  0.000000000000E+00 , -0.439794973910E-17 , -0.143880417820E-23 ,  0.000000000000E+00 ,  0.000000000000E+00 , -0.198892668780E-19 , -0.121047212750E-25 ,  0.208492293390E-24 ,  0.000000000000E+00 , -0.281038625251E-26 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.282135219250E-16 ,  0.000000000000E+00 ,  
/* c10 = */   0.000000000000E+00 ,  0.000000000000E+00 , -0.164147763550E-19 ,  0.359608994810E-27 ,  0.000000000000E+00 ,  0.000000000000E+00 , -0.163226974860E-22 ,  0.000000000000E+00 , -0.306821961510E-28 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.142515947790E-18 ,  0.000000000000E+00 ,  
/* c11 = */   0.000000000000E+00 ,  0.000000000000E+00 , -0.396736195160E-22 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.487686622860E-21 ,  0.000000000000E+00 ,  
/* c12 = */   0.000000000000E+00 ,  0.000000000000E+00 , -0.558273287210E-25 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.107955392700E-23 ,  0.000000000000E+00 ,  
/* c13 = */   0.000000000000E+00 ,  0.000000000000E+00 , -0.346578420130E-28 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.139450270620E-26 ,  0.000000000000E+00 ,  
/* c14 = */   0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.797951539270E-30 ,  0.000000000000E+00 ,  
/*  a0 = */   0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.118597600000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  
/*  a1 = */   0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 , -0.118343200000E-03 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  
/*  a2 = */   0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.126968600000E+03 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 ,  0.000000000000E+00 , 
};

float TCs::InvPHorner ( float x, float * _in, int column, int lines ) {      // calculation of polynom for inverse NIST table using Horner's method
  int columns = 23;
  float r;
  int i;
  r = pgm_read_float( _in + ( lines * columns ) + column -1 );
  for (i = lines-1; i >= 0; i--)
    r = r*x + pgm_read_float( _in + ( i * columns ) + column -1 );
  return (float) r;
}


float TCs::PHorner ( float x, float * _in, int column, int lines ) {       // calculation of polynom for NIST table using Horner's method
  int columns = 18;
  float r;
  int i;
  r = pgm_read_float( _in + ( lines * columns ) + column -1 );
  for (i = lines-1; i >= 0; i--)
    r = r*x + pgm_read_float( _in + ( i * columns ) + column -1 );

    r = r + pgm_read_float( _in + ( (lines + 1) * columns ) + column -1) * exp(       // from here Gaussian part, parameters exist only for Type K but calculated for all, lines 15-17
            pgm_read_float( _in + ( (lines + 2) * columns ) + column -1) * (
            pgm_read_float( _in + ( (lines + 3) * columns ) + column -1) - x) * (
            pgm_read_float( _in + ( (lines + 3) * columns ) + column -1) - x) );
  return (float) r;
}



// calculate hot junction Temp from reading in mV and cold junction Temp in °C and thermocouple Type
//   all parameters and jump points to reference tables are hard coded
//
float TCs::getTemp_C (float hotJunctionVoltage, float coldJunctionTemp, char Type) {
  float PHorn_coldJunctionVoltage;
  int Nist_lines  = 14;
  int invNIST_lines = 10;
  
     if     (Type == 'B'){                  // B {  0.291 , 2.431 , 13.820 }, {    0.0 , 630.615 , 1820.0 }
         if      (coldJunctionTemp <      0.0)  PHorn_coldJunctionVoltage = _OutOfRange;         
         else if (coldJunctionTemp <= 630.615)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 1, Nist_lines);         
         else if (coldJunctionTemp <=  1820.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 2, Nist_lines);     
         else                                   PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <   0.291)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=  2.432)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 1, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 13.820)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 2, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'E'){                 // E { -8.825 , 0.000 , 76.373 }, { -270.0 ,   0.000 , 1000.0 },
         if     (coldJunctionTemp <  -270.0)  PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <=    0.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 3, Nist_lines);         
         else if(coldJunctionTemp <= 1000.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 4, Nist_lines);         
         else                                 PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -8.825)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=  0.000)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 3, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 76.373)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 4, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'J'){                 // J { -8.095 , 0.000 , 42.919 , 69.553 }, { -210.0 ,   760.0 , 1260.0 }
         if     (coldJunctionTemp <  -210.0)  PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <=  760.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 5, Nist_lines);         
         else if(coldJunctionTemp <= 1260.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 6, Nist_lines);         
         else                                 PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -8.095)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=  0.000)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 5, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 42.919)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 6, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 69.553)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 7, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'K'){              // K { -5.891 , 0.000 , 20.644 , 54.886 }, { -270.0 ,   0.000 , 1372.0 }
         if     (coldJunctionTemp <  -270.0)  PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <=    0.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 7, Nist_lines);         
         else if(coldJunctionTemp <= 1372.0)  PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 8, Nist_lines);         
         else                                 PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -5.891)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=    0.0)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable,  8, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 20.466)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable,  9, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 54.866)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 10, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'N'){              // N { -3.990 , 0.000 , 20.613 , 47.513 }, { -270.0 ,   0.000 , 1300.0 }
         if     (coldJunctionTemp <  -270.0) PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <=    0.0) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable,  9, Nist_lines);         
         else if(coldJunctionTemp <= 1300.0) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 10, Nist_lines);         
         else                                PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -3.990)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=    0.0)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable,  11, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 20.613)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable,  12, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 47.513)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable,  13, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'R'){              // R { -0.226 , 1.923 , 13.228 , 19.739 , 21.103 }, {  -50.0 , 1064.18 , 1664.5 , 1768.1 }
         if     (coldJunctionTemp <   -50.0) PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <= 1064.5) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 11, Nist_lines);         
         else if(coldJunctionTemp <= 1664.5) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 12, Nist_lines);         
         else if(coldJunctionTemp <= 1768.1) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 13, Nist_lines);         
         else                                PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -0.226)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=  1.923)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 14, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 13.228)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 15, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 19.739)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 16, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 21.103)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 17, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'S'){              // S { -0.235 , 1.874 , 11.950 , 17.536 , 18.693 }, {  -50.0 , 1064.18 , 1664.5 , 1768.1 }
         if     (coldJunctionTemp <   -50.0) PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <= 1064.5) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 14, Nist_lines);         
         else if(coldJunctionTemp <= 1664.5) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 15, Nist_lines);         
         else if(coldJunctionTemp <= 1768.1) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 16, Nist_lines);         
         else                                PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -0.235)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=  1.874)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 18, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 11.950)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 19, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 17.536)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 20, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 18.693)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 21, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else if(Type == 'T'){              // T { -5.603 , 0.000 , 20.872 }, { -270.0 ,   0.000 ,  400.0 }
         if     (coldJunctionTemp <  -50.0) PHorn_coldJunctionVoltage = _OutOfRange;     
         else if(coldJunctionTemp <=   0.0) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 17, Nist_lines);         
         else if(coldJunctionTemp <= 400.0) PHorn_coldJunctionVoltage = PHorner(coldJunctionTemp, P_NISTtable, 18, Nist_lines);         
         else                               PHorn_coldJunctionVoltage = _OutOfRange;      

         if     (hotJunctionVoltage + PHorn_coldJunctionVoltage <  -5.603)  return _OutOfRange;     
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <=    0.0)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 22, invNIST_lines);         
         else if(hotJunctionVoltage + PHorn_coldJunctionVoltage <= 20.872)  return InvPHorner(hotJunctionVoltage + PHorn_coldJunctionVoltage, invP_NISTtable, 23, invNIST_lines);         
         else                                                               return _OutOfRange;      
     }
     else {
        return _OutOfRange;      
     }
}
