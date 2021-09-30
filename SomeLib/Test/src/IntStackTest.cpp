#include <Stack.h>
#include <gtest/gtest.h>

class IntStackTest : public ::testing::Test
{
public:
	Stack<int> intStack;
};


TEST_F(IntStackTest, InitialSizeShouldBeZero)
{
	EXPECT_EQ(intStack.Size(), 0);
}

TEST_F(IntStackTest, PushPopAffectsSize)
{
	intStack.Push(1);
	EXPECT_EQ(intStack.Size(), 1);

	intStack.Pop();
	EXPECT_EQ(intStack.Size(), 0);
}

TEST_F(IntStackTest, CanQuerySizeInLoop)
{
	for (auto i = 0; i < intStack.Capacity(); i++)
		intStack.Push(i);

	EXPECT_EQ(intStack.Size(), intStack.Capacity());

	for (auto i = 0; intStack.Size(); i++)
		intStack.Pop();

	EXPECT_EQ(intStack.Size(), 0);
}

TEST_F(IntStackTest, PushPopAffectsTop)
{
	intStack.Push(100);
	EXPECT_EQ(intStack.Top(), 100);

	intStack.Push(3000);
	EXPECT_EQ(intStack.Top(), 3000);

	intStack.Pop();
	EXPECT_EQ(intStack.Top(), 100);
}

TEST_F(IntStackTest, ResizeAffectsCapacity)
{
	EXPECT_EQ(intStack.Capacity(), 8);

	intStack.Resize(16);
	EXPECT_EQ(intStack.Capacity(), 16);

	intStack.Resize(4);
	EXPECT_EQ(intStack.Capacity(), 4);
}

TEST_F(IntStackTest, ResizeCopiesAllItemsInOrder)
{
	const auto count = intStack.Capacity();
	for (auto i = 0; i < count; i++)
		intStack.Push(i);

	intStack.Resize(16);

	for (auto i = 0; i < count; i++)
	{
		EXPECT_EQ(intStack.Top(), count - i - 1);
		intStack.Pop();
	}
}

// Death Tests
using IntStackDeathTest = IntStackTest;

TEST_F(IntStackDeathTest, QueryingTopWhenEmpty)
{
	EXPECT_DEATH(intStack.Top(), "");
}

TEST_F(IntStackDeathTest, PopWhenEmpty)
{
	EXPECT_DEATH(intStack.Pop(), "");
}

TEST_F(IntStackDeathTest, PushWhenCapacityFull)
{
	const auto count = intStack.Capacity();
	for (auto i = 0; i < count; i++)
		intStack.Push(i);

	EXPECT_DEATH(intStack.Push(count), "");
}

TEST_F(IntStackDeathTest, ResizeToSmallerThanSize)
{
	constexpr auto count = 6;
	for (auto i = 0; i < count; i++)
		intStack.Push(i);

	EXPECT_DEATH(intStack.Resize(count - 2), "");
}