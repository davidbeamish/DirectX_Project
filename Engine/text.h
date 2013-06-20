////////////////////////////////////////////////////////////////////////////////
// Filename: text.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut12.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXT_H_
#define _TEXT_H_

///////////////////////
// MY  INCLUDES //
///////////////////////
#include "font.h"

///////////////////////
// FORWARD DECLARATIONS //
///////////////////////

class ShaderManager;
class FontShader;

////////////////////////////////////////////////////////////////////////////////
//  name: Text
////////////////////////////////////////////////////////////////////////////////
class Text
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Text();
	Text(const Text&);
	~Text();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, D3DXMATRIX baseViewMatrix);
	void Shutdown();
	bool Render(ID3D11DeviceContext* deviceContext, FontShader* m_FontShader, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);
	bool SetFps(int fps, ID3D11DeviceContext* deviceContext);
	bool SetCpuManager(int cpumanager, ID3D11DeviceContext* deviceContext);

	bool SetVideoCardInfo(char* videoCardName, int videoCardMemory, ID3D11DeviceContext* deviceContext);
	bool SetCameraPosition(float posX, float posY, float posZ, ID3D11DeviceContext* deviceContext);
	bool SetCameraRotation(float rotX, float rotY, float rotZ, ID3D11DeviceContext* deviceContext);
	bool SetMousePosition(int posX, int posY, bool collision, ID3D11DeviceContext* deviceContext);
	bool SetRenderCount(int count, ID3D11DeviceContext* deviceContext);

	bool InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device);
	bool UpdateSentence(SentenceType* sentence, char* text, int positionX, int positionY, float red, float green, float blue, ID3D11DeviceContext* deviceContext);
	void ReleaseSentence(SentenceType** sentence);

	//bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);
	bool RenderSentence(SentenceType* sentence, ID3D11DeviceContext* deviceContext, FontShader* FontShader, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);

private:
	

private:
	Font* m_Font;
	ShaderManager* m_ShaderManager;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;

	SentenceType *m_sentence1, *m_sentence2, *m_sentence3, *m_sentence4, *m_sentence5;
	SentenceType *m_sentence6, *m_sentence7, *m_sentence8, *m_sentence9, *m_sentence10, *m_sentence11, *m_sentence12, *m_sentence13, *m_sentence14;
};

#endif