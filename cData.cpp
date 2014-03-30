#include "cData.h"

cData::cData(void) {}
cData::~cData(void){}

void cData::init() {
	//init FMOD
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels
}

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

bool cData::LoadSound(int id, char *filename)
{
	//load sounds
	system->createSound(filename, FMOD_HARDWARE, 0, &sound[id]);
	sound[id]->setMode(FMOD_LOOP_OFF);    
	return true;
}

bool cData::LoadMusic(int id, char *filename)
{
	//load sounds
	system->createSound(filename, FMOD_HARDWARE, 0, &sound[id]);
	sound[id]->setMode(FMOD_LOOP_NORMAL);   
	return true;
}

void cData::PlaySound(int id) {
	system->playSound(sound[id], NULL, false, 0);
}

void cData::PlayMusic(int id) {
	system->playSound(sound[id], NULL, false, &channelMusic);
}

void cData::StopMusic() {
	channelMusic->stop();
}

void cData::PauseMusic() {
	bool p;
	channelMusic->getPaused(&p);
	channelMusic->setPaused(!p);
}

void cData::Update() {
		system->update(); //update FMOD, need to call this once per frame to keep the sound engine running
}

void cData::Release() {
	for(int i=0; i< NUM_AUDIO ;++i) {
		sound[i]->release();
	}
    system->close();
    system->release();
}