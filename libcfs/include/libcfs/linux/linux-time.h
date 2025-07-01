/* SPDX-License-Identifier: GPL-2.0 */

/*
 * Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 2014, Intel Corporation.
 */

/*
 * This file is part of Lustre, http://www.lustre.org/
 *
 * Implementation of portable time API for Linux (kernel and user-level).
 *
 * Author: Nikita Danilov <nikita@clusterfs.com>
 */

#ifndef __LIBCFS_LINUX_LINUX_TIME_H__
#define __LIBCFS_LINUX_LINUX_TIME_H__

/* Portable time API */
#include <linux/hrtimer.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/jiffies.h>
#include <linux/hrtimer.h>
#include <linux/types.h>
#include <linux/time.h>
#include <asm/div64.h>

/*
 * Generic kernel stuff
 */
#ifdef HAVE_TIMESPEC64
// Kernel provides struct timespec64 and related conversion functions, do not redefine
#else
// (Compatibility implementation here if needed)
#endif /* HAVE_TIMESPEC64 */

#ifdef HAVE_NS_TO_TIMESPEC64
// Kernel provides ns_to_timespec64, do not redefine
#endif /* HAVE_NS_TO_TIMESPEC64 */

#ifdef HAVE_KTIME_ADD
// Kernel provides ktime_add, do not redefine
#endif /* HAVE_KTIME_ADD */

#ifdef HAVE_KTIME_AFTER
// Kernel provides ktime_after, do not redefine
#endif /* HAVE_KTIME_AFTER */

#ifdef HAVE_KTIME_BEFORE
// Kernel provides ktime_before, do not redefine
#endif /* HAVE_KTIME_BEFORE */

#ifdef HAVE_KTIME_COMPARE
// Kernel provides ktime_compare, do not redefine
#endif /* HAVE_KTIME_COMPARE */

#ifdef HAVE_KTIME_GET_TS64
// Kernel provides ktime_get_ts64, do not redefine
#endif /* HAVE_KTIME_GET_TS64 */

#ifdef HAVE_KTIME_GET_REAL_TS64
// Kernel provides ktime_get_real_ts64, do not redefine
#endif /* HAVE_KTIME_GET_REAL_TS */

#ifdef HAVE_KTIME_GET_REAL_SECONDS
// Kernel provides ktime_get_real_seconds, do not redefine
#endif /* HAVE_KTIME_GET_REAL_SECONDS */

#ifdef HAVE_KTIME_GET_SECONDS
// Kernel provides ktime_get_seconds, do not redefine
#endif /* HAVE_KTIME_GET_SECONDS */

#ifdef HAVE_KTIME_MS_DELTA
// Kernel provides ktime_ms_delta, do not redefine
#endif /* HAVE_KTIME_MS_DELTA */

#ifdef HAVE_KTIME_TO_TIMESPEC64
// Kernel provides ktime_to_timespec64, do not redefine
#endif /* HAVE_KTIME_TO_TIMESPEC64 */

#ifdef HAVE_TIMESPEC64_SUB
// Kernel provides timespec64_sub, do not redefine
#endif /* HAVE_TIMESPEC64_SUB */

#ifdef HAVE_TIMESPEC64_TO_KTIME
// Kernel provides timespec64_to_ktime, do not redefine
#endif /* HAVE_TIMESPEC64_TO_KTIME */

static inline unsigned long cfs_time_seconds(time64_t seconds)
{
	return nsecs_to_jiffies64(seconds * NSEC_PER_SEC);
}

#ifdef HAVE_NEW_DEFINE_TIMER
# ifndef TIMER_DATA_TYPE
# define TIMER_DATA_TYPE struct timer_list *
# endif

#define CFS_DEFINE_TIMER(_name, _function, _expires, _data) \
	DEFINE_TIMER((_name), (_function))
#else
# ifndef TIMER_DATA_TYPE
# define TIMER_DATA_TYPE unsigned long
# endif

#define CFS_DEFINE_TIMER(_name, _function, _expires, _data) \
	DEFINE_TIMER((_name), (_function), (_expires), (_data))
#endif

#ifdef HAVE_TIMER_SETUP
#define cfs_timer_cb_arg_t struct timer_list *
#define cfs_from_timer(var, callback_timer, timer_fieldname) \
	from_timer(var, callback_timer, timer_fieldname)
#define cfs_timer_setup(timer, callback, data, flags) \
	timer_setup((timer), (callback), (flags))
#define cfs_timer_cb_arg(var, timer_fieldname) (&(var)->timer_fieldname)
#else
#define cfs_timer_cb_arg_t unsigned long
#define cfs_from_timer(var, data, timer_fieldname) (typeof(var))(data)
#define cfs_timer_setup(timer, callback, data, flags) \
	setup_timer((timer), (callback), (data))
#define cfs_timer_cb_arg(var, timer_fieldname) (cfs_timer_cb_arg_t)(var)
#endif

#endif /* __LIBCFS_LINUX_LINUX_TIME_H__ */
