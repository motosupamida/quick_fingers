#pragma once

#include "QuickFingersCore.h"

class TaskCore
{
public:
	TaskCore(
		sf::RenderWindow* window, 
		const TextParameter textParameter, 
		const TextGenerator::Language language, 
		const TextGenerator::GenerationType generationType);
private:
	sf::RenderWindow* m_window;
	sf::Clock m_timer;
	float m_deltaTime;
	float m_elapsedTime;
	bool m_stop;
	KeyboardVisualizer m_visualizer;
	TextField m_taskText;
	TextField m_timerText;
	TextField m_accuracyText;
	TextField m_velocityText;
};

