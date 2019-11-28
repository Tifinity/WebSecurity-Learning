#pragma once
#include <bitset>
#include <string>
using namespace std;

class DES {
private:
	bitset<64> key;        //��Կ
	string keystr;         //��Կ
	bitset<48> subkeys[16];//����Կ
	static int IP[64];     //IP��ʼ�û���
	static int IP_1[64];   //IP���û���
	
	//��������Կ�����û���
	static int PC_1[56];   //PC_1�û���
	static int PC_2[48];   //PC_2�û���

	//���뺯��F�����û���
	static int E[48];      //E��
	static int P[32];      //P��
	static int S_BOX[8][4][16]; //8��S��

	// IP�û�
	bitset<64> IP_replace(const bitset<64> & plain);
	// IP���û�
	bitset<64> IP_inverse_replace(const bitset<64> & bits);
	// Feistel�ֺ���
	bitset<32> F(const bitset<32> & right, const bitset<48> & subKey);
	// ��������Կ
	void generate_subkeys(const bitset<64> & key);
	//����
	void left_shift(bitset<28> & bits, int shift);
	//charת��Ϊbitset
	bitset<64> chars_to_bitset(const char s[8]);
	//bitsetת��Ϊchar
	char* bitset_to_chars(const bitset<64> bits);

public:
	DES();
	//����
	bitset<64> encrypt(const bitset<64> & plain);
	//����
	bitset<64> decrypt(const bitset<64> & plain);

	//������Կ
	void set_key(string keystr);
	string get_key();
};
