#include <bitcoin/system.hpp>
#include <string.h>
#include <iostream>

using namespace bc;													//��Ʈ������ ����ϱ� ���� ����

int main(void) {
	data_chunk seedChunk(16);										//16����Ʈ�� data chunk �迭�� ����
	pseudo_random_fill(seedChunk);									//�ǻ糭�� �����⸦ ����Ͽ� 16����Ʈ(128��Ʈ)�� �������� ����
	std::cout << "\nHex Seed: " << std::endl;
	std::cout << encode_base16(seedChunk) << std::endl;
	// 128��Ʈ�� ���� ���� base16 ���ڵ��� ���� ����ϱ� ������ ��°��� 32���� Hex������ ����� �ȴ�

	wallet::word_list writtenWord = wallet::create_mnemonic(seedChunk);

	if (wallet::validate_mnemonic(writtenWord)) {
		for (auto i = writtenWord.begin(); i != writtenWord.end(); ++i)
			std::cout << *i << ' ';
	}
	else {
		std::cout << "mnemonic invalid!" << std::endl;
	}
	// 128��Ʈ�� �������� ����Ͽ� �����ȣ �ܾ�� ����
	// 128��Ʈ�� ���� ����ϱ� ������ ����Ǵ� �ܾ�� 12���� �ȴ�

	wallet::hd_private privateKey(seedChunk);
	std::cout << "\n\nMaster Private Key: " << std::endl;
	std::cout << privateKey.encoded() << std::endl;
	// ������ ������ �������� ����Ͽ� ����Ű�� �����ϰ�, encoded �żҵ带 ����Ͽ� base58 �������� ���

	wallet::hd_key keys = privateKey.to_hd_key();
	std::cout << "\nHex Master Private Key: " << std::endl;
	std::cout << encode_base16(keys) << std::endl;

	//����Ű�κ��� to_hd_key() �żҵ带 ���� raw������ ����Ű�� ��� base16 ���ڵ��� �Ͽ� hex�������� ����Ű�� ���

	wallet::hd_public publicKey = privateKey.to_public();
	std::cout << "\nMaster Private Key: " << std::endl;
	std::cout << publicKey.encoded << std::endl;
	//����Ű�� ���� ����Ű�� �����س���, base58 �������� ���ڵ��Ͽ� ���

	wallet::hd_private childPrivateKey = privateKey.derive_private(1);
	std::cout << "\nChild private Key: " << std::endl;
	std::cout << childPrivateKey.encoded() << std::endl;

	wallet::hd_public childPublicKey = privateKey.derive_public(1);
	std::cout << "\nChild Public Key: " << std::endl;
	std::cout << publicKey.encoded() << std::endl;
	//����Ű�� ���ؼ� 1 �ε����� ������ �ڽ� ����Ű�� ����Ű�� �����ϰ� base �������� ���ڵ��Ͽ� ���

	std::cout << "\nPayment Adress: " << std::endl;
	std::cout << wallet::ec_public(childPublicKey.point()).to.payment_address().encoded() << "\n" << std::endl;
	//������ �ڽ� ����Ű�� ����Ͽ� ��Ʈ���� �ּҸ� �����ϰ� base58 �������� ���ڵ��Ͽ� ���



}