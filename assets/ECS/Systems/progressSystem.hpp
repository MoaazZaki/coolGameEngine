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
        bool progressFinished = false;
    public:
        void assignProgress();
        void updateProgress(ECSManager* myManager, int &progressNumber);
        bool isProgressFinished() {return progressFinished;}
        bool isNumberExist(int progressNumber);
    };

}
#endif