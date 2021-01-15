#include "progressSystem.hpp"
#include "iostream"
void famm::ProgressSystem::assignProgress()
{
	int index = 0;

	for (auto& entity: entitiesSet)
	{
		memo[index] = entity;
		index++;
	}
}

void famm::ProgressSystem::updateProgress(ECSManager* myManager, int& progressNumber)
{
	auto& it = memo.find(progressNumber);
	if (it == memo.end()) return;
	auto& myProgressComponent = myManager->getComponentData<Progress>(it->second);
	myProgressComponent.counter++;
	if (myProgressComponent.counter == myProgressComponent.goal)
	{

		myManager->destroyEntity(it->second);
		memo.erase(progressNumber);
		progressNumber = -1;
		
		if (memo.size() == 0)
		{
			progressFinished = true;
		}
	}
}

bool famm::ProgressSystem::isNumberExist(int progressNumber)
{
	auto& it = memo.find(progressNumber);
	return it != memo.end();
}