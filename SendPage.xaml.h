//
// SendPage.xaml.h
// Declaration of the SendPage class
//

#pragma once

#include "SendPage.g.h"

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SendPage sealed
	{
	public:
		SendPage();
	private:
		void toUserProfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Send_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
