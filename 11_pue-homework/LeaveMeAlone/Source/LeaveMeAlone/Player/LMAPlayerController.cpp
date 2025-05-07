// LeaveMeAlone Game by Netology. All Rights Reserved.


#include "LMAPlayerController.h"

ALMAPlayerController::ALMAPlayerController() {

}

void ALMAPlayerController::BeginPlay() {
  Super::BeginPlay();

  SetInputMode(FInputModeGameOnly());
  bShowMouseCursor = false; 
}