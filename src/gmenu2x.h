/***************************************************************************
 *   Copyright (C) 2006 by Massimiliano Torromeo                           *
 *   massimiliano.torromeo@gmail.com                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef GMENU2X_H
#define GMENU2X_H

#include "buildopts.h"
#include "contextmenu.h"
#include "cpu.h"
#include "surfacecollection.h"
#include "translator.h"
#include "inputmanager.h"
#include "powersaver.h"
#include "surface.h"
#include "utilities.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class BottomBar;
class BrightnessManager;
class Button;
class FontStack;
class HelpPopup;
class IconButton;
class Launcher;
class Layer;
class Layout;
class LayoutItem;
class MediaMonitor;
class Menu;

const int LOOP_DELAY = 30000;

extern const char *CARD_ROOT;

// Note: Keep this in sync with colorNames!
enum color {
	COLOR_TOP_BAR_BG,
	COLOR_BOTTOM_BAR_BG,
	COLOR_SELECTION_BG,
	COLOR_MESSAGE_BOX_BG,
	COLOR_MESSAGE_BOX_BORDER,
	COLOR_MESSAGE_BOX_SELECTION,

	NUM_COLORS,
};

class GMenu2X {
private:
	std::shared_ptr<Menu> menu;
#ifdef ENABLE_INOTIFY
	MediaMonitor *monitor;
#endif
	std::unique_ptr<BrightnessManager> brightnessmanager;

	std::unique_ptr<Launcher> toLaunch;

	std::vector<std::shared_ptr<Layer>> layers;

	std::unique_ptr<Layout> layout;
	std::shared_ptr<LayoutItem> top;
	std::shared_ptr<BottomBar> bottomBar;

	/*!
	Displays a selector and launches the specified executable file
	*/
	void explorer();

	std::string lastSelectorDir;
	int lastSelectorElement;
	void readConfig();
	void readConfig(std::string path);
	void sanitizeConfig();
	void readTmp();

	// Returns true if the font has changed.
	bool initFont();

	void initMenu();
	void initBG();

	std::string getLocalSkinTopPath() const {
		return getHome() + "/skins/" + std::to_string(width())
			+ "x" + std::to_string(height());
	}

	std::string getSystemSkinTopPath() const {
		return GMENU2X_SYSTEM_DIR "/skins/" + std::to_string(width())
			+ "x" + std::to_string(height());
	}

public:
	static void run();

	GMenu2X();
	~GMenu2X();

	static const std::string getLogFile() {
		return getHome() + "/gmenu2x.log";
	}

	const unsigned int getUiScale() const {
		return const_cast<ConfIntHash&>(skinConfInt)["uiScale"] ?: 1;
	}

	/* Returns the home directory of gmenu2x, usually
	 * ~/.gmenu2x */
	static const std::string getHome();

	const unsigned int width() const { return s->width(); }
	const unsigned int height() const { return s->height(); }

	void enableManualIcon(bool enable);
	void showCpuFreq(unsigned long mhz = 0);

	/*
	 * Variables needed for elements disposition
	 */
	uint32_t bottomBarIconY, bottomBarTextY;
	unsigned short cpuX; //!< Offset for displaying cpu clock information
	unsigned short manualX; //!< Offset for displaying the manual indicator in the taskbar

	/**
	 * Gets the position and height of the area between the top and bottom bars.
	 */
	std::pair<unsigned int, unsigned int> getContentArea() {
		const unsigned int top = skinConfInt["topBarHeight"];
		const unsigned int bottom = skinConfInt["bottomBarHeight"];
		return std::make_pair(top, s->height() - top - bottom);
	}

	std::shared_ptr<PowerSaver> powerSaver;
	InputManager input;
#ifdef ENABLE_CPUFREQ
	Cpu cpu;
#endif

	//Configuration hashes
	ConfStrHash confStr, skinConfStr;
	ConfIntHash confInt, skinConfInt;
	RGBAColor skinConfColors[NUM_COLORS];

	//Configuration settings
	bool useSelectionPng;
	void setSkin(const std::string &skin, bool setWallpaper = true);
	bool readSkinConfig(const std::string& conffile);

	SurfaceCollection sc;
	Translator tr;
	std::unique_ptr<OutputSurface> s;
	/** Background with empty top and bottom bar. */
	std::shared_ptr<OffscreenSurface> bg;
	/** Background with empty top bar and a partially filled bottom bar. */
	std::shared_ptr<OffscreenSurface> bgmain;
	std::unique_ptr<FontStack> font;

	//Status functions
	void mainLoop();
	void showContextMenu();
	void showHelpPopup();
	void showManual();
	void showSettings();
	void skinMenu();
	void about();
	void viewLog();
	void changeWallpaper();

	/**
	 * Requests that the given application be launched.
	 * The launch won't happen immediately; it will happen after control
	 * returns to the main loop.
	 */
	void queueLaunch(std::unique_ptr<Launcher>&& launcher,
					 std::shared_ptr<Layer> launchLayer);

	void saveSelection();
	void writeConfig();
	void writeSkinConfig();
	void writeTmp(int selelem=-1, const std::string &selectordir="");

	void addLink();
	void editLink();
	void deleteLink();
	void addSection();
	void deleteSection();

	int drawButton(Surface& s, const std::string &btn, const std::string &text, int x=5, int y=-10);
	int drawButtonRight(Surface& s, const std::string &btn, const std::string &text, int x=5, int y=-10);
	void drawScrollBar(uint32_t pageSize, uint32_t totalSize, uint32_t pagePos);

	void drawTopBar(Surface& s);
	void drawBottomBar(Surface& s);

	std::string getLocalSkinPath(const std::string& skin) const {
		return getLocalSkinTopPath() + "/" + skin;
	}

	std::string getSystemSkinPath(const std::string &skin) const {
		return getSystemSkinTopPath() + "/" + skin;
	}
};

#endif // GMENU2X_H
