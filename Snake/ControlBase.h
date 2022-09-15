#ifndef CONTROLBASE_H
#define CONTROLBASE_H

#include <SFML/Window/Event.hpp>
#include <queue>
#include <optional>

#ifndef NDEBUG
#define LOG(str) printf("%s", str)
#endif


namespace ControlBase
{
	template<class T>
	class ControlBase
	{
	protected:
		std::queue<T> eventsQ;
		void flushQ();

	public:

		virtual void AddPressEvent(const sf::Event& _ev)	= 0;
		virtual void AddReleaseEvent(const sf::Event& _ev)	= 0;

		virtual ~ControlBase(){};

		std::optional<T> GetEvent();
	};

	template<class T>
	inline void ControlBase<T>::flushQ()
	{
		if (!eventsQ.empty())
		{
			std::queue<T> empt;
			std::swap(eventsQ, empt);
		}

		#ifndef NDEBUG
		LOG("Flush events q\n");
		#endif 
	}

	template<class T>
	inline std::optional<T> ControlBase<T>::GetEvent()
	{
		std::optional<T> ev;
		if (!eventsQ.empty())
		{
			ev = eventsQ.front();
			eventsQ.pop();

			#ifndef NDEBUG
			LOG("Handle events\n");
			#endif 
		}

		return ev;
	}

}
#endif
