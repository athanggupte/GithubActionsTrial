#pragma once

#include "Asserts.h"

#include <cassert>

template<typename T>
class Stack
{
public:
	explicit Stack(const size_t capacity = 8)
		: m_Capacity(capacity)
	{
		m_Base = new T[m_Capacity];
		m_Top = m_Base;
	}

	~Stack()
	{
		delete[] m_Base;
	}

	T& Top()
	{
		APEX_ASSERT(m_Size > 0, "Stack is empty! Cannot retrieve Top.");

		auto top = m_Top;
		return *(--top);
	}

	[[nodiscard]] const T& Top() const
	{
		APEX_ASSERT(m_Size > 0, "Stack is empty! Cannot retrieve Top.");

		auto top = m_Top;
		return *(--top);
	}

	[[nodiscard]] size_t Capacity() const
	{
		return m_Capacity;
	}

	[[nodiscard]] size_t Size() const
	{
		return m_Size;
	}

	void Push(const T& value)
	{
		APEX_ASSERT(m_Size < m_Capacity, "Stack capacity is full! Cannot push element.");

		*m_Top = value;
		++m_Top;
		++m_Size;
	}

	void Pop()
	{
		APEX_ASSERT(m_Size > 0, "Stack is empty! Cannot pop element.");

		--m_Top;
		--m_Size;
	}

	void Resize(const size_t capacity)
	{
		APEX_ASSERT(capacity >= m_Size, "Size is greater than new capacity! Cannot resize stack.");

		auto oldBase = m_Base;
		m_Base = new T[capacity];
		m_Capacity = capacity;

		auto tgtPtr = m_Base;
		auto srcPtr = oldBase;
		for (auto i = 0; i < m_Size; i++)
		{
			*tgtPtr = *srcPtr;
			++tgtPtr;
			++srcPtr;
		}

		m_Top = tgtPtr;
		delete[] oldBase;
	}

private:
	size_t m_Capacity;
	size_t m_Size = 0;
	T* m_Base = nullptr;
	T* m_Top = nullptr;
};
