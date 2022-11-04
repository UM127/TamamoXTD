/*!
 * @brief シャドウマップ描画用のシェーダー
 */

// モデル用の定数バッファー
cbuffer ModelCb : register(b0)
{
    float4x4 mWorld;
    float4x4 mView;
    float4x4 mProj;
};
// step-3 ライトビュープロジェクション行列の定数バッファーを定義
cbuffer ShadowCb : register(b1)
{
    float4x4 mLVP;
};
//スキニング用の頂点データをひとまとめ。
struct SSkinVSIn
{
    int4 Indices : BLENDINDICES0;
    float4 Weights : BLENDWEIGHT0;
};
//頂点シェーダーへの入力。
struct SVSIn
{
    float4 pos : POSITION; //モデルの頂点座標。
    float3 normal : NORMAL;
    
    //頂点シェーダーの入力に接ベクトルと従ベクトルを追加
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    float2 uv : TEXCOORD0; //UV座標。
    SSkinVSIn skinVert; //スキン用のデータ。
};
//ピクセルシェーダーへの入力。
struct SPSIn
{
    float4 pos : SV_POSITION; //スクリーン空間でのピクセルの座標。
    float3 normal : NORMAL;
    
    // step-2 ピクセルシェーダーの入力に接ベクトルと従ベクトルを追加
    float3 tangent : TANGENT;
    float3 biNormal : BINORMAL;
    
    float2 uv : TEXCOORD0; //uv座標。
    float3 worldPos : TEXCOORD1;
    // step-1 ピクセルシェーダーへの入力にカメラ空間の法線を追加する
    float3 normalInView : TEXCOORD2; //カメラ空間の法線。
    
    // step-4 ライトビュースクリーン空間での座標を追加
    float4 posInLVP : TEXCOORD3; //ライトビュースクリーン空間でのピクセルの座標
};
struct SPSOut
{
    float4 Color;
};

///////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////
StructuredBuffer<float4x4> g_boneMatrix : register(t3); // ボーン行列。


/// <summary>
//スキン行列を計算する。
/// </summary>
float4x4 CalcSkinMatrix(SSkinVSIn skinVert)
{
    float4x4 skinning = 0;
    float w = 0.0f;
	[unroll]
    for (int i = 0; i < 3; i++)
    {
        skinning += g_boneMatrix[skinVert.Indices[i]] * skinVert.Weights[i];
        w += skinVert.Weights[i];
    }
    
    skinning += g_boneMatrix[skinVert.Indices[3]] * (1.0f - w);
	
    return skinning;
}
/// <summary>
/// 頂点シェーダーのコア関数。
/// </summary>
SPSIn VSMainCore(SVSIn vsIn, uniform bool hasSkin)
{
    SPSIn psIn;
    float4x4 m;
    if (hasSkin)
    {
        m = CalcSkinMatrix(vsIn.skinVert);
    }
    else
    {
        m = mWorld;
    }
    psIn.pos = mul(m, vsIn.pos);
    psIn.worldPos = psIn.pos;
    psIn.pos = mul(mView, psIn.pos);
    psIn.pos = mul(mProj, psIn.pos);
    
    //psIn.normal = mul(m, vsIn.normal); //法線を回転させる。
    //psIn.normal = normalize(psIn.normal);
    psIn.normal = normalize(mul(m, vsIn.normal));
    
    // カメラ空間の法線を求める
    psIn.normalInView = mul(mView, psIn.normal); //カメラ空間の法線を求める。
    psIn.normalInView = normalize(psIn.normalInView);

    // 接ベクトルと従ベクトルをワールド空間に変換する
    psIn.tangent = normalize(mul(m, vsIn.tangent));
    psIn.biNormal = normalize(mul(m, vsIn.biNormal));
    psIn.uv = vsIn.uv;
    (mul(m, vsIn.tangent));
    
    // step-5 ライトビュースクリーン空間の座標を計算する
    psIn.posInLVP = mul(mLVP, psIn.worldPos);
    
    return psIn;
}

/// <summary>
/// シャドウマップ描画用のピクセルシェーダー
/// </summary>
float4 PSMain(SPSIn psIn) : SV_Target0
{
    // step-5 シャドウマップ描画用のピクセルシェーダーを作成する
    return float4(0.5f, 0.5f, 0.5f, 1.0f);
}
/// <summary>
/// スキンなしメッシュ用の頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, false);
}
/// <summary>
/// スキンありメッシュの頂点シェーダーのエントリー関数。
/// </summary>
SPSIn VSSkinMain(SVSIn vsIn)
{
    return VSMainCore(vsIn, true);
}