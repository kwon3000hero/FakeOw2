// Copyright Epic Games, Inc. All Rights Reserved.

#include "FakeOw2Character.h"
#include "FakeOw2Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyInputConfigData.h"
#include "FakeOw2.h"

//////////////////////////////////////////////////////////////////////////
// AFakeOw2Character

void AFakeOw2Character::InputJump()
{
	Jump();
}

AFakeOw2Character::AFakeOw2Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	//스켈레탈메시를 불러온다.
	ConstructorHelpers::FObjectFinder<USkeletalMesh> TempMesh(
		TEXT("Script / Engine.SkeletalMesh'/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms'")
	);

	if (TempMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(TempMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, 0, 0));
		Mesh1P = GetMesh();
	}

	fpsCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("fpsCameraComponent"));
	fpsCameraComponent->SetupAttachment(RootComponent);
	fpsCameraComponent->SetRelativeLocation(FVector(-10, 0, 60));
	fpsCameraComponent->bUsePawnControlRotation = true;	

	//	bUseControllerRotationYaw = true;
	//
	//	//2단 점프
	//	//JumpMaxCount = 2;
}

void AFakeOw2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

}

//////////////////////////////////////////////////////////////////////////// Input

void AFakeOw2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Get the local player subsystem
	APlayerController* PC = Cast<APlayerController>(GetController());

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	// Clear out existing mapping, and add our mapping
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMoveMapping, 0);
	Subsystem->AddMappingContext(InputActionMapping, 1);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComponent->BindAction(InputConfigData->InputMove, ETriggerEvent::Triggered, this, &AFakeOw2Character::Move);
	EnhancedInputComponent->BindAction(InputConfigData->InputLook, ETriggerEvent::Triggered, this, &AFakeOw2Character::Look);
}

void AFakeOw2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AFakeOw2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator MovementRotation(0, Controller->GetControlRotation().Yaw, 0);

	// Forward/Backward direction
	if (MovementVector.Y != 0.f)
	{
		// Get forward vector
		const FVector Direction = MovementRotation.RotateVector(FVector::ForwardVector);

		AddMovementInput(Direction, MovementVector.Y);
	}
	if (MovementVector.X != 0.f)
	{
		// Get forward vector
		const FVector Direction = MovementRotation.RotateVector(FVector::RightVector);

		AddMovementInput(Direction, MovementVector.X);
	}
}

void AFakeOw2Character::Look(const FInputActionValue& Value)
{
	if (Controller != nullptr)
	{
		// input is a Vector2D
		FVector2D LookAxisVector = Value.Get<FVector2D>();

		// add yaw and pitch input to controller
		AddControllerYawInput(-LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFakeOw2Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AFakeOw2Character::GetHasRifle()
{
	return bHasRifle;
}