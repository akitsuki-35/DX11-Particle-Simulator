/*============================================================
*	@file	 : Audio.h
*	@brief	 : オーディオリソース
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/09
*	@updated : 2026/08/09
*============================================================*/
#pragma once

#include <xaudio2.h>
#include <vector>

/*============================================================
*	@class	: Audio
*	@brief	: オーディオリソース
*============================================================*/
class Audio
{
	friend class AudioManager;

private:
    std::vector<BYTE> mPCM{}; // PCMデータ
    WAVEFORMATEX mFormat{}; // フォーマット
    UINT mBytes{ 0 }; // PCMバイト数
    UINT mSamples{ 0 }; // サンプル数

    // ループタグ
    int mLoopStart{ -1 };
    int mLoopEnd = { -1 };
	
public:
    // PCMデータ取得
    const BYTE* GetPCM() const { return mPCM.data(); }

    // フォーマット取得
    const WAVEFORMATEX* GetFormat() const { return &mFormat; }

    // PCMバイト数取得
    UINT GetAudioBytes() const { return mBytes; }

    // サンプル数取得
    UINT GetSamples() const { return mSamples; }

    // ループ関連取得
    bool IsLoopTag() const { return (mLoopStart >= 0 && mLoopEnd > mLoopStart); }
    int GetLoopStart() const { return mLoopStart; }
    int GetLoopEnd() const { return mLoopEnd; }
};