// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/ZPUserWidget.h"

void UZPUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	OnWidgetControllerSet();
}
