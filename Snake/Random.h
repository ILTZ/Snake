#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace RND
{
	class RandomINT
	{
	private:
		std::random_device	rd;
		std::mt19937		gen;

	public:
		RandomINT();
		 
	public:
		RandomINT(const RandomINT&) = delete;
		RandomINT& operator=(const RandomINT&) = delete;

	public:
		template <typename T>
		T GetValue(T _minVal, T _maxVal);

	private:

	};

	template<typename T>
	inline T RandomINT::GetValue(T _minVal, T _maxVal)
	{
		std::uniform_int_distribution<decltype(_maxVal)> dist(_minVal, _maxVal);

		return dist(gen);
	}
}

#endif

