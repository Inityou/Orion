// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCPP.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterCPP::ACharacterCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// устанавлваем размер капсуле
	GetCapsuleComponent()->InitCapsuleSize(42.0f,96.0f);

	// Крч тонкости камеры (посмотрим возможно уберу)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Настраиваем Spring arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	// Настраиваем Spring arm
	CameraBoom1 = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom1"));
	CameraBoom1->SetupAttachment(RootComponent);


	// Настраиваем камеру
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	FollowCamera-> FieldOfView = 120;

	// Настраиваем камеру от 1 лица
	FollowCamera1 = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera1"));
	FollowCamera1->SetupAttachment(CameraBoom1, USpringArmComponent::SocketName);

	// ДВижение персонажа
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 640.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 750.0f;
}



// Called when the game starts or when spawned
void ACharacterCPP::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACharacterCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Управление мышкой
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// Биндим прыжок
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacterCPP::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterCPP::StopJumping);
	//Биндим движение по оси XY
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterCPP::MoveX);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterCPP::MoveY);
	// Биндим UI элементы
	PlayerInputComponent->BindAction("UI", IE_Pressed, this, &ACharacterCPP::UI_Camera);
}
void ACharacterCPP::MoveY(float Axis){
	if ((Controller != NULL) &&(Axis != 0.0f)) {
		//Получаем угл направление камеры
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);
	}
}

void ACharacterCPP::MoveX(float Axis)
{
	if ((Controller != NULL) && (Axis != 0.0f)) {
		//Получаем угл направление камеры
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Axis);

	}
}

void ACharacterCPP::Jump()
{
	if (Controller != NULL) {
		ACharacter::Jump();
	}
}

void ACharacterCPP::StopJumping()
{
	if (Controller != NULL) {
		ACharacter::StopJumping();
	}
}

void ACharacterCPP::UI_Camera()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("This is an on screen message!"));
}
