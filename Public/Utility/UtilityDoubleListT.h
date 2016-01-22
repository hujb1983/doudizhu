#ifndef _UtilityDoubleListT_H_
#define _UtilityDoubleListT_H_
#include "UtilitySingleListT.h"

template <typename X, typename F> class UtilityDoubleListT;
template <typename X>
class LinkD_T
{
    template <typename , typename > friend class UtilityDoubleListT;
    typedef  LinkS_T <X> LinkS;
	
public:
    LinkD_T () : next_ (0), prev_ (0) {}
    ~LinkD_T () {}

    bool is_free () const {
        return (next_.is_free() && prev_.is_free());
    }

    bool is_last () const { return next_.is_end (); }
    bool is_first() const { return prev_.is_end (); }

    X * next() const { return next_.get ();}
    X * prev() const { return prev_.get ();}

private:
    void set_next (X * x) {
         next_.set (x);
    }

    void set_prev (X * x) {
        prev_.set (x);
    }

    void set_free () {
        next_.set_free ();
        prev_.set_free ();
    }

    LinkS  next_;
    LinkS  prev_;
};


template <typename X>
class LinkD_Functor_T :  public std::unary_function < X, LinkD_T <X> >
{
public :
    LinkD_T <X> *  operator ()( const X * x )  const {
        return  const_cast < X* > (x);
    }
};

template <typename X, typename F = LinkD_Functor_T <X> >
class UtilityDoubleListT
{
public:
    typedef UtilityDoubleListT<X,F> List;
    typedef LinkD_T<X>         LinkD;
    typedef LinkS_T<X>         LinkS;

    class iterator
    {
        friend class UtilityDoubleListT<X,F>;
    public:
        ~iterator () {}

        iterator ()
        : x_   (0)
        , list_(0)
        {}

        iterator(const iterator & other )
        : x_   (other.x_)
        , list_(other.list_)
        {}


        iterator & operator = (const iterator & other )
        {
            x_ = other.x_;
            list_ = other.list_;
            return *this;
        }

        bool operator == (const iterator & other )const
        {
            return (x_ == other.x_ && list_ == other.list_);
        }

        bool operator != (const iterator & other )const
        {
            return (x_ != other.x_ || list_ != other.list_);
        }

        iterator & operator ++ ();

        iterator operator ++ (int);

        iterator & operator -- ();

        iterator operator -- (int);

        X * remove ()
        {
            if (list_ == 0)
                return 0;

            return list_->remove ((*this)++);
        }

        operator X *   () const { return x_; }
        X * operator * () const { return x_; }


    private:
        iterator(X * x, List & list)
            : x_    (x)
            , list_ (&list)
        {}

        X *   x_;
        UtilityDoubleListT<X, F>  * list_;
    };

    friend class  iterator;


    UtilityDoubleListT ()
        : head_ (LinkS::end())
        , tail_ (LinkS::end())
        , size_ (0)
    {}

    bool   empty () const  { return (size_ == 0); }
    size_t size  () const  { return size_; }

    iterator begin() { return iterator(head_.get(), *this); }
    iterator end ()  { return iterator(LinkS::end(), *this); }

    iterator push_front (X * x);
    iterator push_back  (X * x);


    X * pop_front ();
    X * pop_back  ();

    X * front () ;
    X * back  () ;

    iterator insert  (X * what, iterator where);

    X * remove (iterator itr);

    void swap   (UtilityDoubleListT<X, F>  & other);
    void splice (UtilityDoubleListT<X, F>  & other );
    void clear	();

private:
    /// Protect from copy and assignment
    UtilityDoubleListT  (const UtilityDoubleListT<X, F>  & other);
    UtilityDoubleListT & operator= (const UtilityDoubleListT <X, F> & other);


    // functor that converts object pointer to link pointer
    // does it make sense to have non-static converter ??
    static LinkD * get_link (const X * x);

    static X *    get_next (const X * x);
    static X *    get_prev (const X * x);

    static bool is_end (const X * x)
    {
        return x == LinkS::end ();
    }

    iterator insert_impl (X *x, X * x2);
    X *  remove_impl (X * x);

    LinkS    head_;
    LinkS    tail_;
    size_t   size_;
};

//-----------------------------------------------------
//   UtilityDoubleListT::iterator
//-----------------------------------------------------
template <class X, class F>
inline typename UtilityDoubleListT<X,F>::iterator &
UtilityDoubleListT<X,F>::iterator::operator ++()
{
    // behavior unpredictable if iterator not valid
    if (!UtilityDoubleListT<X,F>::is_end(x_))
    {
        x_ = UtilityDoubleListT<X,F>::get_next (x_);
    }
    return *this;
}

template <class X, class F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::iterator::operator ++(int)
{
    // behavior unpredictable if iterator not valid
    iterator itr (*this);
    ++(*this);
    return itr;
}

