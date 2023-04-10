// Copyright Epic Games, Inc. All Rights Reserved.

#include "FakeOw2Character.h"
#include "FakeOw2Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//////////////////////////////////////////////////////////////////////////
// AFakeOw2Character

void AFakeOw2Character::Turn(float value)
{
	//Pawn의 함수
	AddControllerYawInput(value);

	bUseControllerRotationYaw = true;
	
	//2단 점프
	//JumpMaxCount = 2;
}

void AFakeOw2Character::LookUp(float value)
{
	//Pawn의 함수
	AddControllerPitchInput(value);
}

void AFakeOw2Character::InputHorizontal(float value)
{
	Direction.Y = value;
}

void AFakeOw2Character::InputVertical(float value)
{
	Direction.X = value;
}

void AFakeOw2Character::InputJump()
{
	Jump();
}

void AFakeOw2Character::Move()
{
	Direction = FTransform(GetControlRotation()).TransformVector(Direction);

	AddMovementInput(Direction);
	Direction = FVector::ZeroVector;
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
}

void AFakeOw2Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AFakeOw2Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UInputComponent* EnhancedInputComponent = CastChecked<UInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAxis(TEXT("Turn"), this, &AFakeOw2Character::Turn);
		EnhancedInputComponent->BindAxis(TEXT("LookUp"), this, &AFakeOw2Character::LookUp);
		EnhancedInputComponent->BindAxis(TEXT("MoveRight"), this, &AFakeOw2Character::InputHorizontal);
		EnhancedInputComponent->BindAxis(TEXT("MoveForward"), this, &AFakeOw2Character::InputVertical);

		EnhancedInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AFakeOw2Character::InputJump);
	}
}

void AFakeOw2Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move();
}


void AFakeOw2Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFakeOw2Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
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