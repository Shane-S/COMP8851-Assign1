#ifndef QUEUE_H
#define QUEUE_H

#include <cstdio>
#include <vector>

template <typename Object>
class Queue
{
public:
	Queue(std::size_t capacity)
		: _size(0), _capacity(capacity), _list(capacity), _front(0), _back(0)
	{}

	/**
	 * @brief	Adds an object onto the end of this queue.
	 *
	 * @author	Shane
	 * @date	2/13/2016
	 *
	 * @param	item	The item to enqueue.
	 */
	void enqueue(const Object& item)
	{
		_list[_back] = item;
		_back++;
		_size++;
		_back %= _capacity;
	}

	/**
	 * @brief	Adds an object onto the end of this queue.
	 *
	 * @author	Shane
	 * @date	2/13/2016
	 *
	 * @param	item	The item to enqueue.
	 */
	void enqueue(const Object&& item)
	{
		_list[_back] = std::move(item);
		_back++;
		_size++;
		_back %= _capacity;
	}

	/**
	 * @brief	Removes the head object from this queue and returns a copy of it.
	 *
	 * @author	Shane
	 * @date	2/13/2016
	 *
	 * @return	The head object from this queue.
	 */
	Object dequeue()
	{
		_size--;
		std::size_t prevFront = _front;
		_front++;
		_front %= _capacity;

		return _list[prevFront];
	}

	/**
	 * @brief	Whether the queue is empty.
	 *
	 * @author	Shane
	 * @date	2/13/2016
	 *
	 * @return	true if the queue is empty, false otherwise.
	 */
	bool empty() const
	{
		return _size == 0;
	}

	std::size_t size() const
	{
		return _size;
	}

	std::size_t capacity() const
	{
		return _capacity;
	}

private:
	std::vector<Object> _list;
	std::size_t _size;
	std::size_t _capacity;
	int _front;
	int _back;
};

#endif