//
// PostToFeedPage.xaml.h
// Declaration of the PostToFeedPage class
//

#pragma once

#include "PostToFeedPage.g.h"

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class PostToFeedPage sealed
	{
	public:
		PostToFeedPage();
	private:
		void toUserProfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Post_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
