#ifndef GALLOCY_UTILS_CONFIG_H_
#define GALLOCY_UTILS_CONFIG_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "gallocy/allocators/internal.h"
#include "gallocy/common/peer.h"


/**
 * The gallocy configuration.
 *
 * As of today, exists soley to hide the ugly fucking handling of
 * nlohmann::json implicit converstion issues from the rest of the application.
 */
class GallocyConfig {
 public:
  /**
   * Create a configuration.
   *
   * \param address This node's internet address.
   * \param peers This node's peer list.
   * \param port This node's port.
   */
  GallocyConfig(const gallocy::string &address,
                const gallocy::vector<gallocy::common::Peer> &peer_list,
                uint16_t port)
    : address(address),
      peer_list(peer_list),
      port(port) {}

  /**
   * Create a configuration.
   *
   * \param config_json A JSON object with keys for "self", "port", and "peers".
   */
  explicit GallocyConfig(gallocy::json config_json) {
    port = config_json["port"];

    // TODO(sholsapp): Gah, this is driving me insane, we need to fix this
    // implicit converstion nightmare.
    gallocy::json::string_t _address = config_json["self"];
    address = _address.c_str();

    for (gallocy::json::string_t peer_ip_string : config_json["peers"]) {
      peer_list.push_back(gallocy::common::Peer(peer_ip_string.c_str(), port));
    }
  }

 public:
  gallocy::string address;
  gallocy::vector<gallocy::common::Peer> peer_list;
  uint16_t port;
};


GallocyConfig *load_config(const gallocy::string &);

#endif  // GALLOCY_UTILS_CONFIG_H_
