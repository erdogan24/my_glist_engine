/*
 * GameCanvas.cpp
 *
 *  Created on: May 6, 2020
 *      Author: noyan
 */


#include "GameCanvas.h"
#include "MainMenu.h"


GameCanvas::GameCanvas(gApp* root) : gBaseCanvas(root) {
	this->root = root;
}

GameCanvas::~GameCanvas() {
}


void GameCanvas::setup() {
	img_blueprint.loadImage("GUI/blueprint.png");

	gLogi("GameCanvas Setup");
}

void GameCanvas::update() {
	listenButtons();
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

void GameCanvas::draw() {

	if (status == LOADING) {
		drawLoad();
		//DEBUG
		font[font_LOAD2].drawText("Seconds passed : " + gToStr(seccounter),10,10);
		font[font_LOAD2].drawText("Frames  passed : " + gToStr(framecounter),10,30);

	} else if (status == PLAYING) {
		drawGame();
		drawGUI();
		drawButtons();


	}

}

void GameCanvas::initilaize() {
	gLogi("GameCanvas initilaize");
	isPaused = false;

	gFont empty1, empty2, empty3, empty4, empty5;
	img_blueprint.loadImage("GUI/blueprint.png");
	status = LOADING;
	loadindex = 0;
	framecounter = 0;
	seccounter = 0;

	fontsizes.push_back(24);//LOAD1
	fontsizes.push_back(14);//LOAD2

	fontsizes.push_back(14);//BUTTON
	fontsizes.push_back(14);//INGAME
	fontsizes.push_back(48);//PAUSED


	font.push_back(empty1);
	font[font_LOAD1].loadFont("FreeSans.ttf", fontsizes[font_LOAD1]);
	font.push_back(empty2);
	font[font_LOAD2].loadFont("FreeSans.ttf", fontsizes[font_LOAD2]);

	font.push_back(empty3);
	font[font_BUTTON].loadFont("FreeSans.ttf", fontsizes[font_BUTTON]);
	font.push_back(empty4);
	font[font_INGAME].loadFont("FreeSans.ttf", fontsizes[font_INGAME]);
	font.push_back(empty5);
	font[font_POUSE].loadFont("FreeSans.ttf", fontsizes[font_POUSE]);


	loadingtext.push_back("LOADING");
	loadingtext.push_back("");
}

void GameCanvas::updateLoad(int index) {
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
		case 2: // BUTTONLAR YÜKLENDÝ
			loadingtext[1] += "menu/btn.png";
			for(int i = 0; i < btnAmount; i++) {
				img_button[i].loadImage("menu/btn_" + gToStr(i) + ".png");
			}
			break;
		case 3:
			img_background.loadImage("game/map.png");
			loadingtext[1] += "game/map.png";
			break;
		case 4:
			loadingtext[1] += "Props";
			for(int i = 0; i < propAmount; i++) {
				img_props[i].loadImage("game/props/prop_" + gToStr(i) + ".png");
			}
			break;
		case 5:
			loadingtext[1] += "Buildings";
			for(int i = 0; i < buildingAmount; i++) {
				img_buildings[i].loadImage("game/props/building_" + gToStr(i) + ".png");
				for(int j = 0; j < interiorAmounts[i]; j++) {
					img_interior[i][j].loadImage("game/props/building_" + gToStr(i) + "" + gToStr(j) +".png");
				}
			}
		break;
		case 6:
			loadingtext[1] += "NPCs";
			for(int i = 0; i < NPCAmount; i++) {
				img_NPCs[i].loadImage("game/props/NPC_" + gToStr(i) + ".png");
			}
		break;
		case 7:
			img_pouseMenu.loadImage("GUI/dialogbox1.png");

			//img_pouseMenux = (getWidth()  - (img_pouseMenu.getWidth() * globalscale))/2;
			//img_pouseMenuy = (getHeight() - (img_pouseMenu.getHeight() * globalscale))/2;

/* *
			img_pouseMenux= (getWidth() - (img_pouseMenu.getWidth() * globalscale))/2;
			img_pouseMenuy = (getHeight() - (img_pouseMenu.getHeight() * globalscale))/2;
*/

			loadingtext[1] = "GUI/dialogbox1.png";
			break;
		case 8:
			img_sagust.loadImage("GUI/Untitled1.jpeg");

			loadingtext[1] = "GUI/Untitled1.jpeg";
			break;

		case 9:
			img_solust.loadImage("GUI/Untitled2.jpg");

			loadingtext[1] = "GUI/Untitled2.jpg";
			setInitialVariables();
			break;
		case 100:
			status = PLAYING;
			break;
		}
}

void GameCanvas::setInitialVariables() {
	globalscale = getWidth() / 1920.0f;
	camx = img_background.getWidth() / 2;
	camy = 0;


	cx = getWidth() / 2; // baþlangýç pozisyonu x
	cy = 100; // baþlangýç pozisyonu y

	img_pouseMenux = getWidth()/2 - img_pouseMenu.getWidth()/2 * globalscale;	// center
	img_pouseMenuy = getHeight()/2 - img_pouseMenu.getHeight()/2 * globalscale;	// center

	propXs[SPAWN_POINT] = (getWidth() - img_props[SPAWN_POINT].getWidth()) / 2;
	propYs[SPAWN_POINT] = 100;

	propXs[SHOP_POTION] = propXs[SPAWN_POINT] - img_buildings[SHOP_POTION].getWidth()/2 + 150;
	propYs[SHOP_POTION] = 250;

	propXs[SHOP_ARMORY] = propXs[SHOP_ARMORY] - img_buildings[SHOP_ARMORY].getWidth()/2 - 150;
	propYs[SHOP_ARMORY] = 250;


	img_sagustx = 0;
	img_solusty = getWidth() - img_sagust.getWidth();


	createButton("PAUSED", img_pouseMenux, img_pouseMenuy, 4, 255, 0, 0, font_POUSE);

}

