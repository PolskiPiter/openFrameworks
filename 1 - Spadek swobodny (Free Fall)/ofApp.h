#pragma once

#include "ofMain.h"
#include <time.h>

class ofApp : public ofBaseApp{
	private:
		
		// Wektory ruchu - przyspieszenia, pr�dko�ci, po�o�enia
		ofVec2f a;
		ofVec2f v;
		ofVec2f vn_1;
		ofVec2f r;

		// Krok czasowy (krok ca�kowania w metodzie Eulera)
		float dt;

		//Sprawdzenie czy dosz�o do kolizji
		bool collision;

		//Zmienne z tekstami do wy�wietlenia na ekranie
		string aVec_string;
		string vVec_string;
		string rVec_string;

		string dt_string;

		string Description;

		//Czcionka do tekstu
		ofTrueTypeFont FontArial;

		// Pi�ka do koszyk�wki - Rysunek
		ofImage BasketballBall;

		//D�wi�k odbicia pi�ki
		ofSoundPlayer BasketballSingleBounceBall;

	public:
		void setup();
		void update();
		void draw();

	
};
