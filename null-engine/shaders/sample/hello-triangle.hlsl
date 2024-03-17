
const float2 g_positions[3] = float2[]
{
    float2( 0.0f, -0.5f),
    float2( 0.5f,  0.5f),
    float2(-0.5f,  0.5f)
};
const float2 g_colours[3] = float2[]
{
    float2(1.0f, 0.0f, 0.0f),
    float2(0.0f, 1.0f, 0.0f),
    float2(0.0f, 0.0f, 1.0f)
};

struct VertexIn
{
    uint id : SV_VertexID;
};

struct VertexOut
{
    float4 positionCS : SV_POSITION;
    float3 colour     : COLOR0;
};

typedef VertexOut FragmentIn;

struct FragmentOut
{
    float4 colour0 : SV_Target0;
};

VertexOut VSMain(VertexIn vtxIn)
{
    VertexOut vtxOut;
    vtxOut.positionCS = float4(g_positions[vtxIn.id], 0.0f, 1.0f);
    vtxOut.colour     = g_colours[vtxIn.id];
    return vtxOut;
}

FragmentOut FSMain(FragmentIn fgmIn)
{
    FragmentOut fgmOut;
    fgmOut.colour0 = float4(fgmIn.colour, 0.0f);
    return fgmOut;
}
