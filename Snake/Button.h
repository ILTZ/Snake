#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>
#include <optional>

#include "SmartPointer.h"
#include "BaseText.h"
#include "BaseDrawable.h"

namespace Buttons
{
	enum class BtnState
	{
		PRESSED		= 0,
		RELEASED	= 1,
	};

	enum class BtnPurpose
	{
		START		= 0,
		EXIT		= 1,
		BACK		= 2,
		CONTINUE	= 3,
		LEADER_BORD	= 4,
		MAIN_MENU	= 5,
		LVL_1		= 6,
		LVL_2		= 7,
		LVL_3		= 8,
		LVL_4		= 9,
		LVL_5		= 10,
	};
	BtnPurpose operator++(BtnPurpose& _x);

	class Button final : public BaseDrawable
	{
	private:
		struct BtnConf
		{
			BtnConf()			= default;
			BtnConf(const char* _pathToBtn);

			SmartPointer::SmartPointer<sf::Texture>			mainText;
			SmartPointer::SmartPointer<sf::RectangleShape>	rectShape;


		};

	private:
		SmartPointer::SmartPointer<BaseText>	text;
		std::unordered_map<BtnState, BtnConf>	btns;
		BtnPurpose								btnPurpose;
		BtnState								curState;
		
	private:
		sf::Vector2f btnsSizeDifference;

	public:
		Button(
			BtnPurpose _btnPurpose, 
			const char* _pathToRelesedBtnTexture, 
			const char* _pathToPressedBtnTexture, 
			const char* _pathToFont, 
			const char* _btnText);
		~Button();

	public:
		Button(const Button&)				= delete;
		Button& operator=(const Button&)	= delete;

	public:
		// Switch PRESSED || RELEASED
		void SetState(BtnState _mode);

		virtual void SetScale(const sf::Vector2f& _newScale)		override;
		virtual void SetPosition(const sf::Vector2f& _newPos)		override;
		virtual void Draw(sf::RenderWindow& _wnd)					override;

	public:
		BtnPurpose GetBtnPurpose()		const;
		BtnState GetBtnState()			const;
		bool GetTouch(float _x, float _y);
	
	private:
		void calculateAndSetBtnsShift(const sf::Vector2f& _btnPos);
		const sf::Vector2f calcRectShapeSizeDifference(
			const sf::RectangleShape& _first, 
			const sf::RectangleShape& _second) const;
	};
}

#endif