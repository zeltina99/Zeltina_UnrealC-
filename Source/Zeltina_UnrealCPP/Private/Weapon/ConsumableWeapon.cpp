// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/ConsumableWeapon.h"

void AConsumableWeapon::OnAttack()
{
	CurrentUseCount--;
	if (CurrentUseCount <= 0)
	{
		OnWeaponUseEnded.Broadcast();
	}
}
