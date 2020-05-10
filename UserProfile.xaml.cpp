#include "pch.h"

#include "MainPage.xaml.h"
#include "UserProfile.xaml.h"
#include "PostToFeedPage.xaml.h"
#include "BasicOAuthOperations.h"
#include "SendPage.xaml.h"
#include "AlbumPage.xaml.h"

using namespace App2;
using namespace Platform::Collections;

using namespace Platform;
using namespace concurrency;
using namespace winsdkfb;
using namespace winsdkfb::Graph;
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

UserProfile::UserProfile()
{
	InitializeComponent();
	FBSession^ sess = FBSession::ActiveSession;
	FBUser^ user = sess->User;
	if (sess->LoggedIn)
	{
		// Get current user
		FBUser^ user = sess->User;
		// Set profile pic
		ProfilePic->UserId = user->Id;
	}
	userName->Text = user->FirstName;
	surName->Text = user->LastName;
	email->Text = user->Id;
	gender->Text = user->Gender;
}

void App2::UserProfile::logoutClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BasicOauth::Logout();
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(MainPage::typeid));
}

void App2::UserProfile::sendMessageButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(SendPage::typeid));
}

void App2::UserProfile::PostToFeedButtonClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(PostToFeedPage::typeid));
}

void App2::UserProfile::albumsClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::AlbumPage::typeid));
}
