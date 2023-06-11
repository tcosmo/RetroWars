#include "geometry.h"

std::ostream& operator<< (std::ostream &os, const Dimension& dim)
{ 
	os << "D{" << dim.w << ", " <<  dim.h<< "}";
	return os; 
}
