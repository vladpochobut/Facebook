//
// PostToFeedPage.xaml.cpp
// Implementation of the PostToFeedPage class
//

#include "pch.h"
#include "UserProfile.xaml.h"
#include "PostToFeedPage.xaml.h"
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

PostToFeedPage::PostToFeedPage()
{
	InitializeComponent();
}


void App2::PostToFeedPage::toUserProfile_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}


void App2::PostToFeedPage::Post_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BasicOauth::PostToFeed(link->Text);
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}
