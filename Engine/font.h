////////////////////////////////////////////////////////////////////////////////
// Filename: font.h
// Code Adapted from tutorial http://www.rastertek.com/dx11tut12.html
////////////////////////////////////////////////////////////////////////////////
#ifndef _FONT_H_
#define _FONT_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <fstream>
using namespace std;


///////////////////////
// MY  INCLUDES //
///////////////////////
class Texture;



////////////////////////////////////////////////////////////////////////////////
//  name: Font
////////////////////////////////////////////////////////////////////////////////
class Font
{
private:

	struct FontType
	{
		float left, right;
		int size;
	};

struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Font();
	Font(const Font&);
	~Font();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

void BuildVertexArray(void*, char*, float, float);

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	Texture* m_Texture;
};

#endif