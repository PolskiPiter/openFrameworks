#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//D�ugo�c wektora
	V = 330;

	//Stopie� fraktala
	deep = 4;

	//Licznik wyboru wsp�czynnik skalowania dla wierzcho�k�w
	counter_param_scale = 1;

	//Tablica z wsp�czynnikami skalowania dla ka�dego zestawu tr�jk�t�w
	for (int i = 0; i <= deep; i++) scale_parameters.push_back(0.f);

	//Wierzcho�ki pierwszego tr�jk�ta
	ver1.set(V * cos((-90 * M_PI) / 180), V * sin((-90 * M_PI / 180)));
	ver2.set(V * cos((-210 * M_PI) / 180), V * sin((-210 * M_PI / 180)));
	ver3.set(V * cos((-330 * M_PI) / 180), V * sin((-330 * M_PI / 180)));

	//Za�adowanie wierzcho�k�w do tablicy wierzcho�k�w
	array_vertex.push_back(ver1);
	array_vertex.push_back(ver2);
	array_vertex.push_back(ver3);

	//Ustawienie koloru t�a
	Blue_hex_00002d.set(0,0,45);

	//Ustawienie kolor�w tr�jk�ta g��wnego
	Blue_hex_4b2dff.set(75, 45, 255);

	//Ustawienie kolor�w pozosta�ych nowo utworzonych tr�jk�t�w
	Red_hex_ff0f55.set(255, 15, 85);

	//Wywo�anie metody rekurencyjnej do wyliczania nowych wierzcho�k�w dla kolejnych tr�jk�t�w
	CalculateVertex(array_vertex, ver1, ver2, ver3, deep);

	//Obliczenia �rodk� dla ka�dego tr�jk�ta
	for (int i = 0; i < array_vertex.size(); i += 3)
	{
		center_triangle_x.push_back((array_vertex[i].x + array_vertex[i+1].x + array_vertex[i+2].x) / 3);
		center_triangle_y.push_back((array_vertex[i].y + array_vertex[i+1].y + array_vertex[i+2].y) / 3);
	}

}

