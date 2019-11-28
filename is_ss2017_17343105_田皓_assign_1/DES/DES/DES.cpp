#include "DES.h"

//IP初始置换表
int DES::IP[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
					60, 52, 44, 36, 28, 20, 12, 4,
					62, 54, 46, 38, 30, 22, 14, 6,
					64, 56, 48, 40, 32, 24, 16, 8,
					57, 49, 41, 33, 25, 17, 9,  1,
					59, 51, 43, 35, 27, 19, 11, 3,
					61, 53, 45, 37, 29, 21, 13, 5,
					63, 55, 47, 39, 31, 23, 15, 7 };

//IP逆置换表
int DES::IP_1[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41,  9, 49, 17, 57, 25
};


//置换选择PC_1
//64bit密钥转为56bit
int DES::PC_1[56] = { 57, 49, 41, 33, 25, 17, 9,
					1, 58, 50, 42, 34, 26, 18,
					10,  2, 59, 51, 43, 35, 27,
					19, 11,  3, 60, 52, 44, 36,
					63, 55, 47, 39, 31, 23, 15,
					7, 62, 54, 46, 38, 30, 22,
					14,  6, 61, 53, 45, 37, 29,
					21, 13,  5, 28, 20, 12,  4 };

//置换选择PC_2
//56bit密钥转为48bit
int DES::PC_2[48] = { 14, 17, 11, 24,  1,  5,
					3, 28, 15,  6, 21, 10,
					23, 19, 12,  4, 26,  8,
					16,  7, 27, 20, 13,  2,
					41, 52, 31, 37, 47, 55,
					30, 40, 51, 45, 33, 48,
					44, 49, 39, 56, 34, 53,
					46, 42, 50, 36, 29, 32 };

//E盒扩展置换表
//将32bit扩展为48bit
int DES::E[48] = { 32,  1,  2,  3,  4,  5,
					4,  5,  6,  7,  8,  9,
					8,  9, 10, 11, 12, 13,
				   12, 13, 14, 15, 16, 17,
				   16, 17, 18, 19, 20, 21,
				   20, 21, 22, 23, 24, 25,
				   24, 25, 26, 27, 28, 29,
				   28, 29, 30, 31, 32,  1 };
//P盒置换表
int DES::P[32] = { 16,  7, 20, 21,
					29, 12, 28, 17,
					1, 15, 23, 26,
					5, 18, 31, 10,
					2,  8, 24, 14,
					32, 27,  3,  9,
					19, 13, 30,  6,
					22, 11,  4, 25 };
