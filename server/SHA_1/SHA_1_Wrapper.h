/**
\file SHA_1_Wrapper.h
\brief Обёртка над модулем расчёта хэша (sha-1) строки 
*/

#pragma once

#include <string>

namespace sha_1 {
	std::string hash(const std::string& value);
}