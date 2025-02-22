#pragma once

#include "Indexbuffer.h"
#include "VertexBuffer.h"
#include "ConstantBuffer.h"

namespace nsK2EngineLow {
	class Texture;

	//スプライトに設定できる最大テクスチャ数。
	const int MAX_TEXTURE = 32;
	//拡張SRVが設定されるレジスタの開始番号。
	const int EXPAND_SRV_REG__START_NO = 20;
	const int EXPAND_MAX_SPRITE_EXPAND_SRV = 32;	//拡張SRVの最大数。

	class IShaderResource;


	/// <summary>
	/// スプライトの初期化データ。
	/// </summary>
	struct SpriteInitData {
		std::array<const char*, MAX_TEXTURE> m_ddsFilePath = { nullptr };	//DDSファイルのファイルパス。
		std::array<Texture*, MAX_TEXTURE> m_textures = { nullptr };		//使用するテクスチャ。DDSファイルのパスが指定されている場合は、このパラメータは無視されます。
		const char* m_vsEntryPointFunc = "VSMain";						//頂点シェーダーのエントリーポイント。
		const char* m_psEntryPoinFunc = "PSMain";						//ピクセルシェーダーのエントリーポイント。
		const char* m_fxFilePath = nullptr;								//.fxファイルのファイルパス。
		UINT m_width = 0;												//スプライトの幅。
		UINT m_height = 0;												//スプライトの高さ。
		void* m_expandConstantBuffer = nullptr;							//ユーザー拡張の定数バッファ
		int m_expandConstantBufferSize = 0;								//ユーザー拡張の定数バッファのサイズ。
		std::array<IShaderResource*, EXPAND_MAX_SPRITE_EXPAND_SRV> m_expandShaderResoruceView = { nullptr };			//ユーザー拡張のシェーダーリソース。
		AlphaBlendMode m_alphaBlendMode = AlphaBlendMode_None;			//アルファブレンディングモード。
		std::array<DXGI_FORMAT, MAX_RENDERING_TARGET> m_colorBufferFormat = {
			DXGI_FORMAT_R8G8B8A8_UNORM,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
			DXGI_FORMAT_UNKNOWN,
		};	//レンダリングするカラーバッファのフォーマット。
		D3D12_TEXTURE_ADDRESS_MODE textureAddressMode = D3D12_TEXTURE_ADDRESS_MODE_CLAMP;	// テクスチャアドレッシングモード。
	};
	/// <summary>
	/// スプライトクラス。
	/// </summary>
	class Sprite : public Noncopyable {
	public:
		static const Vector2	DEFAULT_PIVOT;					//!<ピボット。
		virtual ~Sprite();
		/// <summary>
		/// 初期化。
		/// </summary>
		/// <param name="initData">初期化データ</param>
		void Init(const SpriteInitData& initData);
		/// <summary>
		/// 乗算カラーを設定。
		/// </summary>
		/// <param name="mulColor">乗算カラー。</param>
		void SetMulColor(const Vector4& mulColor)
		{
			m_mulColor = mulColor;
		}
		/// <summary>
		/// 乗算カラーを取得。
		/// </summary>
		/// <returns>乗算カラー。</returns>
		const Vector4& GetMulColor() const
		{
			return m_mulColor;
		}
		/// <summary>
		/// 更新。
		/// </summary>
		/// <param name="pos">座標</param>
		/// <param name="rot">回転</param>
		/// <param name="scale">拡大率</param>
		/// <param name="pivot">
		/// ピボット
		/// 0.5, 0.5で画像の中心が基点。
		/// 0.0, 0.0で画像の左下。
		/// 1.0, 1.0で画像の右上。
		/// UnityのuGUIに準拠。
		/// </param>
		void Update(const Vector3& pos, const Quaternion& rot, const Vector3& scale, const Vector2& pivot = DEFAULT_PIVOT);
		/// <summary>
		/// 描画。
		/// </summary>
		/// <param name="renderContext">レンダリングコンテキスト</param>
		void Draw(RenderContext& renderContext);
		/// <summary>
		/// ユーザー定義の拡張定数バッファを取得。
		/// </summary>
		/// <returns></returns>
		ConstantBuffer& GetExpandConstantBufferGPU()
		{
			return m_userExpandConstantBufferGPU;
		}
		/// <summary>
		/// テクスチャの幅を取得。
		/// </summary>
		/// <param name="texNo"></param>
		/// <returns></returns>
		int GetTextureWidth(int texNo) const
		{
			return m_textures[texNo].GetWidth();
		}
		/// <summary>
		/// テクスチャの幅を取得。
		/// </summary>
		/// <param name="texNo"></param>
		/// <returns></returns>
		int GetTextureHeight(int texNo) const
		{
			return m_textures[texNo].GetHeight();
		}
		Texture& GetTexture()
		{
			return m_textures[0];
		}
		void SetX(const float x)
		{
			m_x = x;
		}
		void SetY(const float y)
		{
			m_y = y;
		}

