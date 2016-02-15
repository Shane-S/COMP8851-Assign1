#ifndef LIST_H
#define LIST_H

#include <cstdint>

template <typename Object>
class List
{
private:
	struct Node
	{
		Object data;
		Node *prev;
		Node *next;
		bool deleted;

		Node(const Object & d = Object{}, Node * p = nullptr,
			Node * n = nullptr)
			: data{ d }, prev{ p }, next{ n }, deleted{ false } { }

		Node(Object && d, Node * p = nullptr, Node * n = nullptr)
			: data{ std::move(d) }, prev{ p }, next{ n }, deleted{ false } { }
	};

public:
	class const_iterator
	{
	public:
		const_iterator() : _current{ nullptr }
		{ }

		const Object & operator* () const
		{
			return retrieve();
		}

		/**
		 * @brief	Prefix increment operator.
		 *
		 * @return	A reference to the incremented iterator.
		 */
		const_iterator & operator++ ()
		{
			do
			{
				this->_current = this->_current->next;
			} while (this->current->deleted);
			return *this;
		}

		/**
		 * @brief	Postfix increment operator.
		 *
		 * @return	A reference to the incremented iterator.
		 */
		const_iterator operator++ (int)
		{
			const_iterator old = *this;
			++(*this);
			return old;
		}

		const_iterator operator--()
		{
			do
			{
				this->_current = this->_current->prev;
			} while (this->current->deleted);
			return *this;
		}

		const_iterator operator--(int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

		bool operator== (const const_iterator & rhs) const
		{
			return _current == rhs._current;
		}
		bool operator!= (const const_iterator & rhs) const
		{
			return !(*this == rhs);
		}

	protected:
		const List<Object> *_list;
		Node *_current;

		const_iterator(const List<Object> & lst, Node *p)
		 : _list{ &lst }, _current{ p } {}

		void assertIsValid() const
		{
			if (_list == nullptr || _current == nullptr || _current == _list->_head)
				throw IteratorOutOfBoundsException{};
		}

		Object & retrieve() const
		{
			return _current->data;
		}

		/**
		 * @brief	Constructor taking node as an argument and allowing for implicit construction.
		 *
		 * @param 	p	The node that the iterator points to.
		 */
		const_iterator(Node *p) : _current{ p }
		{ }

		friend class List<Object>;
	};

	class iterator : public const_iterator
	{
	public:
		iterator()
		{ }

		Object & operator* ()
		{
			// retrieve() doesn't return const reference, so we can use it
			return const_iterator::retrieve();
		}

		const Object & operator* () const
		{
			return const_iterator::operator*();
		}

		iterator & operator++ ()
		{
			// the caller should make sure things don't fall outside of [begin() end())
			do
			{
				this->_current = this->_current->next;
			} while (this->_current->deleted);
			return *this;
		}

		iterator operator++ (int)
		{
			iterator old = *this;
			++(*this);
			return old;
		}

		iterator operator--()
		{
			do
			{
				this->_current = this->_current->prev;
			} while (this->current->deleted);
			return *this;
		}

		iterator operator--(int)
		{
			iterator old = *this;
			--(*this);
			return old;
		}

	protected:
		iterator(Node *p) : const_iterator{ p }
		{ }

		friend class List<Object>;
	};


public:
	List()
		: _size(0), _head(new Node), _tail(new Node)
	{
		_head->next = _tail;
		_tail->prev = _head;
	}

	List(const List & rhs)
		: List()
	{
		for (auto & x : rhs)
			push_back(x);
	}

	/**
	 * @brief	Move constructor.
	 *
	 * @param [in,out]	rhs	The rvalue source object.
	 */
	List(List && rhs)
		: _size(rhs._size), _head(_rhs._head), _tail(_rhs._tail)
	{
		// Have to zero out everything in rhs so that we don't accidentally delete our own stuff
		rhs._size = 0;
		rhs._head = nullptr;
		rhs._tail = nullptr;
	}

	~List()
	{
		clear();
		delete _head;
		delete _tail;
	}

	/**
	 * @brief	Copy assignment operator; see http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom for rationale behind revisions.
	 *
	 * @author	Shane
	 * @date	2/13/2016
	 *
	 * @param	rhs	The source object from which to copy (passed by value).
	 *
	 * @return	A shallow copy of rhs
	 */
	List & operator= (List rhs)
	{
		std::swap(*this, rhs);
		return *this;
	}

	/**
	 * @brief	Gets an iterator pointing to the first element in the list.
	 *
	 * @return	An iterator pointing to the first element in the list.
	 */
	iterator begin()
	{
		// Find the first non-deleted node
		Node* start = _head->next;
		while (start->deleted) start = start->next;
		return{ start };
	}

	/**
	 * @brief	Gets a constant iterator pointing to the first element in the list.
	 *
	 * @return	A constant iterator pointing to the first element in the list.
	 */
	const_iterator begin() const
	{
		// Find the first non-deleted node
		Node* start = _head->next;
		while (start->deleted) start = start->next;
		return{ start };
	}

	/**
	 * @brief	Gets an iterator pointing one element past the end of the list.
	 * 
	 * @return	An iterator pointing one element past the end of the list.
	 */
	iterator end()
	{
		// Find the last non-deleted node and go one past that
		Node* end = _tail->prev;
		while (end->deleted) end = end->prev;
		return{ end->next };
	}

