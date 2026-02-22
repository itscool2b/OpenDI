/*
 * OpenDI - Master Header File
 * 
 * Include this single header to access all OpenDI functionality:
 * 
 *     #include "opendi.h"
 * 
 * This header includes all primitive operations, calculus functions,
 * linear algebra operations, and the arena allocator.
 */

#ifndef OPENDI_H
#define OPENDI_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Arena Allocator
 * Linear allocator for fast, contiguous memory allocations
 */
#include "arena.h"

/*
 * Primitive Operations
 * Basic arithmetic and mathematical utilities
 */
#include "primitive/absolute.h"
#include "primitive/add.h"
#include "primitive/divide.h"
#include "primitive/exponents.h"
#include "primitive/minmax.h"
#include "primitive/multiply.h"
#include "primitive/rounding.h"
#include "primitive/subtract.h"

/*
 * Calculus
 * Numerical differentiation and integration
 */
#include "calculus/forwarddiff.h"
#include "calculus/backwarddiff.h"
#include "calculus/centraldiff.h"
#include "calculus/secondderivative.h"
#include "calculus/romberg.h"

/*
 * Linear Algebra - Vectors
 * Vector operations for 2D, 3D, and n-dimensional vectors
 */
#include "linalg/vectors/vecadd.h"
#include "linalg/vectors/veccross.h"
#include "linalg/vectors/vecdot.h"
#include "linalg/vectors/vecnorm.h"
#include "linalg/vectors/vecscale.h"

#ifdef __cplusplus
}
#endif

#endif /* OPENDI_H */
