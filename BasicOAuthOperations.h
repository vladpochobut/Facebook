#pragma once
#include "pch.h"

class BasicOauth {

public:
	static void Initialization();

	static void Login();

	static void Logout();

	static void UserInformation();

	static void ShowSendDialog(Platform::String^ link, Platform::String^ destinationID);

	static void PostToFeed(Platform::String^ link);

	//void UploadPhoto();

	//void UploadVideo();

	//static void UploadAlbums();

	//void UploadInbox();
};