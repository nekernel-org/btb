// ============================================================= //
// btb
// Copyright ZKA Technologies.
// ============================================================= //

#pragma once

#include <cassert>

#define LIKELY(ARG) (ARG) ? assert(false) : (void)0
#define UNLIKELY(ARG) LIKELY(!(ARG))

#define BTBKIT_VERSION "1.0.0"

#define BTBKIT_VERSION_BCD 0x0100

#define BTBKIT_VERSION_MAJOR 1
#define BTBKIT_VERSION_MINOR 0
#define BTBKIT_VERSION_PATCH 0

#define BTB_UNUSED(X) ((void)X)
