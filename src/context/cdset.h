/*********************                                                        */
/** cdset.h
 ** Original author: mdeters
 ** Major contributors: none
 ** Minor contributors (to current version): none
 ** This file is part of the CVC4 prototype.
 ** Copyright (c) 2009, 2010  The Analysis of Computer Systems Group (ACSys)
 ** Courant Institute of Mathematical Sciences
 ** New York University
 ** See the file COPYING in the top-level source directory for licensing
 ** information.
 **
 ** Context-dependent set class.
 **/

#include "cvc4_private.h"

#ifndef __CVC4__CONTEXT__CDSET_H
#define __CVC4__CONTEXT__CDSET_H

#include "context/context.h"
#include "util/Assert.h"

namespace CVC4 {
namespace context {

template <class V, class HashFcn>
class CDSet : protected CDMap<V, V, HashFcn> {
  typedef CDMap<V, V, HashFcn> super;

public:

  CDSet(Context* context) :
    super(context) {
  }

  size_t size() const {
    return super::size();
  }

  size_t count(const V& v) const {
    return super::count(v);
  }

  void insert(const V& v) {
    super::insert(v, v);
  }

  // FIXME: no erase(), too much hassle to implement efficiently...

  class iterator {
    typename super::iterator d_it;

  public:

    iterator(const typename super::iterator& it) : d_it(it) {}
    iterator(const iterator& it) : d_it(it.d_it) {}

    // Default constructor
    iterator() {}

    // (Dis)equality
    bool operator==(const iterator& i) const {
      return d_it == i.d_it;
    }
    bool operator!=(const iterator& i) const {
      return d_it != i.d_it;
    }

    // Dereference operators.
    V operator*() const {
      return (*d_it).first;
    }

    // Prefix increment
    iterator& operator++() {
      ++d_it;
      return *this;
    }

    // Postfix increment: requires a Proxy object to hold the
    // intermediate value for dereferencing
    class Proxy {
      const V& d_val;

    public:

      Proxy(const V& v) : d_val(v) {}

      V operator*() const {
        return d_val;
      }
    };/* class CDSet<>::iterator::Proxy */

    // Actual postfix increment: returns Proxy with the old value.
    // Now, an expression like *i++ will return the current *i, and
    // then advance the orderedIterator.  However, don't try to use
    // Proxy for anything else.
    const Proxy operator++(int) {
      Proxy e(*(*this));
      ++(*this);
      return e;
    }
  };/* class CDSet<>::iterator */

  typedef iterator const_iterator;

  const_iterator begin() const {
    return iterator(super::begin());
  }

  const_iterator end() const {
    return iterator(super::end());
  }

  const_iterator find(const V& v) const {
    return iterator(super::find(v));
  }

};/* class CDSet */

}/* CVC4::context namespace */
}/* CVC4 namespace */

#endif /* __CVC4__CONTEXT__CDSET_H */
