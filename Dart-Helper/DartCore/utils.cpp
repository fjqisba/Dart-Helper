#include "utils.h"

intptr_t Utils::StrNLen(const char* s, intptr_t n)
{
	return strnlen(s, n);
}