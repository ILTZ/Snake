#include "HUD.h"

#include "LeaderRecordWidget.h"

#include <cassert>

using namespace UI;

UI::Ui::Ui(CLoader::HudConfigs& _configs) :
	pathToBtnReleased{_configs.pathToReleaseBtn},
	pathToBtnPressed{_configs.pathToPressBtn},
	pathToFont{_configs.pathToTextFont},
	pathToNameWidget{_configs.pathToNameWidget},
	hud{new sf::Texture()},
	currentScale{1.f,1.f}
{
	hud->loadFromFile(_configs.pathToHud);
	hudSprite = new sf::Sprite(*hud);

	const sf::Vector2f wndSize(
		static_cast<float>(_configs.width),
		static_cast<float>(_configs.height));

	mainLayout = new LAYOUT::Layout(wndSize, wndSize / 2.f);
	mainLayout->SetDistanceBeetwenObjcts(wndSize.y / 10.f);

	widgetLayout = new LAYOUT::Layout(
		sf::Vector2f(
			hudSprite->getGlobalBounds().width,
			hudSprite->getGlobalBounds().height / 2.f),
		sf::Vector2f());
	widgetLayout->SetDistanceBeetwenObjcts(hudSprite->getGlobalBounds().height / 10.f);
}

#pragma region DrawProcesses

void UI::Ui::DrawUI(sf::RenderWindow& _wnd, APP_STATE::States _state)
{
	std::lock_guard lk(defMutex);

	switch (_state)
	{
	case APP_STATE::States::MAIN_MENU:
	case APP_STATE::States::LVL_SELECT:
	case APP_STATE::States::LVL_SELECTED:
	case APP_STATE::States::LEADERS_VIEW:
		DrawMainLayout(_wnd);
		break;

	case APP_STATE::States::GAME_PROCESS:
		DrawHUDSprite(_wnd);
		DrawWidgetLayout(_wnd);
		break;

	case APP_STATE::States::GAME_PAUSE:
	case APP_STATE::States::INPUT_NAME:
	case APP_STATE::States::GAME_OVER:
		DrawHUDSprite(_wnd);
		DrawWidgetLayout(_wnd);
		DrawMainLayout(_wnd);
		break;


	default:
		break;
	}
}

void Ui::DrawHUDSprite(sf::RenderWindow& _wnd)
{
	_wnd.draw(*hudSprite);
}
void Ui::DrawWidgetLayout(sf::RenderWindow& _wnd)
{
	widgetLayout->Draw(_wnd);
}
void UI::Ui::DrawMainLayout(sf::RenderWindow& _wnd)
{
	mainLayout->Draw(_wnd);
}

#pragma endregion

void UI::Ui::SetScale(const sf::Vector2f& _newScale)
{
	currentScale = _newScale;
	hudSprite->setScale(currentScale);

	mainLayout->SetScale(currentScale);
	widgetLayout->SetScale(currentScale);
}

void UI::Ui::fillLeaderbord(LAYOUT::Layout& _layout)
{
	SmartPointer::SmartPointer<CLoader::Loader> loader = new CLoader::Loader();

	auto vec = loader->GetLeaders();
	std::sort(vec.begin(), vec.end(),
		[&](const CLoader::LeadersInfo& _first, const CLoader::LeadersInfo& _second)
		{
			return _first.points > _second.points;
		});

	for (size_t i = 0; i < maxLeaders; ++i)
	{
		if (i < vec.size())
		{
			auto lead = std::make_shared<LeaderRecordWidget>(
				pathToNameWidget.c_str(), 
				pathToFont.c_str(), 
				vec[i].name.c_str(),
				std::to_string(vec[i].points),
				vec[i].TimeToString());
			_layout.AddObject(lead);
			continue;
		}
		mainLayout->AddObject(std::make_shared<LeaderRecordWidget>(pathToNameWidget.c_str(), pathToFont.c_str()));
	}

}

const sf::Vector2u UI::Ui::GetHUDSize() const
{
	return hud->getSize();
}

