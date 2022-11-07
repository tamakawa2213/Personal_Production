//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���` :�̌��ɂ�����̂̓Z�}���e�B�N�X�Ƃ���
//������������������������������������������������������������������������������
Texture2D	g_texture : register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
// �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	matWVP;			//���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	matNormal;		//�ړ��s������������[���h�s��
	float4		diffuseColor;	// �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	bool		isTexture;		// �e�N�X�`���\���Ă��邩�ǂ���
	float		bright;			//�|���S���̖��邳
	float		chromaR;		//R�̍ʓx
	float		chromaG;		//G�̍ʓx
	float		chromaB;		//B�̍ʓx
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos	: SV_POSITION;	//�ʒu
	float2 uv	: TEXCOORD;		//UV���W
	float4 color: COLOR;		//�F�i���邳�j
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 uv : TEXCOORD, float4 normal : NORMAL)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, matWVP);
	outData.uv = uv;

	//�@���Ƀ��[���h�s����|���ĉ�]
	normal = mul(normal, matNormal);

	float4 light = float4(1.0f, 1.0f, 1.0f, 0.0f);
	light = normalize(light);
	outData.color = clamp(dot(normal, light), 0, 1);

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 diffuse;

	float Bright_ = (float)(bright / 255);

	float4 ambient = g_texture.Sample(g_sampler, inData.uv) * float4(Bright_, Bright_, Bright_, 1);

	if (isTexture)
	{
		diffuse = float4(chromaR, chromaG, chromaB, 1) * g_texture.Sample(g_sampler, inData.uv) * inData.color;
	}
	else
	{
		diffuse = float4(chromaR, chromaG, chromaB, 1) * diffuseColor * inData.color;
		//return diffuseColor * inData.color;
	}
	return (diffuse + ambient);
}
//Illegal character in shader file �̃G���[���o����g�p�s�̑S�p���g�p����Ă���