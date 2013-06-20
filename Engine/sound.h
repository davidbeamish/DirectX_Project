///////////////////////////////////////////////////////////////////////////////
// Filename: sound.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut14.html
///////////////////////////////////////////////////////////////////////////////
#ifndef SOUND_H_
#define SOUND_H_

/////////////
// LINKING //
/////////////
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")
 
 
//////////////
// INCLUDES //
//////////////
#include <dsound.h>
 
 
///////////////////////////////////////////////////////////////////////////////
//  name: Sound
///////////////////////////////////////////////////////////////////////////////
class Sound
{
private:

	// Uses .wav file format.
	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};
 
public:
	Sound();
	Sound(const Sound&);
	~Sound();

	bool Initialize(HWND);
	void Shutdown();
 
private:
	bool InitializeDirectSound(HWND);
	void ShutdownDirectSound();
 
	bool LoadWaveFile(char*, IDirectSoundBuffer8**);
	void ShutdownWaveFile(IDirectSoundBuffer8**);
 
	bool PlayWaveFile();
 
private:
	IDirectSound8* m_DirectSound;
	IDirectSoundBuffer* m_primaryBuffer;
	IDirectSoundBuffer8* m_secondaryBuffer1;
};
 
#endif //SOUND_H_
