#include <Geode/modify/FLAlertLayer.hpp>
#include "Utils.hpp"

using namespace geode::prelude;

class $modify(MyFLAlertLayer, FLAlertLayer) {
	bool init(FLAlertLayerProtocol* delegate, char const* title, gd::string desc, char const* btn1, char const* btn2, float width, bool scroll, float height, float textScale) {
		bool isModsLayer = CCDirector::get()->getRunningScene()->getChildByID("ModsLayer");
		if (!Utils::modEnabled() || (!isModsLayer && Utils::getBool("modsLayer"))) {
			return FLAlertLayer::init(delegate, title, desc, btn1, btn2, width, scroll, height, textScale);
		}
		std::string titleString = title;
		std::string descString = desc;
		bool desiredScroll = scroll;
		float desiredScale = textScale;
		float desiredWidth = width;
		float desiredHeight = height;
		if (Utils::getBool("logging")) {
			log::info("-- [BEFORE ALERTLAYERTWEAKS] --");
			log::info("title: {}", titleString);
			log::info("desc: {}", descString);
			if (btn1) { log::info("btn1: {}", btn1); }
			if (btn2) { log::info("btn2: {}", btn2); }
			log::info("width: {}", desiredWidth);
			log::info("scroll: {}", desiredScroll);
			log::info("height: {}", desiredHeight);
			log::info("textScale: {}", desiredScale);
			log::info("bouncing: {}", m_noElasticity);
			log::info("friendly reminder to check if \"Fast Menu\" is enabled inside your in-game settings too :)");
			log::info("also, there's a small chance text contents may have changed based on what mods you have installed. consult your mods list to confirm.");
		}
		if (Utils::getInt("textScroll") < 1) {
			if (!desiredScroll) {
				desiredScale = static_cast<float>(Utils::getDouble("textScale"));
			} else { desiredHeight = 300.f; }
			if (width <= 420.f) {
				desiredWidth = static_cast<float>(width * Utils::getDouble("flAlertWidthMultiplier"));
				if (desiredWidth >= 420.f) { desiredWidth = 420.f; }
			}
		} else {
			desiredWidth = 420.f;
			desiredScroll = (Utils::getInt("textScroll") != -1);
		}
		if (Utils::getInt("bouncingTransition") != 0) {
			m_noElasticity = (Utils::getInt("bouncingTransition") == -1);
		}
		if (Utils::getBool("logging")) {
			log::info("-- [AFTER ALERTLAYERTWEAKS] --");
			log::info("title: {}", titleString);
			log::info("desc: {}", descString);
			if (btn1) { log::info("btn1: {}", btn1); }
			if (btn2) {  log::info("btn2: {}", btn2);  }
			log::info("width: {}", desiredWidth);
			log::info("scroll: {}", desiredScroll);
			log::info("height: {}", desiredHeight);
			log::info("textScale: {}", desiredScale);
			log::info("bouncing: {}", m_noElasticity);
			log::info("friendly reminder to check if \"Fast Menu\" is enabled inside your in-game settings too :)");
			log::info("also, there's a small chance text contents may have changed based on what mods you have installed. consult your mods list to confirm.");
		}
		return FLAlertLayer::init(delegate, title, desc, btn1, btn2, desiredWidth, desiredScroll, desiredHeight, desiredScale);
	}
};