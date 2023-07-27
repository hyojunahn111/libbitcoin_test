#include <bitcoin/bitcoin.hpp>
#include <string>
#include <iostream>

using namespace bc;

class HD_Wallet
{
public:

	// Constructor
	HD_Wallet(const data_chunk Userentropy);
	// ù�� ° �����ڴ� �ǻ糭�� �����⸦ ����Ͽ� ������ ������ ����Ͽ� �����ȣ �ܾ�� �����, �ش� �ܾ�� ����Ͽ� seed�� �����Ͽ�, ����Ű�� ����Ű�� ����


	HD_Wallet(const wallet::word_list mnemonicSeed);
	// �ι� ° �����ڴ� �̹� ������� �����ȣ �ܾ�� ����Ͽ� seed�� �����ϰ� ����Ű�� ����Ű�� ����


private:
	// Members
	data_chunk entropy;
	data_chunk seed;
	wallet::word_list mnemonic;
	wallet::hd_private privateKey;
	wallet::hd_public publicKey;
	//�̿� ���� ������ ���� Ŭ������ �ϱ�� ���� ��������, seed, �����ȣ �ܾ, ����Ű, ����Ű�� �ɹ��� ������ ����


public:
	// Child key
	wallet::hd_private childPrivateKey(int index)
	{
		return privateKey.derive_private(index);
	}

	wallet::hd_public childPublicKey(int index)
	{
		return publicKey.derive_public(index);
	}

	wallet::payment_address childAddress(int index)
	{
		return wallet::ec_public(childPublicKey(index).point()).to_payment_address();
	}
	// �ڽ�Ű ������ ���� �ε��� ���� ���ڷ� �޾Ƽ� ������ �ڽ�Ű�� ����Ű�� ����Ű, �ּҸ� �����ϴ� �żҵ�
	// �ε����� ������ ����Ű�� ����Ͽ� �����Ǵ� �ڽ��� �ε�����, ���������� ���������� �̿Ͱ��� �������� �ε����� �÷�����, �ڽ�Ű, ����Ű�� ������ �� ����


	// Display
	void displayPrivateKey()
	{
		std::cout << "\nPrivate Key:" << privateKey.encoded() << std::endl;
	}

	void displayChildPrivateKey(int index)
	{
		std::cout << "\nChild Key: " << childPrivateKey(index).encoded() << std::endl;
	}

	void displayAddress(int index)
	{
		std::cout << "\nAddress: " << childAddress(index).encoded() << std::endl;
	}

	void addressRange(int start, int end)
	{
		while (start != end)
		{
			displayAddress(start);
			start++;
		}
	}
	//�� Ű ���� ȭ��� ����ϱ� ���� �żҵ�

	void displayMnemonic()
	{
		if (wallet::validate_mnemonic(mnemonic))
		{
			std::string mnemonicString = join(mnemonic);
			std::cout << "\n" << mnemonicString << std::endl;

		}
		else {
			std::cout << "mnemonic invalid!" << std::endl;
		}
	}
	// seed ���� ����Ͽ� ������ �����ȣ �ܾ�� ����ϴ� �żҵ�

	void dumpKeys()
	{
		displayMnemonic();
		displayPrivateKey();
		displayChildPrivateKey(1);
		displayAddress(1);

	}
	//������ Ŭ������ ��� ������ ����ϴ� �żҵ�
	//�ϱ� �żҵ带 ���ؼ� ������ �ܾ�� ������ ����Ű, ������ �ڽ��� ����Ű�� �ּҸ� ���
};

// Constructor

inline HD_Wallet::HD_Wallet(const data_chunk Userentropy)										//HD_WalletŬ���� ����, ������ ����
{
	entropy = Userentropy;
	mnemonic = wallet::create_mnemonic(entropy);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	privateKey = wallet::hd_private(seed);
	publicKey = privateKey.to_public();
}

inline HD_Wallet::HD_Wallet(const wallet::word_list mnemonicSeed)								//������ ����
{
	seed = to_chunk(wallet::decode_mnemonic(mnemonicSeed));
	mnemonic = mnemonicSeed;
	privateKey = wallet::hd_private(seed);
	publicKey = privateKey.to_public();
}
