// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGameUI.h"

#include "SaveSlot.h"

void ULoadGameUI::LoadSaveSlots()
{
	SaveSlot1->InitializeSlot(SaveFileName + FString::FromInt(1));

	SaveSlot2->InitializeSlot(SaveFileName + FString::FromInt(2));

	SaveSlot3->InitializeSlot(SaveFileName + FString::FromInt(3));
	
}
