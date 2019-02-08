#include "representable.h"

#include <ostream>
#include <string>

std::ostream & operator<<(std::ostream & stream, const Representable & printable) {
	return stream << printable.asText();
}

