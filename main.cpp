#include <restinio/all.hpp>

restinio::request_handling_status_t handler(restinio::request_handle_t req) {
  if (restinio::http_method_get() == req->header().method() &&
      req->header().request_target() == "/") {
    req->create_response()
        .append_header(restinio::http_field::server, "RESTinio hello world server")
        .append_header_date_field()
        .append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
        .set_body("Hello world!")
        .done();
    return restinio::request_accepted();
  }
  return restinio::request_rejected();
}

int main() {
  restinio::run(
      restinio::on_this_thread()
          .port(8080).address("localhost")
          .request_handler(handler));

  return 0;
}