	/**
	 * @brief	Gets a constant iterator pointing one element past the end of the list.
	 *
	 * @return	A constant iterator pointing one element past the end of the list.
	 */
	const_iterator end() const
	{
		// Find the last non-deleted node and go one past that
		Node* end = _tail->prev;
		while (end->deleted) end = end->prev;
		return{ end->next };
	}

	std::size_t size() const
	{
		return _numFilled;
	}
	bool empty() const
	{
		return size() == 0;
	}

	/**
	 * @brief	Removes and deletes all elements from the list.
	 */
	void clear()
	{
		while (!empty())
			pop_front();
	}

	/**
	 * @brief	Gets a reference to the first object in the list.
	 *
	 * @return	A reference to the first object in the list.
	 */
	Object & front()
	{
		return *begin();
	}

	/**
	 * @brief	Gets a constant reference to the first object in the list.
	 *
	 * @return	A constant reference to the first object in the list.
	 */
	const Object & front() const
	{
		return *begin();
	}

	/**
	 * @brief	Gets a reference to the last object in the list.
	 *
	 * @return	A reference to the last object in the list.
	 */
	Object & back()
	{
		return *--end();
	}

	/**
 	 * @brief	Gets a constant reference to the last object in the list.
	 *
	 * @return	A constant reference to the last object in the list.
	 */
	const Object & back() const
	{
		return *--end();
	}

	/**
	 * @brief	Pushes an object to the front of the list (at index 0).
	 *
	 *
	 * @param	x	The Object to add.
	 */
	void push_front(const Object & x)
	{
		insert(begin(), x);
	}

	/**
	 * @brief	Pushes an object to the front of the list (at index 0).
	 *
	 *
	 * @param	x	The Object to add.
	 */
	void push_front(Object && x)
	{
		insert(begin(), std::move(x));
	}

	/**
	 * @brief	Pushes an object to the back of the list (at index size - 1).
	 *
	 *
	 * @param	x	The Object to add.
	 */
	void push_back(const Object & x)
	{
		insert(end(), x);
	}

	/**
	 * @brief	Pushes an object to the back of the list (at index size - 1).
	 *
	 *
	 * @param	x	The Object to add.
	 */
	void push_back(Object && x)
	{
		insert(end(), std::move(x));
	}

	/**
	 * @brief	Pops the object at the back of the front (at index 0) and adjusts the list size accordingly.
	 */
	void pop_front()
	{
		lazy_erase(begin());
	}

	/**
	 * @brief	Erases the object at the back of the list (at index size - 1) and adjusts list size accordingly.
	 */
	void pop_back()
	{
		lazy_erase(--end());
	}

	iterator insert(iterator itr, const Object & x)
	{
		Node *p = itr._current;
		_numFilled++;

		if (p->prev->deleted)
		{
			p->prev->deleted = false;
			p->prev->data = x;
			_numDeleted--;
			return{ p->prev };
		}
		else
		{
			_size++;
			return{ p->prev = p->prev->next = new Node{ x, p->prev, p } };
		}         
	}

	iterator insert(iterator itr, Object && x)
	{
		Node *p = itr._current;
		_numFilled++;

		if (p->prev->deleted)
		{
			p->prev->deleted = false;
			p->prev->data = std::move(x);
			_numDeleted--;
		}
		else
		{
			_size++;
			return{ p->prev = p->prev->next = new Node{ sdt::move(x), p->prev, p } };
		}
	}

	iterator erase(iterator itr)
	{
		Node *p = itr._current;
		iterator retVal{ p->next };
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		_size--;
		_numFilled--;

		return retVal;
	}
	iterator erase(iterator from, iterator to)
	{
		for (iterator itr = from; itr != to; )
			itr = erase(itr);

		return to;
	}

	iterator lazy_erase(iterator itr)
	{
		// Seems to make more sense to do it this way; we'll traverse this list a whole hell of a lot more if we call lazy_erase every time from the other one
		return lazy_erase(itr, { itr._current->next });
	}

	/**
	 * @brief Lazily erases the segment of the list between [from, to).
	 *
	 * @param from The iterator from which to start erasing (this will also be erased).
	 * @param to   The iterator at which to stop erasing (won't be erased).
	 * @return     The to iterator.
	 */
	iterator lazy_erase(iterator from, iterator to)
	{
		// Since our iterators actually skip over deleted nodes with their operators, deletion will have to be done using the raw nodes
		Node *from_node = from._current;
		Node *to_node = to._current;
		Node *current = from_node;
		while(current != to_node)
		{
			current->deleted = true;
			current = current->next;
			_numDeleted++;
			_numFilled--;
		}

		// Now we have to clean out the deleted nodes for real. How inconvenient
		// On the plus side, we (should) traverse the list twice max since we're doing it in here
		if (_numDeleted >= _numFilled)
		{
			Node *node = _head->next;
			while (_numDeleted) // *Shouldn't* need to check for anything else here since _numDeleted should always get to 0 before we go out of bounds
			{
				if (node->deleted)
				{
					iterator it = { node };
					node = erase(it)._current;
					_numDeleted--;
				}
				else
				{
					node = node->next;
				}
			}
		}

		return to;
	}

private:
	std::size_t _size;
	Node *_head;
	Node *_tail;
	std::size_t _numDeleted;
	std::size_t _numFilled;
};

#endif