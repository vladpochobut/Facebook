#include "pch.h"

#include "MainPage.xaml.h"
#include "UserProfile.xaml.h"
#include "BasicOAuthOperations.h"


using namespace App2;
using namespace concurrency;
using namespace winsdkfb;
using namespace winsdkfb::Graph;
using namespace Platform::Collections;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Security::Authentication::Web;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
	String^ SID = WebAuthenticationBroker::GetCurrentApplicationCallbackUri()->DisplayUri;
	BasicOauth::Initialization();
}


void MainPage::loginClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	BasicOauth::Login();
	FBSession^ sess = FBSession::ActiveSession;
	if (sess->LoggedIn) {
		Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
//		BasicOauth::UploadInbox();
	}
}

void App2::MainPage::changeUserClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	FBSession^ sess = FBSession::ActiveSession;
	if (sess->LoggedIn)
		BasicOauth::Logout();
	if (!sess->LoggedIn)
		BasicOauth::Login();
	if (sess->LoggedIn)
		Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(App2::UserProfile::typeid));
}
