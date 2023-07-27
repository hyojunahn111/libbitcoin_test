#include <bitcoin/bitcoin.hpp>
#include <string>
#include <iostream>

using namespace bc;

class HD_Wallet
{
public:

	// Constructor
	HD_Wallet(const data_chunk Userentropy);
	// 첫번 째 생성자는 의사난수 생성기를 사용하여 생성된 난수를 사용하여 연상기호 단어열을 만들고, 해당 단어열을 사용하여 seed를 생성하여, 개인키와 공개키를 생성


	HD_Wallet(const wallet::word_list mnemonicSeed);
	// 두번 째 생성자는 이미 만들어진 연상기호 단어열을 사용하여 seed를 생성하고 개인키와 공개키를 생성


private:
	// Members
	data_chunk entropy;
	data_chunk seed;
	wallet::word_list mnemonic;
	wallet::hd_private privateKey;
	wallet::hd_public publicKey;
	//이와 같은 동작을 위해 클래스는 하기와 같은 랜덤값과, seed, 연상기호 단어열, 개인키, 공개키의 맴버를 가지고 있음


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
	// 자식키 생성을 위한 인덱스 값을 인자로 받아서 유도된 자식키의 개인키와 공개키, 주소를 생성하는 매소드
	// 인덱스는 마스터 개인키를 사용하여 유도되는 자식의 인덱스로, 계층결정적 지갑에서는 이와같이 계층별로 인덱스를 늘려가며, 자식키, 손자키를 생성할 수 있음


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
	//각 키 값을 화면상에 출력하기 위한 매소드

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
	// seed 값을 사용하여 생성된 연상기호 단어열을 출력하는 매소드

	void dumpKeys()
	{
		displayMnemonic();
		displayPrivateKey();
		displayChildPrivateKey(1);
		displayAddress(1);

	}
	//생성된 클래스의 모든 정보를 출력하는 매소드
	//하기 매소드를 통해서 연상기로 단어열과 마스터 개인키, 유도된 자식의 개인키와 주소를 출력
};

// Constructor

inline HD_Wallet::HD_Wallet(const data_chunk Userentropy)										//HD_Wallet클래스 정의, 생성자 생성
{
	entropy = Userentropy;
	mnemonic = wallet::create_mnemonic(entropy);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	privateKey = wallet::hd_private(seed);
	publicKey = privateKey.to_public();
}

inline HD_Wallet::HD_Wallet(const wallet::word_list mnemonicSeed)								//생성자 생성
{
	seed = to_chunk(wallet::decode_mnemonic(mnemonicSeed));
	mnemonic = mnemonicSeed;
	privateKey = wallet::hd_private(seed);
	publicKey = privateKey.to_public();
}
