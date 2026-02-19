
#include "units_functions.h"

double MlToTsp(double volume) { return (volume / 4.929); }

double MlToTbsp(double volume) { return (MlToTsp(volume) / 3); }

double MlToOz(double volume) { return (MlToTbsp(volume) / 2); }

double MlToCup(double volume) { return (MlToOz(volume) / 8); }