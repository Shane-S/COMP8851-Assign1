#include <algorithm>
#include <cstdint>
#include <iostream>
#include "PostFixEvaluator.h"
#include "Queue.hpp"

using std::string;

/**
 * @brief	Determines the highest bit that's a 1 in the given number.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param	number	The number to be evaluated.
 *
 * @return	The highest bit set to 1, or -1 if the number is 0.
 */

int highestOneBit(uint32_t number) {
	int highestOne = -1;
	while (number) {
		highestOne++;
		number >>= 1;
	}
	return highestOne;
}

/**
 * @brief	Josephus problem solver.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param	numPeople	Number of people in the circle.
 * @param	numPasses	Number of passes before the hot potato burns someone.
 *
 * @return	The index of the person who won.
 */

int josephus(std::uint32_t numPeople, std::uint32_t numPasses) {
	int safePos;

	// For 2 passes, can do more efficiently
	if (numPasses == 2) {
		int highestOne = 0;
		int valueOfL = numPeople - highestOneBit(numPeople);
		safePos = 2 * valueOfL + 1;

		return safePos;
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

int main() {
	std::cout << "Question 3.22" << std::endl;
	question_3_22();

	std::cout << std::endl;
	
	std::cout << "Question 3.33" << std::endl;
	question_3_33();

	std::cin.get();
	return 0;
}