//8个S盒置换表
//将48bit压缩为32bit
int DES::S_BOX[8][4][16] = {
	{
		{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
		{0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
		{4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
		{15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
	},
	{
		{15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
		{3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
		{0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
		{13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
	},
	{
		{10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
		{13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
		{13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
		{1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
	},
	{
		{7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
		{13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
		{10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
		{3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
	},
	{
		{2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
		{14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
		{4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
		{11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
	},
	{
		{12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
		{10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
		{9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
		{4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
	},
	{
		{4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
		{13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
		{1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
		{6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
	},
	{
		{13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
		{1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
		{7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
		{2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
	}
};

DES::DES() {
	keystr = "";
}

//加密
bitset<64> DES::encrypt(const bitset<64> & input) {
	bitset<32> left;
	bitset<32> right;
	bitset<32> next;
	bitset<64> output;
	//IP初始置换
	output = IP_replace(input);
	//分为左右两部分
	for (int i = 0; i < 32; i++) {
		left[i] = output[i + 32];
		right[i] = output[i];
	}
	//生成子密钥
	generate_subkeys(key);
	//进行16轮F函数
	for (int i = 0; i < 16; i++) {
		next = right;
		right = left ^ F(right, subkeys[i]);
		left = next;
	}
	//合并
	for (int i = 0; i < 32; i++) {
		output[i] = left[i];
		output[i + 32] = right[i];
	}
	//IP逆置换
	bitset<64> tmp = output;
	output = IP_inverse_replace(tmp);
	return output;
}

//解密
bitset<64> DES::decrypt(const bitset<64> & input) {
	//解密过程从后往前使用子密钥，其余部分与加密完全相同
	bitset<32> left;
	bitset<32> right;
	bitset<32> next;
	bitset<64> output;
	output = IP_replace(input);
	for (int i = 0; i < 32; i++) {
		left[i] = output[i + 32];
		right[i] = output[i];
	}	
	generate_subkeys(key);
	for (int i = 0; i < 16; i++) {
		next = right;
		right = left ^ F(right, subkeys[15 - i]); 
		left = next;
	}
	for (int i = 0; i < 32; i++) {
		output[i] = left[i];
		output[i + 32] = right[i];
	}
	bitset<64> tmp = output;
	output = IP_inverse_replace(tmp);
	return output;
}

//IP置换
bitset<64> DES::IP_replace(const bitset<64> & input) {
	bitset<64> output;
	for (int i = 0; i < 64; i++) {
		output[i] = input[IP[i] - 1];
	}
	return output;
}

//IP逆置换
bitset<64> DES::IP_inverse_replace(const bitset<64> & input) {
	bitset<64> output;
	for (int i = 0; i < 64; i++) {
		output[i] = input[IP_1[i] - 1];
	}
	return output;
}

//Feistel轮函数
bitset<32> DES::F(const bitset<32> & data, const bitset<48> & subkey) {
	//E盒扩展
	bitset<48> expand;
	for (int i = 0; i < 48; i++) {
		expand[i] = data[E[i] - 1];
	}
	//子密钥异或
	expand = expand ^ subkey;
	//S盒压缩
	bitset<32> output;
	for (int i = 0; i < 8; i++) {
		int pos = 47 - i * 6; 
		int row = expand[pos] * 2 + expand[pos - 5];
		int col = expand[pos - 1] * 8 + expand[pos - 2] * 4 + expand[pos - 3] * 2 + expand[pos - 4];
		bitset<4> result(S_BOX[i][row][col]);
		for (int j = 0; j < 4; j++) {
			output[31 - i * 4 - j] = result[3 - j];
		}
	}
	//P盒置换
	bitset<32> tmp = output;
	for (int i = 0; i < 32; i++) {
		output[i] = tmp[P[i] - 1];
	}
	return output;
}

//左移函数
void DES::left_shift(bitset<28> & bits, int shift) {
	bitset<28> temp = bits;
	for (int i = 0; i < 28; ++i) {
		bits[i] = temp[(i - shift + 28) % 28];
	}
}

//生成子密钥
void DES::generate_subkeys(const bitset<64> & key) {
	bitset<56> real_key;
	bitset<28> left;
	bitset<28> right;
	//使用PC_1去掉奇偶校验位并重排
	for (int i = 0; i < 56; i++) {
		real_key[i] = key[PC_1[i] - 1];
	}
	//分为左右两部分
	for (int i = 0; i < 28; ++i) {
		left[i] = real_key[i + 28];
		right[i] = real_key[i];
	}
	//轮次位移表
	int shiftBits[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 }; 
	//进行十六轮
	for (int round = 0; round < 16; round++) {
		left_shift(left, shiftBits[round]);
		left_shift(right, shiftBits[round]);
		//合并左右部分
		for (int i = 0; i < 28; ++i) {
			real_key[i] = right[i];
			real_key[i + 28] = left[i];
		}
		//使用PC_2重排并压缩为48位
		for (int j = 0; j < 48; j++) {
			subkeys[round][47 - j] = real_key[56 - PC_2[j]];
		}
	}
}

bitset<64> DES::chars_to_bitset(const char s[8]) {
	bitset<64> bits;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			bits[i * 8 + j] = ((s[7 - i] >> j) & 1);
		}
	}
	return bits;
}

char* DES::bitset_to_chars(const bitset<64> bits) {
	char s[8];
	bitset<8> c;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			c[j] = bits[i * 8 + j];
		}
		s[7 - i] = c.to_ulong();
	}
	return s;
}

void DES::set_key(string keystr) {
	this->keystr = keystr;
	key = chars_to_bitset(keystr.c_str());
}

string DES::get_key() {
	return keystr;
}