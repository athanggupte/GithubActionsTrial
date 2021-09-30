#include "Asserts.h"
#include <stack>

namespace internal
{

	struct StackTrace
	{
		const char* Message;
		const char* Scope;
		const char* File;
		int Line;
	};

	std::ostream& operator <<(std::ostream& out, const StackTrace& st)
	{
		out << st.File << ":" << st.Line << " (" << st.Scope << ") :: " << st.Message;
		return out;
	}

	thread_local std::stack<StackTrace> s_StackTrace;

	void _assert(bool condition, const char* condition_str, const char* msg, const char* func, const char* file, int line)
	{
		auto& out = APEX_ASSERTS_ERROR_STREAM;

		if (condition)
			return;

		out << "Assertion Failed: " << msg << '\n';
		out << "Condition: " << condition_str << '\n';
		out << "Stack trace:" << '\n';

		while (!s_StackTrace.empty())
		{
			out << "\t" << s_StackTrace.top() << '\n';
			s_StackTrace.pop();
		}

		abort();
	}

	_ErrorContext::_ErrorContext(const char* message, const char* scope, const char* file, int line) noexcept
	{
		const StackTrace st {
			message, scope, file, line
		};
		s_StackTrace.push(st);
	}

	_ErrorContext::~_ErrorContext() noexcept
	{
		s_StackTrace.pop();
	}

}