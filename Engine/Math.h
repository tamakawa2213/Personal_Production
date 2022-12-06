#pragma once
#include "Fbx.h"
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

namespace Math
{
	float Det(XMFLOAT3 a, XMFLOAT3 b, XMFLOAT3 c);

	//�����ƃ|���S���̓����蔻����s���֐�
	//������ : �����̎n�_�@������ : �����̏I�_�@��O�`��܈��� : �|���S���̊e���_
	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	bool SegmentToPlane(XMFLOAT3 segstart, XMFLOAT3 segend, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist);

	//�x�N�g���ƃ|���S���̓����蔻����s���֐�
	//������ : �x�N�g���̎n�_�@������ : �x�N�g���̌����@��O�`��܈��� : �|���S���̊e���_
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2);

	//�������Ԃ������蔻��
	bool Intersect(XMFLOAT3 start, XMFLOAT3 dir, XMFLOAT3 v0, XMFLOAT3 v1, XMFLOAT3 v2, float* dist);

	//�������擾����֐�
	//������ : �Ώۂ̒l ������ : ���߂�ŏ��̌� ��O���� : ���߂�ő�̌�
	//���� : �ꌅ�ڂ�0, �񌅖ڂ�1�Ƃ����悤�Ɏw�肵�Ȃ���΂Ȃ�Ȃ�
	//�߂�l : �؂蔲�����l
	int GetDigits(int value, int m, int n);

	//�f���𐶐�������֐�
	//���� : �����������
	//���� : �����Ɏw�肷��l��1�ȏ�ɂ���
	//�߂�l : �������ꂽ�f���̓��I�z��
	std::vector<int> MakePrime(int article);
};