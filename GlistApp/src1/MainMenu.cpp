#include "gApp.h"
#include "MainMenu.h"
#include "GameCanvas.h"

MainMenu::MainMenu(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

MainMenu::~MainMenu() {
}

void MainMenu::setup() {

	gLogi(" getWidth() / 1920 : " + gToStr( (getWidth() / 1920.0f) ));
	globalscale = getWidth() / 1920.0f;

	img_blueprint.loadImage("GUI/blueprint.png");
	status = LOADING;
	loadindex = 0;
	framecounter = 0;
	seccounter = 0;
	initilaize();
}

void MainMenu::update() {
	framecounter++;
	if(framecounter % 60 == 0) {
		seccounter++;
	}
	if (status == LOADING) {
		updateLoad(loadindex);
		loadindex++;
	} else if (status == PLAYING) {

	}
}

void MainMenu::draw() {
	if (status == LOADING) {
		drawLoad();
		//DEBUG
		font[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
		font[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);

	} else if (status == MENU) {
		drawMenu();
	}
}

void MainMenu::initilaize() {
	gFont empty1, empty2;

	fontsizes.push_back(24);
	fontsizes.push_back(14);

	font.push_back(empty1);
	font.push_back(empty2);
	font[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	font[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);

	loadingtext.push_back("LOADING");
	loadingtext.push_back("");
}

void MainMenu::updateLoad(int index) {
	loadingtext[1] = "Loaded : ";
	switch (index) {

	case 0:
		img_menu.loadImage("menu/mainmenubg.png");
		loadingtext[1] += "menu/mainmenubg.png";
		break;
	case 1:
		img_dialogbox.loadImage("GUI/dialogbox2.png");
		loadingtext[1] += "GUI/dialogbox.png";
		break;
	case 2:
		loadingtext[1] += "menu/btn.png";
		for(int i = 0; i < buttonImageAmount; i++) {
			img_button[i].loadImage("menu/btn_" + gToStr(i) + ".png");
		}
		break;
	case 3:
		img_background.loadImage("game/map.png");
		loadingtext[1] += "game/map.png";
		break;
	case 4:

		loadingtext[1] += "";
		break;
	case 5:

		loadingtext[1] += "";
		break;
	case 6:

		loadingtext[1] += "";
		break;
	case 7:

		loadingtext[1] = "Setting up all initial variables...";
		break;
	case 8:

		loadingtext[1] = "Setting up all initial variables...";
		break;
	case 9:
		loadingtext[1] = "Setting up all initial variables...";
		setInitialVariables();
		break;
	case 100:
		status = MENU;
		break;



	}

}

void MainMenu::setInitialVariables() {

	// load saves vs dediðimiz zaman menünün kayacaðý 2. kýsým
	//x_mainmenu = getWidth()/20;								//margin %5 from begin

	x_mainmenu = (getWidth() - (img_menu.getWidth() * globalscale)) / 2;	// center
	y_mainmenu = (getHeight() - (img_menu.getHeight() * globalscale)) / 2;	// center

	x_btnmm2 = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[0].getWidth() * globalscale)) / 2;
	x_btnmm = x_mainmenu + ((img_menu.getWidth() * globalscale) - (img_button[1].getWidth() * globalscale)) / 2;
	y_btnmm = y_mainmenu + (338 * globalscale);
}

void MainMenu::drawLoad() {
	img_blueprint.draw(0, 0, globalscale);

	if(framecounter % 15 == 0) {
		switch(loadingtext[0].length()) {
		case 7: case 8: case 9:
			loadingtext[0] += ".";
			break;
		case 10:
			loadingtext[0] = "LOADING.";
			break;
		}
	}
	//int x = (getWidth() - font[font_LOAD1].getStringWidth(loadingtext[0]))/2;
//	gLogi(gToStr(x));

	font[font_LOAD1].drawText(loadingtext[0], 554, getHeight()*4/5, 255, 255, 0);
	font[font_LOAD2].drawText(loadingtext[1], 500, getHeight()*4/5 + fontsizes[0]);

}

void MainMenu::drawMenu() {
// TODO:: BURADA KALDIN, GLOBAL SCALE DEÐERÝ OLUÞTUR, YENÝ DRAW METHODU YAZ BUNUNLA
	setColor(128,128,128);
	//img_blueprint.draw(0, 0, globalscale);
	img_background.draw((-1 * (img_background.getWidth() / 2)), -20);
	setColor(255,255,255);
	//img_menu.draw(0, 0);
	img_menu.draw(x_mainmenu, y_mainmenu, globalscale);
	//img_menu.draw(0, 0, 20);
	//, x_menu + 100, y_menu + 100
	y_btnmm = y_mainmenu + (338 * globalscale);
	for(int i = 0; i < 4; i++) {
		if(i < 3) {
			img_button[1].draw(x_btnmm, y_btnmm, globalscale);
		} else {
			img_button[0].draw(x_btnmm2, y_btnmm, globalscale);
		}
		y_btnmm += (img_button[1].getHeight() * globalscale) + 11;
	}
}


















void MainMenu::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
}

void MainMenu::keyReleased(int key) {
//	gLogi("GameCanvas") << "keyReleased:" << key;
}

void MainMenu::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void MainMenu::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void MainMenu::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void MainMenu::mousePressed(int x, int y, int button) {
}

void MainMenu::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;

	GameCanvas *cnv = new GameCanvas(this->root);
	root->setCurrentCanvas(cnv);

}

void MainMenu::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void MainMenu::mouseEntered() {
}

void MainMenu::mouseExited() {
}

void MainMenu::windowResized(int w, int h) {
}

void MainMenu::showNotify() {

}

void MainMenu::hideNotify() {

}

