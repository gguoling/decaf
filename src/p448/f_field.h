/**
 * @file f_field.h
 * @brief Field-specific code.
 * @copyright
 *   Copyright (c) 2014 Cryptography Research, Inc.  \n
 *   Released under the MIT License.  See LICENSE.txt for license information.
 * @author Mike Hamburg
 */
#ifndef __F_FIELD_H__
#define __F_FIELD_H__ 1

#include <string.h>
#include "constant_time.h"

#include "p448.h"
#define FIELD_BITS           448
#define field_t              p448_t
#define field_mul            p448_mul
#define field_sqr            p448_sqr
#define field_add            p448_add
#define field_sub            p448_sub
#define field_mulw           p448_mulw
#define field_addw           p448_addw
#define field_subw           p448_subw
#define field_neg            p448_neg
#define field_set_ui         p448_set_ui
#define field_bias           p448_bias
#define field_cond_neg       p448_cond_neg
#define field_inverse        p448_inverse
#define field_eq             p448_eq
#define field_isr            p448_isr
#define field_simultaneous_invert p448_simultaneous_invert
#define field_weak_reduce    p448_weak_reduce
#define field_strong_reduce  p448_strong_reduce
#define field_serialize      p448_serialize
#define field_deserialize    p448_deserialize
#define field_is_zero        p448_is_zero

#endif /* __F_FIELD_H__ */
