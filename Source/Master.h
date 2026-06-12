#pragma once

#include "ResourceManager.h"
#include "Loading.h"
class Master 
{
public:
	
	static ResourceManager* mpResource;	//リソース,ロード関係
	static LoadingManager* mpLoading;	//ローディングで用いる
};
