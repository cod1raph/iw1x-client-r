#pragma once

#define WIN32_LEAN_AND_MEAN

// Windows
#include <Windows.h>
#include <atlbase.h>
#include <dbghelp.h>
#include <wincrypt.h>

// C++
#include <cassert>
#include <fstream>
#include <queue>
#include <sstream>
#include <string>

// Submodules
#include <MinHook.h>

/*
Size found using Ghidra
IMAGE_NT_HEADERS32 -> IMAGE_OPTIONAL_HEADER32: SizeOfImage - SizeOfHeaders
*/
constexpr auto BINARY_PAYLOAD_SIZE = 0x15C1000;

constexpr auto MOD_NAME = "iw1x-r";

#pragma warning(disable: 26440) // Disable "Function '' can be declared 'noexcept'" warning