//--------------------------------------------------------------
void ofApp::update(){
	//Licznik czasu
	time_animation = clock() / CLOCKS_PER_SEC - 15;

	//Obliczanie wsp�czynnik�w skalowania
	if (time_animation >= 5* counter_param_scale)
	{
		if (counter_param_scale <= scale_parameters.size())
		{
			scale_parameters[counter_param_scale - 1] += 0.015f;
			if (scale_parameters[counter_param_scale - 1] >= 1.f)
			{
				scale_parameters[counter_param_scale - 1] = 1.f;
				counter_param_scale++;
			}
		}
	}

	//Gdy od uruchomienia animacji potrwa 60 sekund zamknij aplikacje
	if (time_animation >= 60)
	{
		ofExit();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){

	// Ustaw t�o
	ofSetBackgroundColor(Blue_hex_00002d);
	
	//Ustaw uk�ad wsp�rz�dnych na �rodku ekranu
	ofTranslate(ofGetWidth()/2, ofGetHeight()/2+85);

	//Sterowanie animacj� (Translacja do �rodka tr�jk�ta tam i z powrotem + skalowanie od 0 do 1 we wszystkich osiach)
	//Tr�jk�t bazowy - stopie� 0
	ofPushMatrix();
	ofTranslate(center_triangle_x[0], center_triangle_y[0]);
	ofScale(scale_parameters[0]);
	ofTranslate(-center_triangle_x[0], -center_triangle_y[0]);

	ofSetColor(Red_hex_ff0f55);
	ofDrawTriangle(array_vertex[0], array_vertex[1], array_vertex[2]);
	ofPopMatrix();
	
	//Pierwszy tr�jk�t - stopie� 1
	ofPushMatrix();
	ofTranslate(center_triangle_x[1], center_triangle_y[1]);
	ofScale(scale_parameters[1]);
	ofTranslate(-center_triangle_x[1], -center_triangle_y[1]);

	ofSetColor(Blue_hex_4b2dff);
	ofDrawTriangle(array_vertex[3], array_vertex[4], array_vertex[5]);
	ofPopMatrix();

	//Trzy tr�jk�ty - stopie� 2
	for(int i=0; i<=2; i++)
	{
		ofPushMatrix();
		ofTranslate(center_triangle_x[2 + 13 * i], center_triangle_y[2 + 13 * i]);
		ofScale(scale_parameters[2]);
		ofTranslate(-center_triangle_x[2 + 13 * i], -center_triangle_y[2 + 13 * i]);

		ofSetColor(Blue_hex_4b2dff);
		ofDrawTriangle(array_vertex[6 + 39 * i], array_vertex[7 + 39 * i], array_vertex[8 + 39 * i]);
		ofPopMatrix();
	}

	//Dzi�wi�c tr�jk�t�w - stopie� 3
	for (int i = 0; i <= 8; i++)
	{
		ofPushMatrix();
		if(i >= 3 and i < 6) ofTranslate(center_triangle_x[(3 + 4 * i) + 1], center_triangle_y[(3 + 4 * i) + 1]);
		else if (i >= 6) ofTranslate(center_triangle_x[(3 + 4 * i) + 2], center_triangle_y[(3 + 4 * i) + 2]);
		else ofTranslate(center_triangle_x[(3 + 4 * i)], center_triangle_y[(3 + 4 * i)]);
		ofScale(scale_parameters[3]);
		if (i >= 3 and i < 6) ofTranslate(-center_triangle_x[(3 + 4 * i) + 1], -center_triangle_y[(3 + 4 * i) + 1]);
		else if (i >= 6) ofTranslate(-center_triangle_x[(3 + 4 * i) + 2], -center_triangle_y[(3 + 4 * i) + 2]);
		else ofTranslate(-center_triangle_x[(3 + 4 * i)], -center_triangle_y[(3 + 4 * i)]);

		ofSetColor(Blue_hex_4b2dff);
		if (i >= 3 and i < 6) ofDrawTriangle(array_vertex[(9 + 12 * i) + 3], array_vertex[(10 + 12 * i) + 3], array_vertex[(11 + 12 * i) + 3]);
		else if (i >= 6) ofDrawTriangle(array_vertex[(9 + 12 * i) + 6], array_vertex[(10 + 12 * i) + 6], array_vertex[(11 + 12 * i) + 6]);
		else ofDrawTriangle(array_vertex[9 + 12 * i], array_vertex[10 + 12 * i], array_vertex[11 + 12 * i]);
		ofPopMatrix();
	}

	//Dwadzie�cia siedem tr�jk�t�w - stopie� 4
	for (int i = 0; i <= 26; i++)
	{
		ofPushMatrix();
		if (i >= 3 and i < 6) ofTranslate(center_triangle_x[(4 + 1 * i) + 1], center_triangle_y[(4 + 1 * i) + 1]);
		else if (i >= 6 and i < 9) ofTranslate(center_triangle_x[(4 + 1 * i) + 2], center_triangle_y[(4 + 1 * i) + 2]);
		else if (i >= 9 and i < 12) ofTranslate(center_triangle_x[(4 + 1 * i) + 4], center_triangle_y[(4 + 1 * i) + 4]);
		else if (i >= 12 and i < 15) ofTranslate(center_triangle_x[(4 + 1 * i) + 5], center_triangle_y[(4 + 1 * i) + 5]);
		else if (i >= 15 and i < 18) ofTranslate(center_triangle_x[(4 + 1 * i) + 6], center_triangle_y[(4 + 1 * i) + 6]);
		else if (i >= 18 and i < 21) ofTranslate(center_triangle_x[(4 + 1 * i) + 8], center_triangle_y[(4 + 1 * i) + 8]);
		else if (i >= 21 and i < 24) ofTranslate(center_triangle_x[(4 + 1 * i) + 9], center_triangle_y[(4 + 1 * i) + 9]);
		else if (i >= 24) ofTranslate(center_triangle_x[(4 + 1 * i) + 10], center_triangle_y[(4 + 1 * i) + 10]);
		else ofTranslate(center_triangle_x[4 + 1 * i], center_triangle_y[4 + 1 * i]);
		ofScale(scale_parameters[4]);
		if (i >= 3 and i < 6) ofTranslate(-center_triangle_x[(4 + 1 * i) + 1], -center_triangle_y[(4 + 1 * i) + 1]);
		else if (i >= 6 and i < 9) ofTranslate(-center_triangle_x[(4 + 1 * i) + 2], -center_triangle_y[(4 + 1 * i) + 2]);
		else if (i >= 9 and i < 12) ofTranslate(-center_triangle_x[(4 + 1 * i) + 4], -center_triangle_y[(4 + 1 * i) + 4]);
		else if (i >= 12 and i < 15) ofTranslate(-center_triangle_x[(4 + 1 * i) + 5], -center_triangle_y[(4 + 1 * i) + 5]);
		else if (i >= 15 and i < 18) ofTranslate(-center_triangle_x[(4 + 1 * i) + 6], -center_triangle_y[(4 + 1 * i) + 6]);
		else if (i >= 18 and i < 21) ofTranslate(-center_triangle_x[(4 + 1 * i) + 8], -center_triangle_y[(4 + 1 * i) + 8]);
		else if (i >= 21 and i < 24) ofTranslate(-center_triangle_x[(4 + 1 * i) + 9], -center_triangle_y[(4 + 1 * i) + 9]);
		else if (i >= 24) ofTranslate(-center_triangle_x[(4 + 1 * i) + 10], -center_triangle_y[(4 + 1 * i) + 10]);
		else ofTranslate(-center_triangle_x[4 + 1 * i], -center_triangle_y[4 + 1 * i]);
		
		ofSetColor(Blue_hex_4b2dff);
		if (i >= 3 and i < 6) ofDrawTriangle(array_vertex[(12 + 3 * i) + 3], array_vertex[(13 + 3 * i) + 3], array_vertex[(14 + 3 * i) + 3]);
		else if (i >= 6 and i < 9) ofDrawTriangle(array_vertex[(12 + 3 * i) + 6], array_vertex[(13 + 3 * i) + 6], array_vertex[(14 + 3 * i) + 6]);
		else if (i >= 9 and i < 12) ofDrawTriangle(array_vertex[(12 + 3 * i) + 12], array_vertex[(13 + 3 * i) + 12], array_vertex[(14 + 3 * i) + 12]);
		else if (i >= 12 and i < 15) ofDrawTriangle(array_vertex[(12 + 3 * i) + 15], array_vertex[(13 + 3 * i) + 15], array_vertex[(14 + 3 * i) + 15]);
		else if (i >= 15 and i < 18) ofDrawTriangle(array_vertex[(12 + 3 * i) + 18], array_vertex[(13 + 3 * i) + 18], array_vertex[(14 + 3 * i) + 18]);
		else if (i >= 18 and i < 21) ofDrawTriangle(array_vertex[(12 + 3 * i) + 24], array_vertex[(13 + 3 * i) + 24], array_vertex[(14 + 3 * i) + 24]);
		else if (i >= 21 and i < 24) ofDrawTriangle(array_vertex[(12 + 3 * i) + 27], array_vertex[(13 + 3 * i) + 27], array_vertex[(14 + 3 * i) + 27]);
		else if (i >= 24) ofDrawTriangle(array_vertex[(12 + 3 * i) + 30], array_vertex[(13 + 3 * i) + 30], array_vertex[(14 + 3 * i) + 30]);
		else ofDrawTriangle(array_vertex[12 + 3 * i], array_vertex[13 + 3 * i], array_vertex[14 + 3 * i]);
		ofPopMatrix();
	}
	/*
	//Narysuj tr�jk�ty - do renderu
	for (int i = 0; i < array_vertex.size(); i+=3)
	{
		if(i<=0) ofSetColor(Red_hex_ff0f55);
		else ofSetColor(Blue_hex_4b2dff);
		ofDrawTriangle(array_vertex[i], array_vertex[i+1], array_vertex[i+2]);
	}
	*/
	
}

void ofApp::CalculateVertex(vector<ofVec2f>& array_vertex, ofVec2f ver1, ofVec2f ver2, ofVec2f ver3, int deep) {
	
	//Je�eli stopien podanego fraktala jest wi�kszy ni� zero
	if (deep > 0)
	{ 
		//stw�rz nowe wektory wierzcho�k�w
		ofVec2f ver1p;
		ofVec2f ver2p;
		ofVec2f ver3p;

		//oblicz nowe wierzcho�ki na bazie wyznaczonych �rodk�w bok�w poprzednich tr�jk�t�w
		ver1p.set((ver1.x + ver2.x) / 2, (ver1.y + ver2.y) / 2);
		ver2p.set((ver2.x + ver3.x) / 2, (ver2.y + ver3.y) / 2);
		ver3p.set((ver3.x + ver1.x) / 2, (ver3.y + ver1.y) / 2);

		//Dodaj nowe wierzcho�ki do tabeli
		array_vertex.push_back(ver1p);
		array_vertex.push_back(ver2p);
		array_vertex.push_back(ver3p);

		//Wywo�aj kolejne razy metode z nowym zestawem danych
		CalculateVertex(array_vertex, ver1, ver1p, ver3p, deep - 1);
		CalculateVertex(array_vertex, ver1p, ver2, ver2p, deep - 1);
		CalculateVertex(array_vertex, ver2p, ver3p, ver3, deep - 1);
	}
}

