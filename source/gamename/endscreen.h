// COMP710 GP Framework 2022
#ifndef __ENDSCREEN_H__
#define __ENDSCREEN_H__

// Local includes:

// Forward declarations:
class Renderer;
class InputSystem;
class Sprite;

// Class declaration:
class EndScreen
{
	// Member methods:
public:
	EndScreen();
	~EndScreen();
	bool Initialise(Renderer& renderer);
	void DebugDraw();
	void Draw(Renderer& renderer);

	void SetScore(int score);
	void SetScorePercentage(float scorePercentage);
protected:
private:
	EndScreen(const EndScreen& endScreen);
	EndScreen& operator=(const EndScreen& endScreen);
	// Member data:
public:
protected:
private:
	Renderer* m_pRenderer;

	Sprite* m_pEndScreen;
	Sprite* m_pWinText;
	Sprite* m_pLoseText;

	int m_iScore;
	float m_fScorePercentage;
};
#endif // __CURSOR_H__