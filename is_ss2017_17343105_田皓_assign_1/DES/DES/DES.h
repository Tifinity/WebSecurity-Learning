#pragma once
#include <bitset>
#include <string>
using namespace std;

class DES {
private:
	bitset<64> key;        //密钥
	string keystr;         //密钥
	bitset<48> subkeys[16];//子密钥
	static int IP[64];     //IP初始置换表
	static int IP_1[64];   //IP逆置换表
	
	//生成子密钥所用置换表
	static int PC_1[56];   //PC_1置换表
	static int PC_2[48];   //PC_2置换表

	//密码函数F所用置换表
	static int E[48];      //E盒
	static int P[32];      //P盒
	static int S_BOX[8][4][16]; //8个S盒

	// IP置换
	bitset<64> IP_replace(const bitset<64> & plain);
	// IP逆置换
	bitset<64> IP_inverse_replace(const bitset<64> & bits);
	// Feistel轮函数
	bitset<32> F(const bitset<32> & right, const bitset<48> & subKey);
	// 生成子密钥
	void generate_subkeys(const bitset<64> & key);
	//左移
	void left_shift(bitset<28> & bits, int shift);
	//char转换为bitset
	bitset<64> chars_to_bitset(const char s[8]);
	//bitset转换为char
	char* bitset_to_chars(const bitset<64> bits);

public:
	DES();
	//加密
	bitset<64> encrypt(const bitset<64> & plain);
	//解密
	bitset<64> decrypt(const bitset<64> & plain);

	//设置密钥
	void set_key(string keystr);
	string get_key();
};
