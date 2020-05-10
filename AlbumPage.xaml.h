//
// AlbumPage.xaml.h
// Declaration of the AlbumPage class
//

#pragma once

#include "AlbumPage.g.h"
#include <cpprest\http_client.h>

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AlbumPage sealed
	{
	public:
		AlbumPage();
	private:
		void AlbumButton_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void ToUserProfile_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};

	[Windows::UI::Xaml::Data::Bindable]
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class FacebookAlbum sealed
	{
	internal:
		FacebookAlbum(std::wstring title, std::wstring date, std::wstring id/*, std::wstring photo_id/*, int count*/) :
			title_(title), created(date), id_(id)/*, photo_id_(photo_id)*/ {}
	public:
		property Platform::String^ Title {
			Platform::String^ get();
		}
		property Platform::String^ ID {
			Platform::String^ get();
		}
		property Windows::UI::Xaml::Media::ImageSource^ Preview {
			Windows::UI::Xaml::Media::ImageSource^ get();
		}
	private:
		std::wstring created;
		std::wstring title_;
		std::wstring photo_id_;
		std::wstring id_;
		Windows::UI::Xaml::Media::ImageSource^ preview_;
	};
}