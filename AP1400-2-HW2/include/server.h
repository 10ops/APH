
#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <regex>
#include "client.h"

class Client;

class Server
{
public:
	Server();
	std::shared_ptr<Client> add_client(std::string id);
	std::shared_ptr<Client> get_client(std::string id) const;
	double get_wallet(std::string id) const;
	bool add_pending_trx(std::string trx, std::string signature) const;
	std::size_t mine();
friend void show_wallets(const Server &server);
private:
	std::map<std::shared_ptr<Client>, double> clients;
	std::string create_mempool(std::vector<std::string> vec);
	void add_coins(std::shared_ptr<Client> sh, double value);
	void exec_trxs(std::vector<std::string> &pending_trxs);
};

bool parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value);
	
extern std::vector<std::string> pending_trxs;

#endif //SERVER_H