		void SetIsDisplayRestrictionLeftSide(const bool isLeft)
		{
			if (isLeft)
			{
				m_isDisplayRestrictionRightSide = 0;
			}
			else
			{
				m_isDisplayRestrictionRightSide = 1;
			}
		}
		void SetIsDisplayRestrictionRightSide(const bool isRight)
		{
			if (isRight)
			{
				m_isDisplayRestrictionRightSide = 1;
			}
			else
			{
				m_isDisplayRestrictionRightSide = 0;
			}
		}

		void SetIsDisplayRestrictionUpSide(const bool isUp)
		{
			if (isUp)
			{
				m_isDisplayRestrictionUpSide = 1;
			}
			else
			{
				m_isDisplayRestrictionUpSide = 0;
			}
		}
		void SetIsDisplayRestrictionDownSide(const bool isDown)
		{
			if (isDown)
			{
				m_isDisplayRestrictionUpSide = 0;
			}
			else
			{
				m_isDisplayRestrictionUpSide = 1;
			}
		}
	private:
		/// <summary>
		/// テクスチャを初期化。
		/// </summary>
		/// <param name="initData"></param>
		void InitTextures(const SpriteInitData& initData);
		/// <summary>
		/// シェーダーを初期化。
		/// </summary>
		/// <param name="initData"></param>
		void InitShader(const SpriteInitData& initData);
		/// <summary>
		/// ディスクリプタヒープを初期化。
		/// </summary>
		/// <param name="initData"></param>
		void InitDescriptorHeap(const SpriteInitData& initData);
		/// <summary>
		/// 頂点バッファとインデックスバッファを初期化。
		/// </summary>
		/// <param name="initData"></param>
		void InitVertexBufferAndIndexBuffer(const SpriteInitData& initData);
		/// <summary>
		/// パイプラインステートを初期化する。
		/// </summary>
		void InitPipelineState(const SpriteInitData& initData);
		/// <summary>
		/// 定数バッファを初期化。
		/// </summary>
		/// <param name="initData"></param>
		void InitConstantBuffer(const SpriteInitData& initData);
	private:
		IndexBuffer m_indexBuffer;			//インデックスバッファ。
		VertexBuffer m_vertexBuffer;		//頂点バッファ。
		int m_numTexture = 0;				//テクスチャの枚数。
		Texture m_textures[MAX_TEXTURE];	//テクスチャ。
		Texture* m_textureExternal[MAX_TEXTURE] = { nullptr };	//外部から指定されたテクスチャ
		Vector3 m_position;				//座標。
		Vector2 m_size;						//サイズ。
		Quaternion m_rotation;			//回転。
		Matrix m_world;					//ワールド行列。
		float m_x = 1.0f;
		float m_y = 1.0f;
		int m_isDisplayRestrictionRightSide = 1;
		int m_isDisplayRestrictionUpSide = 1;

		struct LocalConstantBuffer {
			Matrix mvp;
			Vector4 mulColor;
			Vector4 screenParam;
		};
		LocalConstantBuffer m_constantBufferCPU;	//CPU側の定数バッファ。
		ConstantBuffer		m_constantBufferGPU;	//GPU側の定数バッファ。
		ConstantBuffer		m_userExpandConstantBufferGPU;	//ユーザー拡張の定数バッファ(GPU側)
		void* m_userExpandConstantBufferCPU = nullptr;		//ユーザー拡張の定数バッファ(CPU側)
		DescriptorHeap		m_descriptorHeap;		//ディスクリプタヒープ。
		RootSignature		m_rootSignature;		//ルートシグネチャ。
		PipelineState		m_pipelineState;		//パイプラインステート。
		Shader				m_vs;					//頂点シェーダー。
		Shader				m_ps;					//ピクセルシェーダー。
		Vector4				m_mulColor = Vector4::White;	//乗算カラー。
	};
}