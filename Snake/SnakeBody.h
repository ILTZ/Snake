#ifndef SNAKEBODY_H
#define SNAKEBODY_H

#include <vector>
#include <mutex>

#include "BasePlayerControlObj.h"
#include "BaseScalable.h"
#include "SnakePart.h"

namespace Snake
{

	class SnakeBody : public Base::BasePlayerControlObj, public BaseScalable
	{
	private:
		const std::string headTPath;
		const std::string torsoTPath;

	private:
		int		xDir		= 0;
		int		yDir		= 0;
		bool	firstMove	= false;

	private:
		std::vector<SnakePart>	body;
		const unsigned int						snakeStartSize	= 4;

	private:
		std::mutex defMt;

	public:
		SnakeBody(
			const char* _pathToHead, 
			const char* _pathToBody);

	public:
		SnakeBody(const SnakeBody&)					= delete;
		SnakeBody& operator=(const SnakeBody&)		= delete;

		// <Base::BasePlayerControlObj> funcs {
	public: 
		//<BaseD> funcs {
		void Draw(sf::RenderWindow& _wnd)						override;
		void SetScale(const sf::Vector2f& _newScale)			override;
		//<BaseD> funcs }
		
		//<BasePawn> funcs {
		void Move()								override;
		void SetDir(BaseP::Direction _dir)		override;
		void DoSomeSpecifyActions()				override;
		void SetPos(const sf::Vector2u& _pos)	override;
		sf::Vector2u const GetPos() const		override;
		//<BasePawn> funcs }
		// 
		// <Base::BasePlayerControlObj> funcs }

	public:
		void CalculateAndSetScale(const ScaleDeterminant& _det) override;

	public:
		void				GrowUp();
		const sf::Vector2u	GetHeadPos()						const;
		const sf::Vector2u	GetPosOnIndex(unsigned int _pos)	const;
		const size_t		GetCurLen()							const;

	private:
		void addTorsoSection(const char* _pathToTorso);
		void clearBody();
		void fillBody(
			int _count, 
			const char* _pathToHead, 
			const char* _pathToTorso);	
	};
}

#endif

