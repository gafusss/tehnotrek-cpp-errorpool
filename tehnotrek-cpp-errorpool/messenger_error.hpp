#pragma once

#include <system_error>

namespace messenger_error
{
	enum class messenger_error_t : int
	{
		ok = -1,
		connection_error,
		server_untrusted,
		server_connection_error,
		server_internal_error,
		client_untrusted,
		server_protocol_version_mismatch,
		authorization_failure,
		contact_protocol_version_mismatch
	};

	class messenger_category_impl : public std::error_category
	{
	public:
		const char* name() const noexcept override
		{
			return "messenger";
		}

		std::string message(int ev) const override
		{
			switch (ev)
			{
			case static_cast<int>(messenger_error_t::ok) : return "Ok";
			case static_cast<int>(messenger_error_t::connection_error) : return "Can't connect to server";
			case static_cast<int>(messenger_error_t::server_untrusted) : return "Unknown server identity";
			case static_cast<int>(messenger_error_t::server_connection_error) : return "Server-side connection error";
			case static_cast<int>(messenger_error_t::server_internal_error) : return "Server internal error";
			case static_cast<int>(messenger_error_t::client_untrusted) : return "Unknown client identity";
			case static_cast<int>(messenger_error_t::server_protocol_version_mismatch) : return "Couldn't negotiate protocol version with server";
			case static_cast<int>(messenger_error_t::authorization_failure) : return "Authorizarion failure";
			case static_cast<int>(messenger_error_t::contact_protocol_version_mismatch) : return "Couldn't negotiate protocol version with client";
			default: return "Unknown error";
			}
		}
	};

	inline const std::error_category& message_category()
	{
		static messenger_category_impl instance;
		return instance;
	}

	inline std::error_code make_error_code(messenger_error_t ec) noexcept
	{
		return std::error_code(static_cast<int>(ec), message_category());
	}

	inline std::error_condition make_error_condition(messenger_error_t ec) noexcept
	{
		return std::error_condition(static_cast<int>(ec), message_category());
	}
}

namespace std
{
	template <>
	struct is_error_code_enum<messenger_error::messenger_error_t> : public true_type { };
}