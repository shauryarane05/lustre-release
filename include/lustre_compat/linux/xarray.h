/* SPDX-License-Identifier: GPL-2.0+ */

#ifndef _LINUX_XARRAY_LUSTRE_H
#define _LINUX_XARRAY_LUSTRE_H

#define HAVE_XARRAY_SUPPORT 1

#ifdef HAVE_XARRAY_SUPPORT
#include <linux/xarray.h>
#else
// Only define compatibility helpers, types, and macros if the kernel does NOT provide them
#define BITS_PER_XA_VALUE (BITS_PER_LONG - 1)

static inline void *xa_mk_value(unsigned long v)
{
	WARN_ON((long)v < 0);
	return (void *)((v << 1) | 1);
}

static inline unsigned long xa_to_value(const void *entry)
{
	return (unsigned long)entry >> 1;
}

static inline bool xa_is_value(const void *entry)
{
	return (unsigned long)entry & 1;
}

static inline void *xa_tag_pointer(void *p, unsigned long tag)
{
	return (void *)((unsigned long)p | tag);
}

static inline void *xa_untag_pointer(void *entry)
{
	return (void *)((unsigned long)entry & ~3UL);
}

static inline unsigned int xa_pointer_tag(void *entry)
{
	return (unsigned long)entry & 3UL;
}

static inline void *xa_mk_internal(unsigned long v)
{
	return (void *)((v << 2) | 2);
}

static inline unsigned long xa_to_internal(const void *entry)
{
	return (unsigned long)entry >> 2;
}

static inline bool xa_is_internal(const void *entry)
{
	return ((unsigned long)entry & 3) == 2;
}

#define XA_ZERO_ENTRY xa_mk_internal(257)

static inline bool xa_is_zero(const void *entry)
{
	return unlikely(entry == XA_ZERO_ENTRY);
}

static inline bool xa_is_err(const void *entry)
{
	return unlikely(xa_is_internal(entry) &&
			entry >= xa_mk_internal(-MAX_ERRNO));
}

static inline int xa_err(void *entry)
{
	if (xa_is_err(entry))
		return (long)entry >> 2;
	return 0;
}

struct xa_limit {
	u32 max;
	u32 min;
};

#define XA_LIMIT(_min, _max) (struct xa_limit) { .min = _min, .max = _max }

#define xa_limit_32b	XA_LIMIT(0, UINT_MAX)
#define xa_limit_31b	XA_LIMIT(0, INT_MAX)

typedef unsigned __bitwise xa_mark_t;
#define XA_MARK_0		((__force xa_mark_t)0U)
#define XA_MARK_1		((__force xa_mark_t)1U)
#define XA_MARK_2		((__force xa_mark_t)2U)
#define XA_PRESENT		((__force xa_mark_t)8U)
#define XA_MARK_MAX		XA_MARK_2
#define XA_FREE_MARK		XA_MARK_0

enum xa_lock_type {
	XA_LOCK_IRQ = 1,
	XA_LOCK_BH = 2,
};

#define XA_FLAGS_LOCK_IRQ	((__force gfp_t)XA_LOCK_IRQ)
#define XA_FLAGS_LOCK_BH	((__force gfp_t)XA_LOCK_BH)
#define XA_FLAGS_TRACK_FREE	((__force gfp_t)4U)
#define XA_FLAGS_ZERO_BUSY	((__force gfp_t)8U)
#define XA_FLAGS_ALLOC_WRAPPED	((__force gfp_t)16U)
#define XA_FLAGS_ACCOUNT	((__force gfp_t)32U)
#define XA_FLAGS_MARK(mark)	((__force gfp_t)((1U << __GFP_BITS_SHIFT) << \
					(__force unsigned)(mark)))
#define XA_FLAGS_ALLOC	(XA_FLAGS_TRACK_FREE | XA_FLAGS_MARK(XA_FREE_MARK))
#define XA_FLAGS_ALLOC1	(XA_FLAGS_TRACK_FREE | XA_FLAGS_ZERO_BUSY)

struct xarray {
	spinlock_t	xa_lock;
	gfp_t		xa_flags;
	void __rcu	*xa_head;
};

#define XARRAY_INIT(name, flags) {\
	.xa_lock = __SPIN_LOCK_UNLOCKED(name.xa_lock),\
	.xa_flags = flags,\
	.xa_head = NULL,\
}
#define DEFINE_XARRAY_FLAGS(name, flags)\
	struct xarray name = XARRAY_INIT(name, flags)
#define DEFINE_XARRAY(name) DEFINE_XARRAY_FLAGS(name, 0)
#define DEFINE_XARRAY_ALLOC(name) DEFINE_XARRAY_FLAGS(name, XA_FLAGS_ALLOC)
#define DEFINE_XARRAY_ALLOC1(name) DEFINE_XARRAY_FLAGS(name, XA_FLAGS_ALLOC1)

#endif // HAVE_XARRAY_SUPPORT

#endif // _LINUX_XARRAY_LUSTRE_H
