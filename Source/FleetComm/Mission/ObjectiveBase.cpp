#include "ObjectiveBase.h"

void UObjectiveBase::NotifyEvent(FObjectiveData ObjData)
{
	if (ObjData.Tags.HasAll(RequiredTags))
	{
		ObjectiveCurrentProgress+=ObjData.Progress;
		UpdateUI();
		if (ObjectiveCurrentProgress >= ObjectiveRequiredProgress)
		{
			ObjectiveStateChanged(EObjectiveState::Succeeded);
		}
	}
}


void UObjectiveBase::ObjectiveStateChanged(EObjectiveState NewObjectiveState)
{
	CurrentState = NewObjectiveState;
	OnObjectiveStateChanged_Delegate.Broadcast(CurrentState);
}

void UObjectiveBase::StartObjective()
{
	//Create UI
}

void UObjectiveBase::UpdateUI()
{
	//Update UI
}

