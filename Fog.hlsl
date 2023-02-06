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
	float4		diffuseColor;	//�f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		chroma;			//Red, Green, Blue, Alpha
	float4		light;			//���̃x�N�g��
	bool		isTexture;		//�e�N�X�`���\���Ă��邩�ǂ���
	float		bright;			//�|���S���̖��邳
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos	: SV_POSITION;	//�ʒu
	float4 posw : POSITION0;
	float2 uv	: TEXCOORD;		//UV���W
	float4 normal: COLOR;		//�F�i���邳�j
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
	outData.posw = mul(pos, matNormal);
	outData.uv = uv;

	//�@���Ƀ��[���h�s����|���ĉ�]
	outData.normal = mul(normal, matNormal);

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	float4 diffuse;

	float4 Light = light - inData.posw;
	Light.a = 0;
	float len = length(Light);
	Light = normalize(Light);
	float trans = abs(saturate((len - 30) / 50) - 1);
	float4 Color = saturate(dot(normalize(inData.normal), Light));
	float4 backGround = saturate(float4(0.0f, 0.5f, 0.5f, 1.0f));
	float Bright_ = (bright / 255.0f);
	Color.a = 1.0f;

	float4 ambient = g_texture.Sample(g_sampler, inData.uv) * float4(Bright_, Bright_, Bright_, 1);

	if (isTexture)
	{
		diffuse = chroma * g_texture.Sample(g_sampler, inData.uv) * Color;
		return (chroma * (diffuse + ambient) * trans) + (backGround * (1 - trans));
	}
	else
	{
		return (chroma * diffuseColor * Color * trans) + (backGround * (1 - trans));
	}
}
//Illegal character in shader file �̃G���[���o����g�p�s�̑S�p���g�p����Ă���