#include <algorithm>
#include <cstdint>
#include <iostream>
#include "PostFixEvaluator.h"
#include "Queue.hpp"

using std::string;

/**
 * @brief	Returns the highest power of two for the given number.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param	number	The number to be evaluated.
 *
 * @return	The value of the number's highest bit set to 1 or 0 if number is 0.
 */
int highest_one_bit(uint32_t number) {
	if (!number) return 0;

	std::size_t highestOne = 0;
	std::uint32_t number_copy = number;
	while (number_copy) {
		highestOne++;
		number_copy >>= 1;
	}
	std::uint32_t ret = number & (1 << (highestOne - 1));
	return ret;
}

/**
 * @brief	Iterative Josephus problem solver.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param	num_ppl		Number of people in the circle.
 * @param	num_passes	Number of passes before the "hot potato" "burns" someone.
 *
 * @return	The index of the person who survived.
 */

int josephus(std::uint32_t num_ppl, std::uint32_t num_passes) {
	if (num_ppl == 1) return 0;
	if (num_passes == 0) return num_ppl - 1;

	// For 2 passes, can do more efficiently
	// See https://en.wikipedia.org/wiki/Josephus_problem#k.3D2
	if (num_passes == 2)
	{
		int value_of_L = num_ppl - highest_one_bit(num_ppl);
		return 2 * value_of_L + 1;
	}
	else
	{
		int next_death = num_passes;
		for (int i = 1; i <= num_ppl; ++i)
		{
			next_death = (next_death + num_passes) % num_ppl;
		}
		return (next_death + num_passes) % num_ppl;
	}
}

void question_3_22() {
	// Question 3.22
	const char* test0 = "1 2 +";
	const char* test1 = "6 5 2 3 + 8 * + 3 + *";
	const char* test2 = "4 4 4 4 4 * * * *";
	const char* test3 = "4.5 6.12 3 * 2.6 + -";
	double expected0 = 1 + 2;
	double expected1 = ((((3 + 2) * 8) + 5) + 3) * 6;
	double expected2 = 4 * 4 * 4 * 4 * 4;
	double expected3 = ((6.12 * 3) + 2.6) - 4.5;
	double result0 = postfixEvaluator(test0);
	double result1 = postfixEvaluator(test1);
	double result2 = postfixEvaluator(test2);
	double result3 = postfixEvaluator(test3);


	std::cout << "Result 0 (expected: " << expected0 << "): \t" << result0 << std::endl;
	std::cout << "Result 1 (expected: " << expected1 << "): \t" << result1 << std::endl;
	std::cout << "Result 2 (expected: " << expected2 << "): \t" << result2 << std::endl;
	std::cout << "Result 3 (expected: " << expected3 << "): \t" << result3 << std::endl;
}

void question_3_33()
{
	Queue<int> intQueue(10);
	intQueue.enqueue(5);

	std::cout << "Current queue size (expected: 1): " << intQueue.size() << std::endl;

	int result = intQueue.dequeue();
	std::cout << "Dequeued (expected: 5): " << result << std::endl;
	std::cout << "Is queue empty? (Expected: yes): " << (intQueue.empty() ? "yes" : "no") << std::endl;

	std::cout << "Enqueuing and dequeuing numbers 0 through 9. " << std::endl << "\tSize after enqueuing (expected: 10): ";
	for (int i = 0; i < intQueue.capacity(); i++) intQueue.enqueue(i);
	std::cout << intQueue.size() << std::endl;

	std::cout << "\tContents of queue: ";
	while (!intQueue.empty()) std::cout << " " << intQueue.dequeue();
	std::cout << std::endl;
	std::cout << "\tSize after dequeuing (expected: 0): " << intQueue.size() << std::endl;

}

void question_3_6()
{
	int num_ppl = 14;
	int num_passes = 2;

	std::cout << "Result: " << josephus(num_ppl, num_passes) << std::endl;
}

int main() {
	std::cout << "Question 3.6" << std::endl;
	question_3_6();

	std::cout << std::endl;

	std::cout << "Question 3.22" << std::endl;
	question_3_22();

	std::cout << std::endl;
	
	std::cout << "Question 3.33" << std::endl;
	question_3_33();

	std::cin.get();
	return 0;
}