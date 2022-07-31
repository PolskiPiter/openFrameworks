#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Ustawienie warunk�w pocz�tkowych do wyliczania po�o�enia i pr�dko�ci
	a.set(0, 9.81); //Sk�adowe ax i ay (Inaczej wektory sk�adowe)
	v.set(0, -50);	//Sk�adowe vx i vy
	r.set(0,0); //Sk�adowe rx i ry

	//Ustawienie kroku czasowego
	dt = 0.2f;

	//Ustawienie flagi odpowiedzialnej za sprawdzenie czy nast�pi�a kolizja
	collision = false;

	//Ustawienie string�w (tekst�w do wy�wietlenia na ekranie)
	aVec_string = "a : (" + ofToString(a) + ")";
	vVec_string = "v : (" + ofToString(v) + ")";
	rVec_string = "r : (" + ofToString(r) + ")";
	dt_string = "delta time: " + ofToString(dt);

	Description = "Spadek swobodny na przykladzie pilki do koszykowki: \n\t\t\t\t\t\t\t - Spadek swobodny; \n\t\t\t\t\t\t\t - Metoda Eulera; \n\t\t\t\t\t\t\t - Kolizja i odbicie od podloza;";

	//Za�adowanie czcionki
	FontArial.load("arialbd.ttf", 13);

	// Za�adowanie obrazka pi�ki i zmiana jego rozmiar�w wy�wietlania na ekranie
	BasketballBall.load("Basketball_Ball.png");
	BasketballBall.resize(BasketballBall.getWidth() / 2, BasketballBall.getHeight() / 2);

	// Za�adowanie d�wi�ku odbicia pi�ki do koszyk�wki od powierzchni
	BasketballSingleBounceBall.load("Basketball_Single_Bouncel_ball.mp3");
	BasketballSingleBounceBall.setVolume(10.f);

}

//--------------------------------------------------------------
void ofApp::update(){
	
	// Odliczanie czasu. Je�eli czas dzia�ania programu przekroczy 15 sekund rozpocznij symulacje
	if (clock() / CLOCKS_PER_SEC >= 10)
	{ 
		// Metoda Eulera - obliczenie pr�dko�ci i pozycji pi�ki w spadku swobodnym
		vn_1 = v;
		v = v + a * dt;
		r = r + (v+vn_1/2) * dt;

		//Kolizja z pod�og�
		// Je�li nast�pi�a kolizja to ustaw flag� (collision) na true i
		// zmie� wektor przyspieszenia i pr�dko�ci na przeciwny
		if (r.y - BasketballBall.getHeight() >= (ofGetHeight() / 2 - BasketballBall.getHeight() / 2) - BasketballBall.getHeight())
		{
			collision = true;
			a.y = -a.y;
			v.y = -(v.y);
		}

		// Sprawdzenie czy kolizja ju� nast�pi�a i j�sli tak to zmie� wektor przyspieszania
		// na przeciwny. Pr�cz tego odtw�rz d�wi�k odbicia pi�ki od pod�o�a i zmie� flag� na false
		if (collision == true)
		{
			BasketballSingleBounceBall.play();
			a.y = -a.y;
			collision = false;
		}
	}
	
	//Ustawienie string�w (tekst�w do wy�wietlenia na ekranie)
	vVec_string = "v : (" + ofToString(v) + ")";
	rVec_string = "r : (" + ofToString(r) + ")";

	if (clock() / CLOCKS_PER_SEC >= 95)
	{
		ofExit();
	}
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	//Translacja - domy�lny punkt pocz�tku uk�adu wsp�rz�dnych
	ofTranslate(0, 0);
	FontArial.drawString("Czas symulacji: " + ofToString(clock() / CLOCKS_PER_SEC), 50, 50);
	
	// Translacja pozycji nowych obiekt�w
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	
	// Rysowanie pi�ki do koszyk�wki
	BasketballBall.draw(r.x-BasketballBall.getWidth()/2, r.y-BasketballBall.getHeight()/2);

	//Wy�wietlenie tekstu na ekranie
	FontArial.drawString(Description, -FontArial.stringWidth(Description) / 2, -ofGetHeight() / 2 + 25);

	FontArial.drawString(aVec_string, -FontArial.stringWidth(aVec_string) / 2, -ofGetHeight() / 2 + 115);
	FontArial.drawString(vVec_string, -FontArial.stringWidth(vVec_string) / 2, -ofGetHeight() / 2 + 135);
	FontArial.drawString(rVec_string, -FontArial.stringWidth(rVec_string) / 2, -ofGetHeight() / 2 + 155);
	FontArial.drawString(dt_string, -FontArial.stringWidth(dt_string) / 2, -ofGetHeight() / 2 + 175);

	FontArial.drawString(" < (0,0)", 100, 0);
}


