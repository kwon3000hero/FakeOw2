// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TP_WeaponComponent.h"
#include "../../private/Base/BaseWeaponInterface.h"
#include "Soldier_WeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class FAKEOW2_API USoldier_WeaponComponent final: public UTP_WeaponComponent, public IBaseWeaponInterface
{
	GENERATED_BODY()

public:
	virtual void DoAttack() override;	
};
