#pragma once
#include "pch.h"
#include <cpprest\http_client.h>
#include "BasicOAuthOperations.h"
#include "UserProfile.xaml.h"
#include "FBReturnObject.h"
#include "AlbumPage.xaml.h"
#include "Facebook.h"

using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::Pickers;
using namespace Windows::Data::Json;
using namespace Platform;
using namespace concurrency;
using namespace winsdkfb;
using namespace winsdkfb::Graph;
using namespace Platform::Collections;
using namespace Windows::UI::Xaml::Controls;

void BasicOauth::Initialization()
{
	FBSession^ sess = FBSession::ActiveSession;
	sess->FBAppId = "239195109970945";
	sess->WinAppId = "s-1-15-2-241198405-1672178590-4135340502-2609782583-2806565537-4251846274-2408249771";
}

void BasicOauth::Login()
{
	// Get active session
	FBSession^ sess = FBSession::ActiveSession;
	// Add permissions required by the app
	Vector<String^>^ permissionList = ref new Vector<String^>();
	permissionList->Append(L"public_profile");
	permissionList->Append(L"user_friends");
	permissionList->Append(L"user_likes");
	permissionList->Append(L"user_photos");
	permissionList->Append(L"user_videos");
	permissionList->Append(L"read_page_mailboxes");
	permissionList->Append(L"user_posts");
	FBPermissions^ permissions = ref new FBPermissions(permissionList->GetView());
	// Login to Facebook
	create_task(sess->LoginAsync(permissions)).then([=](FBResult^ result)
	{
		if (result->Succeeded) {
			return true;
		}
		else
			return false;
	});
	BOOL success = FALSE;
	FBAccessTokenData^ data = FBSession::ActiveSession->AccessTokenData;
	if (data)
	{
		success = !data->DeclinedPermissions->Values->Size;
	}
}

void BasicOauth::Logout()
{
	BOOL success = FALSE;
	FBAccessTokenData^ data = FBSession::ActiveSession->AccessTokenData;
	if (data)
	{
		success = !data->DeclinedPermissions->Values->Size;
	}
	FBSession^ sess = FBSession::ActiveSession;
	sess->LogoutAsync();
}

void BasicOauth::ShowSendDialog(Platform::String^ link, Platform::String^ destinationID)
{
	//Get active session
	FBSession^ sess = FBSession::ActiveSession;
	if (sess->LoggedIn)
	{
		PropertySet^ parameters = ref new PropertySet();
		if (!(link->IsEmpty()))
			parameters->Insert(L"link", link);
		else
			parameters->Insert(L"link", L"https://www.facebook.com/");
		if (!(destinationID->IsEmpty()))
			parameters->Insert(L"to", destinationID);
		//Display send dialog
		create_task(sess->ShowSendDialogAsync(parameters));
	}
}

void BasicOauth::PostToFeed(String^ link)
{
	FBSession^ sess = FBSession::ActiveSession;
	if (sess->LoggedIn)
	{
		// Set caption, link and description parameters
		PropertySet^ parameters = ref new PropertySet();
		if (!(link->IsEmpty()))
			parameters->Insert(L"link", link);
		else
			parameters->Insert(L"link", L"https://www.facebook.com/");
		// Display feed dialog
		create_task(sess->ShowFeedDialogAsync(parameters));
	}
}

/*void UploadPhoto()
{
	StorageFile^ selectedPhoto;
	// Read image file into selectedPhoto
	FileOpenPicker^ fop = ref new FileOpenPicker();
	fop->ViewMode = PickerViewMode::Thumbnail;
	fop->SuggestedStartLocation = PickerLocationId::PicturesLibrary;
	fop->FileTypeFilter->Append(L".jpg");
	fop->FileTypeFilter->Append(L".png");

	create_task(fop->PickSingleFileAsync()).then([&](StorageFile^ storageFile)
	{
		//if (storageFile)
			//selectedPhoto = storageFile;
		return storageFile->OpenReadAsync();
	}).then([=, &selectedPhoto](IRandomAccessStreamWithContentType^ stream)
	{
		// Create media stream
		FBMediaStream^ fbStream = ref new FBMediaStream(selectedPhoto->Name, stream);

		// Get active session
		FBSession^ sess = FBSession::ActiveSession;
		if (sess->LoggedIn)
		{

			PropertySet^ parameters = ref new PropertySet();
			// Set media stream
			parameters->Insert("source", fbStream);

			// Create Graph API path
			String^ graphPath = sess->User->Id + L"/photos";

			// Create a json class factory with a class (FBReturnObject class) that
			// can receive and parse the json response returned
			FBJsonClassFactory^ fact = ref new FBJsonClassFactory([](String^ JsonText) ->
				Object^
			{
				auto returnObject = ref new FBReturn::FBReturnObject();
				returnObject->Id = Windows::Data::Json::JsonObject::Parse(JsonText)->GetNamedString("id");
				return returnObject;
			});

			FBSingleValue^ sval = ref new FBSingleValue(graphPath, parameters, fact);
			create_task(sval->PostAsync()).then([=](FBResult^ result)
			{
				if (result->Succeeded)
				{
					FBReturn::FBReturnObject^ response = static_cast<FBReturn::FBReturnObject ^>(result->Object);
				}
				else
				{
					// Posting failed
				}
			});
		}
	});
}

void UploadVideo()
{
	FileOpenPicker^ fop = ref new FileOpenPicker();
	fop->ViewMode = PickerViewMode::Thumbnail;
	fop->SuggestedStartLocation = PickerLocationId::VideosLibrary;
	fop->FileTypeFilter->Append(L".mp4");
	StorageFile^ storageFile;

	create_task(fop->PickSingleFileAsync()).then([=, &storageFile](StorageFile^ tempStorageFile)
	{
		storageFile = tempStorageFile;
		return tempStorageFile->OpenReadAsync();
	}).then([=](IRandomAccessStreamWithContentType^ stream)
	{
		FBMediaStream^ mediaStream = ref new FBMediaStream(storageFile->Name, stream);
		FBSession^ sess = FBSession::ActiveSession;
		if (sess->LoggedIn)
		{
			FBUser^ user = sess->User;
			PropertySet^ parameters = ref new PropertySet();
			parameters->Insert(L"title", L"Test video");
			parameters->Insert(L"source", mediaStream);
			String^ path = L"/" + user->Id + L"/videos";

			FBJsonClassFactory^ factory = ref new FBJsonClassFactory([](String^ s)
			{
				JsonObject^ jsonObject = JsonObject::Parse(s);
				auto returnObject = ref new FBReturn::FBReturnObject();
				returnObject->Id = jsonObject->GetNamedString(L"id");
				returnObject->Post_Id = jsonObject->GetNamedString(L"post_id");
				return returnObject;
			});

			FBSingleValue^ singleValue = ref new FBSingleValue(path, parameters, factory);
			return create_task(singleValue->PostAsync());
		}
		return create_task([]()
		{
			return ref new FBResult(ref new FBError(0, L"Not logged in", L"Log in first"));
		});
	}).then([=](FBResult^ result)
	{
		if (result->Succeeded)
		{
			FBReturn::FBReturnObject^ response = static_cast<FBReturn::FBReturnObject^>(result->Object);
		}
	});
}

void UploadInbox() {
	using namespace pplx;
	using namespace web::http;
	facebook_client::instance().get(L"/me/posts").
		then([](web::json::value v) {
		web::json::object& obj = v.as_object();
		web::json::array objAsArr = obj[L"data"].as_array();
		for (int i = 0; i < objAsArr.size(); i++) {
			web::json::value post = objAsArr[i];
		}
	});
}*/