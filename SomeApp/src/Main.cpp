#include <Asserts.h>
#include <Stack.h>


void failing_assertion()
{
	ERROR_CONTEXT_MSG("Checking a failing assertion");
	APEX_ASSERT(1 == 0, "This should fail");
}

void calling_function()
{
	ERROR_CONTEXT_INIT
	failing_assertion();
}

int main()
{
	ERROR_CONTEXT_INIT

	{
		ERROR_CONTEXT_SCOPE("Scope #1");
		std::cout << "This is inside scope #1" << '\n';
	}

	{
		ERROR_CONTEXT_SCOPE("Scope #2");
		calling_function();
	}

	return 0;
}
