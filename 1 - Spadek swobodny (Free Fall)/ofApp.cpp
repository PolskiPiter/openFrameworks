#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Ustawienie warunków pocz¹tkowych do wyliczania po³o¿enia i prêdkoœci
	a.set(0, 9.81); //Sk³adowe ax i ay (Inaczej wektory sk³adowe)
	v.set(0, -50);	//Sk³adowe vx i vy
	r.set(0,0); //Sk³adowe rx i ry

	//Ustawienie kroku czasowego
	dt = 0.2f;

	//Ustawienie flagi odpowiedzialnej za sprawdzenie czy nast¹pi³a kolizja
	collision = false;

	//Ustawienie stringów (tekstów do wyœwietlenia na ekranie)
	aVec_string = "a : (" + ofToString(a) + ")";
	vVec_string = "v : (" + ofToString(v) + ")";
	rVec_string = "r : (" + ofToString(r) + ")";
	dt_string = "delta time: " + ofToString(dt);

	Description = "Spadek swobodny na przykladzie pilki do koszykowki: \n\t\t\t\t\t\t\t - Spadek swobodny; \n\t\t\t\t\t\t\t - Metoda Eulera; \n\t\t\t\t\t\t\t - Kolizja i odbicie od podloza;";

	//Za³adowanie czcionki
	FontArial.load("arialbd.ttf", 13);

	// Za³adowanie obrazka pi³ki i zmiana jego rozmiarów wyœwietlania na ekranie
	BasketballBall.load("Basketball_Ball.png");
	BasketballBall.resize(BasketballBall.getWidth() / 2, BasketballBall.getHeight() / 2);

	// Za³adowanie dŸwiêku odbicia pi³ki do koszykówki od powierzchni
	BasketballSingleBounceBall.load("Basketball_Single_Bouncel_ball.mp3");
	BasketballSingleBounceBall.setVolume(10.f);

}

//--------------------------------------------------------------
void ofApp::update(){
	
	// Odliczanie czasu. Je¿eli czas dzia³ania programu przekroczy 15 sekund rozpocznij symulacje
	if (clock() / CLOCKS_PER_SEC >= 10)
	{ 
		// Metoda Eulera - obliczenie prêdkoœci i pozycji pi³ki w spadku swobodnym
		vn_1 = v;
		v = v + a * dt;
		r = r + (v+vn_1/2) * dt;

		//Kolizja z pod³og¹
		// Jeœli nast¹pi³a kolizja to ustaw flagê (collision) na true i
		// zmieñ wektor przyspieszenia i prêdkoœci na przeciwny
		if (r.y - BasketballBall.getHeight() >= (ofGetHeight() / 2 - BasketballBall.getHeight() / 2) - BasketballBall.getHeight())
		{
			collision = true;
			a.y = -a.y;
			v.y = -(v.y);
		}

		// Sprawdzenie czy kolizja ju¿ nast¹pi³a i jêsli tak to zmieñ wektor przyspieszania
		// na przeciwny. Prócz tego odtwórz dŸwiêk odbicia pi³ki od pod³o¿a i zmieñ flagê na false
		if (collision == true)
		{
			BasketballSingleBounceBall.play();
			a.y = -a.y;
			collision = false;
		}
	}
	
	//Ustawienie stringów (tekstów do wyœwietlenia na ekranie)
	vVec_string = "v : (" + ofToString(v) + ")";
	rVec_string = "r : (" + ofToString(r) + ")";

	if (clock() / CLOCKS_PER_SEC >= 95)
	{
		ofExit();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Translacja - domyœlny punkt pocz¹tku uk³adu wspó³rzêdnych
	ofTranslate(0, 0);
	FontArial.drawString("Czas symulacji: " + ofToString(clock() / CLOCKS_PER_SEC), 50, 50);
	
	// Translacja pozycji nowych obiektów
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	// Rysowanie pi³ki do koszykówki
	BasketballBall.draw(r.x-BasketballBall.getWidth()/2, r.y-BasketballBall.getHeight()/2);

	//Wyœwietlenie tekstu na ekranie
	FontArial.drawString(Description, -FontArial.stringWidth(Description) / 2, -ofGetHeight() / 2 + 25);

	FontArial.drawString(aVec_string, -FontArial.stringWidth(aVec_string) / 2, -ofGetHeight() / 2 + 115);
	FontArial.drawString(vVec_string, -FontArial.stringWidth(vVec_string) / 2, -ofGetHeight() / 2 + 135);
	FontArial.drawString(rVec_string, -FontArial.stringWidth(rVec_string) / 2, -ofGetHeight() / 2 + 155);
	FontArial.drawString(dt_string, -FontArial.stringWidth(dt_string) / 2, -ofGetHeight() / 2 + 175);

	FontArial.drawString(" < (0,0)", 100, 0);
}


