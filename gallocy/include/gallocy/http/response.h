#ifndef GALLOCY_HTTP_RESPONSE_H_
#define GALLOCY_HTTP_RESPONSE_H_

#include <map>

#include "gallocy/allocators/internal.h"
#include "gallocy/peer.h"

/**
 * A HTTP response.
 */
class Response {
 public:
  // Types
  typedef gallocy::map<
    gallocy::string, gallocy::string>
    Headers;

  // Constructors
  Response();
  Response(const Response&) = delete;
  Response &operator=(const Response&) = delete;

  // Members
  Headers headers;
  gallocy::common::Peer peer;
  gallocy::string body;
  gallocy::string protocol;
  gallocy::string str();
  uint64_t size();
  uint64_t status_code;
};

#endif  // GALLOCY_HTTP_RESPONSE_H_
