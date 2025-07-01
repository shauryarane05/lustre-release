/* SPDX-License-Identifier: GPL-2.0 */

/*
 * Copyright (c) 2008, 2010, Oracle and/or its affiliates. All rights reserved.
 * Use is subject to license terms.
 *
 * Copyright (c) 2011, 2014, Intel Corporation.
 */

/*
 * This file is part of Lustre, http://www.lustre.org/
 *
 * Basic library routines.
 */

#ifndef __LIBCFS_LINUX_CFS_MEM_H__
#define __LIBCFS_LINUX_CFS_MEM_H__

#include <linux/mm.h>
#include <linux/vmalloc.h>
#include <linux/pagemap.h>
#include <linux/slab.h>
#ifdef HAVE_MM_INLINE
# include <linux/mm_inline.h>
#endif
#include <linux/sched.h>
#ifdef HAVE_SCHED_HEADERS
#include <linux/sched/mm.h>
#endif

unsigned long cfs_totalram_pages(void);

#ifdef HAVE_MEMALLOC_NORECLAIM_SAVE
// Kernel provides memalloc_noreclaim_save, do not redefine
#else
// (Compatibility implementation here if needed)
#endif /* HAVE_MEMALLOC_NORECLAIM_SAVE */

#ifdef HAVE_MEMALLOC_NORECLAIM_RESTORE
// Kernel provides memalloc_noreclaim_restore, do not redefine
#else
// (Compatibility implementation here if needed)
#endif /* HAVE_MEMALLOC_NORECLAIM_RESTORE */

#ifdef HAVE_BITMAP_ALLOC
// Kernel provides bitmap_alloc, bitmap_zalloc, bitmap_free, do not redefine
#else
// (Compatibility implementation here if needed)
#endif /* HAVE_BITMAP_ALLOC */

#ifdef HAVE_MMAP_WRITE_LOCK
// Kernel provides mmap_write_lock, mmap_write_trylock, mmap_write_unlock, mmap_read_lock, mmap_read_trylock, mmap_read_unlock, do not redefine
#else
// (Compatibility implementation here if needed)
#endif /* HAVE_MMAP_WRITE_LOCK */

/*
 * Shrinker
 */
#ifndef SHRINK_STOP
# define SHRINK_STOP (~0UL)
#endif

#ifdef HAVE_VMALLOC_2ARGS
#define __ll_vmalloc(size, flags) __vmalloc(size, flags)
#else
#define __ll_vmalloc(size, flags) __vmalloc(size, flags, PAGE_KERNEL)
#endif

void init_libcfs_vfree_atomic(void);
void exit_libcfs_vfree_atomic(void);

/* atomic-context safe vfree */
void libcfs_vfree_atomic(const void *addr);

#ifndef HAVE_KFREE_SENSITIVE
#define kfree_sensitive(x)      kzfree(x)
#endif

#endif /* __LINUX_CFS_MEM_H__ */
