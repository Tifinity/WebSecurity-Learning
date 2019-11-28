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
		cout << "1.������Կ" << endl;
		cout << "2.�鿴��Կ" << endl;
		cout << "3.��ʼ����" << endl;
		cout << "4.��ʼ����" << endl;
		cout << "5.�˳�" << endl;
		cout << "---------------" << endl;
		cin >> ch;
		switch (ch) {
		case 1: {
			cout << des.get_key() << endl;
			cout << "������Կ:" << endl;
			string keystr = "";
			cin >> keystr;
			des.set_key(keystr);
			cout << "��Կ���óɹ�" << endl;
			break;
		}
		case 2: {
			cout << "��ǰ��Կ:" << endl;
			cout << des.get_key() << endl;
			break;
		}
		case 3: {
			cout << "��������Ҫ���ܵ��ļ�:" << endl;
			string filename;
			cin >> filename;
			cout << "���ڼ���" << endl;
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
			cout << "���ܳɹ�" << endl;
			break;
		}	
		case 4: {
			cout << "��������Ҫ���ܵ��ļ�:" << endl;
			string filename;
			cin >> filename;
			cout << "���ڽ���" << endl;
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
			cout << "���ܳɹ�" << endl;
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