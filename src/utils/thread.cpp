/***************************************************************************
  file : $URL$
  version : $LastChangedRevision$  $LastChangedBy$
  date : $LastChangedDate$
  email : jdetaeye@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * Copyright (C) 2007 by Johan De Taeye                                    *
 *                                                                         *
 * This library is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU Lesser General Public License as published   *
 * by the Free Software Foundation; either version 2.1 of the License, or  *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU Lesser General Public        *
 * License along with this library; if not, write to the Free Software     *
 * Foundation Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA *
 *                                                                         *
 ***************************************************************************/


#define FREPPLE_CORE
#include "frepple/utils.h"

namespace frepple
{

DECLARE_EXPORT LockManager* LockManager::mgr;

DECLARE_EXPORT void LockManager::obtainReadLock(const Lock& l, priority p) {}
DECLARE_EXPORT void LockManager::obtainWriteLock(Lock& l, priority p) {}
DECLARE_EXPORT void LockManager::releaseReadLock(const Lock& l) {}
DECLARE_EXPORT void LockManager::releaseWriteLock(Lock& l) {}

#ifdef MT
Pool<Lock> pool_locks;


DECLARE_EXPORT void LockManager::obtainReadLock(const Object* l, priority p)
{
  // Check if exclusivewrite is on and I am not the writer
  // if yes wait, then repeat

  //if (!l->lock)
  //  const_cast<Object*>(l)->lock = pool_locks.Alloc();

  //cout << "Read locking " << l << "  " << l->getType().type <<  endl;
  // if writelock > 0 and I am not the writer, wait, then repeat

  // insert in the table
  // increment readers
};


DECLARE_EXPORT void LockManager::obtainWriteLock(Object* l, priority p)
{
  // Check if exclusiveread is on
  // if yes wait, then repeat

  l->getType().raiseEvent(l, SIG_BEFORE_CHANGE);

  // if readlock > 0, wait, then repeat
  //if (!l->lock)
  //  l->lock = pool_locks.Alloc();

  //cout << "Write locking " << l << "  " << l->getType().type << endl;

  // increment writers
};


DECLARE_EXPORT void LockManager::releaseReadLock(const Object* l)
{
  //  readers is expected to be >0
  //  writers is expected to be 0
  //  exclusive write is expected to be off

  //if (!l->lock)
  //  throw RuntimeException("Releasing invalid lock");

  //cout << "Read unlocking " << l << "  " << l->getType().type << endl;

  // decrement readers

  // when readers & writers & wait = 0, remove from table
};


DECLARE_EXPORT void LockManager::releaseWriteLock(Object* l)
{
  //  readers is expected to be = 0
  //  writers is expected to be me

  l->getType().raiseEvent(l, SIG_AFTER_CHANGE);

  //if (!l->lock)
    //throw RuntimeException("Releasing invalid lock");

  //cout << "Write unlocking " << l << "  " << l->getType().type << endl;

  // decrement writers

  // when readers & writers & wait = 0, remove from table
};


#else // Compiling without thread support


DECLARE_EXPORT void LockManager::obtainReadLock(const Object* l, priority p)
{
  //cout << "Read locking " << l << "  " << l->getType().type <<  endl;
};


DECLARE_EXPORT void LockManager::obtainWriteLock(Object* l, priority p)
{
  // Lock already exists
  if (l->lock) return;
  l->lock = reinterpret_cast<Lock*>(l);
  l->getType().raiseEvent(l, SIG_BEFORE_CHANGE);
  //cout << "Write locking " << l << "  " << l->getType().type << endl;
};


DECLARE_EXPORT void LockManager::releaseReadLock(const Object* l)
{
  //cout << "Read unlocking " << l << "  " << l->getType().type << endl;
};


DECLARE_EXPORT void LockManager::releaseWriteLock(Object* l)
{
  // There was no lock set
  if (!l->lock) return;
  //cout << "Write unlocking " << l << "  " << l->getType().type << endl;
  l->lock = NULL;
  l->getType().raiseEvent(l, SIG_AFTER_CHANGE);
};


#endif  // endif MT

}  // End Namespace
