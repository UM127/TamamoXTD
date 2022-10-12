#pragma once

namespace nsK2EngineLow {
	class ModelRender {
	public:
		ModelRender();
		~ModelRender();
		/// <summary>
		/// �������B�ʏ�͂��̊֐��ŏ��������Ă��������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		/// <param name="isShadowReciever">�V���h�E���V�[�o�[�t���Otrue�Ȃ�e��������B</param>
		/// <param name="maxInstance">
		/// �C���X�^���X�̍ő吔�B���̈������P���傫������ƃC���X�^���V���O�`�悪�s���܂��B
		/// �C���X�^���V���O�`����s���ۂ͕`�悵�����C���X�^���X�̐��������AUpdateInstancingDraw()���Ăяo���K�v������܂��B
		/// �C���X�^���V���O�`��̏ڍׂ�Smaple_XX���Q�Ƃ��Ă��������B
		/// </param>
		void Init(
			const char* filePath, bool shadow = false, AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		/// <summary>
		/// �V���h�E�̏������B
		/// </summary>
		/// <param name="filePath">�t�@�C���p�X�B</param>
		/// <param name="animationClips">�A�j���[�V�����N���b�v�B</param>
		/// <param name="numAnimationClips">�A�j���[�V�����N���b�v�̐��B</param>
		/// <param name="enModelUpAxis">���f���̏�����B</param>
		/// <param name="isShadowReciever">�V���h�E���V�[�o�[�t���Otrue�Ȃ�e��������B</param>
		/// <param name="maxInstance">
		/// �C���X�^���X�̍ő吔�B���̈������P���傫������ƃC���X�^���V���O�`�悪�s���܂��B
		/// �C���X�^���V���O�`����s���ۂ͕`�悵�����C���X�^���X�̐��������AUpdateInstancingDraw()���Ăяo���K�v������܂��B
		/// �C���X�^���V���O�`��̏ڍׂ�Smaple_XX���Q�Ƃ��Ă��������B
		/// </param>
		void ShadowInit(
			const char* filePath,
			bool shadow = false,
			AnimationClip* animationClips = nullptr,
			int numAnimationClips = 0,
			EnModelUpAxis enModelUpAxis = enModelUpAxisZ);
		/// <summary>
		/// �`�揈���B
		/// </summary>
		void Update();
		/// <summary>
		/// �`�揈���B
		/// </summary>
		void Draw(RenderContext& rc);

		/// <summary>
		/// ���f�����擾�B
		/// </summary>
		/// <returns>���f��</returns>
		Model& GetModel()
		{
			return m_model;
		}

		Model& GetShadowModel()
		{
			return m_ShadowModel;
		}


		/// <summary>
				/// ���W��ݒ�B
				/// </summary>
				/// <remark>
				/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
				/// </remark>
				/// <param name="pos">���W�B</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}
		/// <summary>
		/// ���W��ݒ�B
		/// </summary>
		/// <param name="x">x���W</param>
		/// <param name="y">y���W</param>
		/// <param name="z">z���W</param>
		void SetPosition(float x, float y, float z)
		{
			SetPosition({ x, y, z });
		}
		/// <summary>
		/// ��]��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="rotation">��]�B</param>
		void SetRotation(const Quaternion& rotation)
		{
			m_rotation = rotation;
		}
		/// <summary>
		/// �g�嗦��ݒ�B
		/// </summary>
		/// <remark>
		/// �C���X�^���V���O�`�悪�L���̏ꍇ�́A���̐ݒ�͖�������܂��B
		/// </remark>
		/// <param name="scale">�g�嗦�B</param>
		void SetScale(const Vector3& scale)
		{
			m_scale = scale;
		}
		void SetScale(float x, float y, float z)
		{
			SetScale({ x, y, z });
		}
		void SetShadowReciverBG()
		{
			m_ShadowRecieverBG = true;
		}
		/// <summary>
		/// �{�[���̖��O����{�[���ԍ��������B
		/// </summary>
		/// <param name="boneName">�{�[���̖��O</param>
		/// <returns>�{�[���ԍ��B������Ȃ������ꍇ��-1���Ԃ��Ă��܂��B</returns>
		int FindBoneID(const wchar_t* boneName) const
		{
			return m_skeleton.FindBoneID(boneName);
		}
		/// <summary>
		/// �{�[���ԍ�����{�[�����擾�B
		/// </summary>
		/// <param name="boneNo">�{�[���ԍ�</param>
		/// <returns>�{�[��</returns>
		Bone* GetBone(int boneNo) const
		{
			return m_skeleton.GetBone(boneNo);
		}
		void AddAnimationEvent(AnimationEventListener eventListener)
		{
			m_animation.AddAnimationEventListener(eventListener);
		}

		/// <summary>
		/// �A�j���[�V�����Đ��B
		/// </summary>
		/// <param name="animNo">�A�j���[�V�����N���b�v�̔ԍ��B</param>
		/// <param name="interpolateTime">�⊮����(�P�ʁF�b�B)</param>
		void PlayAnimation(int animNo, float interpolateTime = 0.0f)
		{
			m_animation.Play(animNo, interpolateTime);
		}
		/// <summary>
		/// �A�j���[�V�����̍Đ����H
		/// </summary>
		bool IsPlayingAnimation() const
		{
			return m_animation.IsPlaying();
		}
		/// <summary>
		/// �`��p�X����Ă΂�鏈��
		/// </summary>
		/// <param name="rc"></param>
		void DrawShadow(RenderContext& rc)
		{
			m_ShadowModel.Draw(rc, g_shadow.GetLightCamera());
		}

	private:
		// �X�P���g����������
		void InitSkeleton(const char* filePath);
		//�A�j���[�V�����̏�����
		void InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis);
	private:
		AnimationClip*              m_animationClips = nullptr;			// �A�j���[�V�����N���b�v�B
		int							m_numAnimationClips = 0;			// �A�j���[�V�����N���b�v�̐��B
		int							m_ShadowRecieverBG = false;			// �V���h�E��������̂��w�i���ۂ�
		Animation					m_animation;						// �A�j���[�V�����B
		Model                       m_model;		         	        // ���f��
		Model						m_bgModel;							// �V���h�E���󂯂�w�i�̃��f��
		Model						m_ShadowModel;						// �V���h�E�p�̃��f��
		ModelInitData				m_bgModelInitData;					// �V���h�E���󂯂�w�i�p��Initdata
		ModelInitData				m_ShadowModelInitData;				// �V���h�E���f���p��Initdata
		Sprite						m_shadowsprite;						// �V���h�E�p�̉摜
		Skeleton                    m_skeleton;	                        // �X�P���g��
		Vector3 					m_position = Vector3::Zero;			// ���W�B
		Quaternion	 				m_rotation = Quaternion::Identity;	// ��]�B
		Vector3						m_scale = Vector3::One;				// �g�嗦�B
		EnModelUpAxis				m_enFbxUpAxis = enModelUpAxisZ;			// FBX�̏�����B
		const char*					m_shadowfilePath;
	};
}