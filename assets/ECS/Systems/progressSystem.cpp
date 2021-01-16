#include "progressSystem.hpp"
#include "iostream"
void famm::ProgressSystem::assignProgress(ECSManager* myManager)
{
	int index = 0;

	for (auto& entity: entitiesSet)
	{
		auto& myProgressComponent = myManager->getComponentData<Progress>(entity);
		memo[index] = entity;
		
		for (auto& p2: myProgressComponent.attachedTo)
		{
			attachProgress(index, p2);
		}
		myProgressComponent.attachedTo.clear();

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
		advanceAttached(myManager, progressNumber);
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

void famm::ProgressSystem::attachProgress(const int& p1, const int& p2) {
	attachedProgress[p2] = p1;
}

void famm::ProgressSystem::advanceAttached(ECSManager* myManager, const int& p1)
{
	std::unordered_map<int, int>::iterator it = attachedProgress.find(p1);
	if (it != attachedProgress.end())
	{
		updateProgress(myManager, it->second);
		attachedProgress.erase(p1);
	}
}