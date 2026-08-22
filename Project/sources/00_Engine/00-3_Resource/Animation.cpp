/*============================================================
*	@file	 : Animation.cpp
*	@brief	 : アニメーションクリップ
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 2026/08/13
*	@updated : 2026/08/13
*============================================================*/
#include "Animation.h"

void Animation::AddChannel(const Channel& channel)
{
	mChannels.push_back(channel);
}