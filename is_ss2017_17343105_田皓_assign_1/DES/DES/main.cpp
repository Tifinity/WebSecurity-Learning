#include <iostream>
#include <fstream>
#include "DES.h"

using namespace std;

int main() {
	DES des;
	ifstream in;
	ofstream out;
	int ch = 0;
	int run = 1;
	while (run) {
		cout << "---------------" << endl;
		cout << "1.设置密钥" << endl;
		cout << "2.查看密钥" << endl;
		cout << "3.开始加密" << endl;
		cout << "4.开始解密" << endl;
		cout << "5.退出" << endl;
		cout << "---------------" << endl;
		cin >> ch;
		switch (ch) {
		case 1: {
			cout << des.get_key() << endl;
			cout << "输入密钥:" << endl;
			string keystr = "";
			cin >> keystr;
			des.set_key(keystr);
			cout << "密钥设置成功" << endl;
			break;
		}
		case 2: {
			cout << "当前密钥:" << endl;
			cout << des.get_key() << endl;
			break;
		}
		case 3: {
			cout << "请输入需要加密的文件:" << endl;
			string filename;
			cin >> filename;
			cout << "正在加密" << endl;
			in.open(filename, ios::binary);
			out.open("encrypt-" + filename, ios::binary);
			bitset<64> file_data;
			while (in.read((char*)& file_data, sizeof(file_data))) {
				bitset<64> cipher = des.encrypt(file_data);
				out.write((char*)& cipher, sizeof(cipher));
				file_data.reset();
			}
			in.close();
			out.close();
			cout << "加密成功" << endl;
			break;
		}	
		case 4: {
			cout << "请输入需要解密的文件:" << endl;
			string filename;
			cin >> filename;
			cout << "正在解密" << endl;
			in.open(filename, ios::binary);
			out.open("decrypt-" + filename, ios::binary);
			bitset<64> file_data;
			while (in.read((char*)& file_data, sizeof(file_data))) {
				bitset<64> plain = des.decrypt(file_data);
				out.write((char*)& plain, sizeof(plain));
				file_data.reset();
			}
			in.close();
			out.close();
			cout << "解密成功" << endl;
			break;
		}
		case 5: {
			run = 0;
		}
		default:
			break;
		}
	}
	return 0;
}