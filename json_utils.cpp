#include "json_utils.h"

void to_json(json& j, const host_info& host) {
	j = json {
		{"Name", host.name},
		{"MAC_Address", host.MAC},
		{"IPv4", host.IPv4},
	};
}

void from_json(const json& j, host_info& host) {
	j.at("Name").get_to(host.name);
	j.at("MAC_Address").get_to(host.MAC);
	j.at("IPv4").get_to(host.IPv4);
}
