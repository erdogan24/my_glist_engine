 /*
 * GameCanvas.h
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */

#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "gBaseCanvas.h"
#include "GameCanvas.h"
#include "gApp.h"
#include "gImage.h"
#include "gFont.h"



class MainMenu : public gBaseCanvas {
public:
	MainMenu(gApp* root);
	virtual ~MainMenu();

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void charPressed(unsigned int codepoint);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y);
	void mouseEntered();
	void mouseExited();
	void windowResized(int w, int h);

	void showNotify();
	void hideNotify();

private:

	static const int LOADING = 0, PLAYING = 1, PAUSED = 2, MENU = -1;
	static const int font_LOAD1 = 0, font_LOAD2 = 1, font_BUTTON = 2, font_INGAME = 3;

	static const int buttonImageAmount = 4;

	void initilaize();
	void updateLoad(int index);
	void drawLoad();

	void setInitialVariables();

	void drawMenu();

	gApp* root;

	gImage img_background;
	gImage img_blueprint;
	gImage img_menu;
	gImage img_dialogbox;
	gImage img_button[buttonImageAmount];
	// TODO: BURADA KALDIN, .cpp dosyasýnda bunlarý yükle

	std::vector<gFont> font;
	std::vector<int> fontsizes;
	std::vector<std::string> loadingtext;

	int status;
	int loadindex;

	float globalscale;

	int framecounter;
	int seccounter;

	int x_mainmenu, y_mainmenu, x_btnmm, x_btnmm2, y_btnmm; //mainmenu

};

#endif /* GAMECANVAS_H_ */
