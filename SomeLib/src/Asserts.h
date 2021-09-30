#pragma once
#include <iostream>

namespace internal
{

	void _assert(bool condition, const char* condition_str, const char* msg, const char* func, const char* file, int line);

	class _ErrorContext
	{
	public:
		_ErrorContext(const char* message, const char* scope, const char* file, int line) noexcept;
		~_ErrorContext() noexcept;

		_ErrorContext(const _ErrorContext&) = delete;
		_ErrorContext(_ErrorContext&&) = delete;

		_ErrorContext& operator = (const _ErrorContext&) = delete;
		_ErrorContext& operator = (_ErrorContext&&) = delete;
	};

}


#ifndef APEX_ASSERTS_ERROR_STREAM
#define APEX_ASSERTS_ERROR_STREAM std::cerr
#endif

#define APEX_ASSERT(condition, message) \
	internal::_assert(condition, #condition, message, __FUNCTION__, __FILE__, __LINE__)

#define ERROR_CONTEXT_MSG_SCOPE(message, scope) \
	auto __ec__ = ::internal::_ErrorContext(message, scope, __FILE__, __LINE__)

#define ERROR_CONTEXT_SCOPE(scope) \
	ERROR_CONTEXT_MSG_SCOPE("", scope)

#define ERROR_CONTEXT_MSG(message) \
	ERROR_CONTEXT_MSG_SCOPE(message, __FUNCTION__)

#define ERROR_CONTEXT_INIT \
	ERROR_CONTEXT_MSG("");