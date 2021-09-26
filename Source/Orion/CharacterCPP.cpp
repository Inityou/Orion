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
	// ������������ ������ �������
	GetCapsuleComponent()->InitCapsuleSize(42.0f,96.0f);

	// ��� �������� ������ (��������� �������� �����)
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// ����������� Spring arm
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;

	// ����������� ������
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	// �������� ���������
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 80.0f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 700.0f;
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

	//���������� ������
	PlayerInputComponent->BindAxis("Turn",this,&APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	// ������ ������
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &ACharacterCPP::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacterCPP::StopJumping);
	//������ �������� �� ��� XY
	PlayerInputComponent->BindAxis("MoveForward", this, &ACharacterCPP::MoveX);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacterCPP::MoveY);
}
void ACharacterCPP::MoveY(float Axis){
	if ((Controller != NULL) &&(Axis != 0.0f)) {
		//�������� ��� ����������� ������
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Axis);

	}
}

void ACharacterCPP::MoveX(float Axis)
{
	if ((Controller != NULL) && (Axis != 0.0f)) {
		//�������� ��� ����������� ������
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