template <class X, class F>
inline typename UtilityDoubleListT<X,F>::iterator &
UtilityDoubleListT<X,F>::iterator::operator --()
{
    // behavior unpredictable if iterator not valid
    if (UtilityDoubleListT<X,F>::is_end(x_))
    {
        x_ = list_->tail_.get();
    }
    else
    {
        x_ = UtilityDoubleListT<X,F>::get_prev (x_);
    }
    return *this;
}

template <class X, class F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::iterator::operator --(int)
{
    // behavior unpredictable if iterator not valid
    iterator itr (*this);
    --(*this);
    return itr;
}
//-----------------------------------------------------
//   UtilityDoubleListT
//-----------------------------------------------------
template <class X, class F>
inline typename UtilityDoubleListT<X,F>::LinkD *
UtilityDoubleListT<X,F>::get_link (const X * x)
{
    assert (x != 0 && !is_end(x));
    static F funcObj2Link;
    return funcObj2Link (x);
}

template <class X, class F>
inline X *
UtilityDoubleListT<X,F>::get_next (const X * x)
{
    return get_link (x)->next ();
}

template <class X, class F>
inline X *
UtilityDoubleListT<X,F>::get_prev (const X * x)
{
    return get_link (x)->prev ();
}

template <typename X, typename F>
inline X *
UtilityDoubleListT<X,F>::remove_impl (X * x)
{
    if (x == 0 || this->is_end(x))
        return 0;

    LinkD * link = get_link (x);

    X * x1 = link->prev ();
    X * x2 = link->next ();

    link->set_free ();

    if (!is_end(x1))
       get_link(x1)->set_next(x2);
    else
       head_.set (x2);

    if (!is_end(x2))
       get_link(x2)->set_prev(x1);
    else
       tail_.set (x1);

    --size_;
    assert (head_.get() != 0 && tail_.get() != 0);
    return x;
}


template <typename X, typename F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::insert_impl (X * x, X * x2)
{
    // insert node x before node x2
    //assert (x != 0 && x2 != 0);

    LinkD * link = get_link (x);
    assert (link->is_free());

    LinkD * link2 = is_end(x2) ? 0 : get_link(x2);

    X *     x1    = link2 ? link2->prev () : tail_.get();

    LinkD * link1 = is_end(x1) ? 0 : get_link(x1);

    link->set_next (x2);
    link->set_prev (x1);

    if (link1)
        link1->set_next (x);
    else
        head_.set(x);

    if (link2)
        link2->set_prev (x);
    else
        tail_.set (x);

    ++size_;

    return iterator (x, *this);
}

template <class X, class F>
inline X *
UtilityDoubleListT<X,F>::front ()
{
    if (size_ == 0)
    {
        return 0;
    }
    return head_.get();
}

template <class X, class F>
inline X *
UtilityDoubleListT<X,F>::back ()
{
    if (size_ == 0)
    {
        return 0;
    }
    return tail_.get();
}

template <typename X, typename F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::push_front (X * x)
{
    //assert (x != 0);
    return insert_impl (x, head_.get());
}

template <typename X, typename F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::push_back (X * x)
{
    //assert (x != 0);
    return insert_impl (x, LinkS::end());
}

template <typename X, typename F>
inline typename UtilityDoubleListT<X,F>::iterator
UtilityDoubleListT<X,F>::insert (X *x, iterator where)
{
    //assert (x != 0);

    if (where.list_ != this)
        return iterator ();

    return insert_impl (x, where.x_);
}

template <typename X, typename F>
inline X *
UtilityDoubleListT<X,F>::pop_front ()
{
    return remove_impl (head_.get());
}

template <typename X, typename F>
inline X *
UtilityDoubleListT<X,F>::pop_back ()
{
    return remove_impl (tail_.get());
}

template <typename X, typename F>
inline X *
UtilityDoubleListT<X,F>::remove (iterator itr)
{
    if (itr.list_ != this)
        return 0;
    return remove_impl (*itr);
}

template <class X, class F>
inline void
UtilityDoubleListT<X,F>::swap (UtilityDoubleListT<X,F>  & other)
{
    if (&other == this)
        return;

    std::swap (head_, other.head_);
    std::swap (tail_, other.tail_);
    std::swap (size_, other.size_);
}

template <class X, class F>
inline void
UtilityDoubleListT<X,F>::splice (UtilityDoubleListT<X,F>  & other)
{
    if (&other == this)
        return;

    if (other.empty())
        return;

    if (this->empty())
    {
        this->swap (other);
        return;
    }

    X * x1 = this->back ();
    X * x2 = other.front();
    get_link(x1)->set_next (x2);
    get_link(x2)->set_prev (x1);

    this->tail_  = other.tail_;
    this->size_ += other.size_;

    other.head_.set_end();
    other.tail_.set_end();
    other.size_ = 0;
}

template <class X, class F>
inline void
UtilityDoubleListT<X,F>::clear ()
{
    head_.set_end();
    tail_.set_end();
    size_ = 0;
}

#endif /* TERABIT_UtilityDoubleListT_H */




