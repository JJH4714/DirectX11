#include "pch.h"
#include "CameraScript.h"

CameraScript::CameraScript()
{
}

CameraScript::~CameraScript()
{

}

void CameraScript::Start()
{

}

void CameraScript::Update()
{
	float dt = TIME->GetDeltaTime();

	// 04. CameraDemo 기준 로컬포지션으로 설정해도 됨(메인카메라는 월드좌표계 사용중이니까...)
	//Vec3 pos = GetTransform()->GetPosition();
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos -= GetTransform()->GetRigt() * _speed * dt;
	}
	if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos += GetTransform()->GetRigt() * _speed * dt;
	}
	if (INPUT->GetButton(KEY_TYPE::W))
	{
		pos += GetTransform()->GetLook() * _speed * dt;
	}
	if (INPUT->GetButton(KEY_TYPE::S))
	{
		pos -= GetTransform()->GetLook() * _speed * dt;
	}
	//GetTransform()->SetPosition(pos);
	GetTransform()->SetLocalPosition(pos);

	// 회전
	Vec3 rotation = GetTransform()->GetLocalRotation();
	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		rotation.x += dt * 0.5f;
	}
	if (INPUT->GetButton(KEY_TYPE::E))
	{
		rotation.x -= dt * 0.5f;
	}
	if (INPUT->GetButton(KEY_TYPE::Z))
	{
		rotation.y += dt * 0.5f;
	}
	if (INPUT->GetButton(KEY_TYPE::C))
	{
		rotation.y -= dt * 0.5f;
	}

	GetTransform()->SetLocalRotation(rotation);
}
