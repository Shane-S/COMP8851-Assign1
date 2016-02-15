#include <algorithm>
#include <cstdint>
#include <iostream>
#include "PostFixEvaluator.h"
#include "Queue.hpp"
#include "CTimer.h"

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
std::uint32_t highest_one_bit(uint32_t number) {
	if (!number) return 0;

	std::size_t highestOne = 0;
	while (number) {
		highestOne++;
		number >>= 1;
	}
	std::uint32_t ret = 1 << (highestOne - 1);
	return ret;
}

/**
 * @brief	Iterative Josephus problem solver.
 *
 * @author	Shane
 * @date	1/25/2016
 *
 * @param	num_ppl		Number of people in the circle.
 * @param	interval	Number of passes before the "hot potato" "burns" someone.
 *
 * @return	The zero-based index of the person who survived.
 */
std::uint32_t josephus(std::uint32_t num_ppl, std::uint32_t interval) {
	// Some easier cases
	if (num_ppl == 1) return 0;
	if (interval == 0) return num_ppl - 1;

	// For interval == 2 (which is actually interval == 1, according to the textbook), we can do better
	// See https://en.wikipedia.org/wiki/Josephus_problem#k.3D2
	if (interval == 1)
	{
		std::uint32_t value_of_L = num_ppl - highest_one_bit(num_ppl);
		return 2 * value_of_L;
	}

	// The text counts the number of passes, i.e. the number of links between people
	// Other descriptions of the problem count the people themselves
	// E.g. according to the text, interval == 2 means that person 0 passes to person 1, person 1 passes to person 2, and person 2 dies
	// Everybody else would say that person 1 dies since we're killing (or burning; whatever floats your boat) every second person
	// So we increment interval to match
	interval++;
	std::uint32_t winner = 0;
	for (std::uint32_t i = 2; i <= num_ppl; ++i)
	{
		// See http://blue.butler.edu/~phenders/InRoads/MathCounts8.pdf
		winner = (winner + interval) % i;
	}
	return winner;
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

	std::cout << "\tContents of queue:";
	while (!intQueue.empty()) std::cout << " " << intQueue.dequeue();
	std::cout << std::endl;
	std::cout << "\tSize after dequeuing (expected: 0): " << intQueue.size() << std::endl;

}

void question_3_6()
{
	std::cout << "josephus(5, 1) (expected: 2, zero-based index): " << josephus(5, 1) << std::endl;

	CTimer timer;
	double time;
	timer.Start();
	int result = josephus(100000, 2);
	timer.End();
	timer.Diff(time);
	std::cout << "Running time for josephus(100 000, 1): " << time * 1000000 << "ms" << std::endl;
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