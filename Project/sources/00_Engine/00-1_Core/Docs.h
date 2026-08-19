/*============================================================
*	@file	 : filename.h
*	@brief	 : 
*
* 　@author  : @akitsuki-35（https://github.com/akitsuki-35）
* 　@date	 : 20XX/XX/XX
*	@updated : 20XX/XX/XX
*============================================================*/
#pragma once

class Singleton final
{
private:
	Singleton() = default;
	Singleton(const Singleton&) = delete;
	
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;

	Singleton& operator=(Singleton&&) = delete;
	~Singleton() {};

public:
	static Singleton& getInstance() {
		static Singleton instance;
		return instance;
	}
};

/*============================================================
*	@class	: class
*	@brief	: 
*============================================================*/

/*============================================================
*	@namespace	: name
*	@brief		: 
*============================================================*/