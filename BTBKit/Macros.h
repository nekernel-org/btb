// ============================================================= //
// btb
// Copyright (C) 2024, Amlal EL Mahrouss, all rights reserved.
// ============================================================= //

#pragma once

#include <cassert>

#define LIKELY(ARG) (ARG) ? assert(false) : ((void)0)
#define UNLIKELY(ARG) LIKELY(!(ARG))

#define BTBKIT_VERSION "1.2.0"

#define BTBKIT_VERSION_BCD 0x0120

#define BTBKIT_VERSION_MAJOR 1
#define BTBKIT_VERSION_MINOR 0
#define BTBKIT_VERSION_PATCH 0

#define BTB_UNUSED(X) ((void)X)
