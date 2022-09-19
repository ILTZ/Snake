#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <unordered_map>

#include "SmartPointer.h"

namespace Buttons
{
	enum class BtnMode
	{
		PRESSED		= 0,
		RELEASED	= 1,
		NONE		= 2,
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
		BtnMode curMode;

	public:
		Button(const char* _pathToU, const char* _pathToD, const char* _pathToText, const char* _btnText = nullptr);

	public:
		Button(const Button&) = delete;
		Button& operator=(const Button&) = delete;

	public:
		// Switch PRESSED || RELEASED
		void SwitchCurrentState(BtnMode _mode);
		void Rescale(const sf::Vector2f& _newScale);
		void Draw(sf::RenderWindow& _wnd, const sf::Vector2f& _pos);

	private:
	};
}

#endif