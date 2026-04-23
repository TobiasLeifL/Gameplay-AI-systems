#pragma once

enum AI_Director_State
{
	Balance,
	IncreasePredator,
	DecreasePredator
};

class AI_Director
{
	public:
		AI_Director();
		~AI_Director();

		void Update(float aTimeDelta);
	private:
		AI_Director_State myState;
		unsigned int myCountedPrey;
		unsigned int myCountedPredators;

		unsigned int myLastEvaluationPrey;
		unsigned int myLastEvaluationPredator;

		int myPreyDiff;
		int myPredatorDiff;

		float myCountTimer;
		float myStateEvaluationTimer;
		float myPreyRespawnTimer;
		float myPreyRespawnCooldown;

		void HandleIMGUI();
		void CountUnits();
		void EvaluateState();
};

