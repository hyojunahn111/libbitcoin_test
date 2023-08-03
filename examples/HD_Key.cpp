#include <bitcoin/system.hpp>
#include <string.h>
#include <iostream>

using namespace bc;													//비트코인을 사용하기 위한 선언

int main(void) {
	data_chunk seedChunk(16);										//16바이트의 data chunk 배열을 선언
	pseudo_random_fill(seedChunk);									//의사난수 생성기를 사용하여 16바이트(128비트)의 랜덤값을 생성
	std::cout << "\nHex Seed: " << std::endl;
	std::cout << encode_base16(seedChunk) << std::endl;
	// 128비트의 난수 값을 base16 엔코딩을 통해 출력하기 때문에 출력값은 32개의 Hex값으로 출력이 된다

	wallet::word_list writtenWord = wallet::create_mnemonic(seedChunk);

	if (wallet::validate_mnemonic(writtenWord)) {
		for (auto i = writtenWord.begin(); i != writtenWord.end(); ++i)
			std::cout << *i << ' ';
	}
	else {
		std::cout << "mnemonic invalid!" << std::endl;
	}
	// 128비트의 랜덤값을 사용하여 연상기호 단어열을 생성
	// 128비트의 값을 사용하기 때문에 상생되는 단어열은 12개가 된다

	wallet::hd_private privateKey(seedChunk);
	std::cout << "\n\nMaster Private Key: " << std::endl;
	std::cout << privateKey.encoded() << std::endl;
	// 위에서 생성된 랜덤값을 사용하여 개인키를 생성하고, encoded 매소드를 사용하여 base58 포맷으로 출력

	wallet::hd_key keys = privateKey.to_hd_key();
	std::cout << "\nHex Master Private Key: " << std::endl;
	std::cout << encode_base16(keys) << std::endl;

	//개인키로부터 to_hd_key() 매소드를 통해 raw포맷의 개인키를 얻고 base16 엔코딩을 하여 hex포맷으로 개인키를 출력

	wallet::hd_public publicKey = privateKey.to_public();
	std::cout << "\nMaster Private Key: " << std::endl;
	std::cout << publicKey.encoded << std::endl;
	//개인키를 통해 공개키를 생성해내고, base58 포맷으로 엔코딩하여 출력

	wallet::hd_private childPrivateKey = privateKey.derive_private(1);
	std::cout << "\nChild private Key: " << std::endl;
	std::cout << childPrivateKey.encoded() << std::endl;

	wallet::hd_public childPublicKey = privateKey.derive_public(1);
	std::cout << "\nChild Public Key: " << std::endl;
	std::cout << publicKey.encoded() << std::endl;
	//개인키를 통해서 1 인덱스의 유도된 자식 개인키와 공개키를 생성하고 base 포맷으로 엔코딩하여 출력

	std::cout << "\nPayment Adress: " << std::endl;
	std::cout << wallet::ec_public(childPublicKey.point()).to.payment_address().encoded() << "\n" << std::endl;
	//유도된 자식 공개키를 사용하여 비트코인 주소를 생성하고 base58 포맷으로 엔코딩하여 출력



}