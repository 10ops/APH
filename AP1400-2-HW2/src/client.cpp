#include "client.h"

	std::string generate_new_id(std::string id) {
		unsigned int x = rand() % 10000;
		std::string res = id + std::to_string(x).c_str();
		return res;
	}

	std::string get_new_id(std::string id, const Server &server) {
		std::shared_ptr<Client> sh = server.get_client(id);
		std::string new_id = id;
		while (sh != std::shared_ptr<Client>()) {
			id = new_id;
			new_id = generate_new_id(id);
			sh = server.get_client(new_id);
		}
		return new_id;
	}

	Client::Client(std::string id, const Server& server) : id(get_new_id(id, server)), server(&server) {
		// generate public key and private key
		std::string pbc_key{}, pvt_key{};
		crypto::generate_key(pbc_key, pvt_key);
		public_key = pbc_key;
		private_key = pvt_key;
	}
	
	std::string Client::get_id() const {
		return id;
	}

	std::string Client::get_publickey() const {
		return public_key;
	}
	
	double Client::get_wallet() {
		return server->get_wallet(id);
	}

	std::string Client::sign(std::string txt) const {
		std::string signature = crypto::signMessage(private_key, txt);
		return signature;
	}

	bool Client::transfer_money(std::string receiver, double value) {
		std::string trx = id + "-" + receiver + "-" + std::to_string(value);
		std::string trx_signature = crypto::signMessage(private_key, trx);
		bool tag = server->add_pending_trx(trx, trx_signature);
		return tag;
	}

	std::size_t Client::generate_nonce() {
		return rand();
	}
