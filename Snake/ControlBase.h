#ifndef CONTROLBASE_H
#define CONTROLBASE_H

#include <SFML/Window/Event.hpp>
#include <queue>
#include <optional>

namespace ControlBase
{
	template<class T>
	class ControlBase
	{
	protected:
		const unsigned int keyBuffer = 16u;
		std::queue<T> eventsQ;
		void flushQ();
		void trimBuffer(std::queue<T>& _que);

	public:

		virtual void AddPressEvent(const sf::Event& _ev)	= 0;
		virtual void AddReleaseEvent(const sf::Event& _ev)	= 0;

		virtual ~ControlBase(){};

		std::optional<T> GetEvent();
	};

	template<class T>
	inline void ControlBase<T>::flushQ()
	{
		eventsQ = std::queue<T>();
	}

	template<class T>
	inline void ControlBase<T>::trimBuffer(std::queue<T>& _que)
	{
		while (_que.size() > keyBuffer)
			_que.pop();
	}

	template<class T>
	inline std::optional<T> ControlBase<T>::GetEvent()
	{
		if (!eventsQ.empty())
		{
			T ev = eventsQ.front();
			eventsQ.pop();

			return ev;
		}

		return {};
	}

}
#endif
