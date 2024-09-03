#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

class Encryption {
    char ch;
    string fileName = "sample.txt";
public:
    void encryptfile();
    void decryptfile();
    void showfile();
};

void Encryption::encryptfile() {
    fstream fin, fout;
    fin.open(fileName, fstream::in);
    if (!fin.is_open()) {
        cout << "Error opening input file for encryption!" << endl;
        return;
    }
    fout.open("sample2.txt", fstream::out);
    if (!fout.is_open()) {
        cout << "Error opening output file for encryption!" << endl;
        fin.close();
        return;
    }
    while (fin >> noskipws >> ch) {
        ch = ch + 100;
        fout << ch;
    }
    fin.close();
    fout.close();

    fin.open("sample2.txt", fstream::in);
    if (!fin.is_open()) {
        cout << "Error opening temporary file for copying!" << endl;
        return;
    }
    fout.open(fileName, fstream::out);
    if (!fout.is_open()) {
        cout << "Error opening original file for overwriting after encryption!" << endl;
        fin.close();
        return;
    }
    while (fin >> noskipws >> ch) {
        fout << ch;
    }
    fin.close();
    fout.close();

    if (remove("sample2.txt") != 0) {
        cout << "Error deleting temporary file!" << endl;
    }

    cout << "\nFile is encrypted successfully\n\n";
}

void Encryption::decryptfile() {
    fstream fin, fout;
    fin.open(fileName, fstream::in);
    if (!fin.is_open()) {
        cout << "Error opening input file for decryption!" << endl;
        return;
    }
    fout.open("sample2.txt", fstream::out);
    if (!fout.is_open()) {
        cout << "Error opening output file for decryption!" << endl;
        fin.close();
        return;
    }
    while (fin >> noskipws >> ch) {
        ch = ch - 100;
        fout << ch;
    }
    fin.close();
    fout.close();

    fin.open("sample2.txt", fstream::in);
    if (!fin.is_open()) {
        cout << "Error opening temporary file for copying!" << endl;
        return;
    }
    fout.open(fileName, fstream::out);
    if (!fout.is_open()) {
        cout << "Error opening original file for overwriting after decryption!" << endl;
        fin.close();
        return;
    }
    while (fin >> noskipws >> ch) {
        fout << ch;
    }
    fin.close();
    fout.close();

    if (remove("sample2.txt") != 0) {
        cout << "Error deleting temporary file!" << endl;
    }

    cout << "\nFile is successfully decrypted\n\n";
}

void Encryption::showfile() {
    fstream fout;
    cout << endl;
    fout.open(fileName, fstream::in);
    if (!fout.is_open()) {
        cout << "Error opening file to display!" << endl;
        return;
    }
    while (fout >> noskipws >> ch) {
        cout << ch;
    }
    fout.close();
    cout << endl << endl;
}

int main() {
    int choice;
    Encryption file;
    cout << "\nWELCOME TO THE FILE ENCRYPTION PROJECT\n\n";
    do {
        cout << "Press 1 to encrypt file\n";
        cout << "Press 2 to decrypt file\n";
        cout << "Press 3 to show file\n";
        cout << "Press 4 to exit\n";
        cout << "Please choose any option: ";
        cin >> choice;
        switch (choice) {
        case 1:
            file.encryptfile();
            break;
        case 2:
            file.decryptfile();
            break;
        case 3:
            file.showfile();
            break;
        case 4:
            break;
        default:
            cout << "\nInvalid option try again\n";
            break;
        }
    } while (choice != 4);
    return 0;
}
