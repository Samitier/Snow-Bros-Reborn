#include "cData.h"

cData::cData(void) {}
cData::~cData(void){}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w,h);
}

bool cData::LoadImage(int img, char *filename, int type)
{
	int res;

	res = texture[img].Load(filename,type);
	if(!res) return false;

	return true;
}

bool cData::LoadSound(int id, string filename)
{
	sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filename)) return false;
	else {
		audiofiles[id] = filename;
		return true;
	}
	return true;
}

void cData::PlaySound(int id) {
	sf::Sound sound;
    if(buffer.loadFromFile(audiofiles[id])){
		sound.setBuffer(buffer);
		sound.play();
	}
}