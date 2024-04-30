#include "server.h"

std::vector<std::string> pending_trxs;

void show_wallets(const Server &server) {
	std::cout << std::string(20, '*') << std::endl;
	for (const auto &client: server.clients) {
		std::cout << client.first->get_id() << " : " << client.second << std::endl;
	}
	std::cout << std::string(20, '*') << std::endl;
}

	std::string Server::create_mempool(std::vector<std::string> vec) {
		if (vec.size() == 0) {
			return "";
		}
		if (vec.size() == 1) {
			return *vec.begin();
		}
		auto begin = vec.begin();
		std::string str = *begin;
		vec.erase(begin);
		begin = vec.begin();
		auto end = vec.end();
		while (begin != end) {
			str = str.c_str() + (*begin);
			vec.erase(begin);
			begin = vec.begin();
			end = vec.end();
		}
		return str;
	}

	void Server::add_coins(std::shared_ptr<Client> sh, double value) {
		clients[sh] += value;
	}
	
	void Server::exec_trxs(std::vector<std::string> &pending_trxs) {
		std::string sender, receiver;
		double wallet;
		std::cout << pending_trxs.size() << std::endl;
		for (auto i = pending_trxs.begin(); i != pending_trxs.end(); ++i) {
			parse_trx(*i, sender, receiver, wallet);
			Server::add_coins(Server::get_client(sender), -wallet);
			Server::add_coins(Server::get_client(receiver), wallet);
		}
		while (pending_trxs.begin() != pending_trxs.end()) {
			pending_trxs.erase(pending_trxs.begin());
		}
	}

	Server::Server() = default;
	
	std::shared_ptr<Client> Server::add_client(std::string id) {
		std::shared_ptr<Client> shClient(new Client(id, *this));
		clients[shClient] = 5.0;
		return shClient;
	}
	
	std::shared_ptr<Client> Server::get_client(std::string id) const {
		for (auto it = clients.begin(); it != clients.end(); ++it) {
			if (it->first->get_id() == id) {
				return it->first;
			}
		}
		return std::shared_ptr<Client>();
	}

	double Server::get_wallet(std::string id) const {
		std::shared_ptr<Client> sh = Server::get_client(id);
		for (auto i = clients.begin(); i != clients.end(); ++i) {
			if (i->first == sh) {
				return i->second;
			}
		}
		return 0;
	}

	bool parse_trx(std::string trx, std::string &sender, std::string &receiver, double &value) {
		// regular expression pattern the trx
		std::regex re("^([a-z||A-Z||0-9||_]+\\-){2}[0-9]+\\.?[0-9]*$");
		std::cmatch m;
		bool tag = std::regex_match(trx.c_str(), m, re);

		// it is right format of a transaction
		if (tag == true) {

			// further dispose
			std::regex sub("[a-z||A-Z||0-9||_]+");
			auto trx_begin = std::sregex_iterator(trx.begin(), trx.end(), sub);
			auto trx_end = std::sregex_iterator();
			std::vector<std::string> match_str;
			for (std::sregex_iterator i = trx_begin; i != trx_end; ++ i) {
				std::smatch match = *i;
				match_str.push_back(match.str());
			}

			// receive value
			sender = *match_str.begin();
			match_str.erase(match_str.begin());
			receiver = *match_str.begin();
			match_str.erase(match_str.begin());
			if (match_str.size() == 2) {
				match_str[0] = match_str[0] + "." + match_str[1];
			}
			value = std::stof(*match_str.begin());
		}		
		else {
			throw std::runtime_error("error");
		}
		return tag;
	}

	bool Server::add_pending_trx(std::string trx, std::string signature) const {
		std::string sender, receiver;
		double coins;
		parse_trx(trx, sender, receiver, coins);
		// verify signature and confirm has enough coins
		std::shared_ptr<Client> cl = Server::get_client(sender);
		if (Server::get_client(receiver) == std::shared_ptr<Client>()) {
			return false;
		}
		if (!crypto::verifySignature( cl->get_publickey(), trx, signature) || Server::get_wallet(sender) < coins) {
			return false;
		}
		pending_trxs.push_back(trx);
		return true;
	}

	std::size_t Server::mine() {
		// create mempool
		std::string alltrx = Server::create_mempool(pending_trxs);
		// for every client
		while (true) {
		for (auto i = clients.begin(); i != clients.end(); ++i) {
			// add a number at the end of this string
			std::shared_ptr<Client> sh = i->first;
			std::size_t res = sh->generate_nonce();
			std::string mempool = alltrx.c_str() + std::to_string(res);

			// calculate the sha256
			std::string sha256_val = crypto::sha256(mempool);

			if (sha256_val.substr(0, 10).find("000") != std::string::npos) {
				std::cout << sh->get_id() << std::endl;
				Server::add_coins(sh, 6.25);
				Server::exec_trxs(pending_trxs);
				return res;
			}

			/*
			// judgement whether content the condition, ten numbers have 4 zeros
			for (auto it = sha256_val.begin(); it != sha256_val.end(); ++it) {
				int count_z = 0, count_n = 0;
				if (std::isdigit(*it)) {
					count_n ++;
					if ((*it) == '0') {	
					count_z ++;
					}
				}
			// ok then print the information: id of miner and return nonce
				if (count_z == 3) {
					std::cout << sh->get_id() << std::endl;
					Server::add_coins(sh, 6.25);
					Server::exec_trxs(pending_trxs);
					return res;
				}
				if (count_n == 10) {
					break;
				}
			}
			*/
		}
		}
	}
