#pragma once
namespace nsK2EngineLow {

	class DirectionLight
	{
	public:
		//�f�B���N�V�������C�g�p�̍\���̂��`����B
		struct DirectionLightST {
			Vector3 ligDirection; //���C�g�̕���
			//HLSL���̒萔�o�b�t�@��float3�^�̕ϐ���16�̔{���̃A�h���X�ɔz�u����邽�߁AC++���ɂ̓p�f�B���O�𖄂߂Ă����B
			float pad;
			Vector3 ligColor;
			float pad1;
		};
		struct PointLightST
		{
			//���C�g�\���̂Ƀ|�C���g���C�g�p�̃����o�ϐ���ǉ�����
			Vector3 ptPosition;		//�ʒu�B
			float pad2;					//�p�f�B���O�B
			Vector3 ptColor;			//�J���[�B
			float ptRange;				//�e���͈́B
		};
		struct SpotLightST
		{
			//���C�g�\���̂ɃX�|�b�g���C�g�p�̃����o�ϐ���ǉ�����
			Vector3 spPosition;		//�ʒu�B
			float pad3;					//�p�f�B���O�B
			Vector3 spColor;			//�J���[�B
			float spRange;				//�e���͈́B
			Vector3 spDirection;	//�ˏo�����B
			float spAngle;				//�ˏo�p�x�B
		};
		struct AmbientLightST
		{
			Vector3 eyePos;         // ���_�̈ʒu
			float pad4;
			Vector3 ambientLight;   // �A���r�G���g���C�g
		};

		struct Light
		{
			DirectionLightST            m_directionLig;				//�f�B���N�V�������C�g�̃f�[�^���쐬����B
			PointLightST                m_pointLig;                 //�|�C���g���C�g�̃f�[�^���쐬����B
			SpotLightST					m_spotLig;					//�X�|�b�g���C�g�̃f�[�^���쐬����B
			AmbientLightST              m_ambientLig;               //�����̃f�[�^���쐬����B
		};

	public:
		DirectionLight() {};
		~DirectionLight();
		/// <summary>
		/// �X�V����
		/// </summary>
		void Update();
		void Init();
		/// <summary>
		/// �f�B���N�V�������C�g�̕�����ݒ�
		/// </summary>
		/// <param name="lig"></param>
		void SetLigDirection(const Vector3& lig)
		{
			m_light.m_directionLig.ligDirection = lig;
		}
		/// <summary>
		/// �f�B���N�V�������C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetLigColor(const Vector3& col)
		{
			m_light.m_directionLig.ligColor = col;
		}
		/// <summary>
		/// �|�C���g���C�g�̈ʒu��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointPos(const Vector3& pos)
		{
			m_light.m_pointLig.ptPosition = pos;
		}
		/// <summary>
		/// �|�C���g���C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetPointColor(const Vector3& col)
		{
			m_light.m_pointLig.ptColor = col;
		}
		/// <summary>
		/// �|�C���g���C�g�̎ˏo�͈͂�ݒ�
		/// </summary>
		/// <param name="range"></param>
		void SetSpotRange(const float& ptrange)
		{
			m_light.m_pointLig.ptRange = ptrange;
		}
		/// <summary>
		/// �X�|�b�g���C�g�̈ʒu��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetSpotPos(const Vector3& pos)
		{
			m_light.m_spotLig.spPosition = pos;
		}
		/// <summary>
		/// �X�|�b�g���C�g�̐F��ݒ�
		/// </summary>
		/// <param name="col"></param>
		void SetSpotColor(const Vector3& col)
		{
			m_light.m_spotLig.spColor = col;
		}
		/// <summary>
		/// �X�|�b�g���C�g�̎ˏo������ݒ�
		/// </summary>
		/// <param name="dil"></param>
		void SetSpotDir(const Vector3& dil)
		{
			m_light.m_spotLig.spDirection = dil;
		}

		/// <summary>
		/// �X�|�b�g���C�g�̎ˏo�p�x��ݒ�
		/// </summary>
		/// <param name="range"></param>
		/*
		void SetSpotAngle(const int& spangle)
		{
			m_light.m_spotLig.spAngle = Math::DegToRad(spangle);
		}*/
		Light& GetLight()
		{
			return m_light;
		}
	private:
		Light m_light;
	};

	//���̏ꏊ�ł��ǂݍ��߂�悤�ɃO���[�o���ɂ���B
	extern DirectionLight g_Lig;
}