#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{
	}

	ModelRender::~ModelRender()
	{

	}

	void ModelRender::Init(const char* filePath, bool shadow , bool selfluminance, AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		//モデルを初期化するための情報を設定。
		ModelInitData initData;

		//シェーダーファイルのファイルパスを指定する。
		initData.m_fxFilePath = "Assets/shader/model.fx";
		if (m_ShadowRecieverBG== true)
		{
			initData.m_psEntryPointFunc = "PSMainShadowReciever";
		}
		else
		{
			initData.m_psEntryPointFunc = "PSMain";
		}
		initData.m_expandShaderResoruceView[0] = &g_shadow.GetShadowMap();
		m_dissolvesprite.Init("Assets/sprite/cloud.dds", 512.0f, 512.0f);
		initData.m_expandShaderResoruceView[1] = &m_dissolvesprite.GetSprite().GetTexture();
		//tkmファイルのファイルパスを指定する。
		initData.m_tkmFilePath = filePath;


		m_animationClips = animationClips;


		if (m_animationClips != nullptr)
		{
			// スケルトンを初期化。
			InitSkeleton(filePath);
			//スケルトンを指定する。
			initData.m_skeleton = &m_skeleton;
			//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
			initData.m_vsSkinEntryPointFunc = "VSSkinMain";
			//モデルの上方向を指定する。
			initData.m_modelUpAxis = enModelUpAxis;
		}
		else {
			//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
			initData.m_vsEntryPointFunc = "VSMain";
		}
		m_light= g_Lig.GetLight();
		if (!selfluminance)
		{
			initData.m_expandConstantBuffer = &m_light;
			initData.m_expandConstantBufferSize = sizeof(m_light);
		}
		else
		{
			initData.m_expandConstantBuffer = &m_light;
			initData.m_expandConstantBufferSize = sizeof(m_light);
			m_light.m_directionLig.ligColor *= 10.0f;
		}
		

		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		//作成した初期化データをもとにモデルを初期化する。
		m_model.Init(initData);
		ShadowInit(filePath, shadow, animationClips, numAnimationClips, enModelUpAxis);
		//Initの中にアップデートを入れることでInitするときにアップデートしなくてよくなる。
		Update();
	}

	void ModelRender::ShadowInit(const char* filePath, 
		bool shadow,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAxis)
	{
		if (shadow==true)
		{
			//影が落とされるモデル用のシェーダーを指定する。
			m_bgModelInitData.m_fxFilePath = "Assets/shader/sampleShadowReciever.fx";
			//シャドウマップを拡張SRVに設定する。
			m_bgModelInitData.m_expandShaderResoruceView[0] = &g_shadow.GetShadowMap();
			//ライトビュープロジェクション行列を拡張定数バッファに設定する。
			m_bgModelInitData.m_expandConstantBuffer = (void*)&g_shadow.GetLightCamera().GetViewProjectionMatrix();
			m_bgModelInitData.m_expandConstantBufferSize = sizeof(g_shadow.GetLightCamera().GetViewProjectionMatrix());
			m_bgModelInitData.m_tkmFilePath = filePath;

			m_bgModel.Init(m_bgModelInitData);
			//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
			m_bgModelInitData.m_vsEntryPointFunc = "VSMain";
		}
		else
		{
			//【注目】シャドウマップ描画用のシェーダーを指定する。
			m_ShadowModelInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
			//m_ShadowModelInitData.m_fxFilePath = "Assets/shader/DrawShadowMap.fx";
			m_ShadowModelInitData.m_tkmFilePath = filePath;
			m_animationClips = animationClips;
			if (m_animationClips != nullptr)
			{
				//スケルトンを指定する。
				m_ShadowModelInitData.m_skeleton = &m_skeleton;
				//スキンメッシュ用の頂点シェーダーのエントリーポイントを指定。
				m_ShadowModelInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
				//モデルの上方向を指定する。
				m_ShadowModelInitData.m_modelUpAxis = enModelUpAxis;
			}
			else {
				//ノンスキンメッシュ用の頂点シェーダーのエントリーポイントを指定する。
				m_ShadowModelInitData.m_vsEntryPointFunc = "VSMain";
			}
			m_ShadowModel.Init(m_ShadowModelInitData);
		}
		// アニメーションを初期化。
		InitAnimation(animationClips, numAnimationClips, enModelUpAxis);
		Update();
	}

	void ModelRender::Update()
	{
		//スケルトンを更新。
		m_skeleton.Update(m_model.GetWorldMatrix());

		//アニメーションを進める。
		m_animation.Progress(g_gameTime->GetFrameDeltaTime());

		// ワールド行列を更新。
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_bgModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_ShadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
	}

	void ModelRender::InitSkeleton(const char* filePath)
	{
		//スケルトンのデータを読み込み。
		std::string skeletonFilePath = filePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips, EnModelUpAxis enModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr) {
			m_animation.Init(m_skeleton,
				m_animationClips,
				numAnimationClips);
		}
	}
	void ModelRender::Draw(RenderContext& rc)
	{

			m_model.Draw(rc);
			if (!m_ShadowRecieverBG)
			{
				g_renderingEngine.AddRenderObject(this);
			}
			else
			{
				m_bgModel.Draw(rc);
			}

	}
}