const sf::Vector2f UI::Ui::GetHudSpritePosition() const
{
	return hudSprite->getPosition();
}

void UI::Ui::SetHudSpritePosition(const sf::Vector2f& _newPos)
{
	hudSprite->setPosition(_newPos);

	widgetLayout->SetPosition({
		_newPos.x + hudSprite->getGlobalBounds().width / 2.f,
		_newPos.y + hudSprite->getGlobalBounds().height / 2.f });
}

std::optional <Buttons::BtnPurpose> UI::Ui::CheckButtonsTouch(float _x, float _y)
{
	for (size_t i = 0; i < btnsLogicArr.size(); ++i)
	{
		if (btnsLogicArr[i]->GetTouch(_x, _y))
		{
			return btnsLogicArr[i]->GetBtnPurpose();
		}
	}

	return {};
}

void UI::Ui::AddWidget(std::shared_ptr<BaseDrawable> _widget)
{
	assert(widgetLayout->GetLayoutSize() != baseWidgetLayoutSize);

	widgetLayout->AddObject(_widget);
}

void UI::Ui::RealeseButtons()
{
	for (auto& el : btnsLogicArr)
	{
		el->SetState(Buttons::BtnState::RELEASED);
	}
}

void UI::Ui::PrepButtons(APP_STATE::States _state, int _lvlCount)
{
	std::lock_guard<std::mutex> lock(defMutex);

	ClearBtnsLogicArr();
	ClearMainLayout();

	switch (_state)
	{
		case APP_STATE::States::MAIN_MENU:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::START, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Start"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::LEADER_BORD, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Leaderbord"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			mainLayout->AddObject(btnsLogicArr.back());

		}
		break;

		case APP_STATE::States::LVL_SELECT:
		{
			assert(_lvlCount);

			Buttons::BtnPurpose tempB = Buttons::BtnPurpose::LVL_1;
			for (int i = 0; i < _lvlCount; ++i)
			{
				btnsLogicArr.emplace_back(new Buttons::Button(tempB, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
					pathToFont.c_str(),
					(std::string("LVL ") + std::to_string(i + 1)).c_str()
				));
				++tempB;

				mainLayout->AddObject(btnsLogicArr.back());
			}
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
			mainLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::LEADERS_VIEW:
		{
			fillLeaderbord(*mainLayout);
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::BACK, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Back"));
			mainLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::GAME_PAUSE:
		{
			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::CONTINUE, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Continue"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			mainLayout->AddObject(btnsLogicArr.back());
		}
		break;

		case APP_STATE::States::INPUT_NAME:
		{
			mainLayout->AddObject(std::make_shared<LeaderRecordWidget>(pathToNameWidget.c_str(), pathToFont.c_str(), "!-Enter your name-!"));

			nameWidget = std::make_shared<InputNameWidget>
				(pathToNameWidget.c_str(), pathToFont.c_str());
			mainLayout->AddObject(nameWidget);

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::NAME_ACEPT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Accept"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::MAIN_MENU, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Main Menu"));
			mainLayout->AddObject(btnsLogicArr.back());

			btnsLogicArr.emplace_back(new Buttons::Button(Buttons::BtnPurpose::EXIT, pathToBtnReleased.c_str(), pathToBtnPressed.c_str(),
				pathToFont.c_str(), "Exit"));
			mainLayout->AddObject(btnsLogicArr.back());
		}
		break;

		default:
			break;
	}

}

std::optional<InputNameWidget*> UI::Ui::GetInputNameWidget()
{
	if (nameWidget.get())
		return nameWidget.get();

	return {};
}

void UI::Ui::ClearInputNameWidget()
{
	if (nameWidget.get())
		nameWidget.reset();
}

void UI::Ui::ClearWidgets()
{
	widgetLayout->ClearLayout();
}

void UI::Ui::ClearBtnsLogicArr()
{
	btnsLogicArr.clear();
}

void UI::Ui::ClearMainLayout()
{
	mainLayout->ClearLayout();
}