#pragma once

/// <summary>
/// DirectX���Ɉˑ����Ȃ�Time
/// </summary>
namespace Time
{
	//������(Main�ŏ�����)
	void Initialize(int FPS);

	//�X�V(Main�ŌĂяo��)
	void Update();

	void Reset();

	void Lock();

	void UnLock();

	//�Ăяo�����_�̎��Ԃ��擾
	int GetTimei();
	float GetTimef();
	double GetTimew();
};

