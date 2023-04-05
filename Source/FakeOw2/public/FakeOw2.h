// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

//FLogCategory �ڷ����� ����ü�� �����Ŷ�� �����Ѵ�. ��Ī�� FAKEOW2 ���ڿ��� ���� ���´�.
DECLARE_LOG_CATEGORY_EXTERN(FAKEOW2, Log, All);

//Unreal Output Log�� ��� ���ο��� ȣ�� �Ǿ����� ���� �Լ�.
#define CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

//Unreal Output Log�� ��� ���ο��� ȣ�� �Ǿ����� ���� �Լ�, Warning ����
#define PRINT_CALLINFO() UE_LOG(FAKEOW2, Warning, TEXT("%s"), *CALLINFO)

//Unreal Output Log�� �������� ���·� ���� �Լ�. \�� ����.
#define PRINT_LOG(fmt, ...) UE_LOG(FAKEOW2, Warning, TEXT("%s %s"), *CALLINFO, \
*FString::Printf(fmt, ##__VA_ARGS__))