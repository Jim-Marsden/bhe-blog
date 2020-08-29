#define RESTINIO_TEST_ON
#ifdef RESTINIO_TEST_ON
#include <restinio/all.hpp>
#define CATCH_CONFIG_RUNNER // Configure catch to use your main, and not its own.
#include <catch2/catch.hpp>


restinio::request_handling_status_t handler(restinio::request_handle_t req) {
  if (restinio::http_method_get() == req->header().method())
    //if (req->header().request_target() == "/" || req->header().request_target() == "/home") {
      req->create_response()
          .append_header(restinio::http_field::server, "RESTinio hello world server")
          .append_header_date_field()
          .append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
          .set_body(req->header().request_target())
          .done();
      return restinio::request_accepted();

  return restinio::request_rejected();
}


int main(int argc, char ** argv) {
  auto const  test_result = Catch::Session().run(argc, argv);

  restinio::run(
      restinio::on_this_thread()
          .port(8080).address("localhost")
          .request_handler(handler));

  return 0;
}
#else
#include <boost/beast/http.hpp>
using namespace boost::beast::http;


#include <cstdlib>
int main(int argc, char ** argv) {
  auto const  test_result = Catch::Session().run(argc, argv);
  return EXIT_SUCCESS;
}
#endif