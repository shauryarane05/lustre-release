/* SPDX-License-Identifier: GPL-2.0 */

/*
 * Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
 *
 * Copyright (c) 2012, 2017, Intel Corporation.
 */

/*
 * This file is part of Lustre, http://www.lustre.org/
 *
 * Basic library routines.
 *
 * Author: liang@whamcloud.com
 */

#ifndef __LIBCFS_LINUX_CPU_H__
#define __LIBCFS_LINUX_CPU_H__

#include <linux/cpu.h>

#ifdef HAVE_TOPOLOGY_SIBLING_CPUMASK
// Kernel provides topology_sibling_cpumask, do not redefine
#else
# define topology_sibling_cpumask(cpu)	topology_thread_cpumask(cpu)
#endif /* HAVE_TOPOLOGY_SIBLING_CPUMASK */

#ifdef HAVE_CPUS_READ_LOCK
// Kernel provides cpus_read_lock, do not redefine
#else
# define cpus_read_lock		get_online_cpus
#endif /* HAVE_CPUS_READ_LOCK */

#ifdef HAVE_CPUS_READ_UNLOCK
// Kernel provides cpus_read_unlock, do not redefine
#else
# define cpus_read_unlock	put_online_cpus
#endif /* HAVE_CPUS_READ_UNLOCK */

#endif /* __LIBCFS_LINUX_CPU_H__ */
