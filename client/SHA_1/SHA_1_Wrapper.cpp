#include "SHA_1_Wrapper.h"

#include "sha1.hpp"


std::string sha_1::hash(const std::string& value)
{
	auto checksum = std::make_unique<SHA1>();
	checksum->update(value);
	return checksum->final();
}