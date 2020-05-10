//
// SendPage.xaml.cpp
// Implementation of the SendPage class
//

#include "pch.h"
#include "SendPage.xaml.h"
#include "UserProfile.xaml.h"
#include "BasicOAuthOperations.h"

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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

SendPage::SendPage()
{
	InitializeComponent();
}


void App2::SendPage::toUserProfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}


void App2::SendPage::Send_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BasicOauth::ShowSendDialog(link->Text, userID->Text);
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}