// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//FLogCategory 자료형의 구조체가 있을거라고 선언한다. 명칭은 FAKEOW2 문자열이 붙은 형태다.
DECLARE_LOG_CATEGORY_EXTERN(FAKEOW2, Log, All);

//Unreal Output Log에 어느 라인에서 호출 되었는지 찍어보는 함수.
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

//Unreal Output Log에 어느 라인에서 호출 되었는지 찍어보는 함수, Warning 생략
#define PRINT_CALLINFO() UE_LOG(FAKEOW2, Warning, TEXT("%s"), *CALLINFO)

//Unreal Output Log에 가변인자 형태로 찍어보는 함수. \는 개행.
#define PRINT_LOG(fmt, ...) UE_LOG(FAKEOW2, Warning, TEXT("%s %s"), *CALLINFO, \
*FString::Printf(fmt, ##__VA_ARGS__))