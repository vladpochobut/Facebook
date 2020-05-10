//
// AlbumPage.xaml.cpp
// Implementation of the AlbumPage class
//

#include "pch.h"
#include "AlbumPage.xaml.h"
#include "UserProfile.xaml.h"
#include "Facebook.h"

using namespace App2;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::Security::Authentication::Web;
using namespace pplx;
using namespace web;
using namespace winsdkfb;
using namespace winsdkfb::Graph;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

AlbumPage::AlbumPage()
{
	InitializeComponent();
}

String^ FacebookAlbum::Title::get() {
	return ref new String(title_.c_str());
}

String^ FacebookAlbum::ID::get() {
	return ref new String(created.c_str());
}

//int FacebookAlbum::Count::get() {
//	return count_;
//}

ImageSource^ FacebookAlbum::Preview::get()
{
	if (preview_ == nullptr) {
		http::uri_builder ret;
		ret.set_path(L"https://graph.facebook.com");
		FBSession^ sess = FBSession::ActiveSession;
		FBUser^ user = sess->User;
		ret.append_query(L"access_token", sess->AccessTokenData->AccessToken->Data());
		auto preview_uri = ret;
		preview_uri.append_path(L"/picture");
		preview_ = ref new Imaging::BitmapImage(ref new Uri(StringReference(preview_uri.to_string().c_str())));
	}
	return preview_;
}

void App2::AlbumPage::AlbumButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	using namespace pplx;
	AlbumButton->IsEnabled = false;
	facebook_client::instance().get(L"/me/albums")
		.then([](web::json::value v) {
		web::json::object& obj = v.as_object();
		web::json::array objAsArr = obj[L"data"].as_array();
		std::vector<FacebookAlbum^> albums;
		auto iter = v.as_object().cbegin();
		const web::json::value vs = iter->second;
		web::json::array n = vs.as_array();
		for (int i = 0; i < n.size(); i++) {
			web::json::value album = n[i];
			utility::string_t temp = album[L"name"].as_string();
			albums.push_back(ref new FacebookAlbum(
				album[L"name"].as_string(),
				album[L"id"].as_string(),
				album[L"created_time"].as_string()
			));
			utility::string_t str = album[L"id"].as_string();
		}

		return task_from_result(std::move(albums));
	}).then([=](std::vector<FacebookAlbum^> albums) {
		AlbumGrid->ItemsSource = ref new Platform::Collections::Vector<FacebookAlbum^>(std::move(albums));
	}, task_continuation_context::use_current());
}

void App2::AlbumPage::ToUserProfile_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}
