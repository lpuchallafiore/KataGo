#ifndef NEURALNET_CUDAHELPERS_H_
#define NEURALNET_CUDAHELPERS_H_

#include "../neuralnet/cudaincludes.h"

//Given two tensors with shapes inA: [n,cA,h,w] and inB: [n,cB,h,w], that are on the GPU
//Copy them into a single tensor out: [n,cA+cB,h,w] that is also allocated on the gpu
void customCudaChannelConcat(const float* inA, const float* inB, float* out, int chwA, int chwB, int n);
void customCudaChannelConcat(const half* inA, const half* inB, half* out, int chwA, int chwB, int n);

//Given a tensor [n,c,hw], extract out channel 0 to [n,hw]
void customCudaChannel0ExtractNCHW(const float* in, float* out, int n, int c, int hw);
void customCudaChannel0ExtractNCHW(const half* in, half* out, int n, int c, int hw);
//Given a tensor [n,hw,c], extract out channel 0 to [n,hw]
void customCudaChannel0ExtractNHWC(const float* in, float* out, int n, int hw, int c);
void customCudaChannel0ExtractNHWC(const half* in, half* out, int n, int hw, int c);

//Given an input tensor and an output buffer of shape [n,c], fill output buffer with sum or max over c.
//Max is POSITIVE max - only computes the max of positive entries, and if there are none, then evaluates to 0.
void customCudaPoolRowsSumNCHW(const float* in, float* out, int nSize, int cSize, int xySize, float scaleSum);
void customCudaPoolRowsMaxPositiveNCHW(const float* in, float* out, int nSize, int cSize, int xySize);
void customCudaPoolRowsSumNHWC(const float* in, float* out, int nSize, int xySize, int cSize, float scaleSum);
void customCudaPoolRowsMaxPositiveNHWC(const float* in, float* out, int nSize, int xySize, int cSize);

//Same, except fills an output buffer of shape [n,c*2] with the sum over c and the max over c, in that order.
void customCudaPoolRowsSumAndMaxPositiveNCHW(const float* in, float* out, int nSize, int cSize, int xySize, float scaleSum);
void customCudaPoolRowsSumAndMaxPositiveNHWC(const float* in, float* out, int nSize, int xySize, int cSize, float scaleSum);
void customCudaPoolRowsSumAndMaxPositiveNCHW(const half* in, half* out, int nSize, int cSize, int xySize, float scaleSum);
void customCudaPoolRowsSumAndMaxPositiveNHWC(const half* in, half* out, int nSize, int xySize, int cSize, float scaleSum);

//Specialized operations for value head and general global pooling. Same as the other pooling, but fusedly fills
//an output buffer of shape [n,c*3].
void customCudaValueHeadPoolNCHW(const float* in, float* out, int nSize, int cSize, int xySize, const float* maskSum);
void customCudaValueHeadPoolNHWC(const float* in, float* out, int nSize, int xySize, int cSize, const float* maskSum);
void customCudaPoolRowsGPoolNCHW(const float* in, float* out, int nSize, int cSize, int xySize, const float* maskSum);
void customCudaPoolRowsGPoolNHWC(const float* in, float* out, int nSize, int xySize, int cSize, const float* maskSum);
void customCudaPoolRowsGPoolNCHW(const half* in, half* out, int nSize, int cSize, int xySize, const float* maskSum);
void customCudaPoolRowsGPoolNHWC(const half* in, half* out, int nSize, int xySize, int cSize, const float* maskSum);


void customCudaNCHWTranspose(const float *in, float* out, int xSize, int ySize, int ncSize);
void customCudaNHWCTranspose(const float *in, float* out, int xSize, int ySize, int cSize, int nSize);
void customCudaNCHWTranspose(const half *in, half* out, int xSize, int ySize, int ncSize);
void customCudaNHWCTranspose(const half *in, half* out, int xSize, int ySize, int cSize, int nSize);

void customCudaMirror(const float *in, float* out, int batchSize, int mSize, int subSize);
void customCudaMirrorNCHW(const float *in, float* out, int batchSize, int cSize, int ySize, int xSize, bool mirrorY, bool mirrorX);
void customCudaMirrorNHWC(const float *in, float* out, int batchSize, int ySize, int xSize, int cSize, bool mirrorY, bool mirrorX);
void customCudaMirror(const half *in, half* out, int batchSize, int mSize, int subSize);
void customCudaMirrorNCHW(const half *in, half* out, int batchSize, int cSize, int ySize, int xSize, bool mirrorY, bool mirrorX);
void customCudaMirrorNHWC(const half *in, half* out, int batchSize, int ySize, int xSize, int cSize, bool mirrorY, bool mirrorX);

void customCudaCopyToHalf(const float* in, half* out, int n);
void customCudaCopyFromHalf(const half* in, float* out, int n);

//Given a tensor, add another tensor to it.
void customCudaAddTensorInplace(half* buf, const half* biases, int n);
//Given an input with shape [n,c] and biases of shape [c], add the biases in-place.
void customCudaAddCBiasInplaceNC(float* buf, const float* biases, int n, int c);
void customCudaAddCBiasInplaceNC(half* buf, const half* biases, int n, int c);
//Given an input with shape [n,c,xy] and biases of shape [n,c], add the biases in-place.
void customCudaAddNCBiasInplaceNCHW(float *buf, const float* biases, int nSize, int cSize, int xySize);
void customCudaAddNCBiasInplaceNCHW(half *buf, const half* biases, int nSize, int cSize, int xySize);
//Given an input with shape [n,xy,c] and biases of shape [n,c], add the biases in-place.
void customCudaAddNCBiasInplaceNHWC(float *buf, const float* biases, int nSize, int xySize, int cSize);
void customCudaAddNCBiasInplaceNHWC(half *buf, const half* biases, int nSize, int xySize, int cSize);

//Given an input with shape [n,c,xy] and scale and biases of shape [c], multiply by scale and add the biases
//Optionally also apply relu.
void customCudaApplyCScaleBiasNCHW(const float* in, float* out, const float* scale, const float* biases, const float* mask, int n, int c, int xy, bool applyRelu);
void customCudaApplyCScaleBiasNCHW(const half* in, half* out, const half* scale, const half* biases, const half* mask, int n, int c, int xy, bool applyRelu);
//Given an input with shape [n,xy,c] and scale and biases of shape [c], multiply by scale and add the biases
//Optionally also apply relu.
//Optionally also multiply by mask (can be null), with shape [n,xy]
void customCudaApplyCScaleBiasNHWC(const float* in, float* out, const float* scale, const float* biases, const float* mask, int n, int xy, int c, bool applyRelu);
void customCudaApplyCScaleBiasNHWC(const half* in, half* out, const half* scale, const half* biases, const half* mask, int n, int xy, int c, bool applyRelu);


#endif  // NEURALNET_CUDAHELPERS_H_
