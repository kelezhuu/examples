#include "my_service.grpc.pb.h"
#include <bits/stdc++.h>
#include <grpcpp/grpcpp.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using myservice::MyRequest;
using myservice::MyResponse;
using myservice::MyService;

class MyServiceImpl final : public MyService::Service {
  Status SayHello(ServerContext *context, const MyRequest *request,
                  MyResponse *reply) override {
    std::string prefix("hello ");
    reply->set_greeting(prefix + request->name());
    return Status::OK;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  MyServiceImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on" << server_address << std::endl;
  server->Wait();
}

int main() {
  RunServer();
  return 0;
}
