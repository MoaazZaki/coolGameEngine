#ifndef PROGRESSSYSTEM_H
#define PROGRESSSYSTEM_H

#include <System.hpp>
#include "../Components/Components.hpp"
#include "../ECSManager.hpp"
#include "unordered_map"
namespace famm {

    class ProgressSystem : public System
    {
    private:
        std::unordered_map<int,Entity> memo;
        std::unordered_map<int, int> attachedProgress;
        bool progressFinished = false;
    public:
        void assignProgress(ECSManager* myManager);
        void updateProgress(ECSManager* myManager, int &progressNumber);
        bool isProgressFinished() {return progressFinished;}
        bool isNumberExist(int progressNumber);
        void attachProgress(const int& p1, const int& p2);
        void advanceAttached(ECSManager* myManager, const int& p1);

        int getEntity(int index)
        {
            auto& it = memo.find(index);
            if (it == memo.end()) return -1;

            return it->second;
        }
    };

}
#endif