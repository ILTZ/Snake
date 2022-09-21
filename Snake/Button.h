#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>
#include <optional>

#include "SmartPointer.h"

namespace Buttons
{
	enum class BtnMode
	{
		PRESSED		= 0,
		RELEASED	= 1,
		NONE		= 2,
	};

	enum class Btn
	{
		START		= 0,
		EXIT		= 1,
		BACK		= 2,
		CONTINUE	= 3,
		LEADER_BORD	= 4,
		MAIN_MENU	= 5,
		LVL			= 6,
	};

	class Button
	{
	private:
		struct BtnConf
		{
			BtnConf()			= default;
			BtnConf(const char* _pathToBtn);

			SmartPointer::SmartPointer<sf::Texture>			mainText;
			SmartPointer::SmartPointer<sf::RectangleShape>	rectShape;
		};

		struct TextConf
		{
			TextConf(const char* _pathToFont, const std::string& _text);

			SmartPointer::SmartPointer<sf::Text> btnText;
			SmartPointer::SmartPointer<sf::Font> textFont;
		};

	private:
		SmartPointer::SmartPointer<TextConf> text;
		std::unordered_map<BtnMode, BtnConf> btns;
		Btn		whatBtn;
		BtnMode curMode;
		
	public:
		Button(Btn _wBtn, const char* _pathToU, const char* _pathToD, const char* _pathToFont, const char* _btnText = nullptr);

	public:
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;

	public:
		// Switch PRESSED || RELEASED
		void SwitchCurrentState(BtnMode _mode);
		void Rescale(const sf::Vector2f& _newScale);
		void Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos);

	public:
		Btn GetBtnDest() const;
		BtnMode GetBtnMode() const;
		bool GetTouch(float _x, float _y);

	private:
	};
}

#endif