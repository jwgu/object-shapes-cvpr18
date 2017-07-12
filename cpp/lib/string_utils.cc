//
// Created by daeyun on 6/20/17.
//

#include "string_utils.h"

#include <iomanip>
#include <sstream>

namespace mvshape {

std::string WithLeadingZeros(int value, int num_digits) {
  std::stringstream stream;
  stream << std::setfill('0') << std::setw(num_digits) << value;
  return stream.str();
}

}
