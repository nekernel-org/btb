#pragma once

#include <cassert>

#define LIKELY(ARG) (ARG) ? assert(false) : (void)0
#define UNLIKELY(ARG) LIKELY(!(ARG))

#define BTBKIT_VERSION "1.0.0"

#define BTB_UNUSED(X) ((void)X)
