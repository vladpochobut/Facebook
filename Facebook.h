#pragma once
#include <string>
#include <cpprest/http_client.h>

class facebook_client {
public:
	static facebook_client& instance(); // Singleton
	pplx::task<web::json::value> get(std::wstring path);
	web::http::uri_builder base_uri(bool absolute = false);

private:
	facebook_client() :
		raw_client(L"https://graph.facebook.com/")
		{}

	web::http::client::http_client raw_client;
};
