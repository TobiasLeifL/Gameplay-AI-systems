#include "AI_Director.h"
#include "SingeltonHandler.h"

AI_Director::AI_Director()
	: myCountTimer(0),
	myCountedPrey(0),
	myCountedPredators(0),
	myStateEvaluationTimer(0),
	myPreyRespawnTimer(0),
	myPreyRespawnCooldown(10),
	myPreyDiff(0),
	myPredatorDiff(0),
	myLastEvaluationPredator(0),
	myLastEvaluationPrey(0)
{
}

AI_Director::~AI_Director()
{
}

void AI_Director::Update(float aTimeDelta)
{
	constexpr float TIMER_INTERVAL = 1.0f;
	constexpr float TIMER_EVALUATION = 5.0f;

	myCountTimer = myCountTimer + aTimeDelta;
	myStateEvaluationTimer = myStateEvaluationTimer + aTimeDelta;
	myPreyRespawnTimer = myPreyRespawnTimer + aTimeDelta;

	if (myCountTimer > TIMER_INTERVAL)
	{
		CountUnits();
		myCountTimer = 0;
	}
	if (myStateEvaluationTimer > TIMER_EVALUATION)
	{
		EvaluateState();
		myStateEvaluationTimer = 0;
	}

	if (myPreyRespawnTimer > myPreyRespawnCooldown)
	{
		GameWorld& gameWorld = SingeltonHandler::GetInstance().GetGameWorld();
		gameWorld.SpawnObject(gameWorld.GetRandomPositionOnScreen(), GameObject_Tag::Tag_Prey, "Hare", Controller_Tag::Controller_UnTagged);
		myPreyRespawnTimer = 0;
	}
	HandleIMGUI();
}

void AI_Director::HandleIMGUI()
{
	ImGui::Begin("AI Director");
	std::string stateString;
	switch (myState)
	{
		case AI_Director_State::Balance:
		{
			stateString = "State: Balance";
		}
		break;

		case AI_Director_State::IncreasePredator:
		{
			stateString = "State: Increase Predator";
		}
		break;

		case AI_Director_State::DecreasePredator:
		{
			stateString = "State: Decrease Predator";
		}
		break;
	}
	ImGui::Text(stateString.c_str());

	ImGui::Text("Counted prey: %d", myCountedPrey);
	ImGui::Text("Counted predators: %d", myCountedPredators);
	ImGui::Text("Prey difference: %d", myPreyDiff);
	ImGui::Text("Predator difference: %d", myPredatorDiff);


	ImGui::Text("__Timers__");
	ImGui::Text(("Count Timer: " + std::to_string(1 - myCountTimer)).c_str());
	ImGui::Text(("Evaluation Timer: " + std::to_string(5 - myStateEvaluationTimer)).c_str());

	ImGui::Text(("Prey Respawn Timer: " + std::to_string(myPreyRespawnCooldown - myPreyRespawnTimer)).c_str());
	ImGui::Text(("Prey Respawn Cooldown: " + std::to_string(myPreyRespawnCooldown)).c_str());

	ImGui::End();
}

void AI_Director::CountUnits()
{
	GameWorld& gameWorld = SingeltonHandler::GetInstance().GetGameWorld();
	std::vector<std::shared_ptr<GameObject>>& objects = gameWorld.GetGameObjects();

	myCountedPrey = 0;
	myCountedPredators = 0;

	for (int i = 0;i < objects.size();i++)
	{
		GameObject* curObject = objects[i].get();
		if (curObject->GetTag() == GameObject_Tag::Tag_Prey)
		{
			myCountedPrey = myCountedPrey + 1;
		}
		else if (curObject->GetTag() == GameObject_Tag::Tag_Predator)
		{
			myCountedPredators = myCountedPredators + 1;
		}
	}

	myPreyRespawnCooldown = std::max(0.5f, 5.0f - (myCountedPrey * 0.1f));
}

void AI_Director::EvaluateState()
{
	GameWorld& gameWorld = SingeltonHandler::GetInstance().GetGameWorld();
	std::vector<std::shared_ptr<GameObject>>& objects = gameWorld.GetGameObjects();

	myPreyDiff = myCountedPrey - myLastEvaluationPrey;
	myPredatorDiff = myCountedPredators - myLastEvaluationPredator;

	//We do increase / decrease at the end of the evaulation phase.
	if (myState == AI_Director_State::IncreasePredator)
	{
		gameWorld.SpawnObject(gameWorld.GetRandomPositionOnScreen(), GameObject_Tag::Tag_Predator, "Lynx", Controller_Tag::Controller_UnTagged);
	}
	else if (myState == AI_Director_State::DecreasePredator)
	{
		for (int i = 0;i < objects.size();i++)
		{
			if (objects[i]->GetTag() == GameObject_Tag::Tag_Predator)
			{
				std::shared_ptr<Actor> actor = std::static_pointer_cast<Actor>(objects[i]);
				actor->Kill();
				break;
			}
		}
	}

	constexpr int PREY_SCALING_FACTOR = 7;

	const unsigned int preyPoints = myCountedPrey / PREY_SCALING_FACTOR;
	const unsigned int predatorPoints = myCountedPredators;

	if (preyPoints > predatorPoints && myPreyDiff > 0)
	{
		myState = AI_Director_State::IncreasePredator;
	}
	else if (predatorPoints > preyPoints && myPreyDiff < 0)
	{
		myState = AI_Director_State::DecreasePredator;
	}
	else
	{
		myState = AI_Director_State::Balance;
	}


	myLastEvaluationPrey = myCountedPrey;
	myLastEvaluationPredator = myCountedPredators;

}