void GameCanvas::drawLoad() {

	img_blueprint.draw(0, 0, globalscale);

	if(framecounter % 15 == 0) {
		gLogi("a");
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

	font[font_LOAD1].drawText(loadingtext[0], 554, getHeight()*4/5);
	font[font_LOAD2].drawText(loadingtext[1], 500, getHeight()*4/5 + fontsizes[0]);

}

void GameCanvas::drawGame() {

	drawMapBG();
	drawMid();
	drawCharacter();
	drawMapFG();

}

void GameCanvas::drawMapBG() {

	img_background.draw(-20,-20, globalscale);
	img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);

	//img_props[SPAWN_POINT].draw(propXs[SPAWN_POINT], propYs[SPAWN_POINT]);


}

void GameCanvas::drawMid() {
	//healer
	//gLogi("global scale : " + gToStr(globalscale));
	img_buildings[SHOP_POTION].draw(propXs[SHOP_POTION], propYs[SHOP_POTION], 0.1f);

	img_buildings[SHOP_ARMORY].draw(propXs[SHOP_ARMORY], propYs[SHOP_ARMORY], 0.1f);

}

void GameCanvas::drawCharacter() {

}


void GameCanvas::drawMapFG() {

}

void GameCanvas::drawGUI() {


	img_sagust.draw(img_sagustx, img_sagusty, globalscale);
	img_sagust.draw(img_solustx, img_solusty, globalscale);

	img_solust.draw(img_sagustx, img_sagusty, globalscale);
	img_solust.draw(img_solustx, img_solusty, globalscale);

}

void GameCanvas::keyPressed(int key) {
//	gLogi("GameCanvas") << "keyPressed:" << key;
}

void GameCanvas::keyReleased(int key) {
	gLogi("GameCanvas") << "keyReleased:" << key;
}

void GameCanvas::charPressed(unsigned int codepoint) {
//	gLogi("GameCanvas") << "charPressed:" << gCodepointToStr(codepoint);
}

void GameCanvas::mouseMoved(int x, int y) {
//	gLogi("GameCanvas") << "mouseMoved" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseDragged(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseDragged" << ", x:" << x << ", y:" << y << ", b:" << button;
}

void GameCanvas::mousePressed(int x, int y, int button) {
}

void GameCanvas::mouseReleased(int x, int y, int button) {
//	gLogi("GameCanvas") << "mouseReleased" << ", button:" << button;
	for(int b = 0; b < buttons.size(); b++) {
		if(x > buttons[b][0] && y > buttons[b][1] && x < buttons[b][7] && y < buttons[b][8]) {
			buttonPressed = b;
			gLogi("buttonPressed = " + gToStr(b));
		}
	}
}

void GameCanvas::mouseScrolled(int x, int y) {
//	gLogi("GameCanvas") << "mouseScrolled" << ", x:" << x << ", y:" << y;
}

void GameCanvas::mouseEntered() {
}

void GameCanvas::mouseExited() {
	isPaused = true;
}

void GameCanvas::windowResized(int w, int h) {
}

void GameCanvas::showNotify() {

}

void GameCanvas::hideNotify() {

}

void GameCanvas::createButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	buttonTexts.push_back(btntext);
	std::vector<int> tmpbtn;
	tmpbtn.push_back(btnx);
	tmpbtn.push_back(btny);
	tmpbtn.push_back(btntype);
	tmpbtn.push_back(btnR);
	tmpbtn.push_back(btnG);
	tmpbtn.push_back(btnB);
	tmpbtn.push_back(texttype);
	tmpbtn.push_back(btnx + img_button[btntype].getWidth());
	tmpbtn.push_back(btny + img_button[btntype].getHeight());
	buttons.push_back(tmpbtn);
}

void GameCanvas::drawButton(std::string btntext, int btnx, int btny, int btntype, int btnR, int btnG, int btnB, int texttype) {
	//gLogi("MENUCANVAS::DRAWBUTTON -> START");
	img_button[btntype].draw(btnx, btny, globalscale);
	//gLogi("draw emptybtns : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale)- font[texttype].getStringWidth(btntext)) / 2) , btny + (img_button[btntype].getHeight() * globalscale)/2 + 3, btnR/3,btnG/3,btnB/3);
	//gLogi("draw savetextshadow : [PASSED]");
	font[texttype].drawText(btntext, btnx + (((img_button[btntype].getWidth() * globalscale) - font[texttype].getStringWidth(btntext)) / 2) - 1, btny + (img_button[btntype].getHeight() * globalscale)/2 + 1, btnR, btnG, btnB);
	//gLogi("draw savetext : [PASSED]");
}

void GameCanvas::drawButtons() {
	for(int i = 0; i < buttons.size(); i++) {

		if(i == 0) {
			if(isPaused) {
				drawButton(buttonTexts[i], buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3], buttons[i][4], buttons[i][5], buttons[i][6]);
			}
		}
		else {
			drawButton(buttonTexts[i], buttons[i][0], buttons[i][1], buttons[i][2], buttons[i][3], buttons[i][4], buttons[i][5], buttons[i][6]);
		}
	}
}

void GameCanvas::listenButtons() {
	if(buttonPressed != -1) {
		gLogi("test 348");
		if(buttonPressed == 0) {
			gLogi("test 349");
			isPaused = false;
		}

		buttonPressed = -1; // reset action
	}
}

