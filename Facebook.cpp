#include "pch.h"
#include "facebook.h"

using namespace pplx;
using namespace web;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Security::Authentication::Web;
using namespace Windows::Storage;
using namespace Windows::Foundation::Collections;
using namespace concurrency;
using namespace winsdkfb;
using namespace winsdkfb::Graph;

facebook_client& facebook_client::instance()
{
	static facebook_client c;
	return c;
}

task<json::value> facebook_client::get(std::wstring path)
{
	using namespace http;
	http_request request(methods::GET);
	request.set_request_uri(base_uri().append_path(path).to_uri());
	request.headers().add(header_names::accept, L"application/json");
	return raw_client.request(request)
		.then([](http_response response) {
		return response.extract_json();
	});
}

http::uri_builder facebook_client::base_uri(bool absolute)
{
	http::uri_builder ret;
	FBSession^ sess = FBSession::ActiveSession;
	if (absolute)
		ret.set_path(L"https://graph.facebook.com");
	const wchar_t *acc = sess->AccessTokenData->AccessToken->Data();
	ret.append_query(L"access_token", sess->AccessTokenData->AccessToken->Data());
	return ret;
}
