#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/websocket.hpp>

using namespace boost::asio;
using namespace boost::beast;
using namespace boost::beast::websocket;

// メッセージ
struct Message {
  std::string type;
  std::string data;
};

// SSE 送信
void send_sse(streambuf& b, const Message& msg) {
  http::response<http::string_body> res;
  res.set(http::field::content_type, "text/event-stream");
  res.set(http::field::cache_control, "no-cache");
  res.body() << "event: " << msg.type << "\n"
            << "data: " << msg.data << "\n\n";
  res.prepare_payload();
  b.commit(res);
}

// POST リクエスト処理
void handle_post(streambuf& b, const http::request<http::string_body>& req) {
  // リクエストボディ取得
  std::string body = req.body();

  // メッセージパース
  Message msg;
  msg.type = "message";
  msg.data = body;

  // SSE 送信
  send_sse(b, msg);
}

// GET リクエスト処理
void handle_get(streambuf& b, const http::request<http::empty_body>& req) {
  // SSE 送信
  send_sse(b, Message{"open", ""});

  // 接続維持
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    send_sse(b, Message{"ping", ""});
  }
}

int main() {
  // ソケット設定
  io_context ioc;
  ip::tcp::endpoint endpoint(ip::address::from_string("0.0.0.0"), 8080);

  // WebSocket サーバー
  websocket::server<streambuf> server(ioc, endpoint);

  // リクエストハンドラ設定
  server.set_open_handler([](websocket::streambuf& b) {
    std::cout << "WebSocket 接続開始" << std::endl;
  });

  server.set_close_handler([](websocket::streambuf& b) {
    std::cout << "WebSocket 接続終了" << std::endl;
  });

  server.set_message_handler([&](websocket::streambuf& b,
                                  websocket::message_data& msg) {
    // メッセージ処理
    std::string message = boost::beast::buffers_to_string(msg.data());
    std::cout << "受信メッセージ: " << message << std::endl;

    // POST リクエスト
    if (msg.opcode() == websocket::opcode::text) {
      http::request<http::string_body> req;
      http::read(b, req);
      handle_post(b, req);
    }
  });

  // サーバ起動
  server.run();

  return 0;
}